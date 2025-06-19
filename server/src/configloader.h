#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <QString>
#include <QJsonObject>
#include <QJsonValue>

class ConfigLoader {
public:
    static void initialize(const QString& path);
    static ConfigLoader& instance();

    bool load();
    QJsonValue getValue(const QString& path) const;
    QString getString(const QString& key) const;
    bool getBool(const QString& key) const;
    bool contains(const QString& key) const;
    int getInt(const QString& key, int defaultValue = 0) const;

private:
    explicit ConfigLoader(const QString& configPath);
    ConfigLoader(const ConfigLoader&) = delete;
    ConfigLoader& operator=(const ConfigLoader&) = delete;

    QString m_configPath;
    QJsonObject m_config;
};

#endif // CONFIGLOADER_H
