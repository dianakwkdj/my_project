#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "mytcpserver.h"
#include "configloader.h"
#include "databasemanager.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // 🔍 Отладочная информация
    qDebug() << "Текущая директория:" << QDir::currentPath();

    // ✅ Инициализация конфигурации
    ConfigLoader::initialize("/Users/anastasiaantipova/my_project/server/src/build/mac-Debug/config.json");

    // ✅ Получаем путь к БД
    QString dbPath = ConfigLoader::instance().getString("database/path");

    // ✅ Проверка наличия файла БД
    QFile dbFile(dbPath);
    if (!dbFile.exists()) {
        if (!dbFile.open(QIODevice::WriteOnly)) {
            qCritical() << "Ошибка создания БД:" << dbFile.errorString();
            return -1;
        }
        dbFile.close();
    }

    // ✅ Подключение к базе данных
    if (!DatabaseManager::instance().connectToDatabase(dbPath)) {
        qCritical() << "Ошибка подключения к БД:" << DatabaseManager::instance().lastError();
        return -1;
    }

    // ✅ Получаем порт из конфигурации
    int port = ConfigLoader::instance().getInt("server/port", 33337);

    // ✅ Запуск сервера
    MyTcpServer server;
    if (!server.startServer(port)) {
        qCritical() << "Ошибка запуска сервера на порту" << port;
        return -1;
    }

    qInfo() << "Сервер успешно запущен на порту" << port;

    return a.exec();
}
