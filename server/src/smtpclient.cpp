#include "smtpclient.h"
#include <QDebug>

SMTPClient::SMTPClient(QObject *parent) : QObject(parent) {
    socket.setProtocol(QSsl::TlsV1_2OrLater);

    connect(&socket, &QSslSocket::connected, this, &SMTPClient::onConnected);
    connect(&socket, &QSslSocket::readyRead, this, &SMTPClient::onReadyRead);
    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QSslSocket::errorOccurred),
            this, &SMTPClient::onErrorOccurred);
    connect(&timeoutTimer, &QTimer::timeout, this, &SMTPClient::onTimeout);

    connect(&socket, &QSslSocket::sslErrors, [this](const QList<QSslError> &errors) {
        qCritical() << "[SMTP] SSL Errors:";
        for (const QSslError &error : errors) {
            qCritical() << " -" << error.errorString();
        }
    });

    timeoutTimer.setInterval(30000);
    state = Disconnected;
}

void SMTPClient::configure(const QString& host, int port,
                           const QString& user, const QString& password, bool useSsl) {
    m_host = host;
    m_port = port;
    m_user = user;
    m_password = password;
    m_useSsl = useSsl;
}

void SMTPClient::sendEmail(const QString& to, const QString& subject, const QString& body) {
    if (state != Disconnected) return;

    qDebug().nospace()
        << "[SMTP] Starting email to:" << to
        << "\nHost:" << m_host
        << "\nPort:" << m_port
        << "\nUser:" << m_user;

    recipient = to;
    emailData = QString(
                    "From: \"Math Solver\" <%1>\r\n"
                    "To: %2\r\n"
                    "Subject: %3\r\n"
                    "MIME-Version: 1.0\r\n"
                    "Content-Type: text/plain; charset=utf-8\r\n"
                    "\r\n"
                    "%4\r\n"
                    ".\r\n"
                    ).arg(m_user, to, subject, body);

    qDebug() << "[SMTP] Connecting...";
    socket.setPeerVerifyName(m_host);
    socket.connectToHostEncrypted(m_host, m_port);
    timeoutTimer.start();
}

void SMTPClient::sendCommand(const QString& command) {
    qDebug() << "[SMTP] >>" << command;
    socket.write(command.toUtf8() + "\r\n");
}

void SMTPClient::processResponse(const QString& response) {
    QString trimmed = response.trimmed();
    qDebug() << "[SMTP] <<" << trimmed;

    if (trimmed.startsWith("535")) {
        qCritical() << "[SMTP] Authentication failed!";
        qDebug() << "[SMTP] Session finished, success:" << (false);
        state = Disconnected;
        emit finished(false, "");
        return;
    }

    // Обработка многострочного 220 приветствия
    static QStringList greetingLines;
    if (state == Connected && trimmed.startsWith("220")) {
        greetingLines << trimmed;
        if (!trimmed.startsWith("220-")) {
            // последняя строка приветствия
            sendCommand("EHLO anastasiaantipova.yandex.ru");
            state = EhloSent;
            greetingLines.clear();
        }
        return;
    }

    switch(state) {
    case EhloSent:
        sendCommand("AUTH LOGIN");
        state = AuthSent;
        break;

    case AuthSent:
        sendCommand(QString(m_user).toUtf8().toBase64());
        state = UserSent;
        break;

    case UserSent:
        sendCommand(QString(m_password).toUtf8().toBase64());
        state = PassSent;
        break;

    case PassSent:
        sendCommand(QString("MAIL FROM: <%1>").arg(m_user));
        state = MailFromSent;
        break;

    case MailFromSent:
        sendCommand(QString("RCPT TO: <%1>").arg(recipient));
        state = RcptToSent;
        break;

    case RcptToSent:
        sendCommand("DATA");
        state = DataSent;
        break;

    case DataSent:
        if (trimmed.startsWith("354")) {
            sendCommand(emailData);
            state = SendingBody;
        }
        break;

    case SendingBody:
        sendCommand("QUIT");
        state = QuitSent;
        emit finished(true, "");
        break;

    default:
        break;
    }
}

void SMTPClient::onConnected() {
    qDebug() << "[SMTP] Connected!";
    state = Connected;
    timeoutTimer.stop();
    // Ждём полный ответ 220 от сервера
}

// Ждём полный ответ 220 от сервера


void SMTPClient::onReadyRead() {
    while (socket.canReadLine()) {
        QString response = socket.readLine();
        processResponse(response);
    }
}

void SMTPClient::onErrorOccurred(QAbstractSocket::SocketError error) {
    state = Disconnected;
    qCritical() << "[SMTP] Error:" << error << socket.errorString();
    emit finished(false, socket.errorString());
}

void SMTPClient::onTimeout() {
    state = Disconnected;
    qCritical() << "[SMTP] Timeout!";
    socket.abort();
    emit finished(false, "Timeout");
}

