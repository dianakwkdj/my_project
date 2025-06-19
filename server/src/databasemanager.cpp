// Подключение заголовочного файла класса
#include "databasemanager.h"

// Необходимые заголовки Qt
#include <QDateTime>          // Для работы с датой/временем
#include <QSqlError>          // Для обработки ошибок SQL
#include <QCryptographicHash> // Для хеширования паролей

// Реализация синглтона (единственного экземпляра класса)
DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance; // Создается при первом вызова
    return instance;                 // Гарантирует единственный экземпляр
}

// Деструктор
DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::connectToDatabase(const QString& path) {
    if (path.isEmpty()) {
        m_lastError = "Путь к базе данных пустой.";
        return false;
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE", "SERVER_DB_CONN");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        m_lastError = m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "login TEXT UNIQUE NOT NULL, "
            "password_hash TEXT NOT NULL, "
            "email TEXT UNIQUE NOT NULL, "
            "is_admin INTEGER DEFAULT 0)")) {
        m_lastError = query.lastError().text();
        return false;
    }

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS password_reset_codes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "user_id INTEGER NOT NULL, "
            "code TEXT NOT NULL, "
            "expires_at DATETIME NOT NULL, "
            "FOREIGN KEY(user_id) REFERENCES users(id))")) {
        m_lastError = query.lastError().text();
        return false;
    }

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS email_confirmation_codes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "email TEXT NOT NULL, "
            "code TEXT NOT NULL, "
            "expires_at DATETIME NOT NULL)")) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::registerUser(const QString& login,
                                   const QString& password,
                                   const QString& email) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "INSERT INTO users (login, password_hash, email) "
        "VALUES (?, ?, ?)"
        );
    query.addBindValue(login);
    query.addBindValue(hashPassword(password));
    query.addBindValue(email);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::authenticateUser(const QString& login,
                                       const QString& password) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT password_hash FROM users "
        "WHERE login = ?"
        );
    query.addBindValue(login);

    if (!query.exec() || !query.next()) {
        m_lastError = "Пользователь не найден.";
        return false;
    }

    return query.value(0).toString() == hashPassword(password);
}

QString DatabaseManager::getEmailByLogin(const QString& loginOrEmail) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT email FROM users "
        "WHERE login = ? OR email = ?"
        );
    query.addBindValue(loginOrEmail);
    query.addBindValue(loginOrEmail);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

bool DatabaseManager::createPasswordResetCode(const QString& loginOrEmail, const QString& code) {
    QMutexLocker locker(&m_mutex);
    qDebug() << "\n=== Creating password reset code ===";

    if (!m_db.transaction()) {
        qCritical() << "Не удалось начать транзакцию:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery userQuery(m_db);
    userQuery.prepare(
        "SELECT id FROM users "
        "WHERE login = ? OR email = ?"
        );
    userQuery.addBindValue(loginOrEmail.trimmed());
    userQuery.addBindValue(loginOrEmail.trimmed());

    if (!userQuery.exec()) {
        qCritical() << "Ошибка поиска пользователя:" << userQuery.lastError().text();
        m_db.rollback();
        return false;
    }

    if (!userQuery.next()) {
        qWarning() << "Пользователь не найден:" << loginOrEmail;
        m_db.rollback();
        return false;
    }

    int userId = userQuery.value(0).toInt();

    QSqlQuery deleteQuery(m_db);
    deleteQuery.prepare("DELETE FROM password_reset_codes WHERE user_id = ?");
    deleteQuery.addBindValue(userId);
    if (!deleteQuery.exec()) {
        m_lastError = deleteQuery.lastError().text();
        return false;
    }

    QDateTime expiresAt = QDateTime::currentDateTime().addSecs(300).toUTC();
    QSqlQuery insertQuery(m_db);
    insertQuery.prepare(
        "INSERT INTO password_reset_codes "
        "(user_id, code, expires_at) "
        "VALUES (?, ?, ?)"
        );

    insertQuery.addBindValue(userId);
    insertQuery.addBindValue(code.trimmed());
    insertQuery.addBindValue(expiresAt.toString(Qt::ISODateWithMs));

    if (!insertQuery.exec()) {
        qCritical() << "Ошибка вставки кода:" << insertQuery.lastError().text();
        m_db.rollback();
        return false;
    }

    if (!m_db.commit()) {
        qCritical() << "Ошибка подтверждения транзакции:" << m_db.lastError().text();
        m_db.rollback();
        return false;
    }

    return true;
}

bool DatabaseManager::validateResetCode(const QString& loginOrEmail, const QString& code) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT COUNT(*) as cnt FROM password_reset_codes "
        "WHERE code = :code "
        "AND user_id IN (SELECT id FROM users WHERE login = :loginOrEmail OR email = :loginOrEmail) "
        "AND expires_at > datetime('now')"
        );
    query.bindValue(":code", code.trimmed());
    query.bindValue(":loginOrEmail", loginOrEmail);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

bool DatabaseManager::updatePassword(const QString& loginOrEmail, const QString& newPassword) {
    QMutexLocker locker(&m_mutex);

    QString hashed = hashPassword(newPassword);

    QSqlQuery query(m_db);
    query.prepare(
        "UPDATE users SET password_hash = ? "
        "WHERE login = ? OR email = ?"
        );
    query.addBindValue(hashed);
    query.addBindValue(loginOrEmail);
    query.addBindValue(loginOrEmail);

    if(!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool DatabaseManager::emailExists(const QString& email) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT COUNT(*) FROM users "
        "WHERE email = ?"
        );
    query.addBindValue(email);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

QString DatabaseManager::hashPassword(const QString& password) {
    return QCryptographicHash::hash(
               password.toUtf8(),
               QCryptographicHash::Sha256
               ).toHex();
}

QString DatabaseManager::lastError() const {
    return m_lastError;
}

bool DatabaseManager::deleteResetCode(const QString& loginOrEmail, const QString& code) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "DELETE FROM password_reset_codes "
        "WHERE code = ? AND user_id IN ("
        "SELECT id FROM users WHERE login = ? OR email = ?)"
        );
    query.addBindValue(code);
    query.addBindValue(loginOrEmail);
    query.addBindValue(loginOrEmail);

    if(!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::createEmailConfirmationCode(const QString& email, const QString& code) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);

    query.prepare("DELETE FROM email_confirmation_codes WHERE email = ?");
    query.addBindValue(email);
    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    QDateTime expiresAt = QDateTime::currentDateTime().addSecs(300);
    query.prepare("INSERT INTO email_confirmation_codes (email, code, expires_at) VALUES (?, ?, ?)");
    query.addBindValue(email);
    query.addBindValue(code);
    query.addBindValue(expiresAt.toString(Qt::ISODate));

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::validateEmailConfirmationCode(const QString& email, const QString& code) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare(
        "SELECT COUNT(*) FROM email_confirmation_codes "
        "WHERE email = ? AND code = ? AND expires_at > datetime('now')"
        );
    query.addBindValue(email);
    query.addBindValue(code);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    m_lastError = query.lastError().text();
    return false;
}

bool DatabaseManager::deleteEmailConfirmationCode(const QString& email) {
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare("DELETE FROM email_confirmation_codes WHERE email = ?");
    query.addBindValue(email);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const {
    return m_db;
}

bool DatabaseManager::userExists(const QString& login) {
    QMutexLocker locker(&m_mutex);
    QSqlQuery query(m_db);
    query.prepare("SELECT COUNT(*) FROM users WHERE login = ?");
    query.addBindValue(login);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
