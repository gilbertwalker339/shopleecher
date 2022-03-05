#include "database.h"

Database::Database()
{
    QSqlDatabase database = QSqlDatabase::database();
    if(!database.isOpen()) database.open();

    qDebug() << "constructor" << Q_FUNC_INFO;
}

Database::~Database()
{
    QSqlDatabase database = QSqlDatabase::database();
    database.close();

    qDebug() << "deconstructor" << Q_FUNC_INFO;
}

bool Database::isOpen()
{
    QSqlDatabase database = QSqlDatabase::database();
    return database.isOpen();
}

void Database::begin()
{
    QSqlDatabase database = QSqlDatabase::database();
    database.transaction();
}

void Database::commit()
{
    QSqlDatabase database = QSqlDatabase::database();
    database.commit();
}

bool Database::exec(QSqlQuery &query)
{
    QSqlDatabase database = QSqlDatabase::database();
    this->begin();
    bool ok = query.exec();
    this->commit();
    return ok;
}

const QString &Database::tableName() const
{
    return m_tableName;
}

void Database::setTableName(const QString &newTableName)
{
    m_tableName = newTableName;
}
