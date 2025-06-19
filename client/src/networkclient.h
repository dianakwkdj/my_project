#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <functional>

class NetworkClient : public QObject {
    Q_OBJECT
public:
    static NetworkClient& instance();
    // networkclient.h
    void checkAdmin(const QString& login, std::function<void(bool)> callback);


    // Основные методы аутентификации
    void authenticate(const QString& login,
                      const QString& password,
                      std::function<void(bool, const QString&)> callback);

    void registerUser(const QString& login,
                      const QString& password,
                      const QString& email,
                      std::function<void(bool, const QString&)> callback);

    // Методы для работы с паролями
    void sendPasswordResetRequest(const QString& loginOrEmail,
                                  std::function<void(bool, const QString&)> callback);

    void validateResetCode(const QString& loginOrEmail,
                           const QString& code,
                           std::function<void(bool, const QString&)> callback);

    void updatePassword(const QString& loginOrEmail,
                        const QString& newPassword,
                        std::function<void(bool, const QString&)> callback);

    // Методы для проверки данных
    void checkEmailExists(const QString& email,
                          std::function<void(bool, const QString&)> callback);

    // Метод для решения уравнений
    void sendSolutionRequest(const QJsonObject& data,
                             std::function<void(bool, const QString&)> callback);
    void sendJsonRequest(const QJsonObject& request, std::function<void(bool, QString)> callback);
    void adminGetUsers(const QString& adminLogin, std::function<void(bool, const QJsonArray&, const QString&)> callback);



    // Запрет копирования
    NetworkClient(const NetworkClient&) = delete;
    NetworkClient& operator=(const NetworkClient&) = delete;

signals:
    void networkErrorOccurred(const QString& error);


private slots:
    void handleReply(QNetworkReply* reply);

private:
    explicit NetworkClient(QObject *parent = nullptr);

    QNetworkAccessManager* m_manager;


    QNetworkAccessManager* networkManager;
    QMap<QNetworkReply*, std::function<void(bool, const QString&)>> callbacks;

};

#endif // NETWORKCLIENT_H
