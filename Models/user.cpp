#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{
    setTableName("users");
    User::install();
}

User::~User()
{

}

bool User::login(const QString &username, const QString &password)
{
    QString sql = "SELECT id FROM `" + m_tableName + "` WHERE username=:username AND password=:password LIMIT 1";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();
    return query.next();
}

void User::install()
{
    QSqlDatabase database = QSqlDatabase::database();

    QString sql = QString();
    QSqlQuery query;

    if(!database.tables().contains(m_tableName)) {
        sql = "CREATE TABLE `" + m_tableName + "`(`id` INT PRIMARY KEY NOT NULL AUTO_INCREMENT, `username` VARCHAR(50) NOT NULL, `password` VARCHAR(50) NOT NULL, `created_at` TIMESTAMP, `updated_at` TIMESTAMP) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci";
        query.prepare(sql);
        bool ok = exec(query);
        if(ok) {
            sql = "INSERT INTO `" + m_tableName + "` VALUES(NULL, :username, :password, :created_at, NULL)";
            query.prepare(sql);
            query.bindValue(":username", adminUsername);
            query.bindValue(":password", adminPassword);
            query.bindValue(":created_at", QDateTime::currentDateTimeUtc());
            exec(query);
        }
    }
    else {
        sql = "SELECT id FROM `" + m_tableName + "` LIMIT 2";
        query.prepare(sql);
        bool ok = exec(query);
        if(ok && query.size() == 0) {
            sql = "INSERT INTO `" + m_tableName + "` VALUES(NULL, :username, :password, :created_at, NULL)";
            query.prepare(sql);
            query.bindValue(":username", adminUsername);
            query.bindValue(":password", adminPassword);
            query.bindValue(":created_at", QDateTime::currentDateTimeUtc());
            exec(query);
        }
    }
}

void User::save()
{

}

void User::remove()
{

}

void User::clear()
{
    m_id = 0;
    m_username.clear();
    m_password.clear();
}

bool User::isExistsRecords()
{

}

