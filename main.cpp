#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Controllers/settingsController.h"
#include "Controllers/userController.h"
#include "Controllers/detailscontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SettingsController>("com.shopleecher.settingsController", 1, 0, "SettingsController");
    qmlRegisterType<UserController>("com.shopleecher.userController", 1, 0, "UserController");
    qmlRegisterType<DetailsController>("com.shopleecher.detailsController", 1, 0, "DetailsController");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ShopLeecher/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
