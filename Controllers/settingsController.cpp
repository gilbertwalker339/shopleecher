#include "settingscontroller.h"

SettingsController::SettingsController(QObject *parent)
    : QObject{parent}
{
    //qDebug() << "constructor" << Q_FUNC_INFO;
}

SettingsController::~SettingsController()
{
    //qDebug() << "deconstructor" << Q_FUNC_INFO;
}

bool SettingsController::save()
{
    QString filePath = QDir::currentPath() + QDir::separator() + "settings.ini";
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup("database");
    settings.setValue("hostName", m_databaseHostname);
    settings.setValue("hostPort", m_databaseHostPort);
    settings.setValue("name", m_databaseName);
    settings.setValue("username", m_databaseUsername);
    settings.setValue("password", m_databasePassword);
    settings.endGroup();
    settings.sync();
    settings.beginGroup("cron");
    settings.setValue("serverFetchXMinutes", m_serverFetchXMinutes);
    settings.setValue("databaseRemoveRecordXMinutes", m_databaseRemoveRecordXMinutes);
    settings.endGroup();
    settings.sync();

    this->init();

    QSqlDatabase database = QSqlDatabase::database();
    bool ok =  database.open();
    database.close();

    return ok;
}

void SettingsController::load()
{
    QString filePath = QDir::currentPath() + QDir::separator() + "settings.ini";
    QSettings settings(filePath, QSettings::IniFormat);

    settings.beginGroup("database");
    QString hostName = settings.value("hostName", QVariant("")).toString();
    unsigned int hostPort = settings.value("hostPort", QVariant("")).toUInt();
    QString name = settings.value("name", QVariant("")).toString();
    QString username = settings.value("username", QVariant("")).toString();
    QString password = settings.value("password", QVariant("")).toString();
    settings.endGroup();

    settings.beginGroup("cron");
    unsigned int serverFetchXMinutes = settings.value("serverFetchXMinutes", QVariant("")).toUInt();
    unsigned int databaseRemoveRecordXMinutes = settings.value("databaseRemoveRecordXMinutes", QVariant("")).toUInt();
    settings.endGroup();

    setDatabaseHostname(hostName);
    setDatabaseHostPort(hostPort);
    setDatabaseName(name);
    setDatabaseUsername(username);
    setDatabasePassword(password);
    setServerFetchXMinutes(serverFetchXMinutes);
    setDatabaseRemoveRecordXMinutes(databaseRemoveRecordXMinutes);

    this->init();
}

unsigned int SettingsController::serverFetchXMinutes()
{
    return m_serverFetchXMinutes;
}

void SettingsController::setServerFetchXMinutes(QVariant param)
{
    bool ok;
    unsigned int minutes = param.toUInt(&ok);
    if(ok) {
        m_serverFetchXMinutes = minutes;
        emit serverFetchXMinutesChanged();
    }
}

unsigned int SettingsController::databaseRemoveRecordXMinutes()
{
    return m_databaseRemoveRecordXMinutes;
}

void SettingsController::setDatabaseRemoveRecordXMinutes(QVariant param)
{
    bool ok;
    unsigned int minutes = param.toUInt(&ok);
    if(ok) {
        m_databaseRemoveRecordXMinutes = minutes;
        emit databaseRemoveRecordXMinutesChanged();
    }
}

QString SettingsController::databaseHostname()
{
    return m_databaseHostname;
}

void SettingsController::setDatabaseHostname(QString hostname)
{
    if(hostname != m_databaseHostname) {
        m_databaseHostname = hostname;
        emit databaseHostnameChanged();
    }
}

unsigned int SettingsController::databaseHostPort()
{
    return m_databaseHostPort;
}

void SettingsController::setDatabaseHostPort(QVariant param)
{
    bool ok;
    quint16 port = param.toUInt(&ok);
    if(ok) {
        m_databaseHostPort = port;
        emit databaseHostPortChanged();
    }
}

QString SettingsController::databaseName()
{
    return m_databaseName;
}

void SettingsController::setDatabaseName(QString name)
{
    if(name != m_databaseName) {
        m_databaseName = name;
        emit databaseNameChanged();
    }
}

QString SettingsController::databaseUsername()
{
    return m_databaseUsername;
}

void SettingsController::setDatabaseUsername(QString username)
{
    if(username != m_databaseUsername) {
        m_databaseUsername = username;
        emit databaseUsernameChanged();
    }
}

QString SettingsController::databasePassword()
{
    return m_databasePassword;
}

void SettingsController::setDatabasePassword(QString password)
{
    if(password != m_databasePassword) {
        m_databasePassword = password;
        emit databasePasswordChanged();
    }
}

void SettingsController::init()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName(m_databaseHostname);
    database.setPort(m_databaseHostPort);
    database.setDatabaseName(m_databaseName);
    database.setUserName(m_databaseUsername);
    database.setPassword(m_databasePassword);
}
