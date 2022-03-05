#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
#include <QDateTime>
#include "database.h"

class User : public QObject, public Database
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    virtual ~User();

    bool login(const QString& username, const QString& password);
signals:


    // Database interface
public:
    void install() Q_DECL_OVERRIDE;
    void save() Q_DECL_OVERRIDE;
    void remove() Q_DECL_OVERRIDE;
    void clear() Q_DECL_OVERRIDE;
    bool isExistsRecords() Q_DECL_OVERRIDE;


private:
    const QString adminUsername{"admin"};
    const QString adminPassword{"admin"};
    unsigned int m_id{0};
    QString m_username{QString()};
    QString m_password{QString()};
    QDateTime m_created_at{QDateTime()};
    QDateTime m_updated_at{QDateTime()};
};

#endif // USER_H
