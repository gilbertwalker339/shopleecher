#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QObject>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSettings>
#include <QDir>

class SettingsController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int serverFetchXMinutes READ serverFetchXMinutes WRITE setServerFetchXMinutes NOTIFY serverFetchXMinutesChanged)
    Q_PROPERTY(unsigned int databaseRemoveRecordXMinutes READ databaseRemoveRecordXMinutes WRITE setDatabaseRemoveRecordXMinutes NOTIFY databaseRemoveRecordXMinutesChanged)
    Q_PROPERTY(QString databaseHostname READ databaseHostname WRITE setDatabaseHostname NOTIFY databaseHostnameChanged)
    Q_PROPERTY(unsigned int databaseHostPort READ databaseHostPort WRITE setDatabaseHostPort NOTIFY databaseHostPortChanged)
    Q_PROPERTY(QString databaseName READ databaseName WRITE setDatabaseName NOTIFY databaseNameChanged)
    Q_PROPERTY(QString databaseUsername READ databaseUsername WRITE setDatabaseUsername NOTIFY databaseUsernameChanged)
    Q_PROPERTY(QString databasePassword READ databasePassword WRITE setDatabasePassword NOTIFY databasePasswordChanged)
public:
    explicit SettingsController(QObject *parent = nullptr);
    virtual ~SettingsController();

    Q_INVOKABLE bool save();
    Q_INVOKABLE void load();
signals:
    void serverFetchXMinutesChanged();
    void databaseRemoveRecordXMinutesChanged();
    void databaseHostnameChanged();
    void databaseHostPortChanged();
    void databaseNameChanged();
    void databaseUsernameChanged();
    void databasePasswordChanged();
public slots:

private:
    unsigned int serverFetchXMinutes();
    void setServerFetchXMinutes(QVariant param);
    unsigned int databaseRemoveRecordXMinutes();
    void setDatabaseRemoveRecordXMinutes(QVariant param);
    QString databaseHostname();
    void setDatabaseHostname(QString hostname);
    unsigned int databaseHostPort();
    void setDatabaseHostPort(QVariant param);
    QString databaseName();
    void setDatabaseName(QString name);
    QString databaseUsername();
    void setDatabaseUsername(QString username);
    QString databasePassword();
    void setDatabasePassword(QString password);

    void init();
private:
    unsigned int m_serverFetchXMinutes{0};
    unsigned int m_databaseRemoveRecordXMinutes{0};
    QString m_databaseHostname{QString()};
    unsigned int m_databaseHostPort{0};
    QString m_databaseName{QString()};
    QString m_databaseUsername{QString()};
    QString m_databasePassword{QString()};
};

#endif // SETTINGSCONTROLLER_H
