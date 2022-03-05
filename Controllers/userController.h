#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QSqlQuery>
#include "Models/user.h"

class UserController : public QObject
{
    Q_OBJECT
public:
    explicit UserController(QObject *parent = nullptr);
    virtual ~UserController();

    Q_INVOKABLE bool login(QString userName, QString password);
signals:

};

#endif // USERCONTROLLER_H
