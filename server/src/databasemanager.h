#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>
#include <QSqlQuery>
#include <QDebug>

class DatabaseManager : public QObject {
    Q_OBJECT
public:
    static DatabaseManager& instance();
    QSqlDatabase getDatabase() const;
    bool userExists(const QString& login);



    bool connectToDatabase(const QString& path);
    bool registerUser(const QString& login,
                      const QString& password,
                      const QString& email);
    bool authenticateUser(const QString& login,
                          const QString& password);
    QString getEmailByLogin(const QString& login);
    bool createPasswordResetCode(const QString& loginOrEmail,
                                 const QString& code);
    bool validateResetCode(const QString& loginOrEmail, const QString& code);
    bool updatePassword(const QString& loginOrEmail,
                        const QString& newPassword);
    bool emailExists(const QString& email);
    bool deleteResetCode(const QString& loginOrEmail, const QString& code);
    bool createEmailConfirmationCode(const QString& email, const QString& code);
    bool validateEmailConfirmationCode(const QString& email, const QString& code);
    bool deleteEmailConfirmationCode(const QString& email);
    QString lastError() const;

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

private:
    DatabaseManager() = default;
    ~DatabaseManager();
    QString hashPassword(const QString& password);

    QSqlDatabase m_db;
    mutable QMutex m_mutex;
    QString m_lastError;
};

#endif // DATABASEMANAGER_H
