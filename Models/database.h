#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class Database
{
public:
    Database();
    virtual ~Database();
    virtual void install() = 0;
    virtual bool isOpen();
    virtual void begin();
    virtual void commit();
    virtual void save() = 0;
    virtual void remove() = 0;
    virtual void clear() = 0;
    virtual bool isExistsRecords() = 0;
    virtual bool exec(QSqlQuery& query);

    const QString &tableName() const;
    void setTableName(const QString &newTableName);

protected:
    QString m_tableName{QString()};
};

#endif // DATABASE_H
