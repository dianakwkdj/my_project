// Заголовочные файлы
#include <QRandomGenerator>
#include "smtpclient.h"
#include "configloader.h"
#include <QObject>
#include "requesthandler.h"
#include "solver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRandomGenerator>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

RequestHandler::RequestHandler(DatabaseManager& db, QObject* parent)
    : QObject(parent), m_db(db) {}

QJsonObject RequestHandler::handleJsonRequest(const QJsonObject& request) {
    QString action = request["action"].toString().toLower();

    if(action == "register_check_login") return processRegisterCheckLogin(request);
    else if(action == "register_check_email") return processRegisterCheckEmail(request);
    else if(action == "register_check_password") return processRegisterCheckPassword(request);
    else if(action == "register") return processRegister(request);
    else if(action == "email_confirm_request") return processEmailConfirmRequest(request);
    else if(action == "email_confirm_validate") return processEmailConfirmValidate(request);
    else if(action == "login") return processLogin(request);
    else if(action == "check_admin_status") return processCheckAdminStatus(request);
    else if(action == "solve") return processSolveEquations(request);
    else if(action == "password_reset_request") return processPasswordResetRequest(request);
    else if(action == "password_reset_confirm") {
        QJsonObject response;
        processPasswordResetConfirmRequest(request, response);
        return response;
    }
    else if(action == "password_reset_update") return processPasswordResetUpdate(request);
    else if(action == "check_email") return processCheckEmail(request);

    QJsonObject response;
    response["status"] = "error";
    response["message"] = "Неизвестное действие";
    return response;
}

QString RequestHandler::handleTextRequest(const QString& request) {
    QString trimmed = request.trimmed();
    QStringList parts = trimmed.split(' ', Qt::SkipEmptyParts);

    if(parts.size() >= 3 && parts[0] == "REGISTER") return handleTextRegister(parts);
    else if(parts.size() >= 3 && parts[0] == "LOGIN") return handleTextLogin(parts);
    else if(trimmed.startsWith("SOLVE ")) return handleSolve(trimmed.mid(6).trimmed());

    return "Неверная команда\r\n";
}

QJsonObject RequestHandler::processRegister(const QJsonObject& request) {
    QJsonObject response;
    QStringList required = {"login", "password", "email"};

    if(!validateRequest(request, required, response)) {
        return response;
    }

    QString login = request["login"].toString().trimmed();
    QString password = request["password"].toString().trimmed();
    QString email = request["email"].toString().trimmed();

    if(m_db.registerUser(login, password, email)) {
        response["status"] = "success";
        response["message"] = "Пользователь зарегистрирован";
    } else {
        response["status"] = "error";
        response["message"] = "Ошибка регистрации: " + m_db.lastError();
    }
    return response;
}

QJsonObject RequestHandler::processLogin(const QJsonObject& request) {
    QJsonObject response;
    QString login = request["login"].toString();
    QString password = request["password"].toString();

    if(m_db.authenticateUser(login, password)) {
        response["status"] = "success";
        response["message"] = "Авторизация успешна";
        response["email"] = m_db.getEmailByLogin(login);
    } else {
        response["status"] = "error";
        response["message"] = "Неверный логин или пароль";
    }
    return response;
}

QJsonObject RequestHandler::processPasswordResetRequest(const QJsonObject& request) {
    QJsonObject response;

    if (!request.contains("login_or_email")) {
        response["status"] = "error";
        response["message"] = "Поле логин обязательно";
        return response;
    }

    QString loginOrEmail = request["login_or_email"].toString().trimmed();
    QString email = m_db.getEmailByLogin(loginOrEmail);

    if (email.isEmpty()) {
        response["status"] = "error";
        response["message"] = "Пользователь не найден";
        return response;
    }

    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));

    if (!m_db.createPasswordResetCode(loginOrEmail, code)) {
        response["status"] = "error";
        response["message"] = "Ошибка сохранения кода";
        return response;
    }

    SMTPClient *smtp = new SMTPClient(this);
    smtp->configure(
        ConfigLoader::instance().getString("smtp/host"),
        ConfigLoader::instance().getInt("smtp/port"),
        ConfigLoader::instance().getString("smtp/user"),
        ConfigLoader::instance().getString("smtp/password"),
        ConfigLoader::instance().getBool("smtp/ssl")
        );

    QString subject = "Код восстановления пароля";
    QString body = QString("Ваш код: %1").arg(code);

    connect(smtp, &SMTPClient::finished, [=](bool success, const QString& error) {
        if (!success) {
            qCritical() << "[SMTP] Ошибка отправки:" << error;
            m_db.deleteResetCode(loginOrEmail, code);
        }
        smtp->deleteLater();
    });

    smtp->sendEmail(email, subject, body);

    response["status"] = "success";
    response["message"] = "Код отправлен на почту";
    return response;
}

void RequestHandler::processPasswordResetConfirmRequest(const QJsonObject& request, QJsonObject& response) {
    qDebug() << "[SERVER] Обработка password_reset_confirm";
    QString loginOrEmail = request.value("login_or_email").toString().trimmed();
    QString code = request.value("code").toString().trimmed();

    if (loginOrEmail.isEmpty() || code.isEmpty()) {
        response["status"] = "error";
        response["message"] = "Недостаточно данных (логин и код обязательны)";
        return;
    }

    if (!m_db.validateResetCode(loginOrEmail, code)) {
        response["status"] = "error";
        response["message"] = "Неверный или просроченный код восстановления.";
        return;
    }

    response["status"] = "success";
    response["message"] = "Код подтвержден.";
}

QJsonObject RequestHandler::processPasswordResetUpdate(const QJsonObject& request) {
    QJsonObject response;
    QStringList required = {"login_or_email", "new_password"};

    if(!validateRequest(request, required, response)) {
        return response;
    }

    QString loginOrEmail = request["login_or_email"].toString().trimmed();
    QString newPassword = request["new_password"].toString().trimmed();

    QString email = m_db.getEmailByLogin(loginOrEmail);
    if(email.isEmpty()) {
        response["status"] = "error";
        response["message"] = "Пользователь не найден";
        return response;
    }

    if(m_db.updatePassword(loginOrEmail, newPassword)) {
        response["status"] = "success";
        response["message"] = "Пароль успешно обновлён";
    } else {
        response["status"] = "error";
        response["message"] = m_db.lastError();
    }
    return response;
}

QJsonObject RequestHandler::processCheckEmail(const QJsonObject& request) {
    QJsonObject response;
    if(!request.contains("email")) {
        response["status"] = "error";
        response["message"] = "Отсутствует поле email";
        return response;
    }

    bool exists = m_db.emailExists(request["email"].toString());
    response["status"] = "success";
    response["exists"] = exists;
    return response;
}

QString RequestHandler::handleTextRegister(const QStringList& parts) {
    if(parts.size() < 3) return "Неверный формат: REGISTER username password\r\n";

    QJsonObject request;
    request["action"] = "register";
    request["login"] = parts[1];
    request["password"] = parts[2];
    request["email"] = parts.size() > 3 ? parts[3] : "";

    QJsonObject response = processRegister(request);
    return QJsonDocument(response).toJson() + "\r\n";
}

QString RequestHandler::handleTextLogin(const QStringList& parts) {
    if(parts.size() < 3) return "Неверный формат\r\n";

    QJsonObject request;
    request["action"] = "login";
    request["login"] = parts[1];
    request["password"] = parts[2];

    QJsonObject response = processLogin(request);
    return QJsonDocument(response).toJson() + "\r\n";
}

bool RequestHandler::validateRequest(const QJsonObject& request, const QStringList& requiredFields, QJsonObject& response) {
    for(const QString& field : requiredFields) {
        if(!request.contains(field)) {
            response["status"] = "error";
            response["message"] = "Отсутствует поле: " + field;
            return false;
        }
    }
    return true;
}

QString RequestHandler::handleSolve(const QString& rawInput) {
    QStringList equations = rawInput.split(';', Qt::SkipEmptyParts);
    for (QString& eq : equations) {
        eq = eq.trimmed();
    }

    QJsonObject response = Solver::solveEquations(equations);

    if (response["status"] != "success") {
        return "Ошибка: " + response["message"].toString() + "\r\n";
    }

    QString result = "Решение:\r\n";
    QJsonArray solution = response["solution"].toArray();
    for (const QJsonValue& val : solution) {
        QJsonObject var = val.toObject();
        result += QString("%1 = %2\r\n")
                      .arg(var["variable"].toString())
                      .arg(var["value"].toDouble());
    }

    QJsonArray steps = response["steps"].toArray();
    result += "\r\nШаги:\r\n";
    for (int i = 0; i < steps.size(); ++i) {
        result += QString("%1. %2\r\n").arg(i + 1).arg(steps[i].toString());
    }

    return result;
}
QJsonObject RequestHandler::processEmailConfirmRequest(const QJsonObject& request) {
    QJsonObject response;
    response["action"] = "email_confirm_request";

    QString email = request.value("email").toString().trimmed();
    QString login = request.value("login").toString().trimmed();

    if (!email.contains("@") || !email.contains(".")) {
        response["status"] = "error";
        response["message"] = "Некорректный email";
        return response;
    }

    // Генерация кода
    QString code = QString::number(QRandomGenerator::global()->bounded(100000, 999999));

    // Сохраняем код в БД
    if (!DatabaseManager::instance().createEmailConfirmationCode(email, code)) {
        response["status"] = "error";
        response["message"] = "Ошибка при сохранении кода";
        return response;
    }

    // Отправка email
    SMTPClient* client = new SMTPClient();
    client->configure(
        ConfigLoader::instance().getString("smtp/host"),
        ConfigLoader::instance().getInt("smtp/port"),
        ConfigLoader::instance().getString("smtp/user"),
        ConfigLoader::instance().getString("smtp/password"),
        ConfigLoader::instance().getBool("smtp/ssl")
        );

    QString subject = "Код подтверждения регистрации";
    QString body = QString("Здравствуйте!\n\nВаш код подтверждения: %1").arg(code);

    connect(client, &SMTPClient::finished, this, [client](bool, const QString&) {
        client->deleteLater();
    });

    client->sendEmail(email, subject, body);

    response["status"] = "success";
    response["message"] = "Код подтверждения отправлен.";
    return response;
}
QJsonObject RequestHandler::processEmailConfirmValidate(const QJsonObject& request) {
    QJsonObject response;
    response["action"] = "email_confirm_validate";

    QString email = request.value("email").toString().trimmed();
    QString code = request.value("code").toString().trimmed();
    QString login = request.value("login").toString().trimmed();
    QString password = request.value("password").toString();

    if (email.isEmpty() || code.isEmpty() || login.isEmpty() || password.isEmpty()) {
        response["status"] = "error";
        response["message"] = "Все поля обязательны";
        return response;
    }

    if (!DatabaseManager::instance().validateEmailConfirmationCode(email, code)) {
        response["status"] = "error";
        response["message"] = "Неверный или просроченный код.";
        return response;
    }

    if (!DatabaseManager::instance().registerUser(login, password, email)) {
        response["status"] = "error";
        response["message"] = "Ошибка при регистрации: " + DatabaseManager::instance().lastError();
        return response;
    }

    DatabaseManager::instance().deleteEmailConfirmationCode(email);

    response["status"] = "success";
    response["message"] = "Регистрация завершена.";
    return response;
}


QJsonObject RequestHandler::processCheckAdminStatus(const QJsonObject& request) {
    QJsonObject response;

    QString loginOrEmail = request.value("login_or_email").toString().trimmed();
    if (loginOrEmail.isEmpty()) {
        response["status"] = "error";
        response["message"] = "Не указан логин или email.";
        return response;
    }

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT is_admin FROM users WHERE login = ? OR email = ?");
    query.addBindValue(loginOrEmail);
    query.addBindValue(loginOrEmail);

    if (!query.exec()) {
        response["status"] = "error";
        response["message"] = "Ошибка запроса к базе данных.";
        return response;
    }

    if (query.next()) {
        response["status"] = "success";
        response["is_admin"] = query.value(0).toBool();
    } else {
        response["status"] = "error";
        response["message"] = "Пользователь не найден.";
    }

    return response;
}



// Проверка логина
QJsonObject RequestHandler::processRegisterCheckLogin(const QJsonObject& request) {
    QString login = request["login"].toString().trimmed();
    QJsonObject response;
    response["action"] = "register_check_login";

    if (login.isEmpty()) {
        response["status"] = "error";
        response["message"] = "Логин не может быть пустым";
        return response;
    }

    if (m_db.userExists(login)) {
        response["status"] = "error";
        response["message"] = "Логин уже занят";
        return response;
    }

    response["status"] = "ok";
    return response;
}


// Проверка email
QJsonObject RequestHandler::processRegisterCheckEmail(const QJsonObject& request) {
    QString email = request["email"].toString().trimmed();
    QJsonObject response;
    response["action"] = "register_check_email";

    if (!email.contains("@") || !email.contains(".")) {
        response["status"] = "error";
        response["message"] = "Некорректный email";
        return response;
    }

    if (m_db.emailExists(email)) {
        response["status"] = "error";
        response["message"] = "Email уже используется";
        return response;
    }

    response["status"] = "ok";
    return response;
}

QJsonObject RequestHandler::processSolveEquations(const QJsonObject& request) {
    QJsonObject response;

    if (!request.contains("equations") || !request["equations"].isArray()) {
        response["status"] = "error";
        response["message"] = "Некорректный формат запроса: отсутствует список уравнений.";
        return response;
    }

    QJsonArray eqArray = request["equations"].toArray();
    if (eqArray.isEmpty() || eqArray.size() > 5) {
        response["status"] = "error";
        response["message"] = "Количество уравнений должно быть от 1 до 5.";
        return response;
    }

    QStringList equations;
    for (const QJsonValue& val : eqArray) {
        if (!val.isString()) {
            response["status"] = "error";
            response["message"] = "Уравнения должны быть строками.";
            return response;
        }
        equations << val.toString();
    }

    // Логирование входящих данных
    qDebug() << "Полученные уравнения:" << equations;

    qDebug() << "Ответ от сервера: " << QJsonDocument(response).toJson(); // Логирование ответа

    // Вызываем решение уравнений
    return Solver::solveEquations(equations);
}
// Проверка пароля
QJsonObject RequestHandler::processRegisterCheckPassword(const QJsonObject& request) {
    QString password = request["password"].toString();
    QJsonObject response;
    response["action"] = "register_check_password";

    if (password.length() < 6 || password.length() > 12) {
        response["status"] = "error";
        response["message"] = "Пароль должен быть от 6 до 12 символов";
        return response;
    }

    response["status"] = "ok";
    return response;
}
