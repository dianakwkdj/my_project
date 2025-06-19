
#include "configloader.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

static ConfigLoader* s_instance = nullptr;

void ConfigLoader::initialize(const QString& path) {
    if (!s_instance)
        s_instance = new ConfigLoader(path);
    s_instance->load();
}

ConfigLoader& ConfigLoader::instance() {
    return *s_instance;
}

ConfigLoader::ConfigLoader(const QString& configPath)
    : m_configPath(configPath) {}

bool ConfigLoader::load() {
    QFile file(m_configPath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Не удалось открыть конфиг:" << file.errorString();
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    m_config = doc.object();
    return true;
}

QJsonValue ConfigLoader::getValue(const QString& path) const {
    QStringList keys = path.split('/');
    QJsonValue current = m_config;
    for (const QString& key : keys) {
        if (!current.isObject()) return {};
        current = current.toObject().value(key);
    }
    return current;
}

QString ConfigLoader::getString(const QString& key) const {
    return getValue(key).toString();
}

bool ConfigLoader::getBool(const QString& key) const {
    return getValue(key).toBool();
}

bool ConfigLoader::contains(const QString& key) const {
    return m_config.contains(key);
}

int ConfigLoader::getInt(const QString& key, int defaultValue) const {
    return getValue(key).toInt(defaultValue);
}
