#include "usercontroller.h"

UserController::UserController(QObject *parent)
    : QObject{parent}
{

}

UserController::~UserController()
{

}

bool UserController::login(QString userName, QString password)
{
    User user;
    return user.login(userName, password);
}
