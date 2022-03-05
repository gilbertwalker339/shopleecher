#ifndef DETAILSCONTROLLER_H
#define DETAILSCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QPluginLoader>
#include <QDir>
#include <QFile>
#include "Extensions/thegioididong.h"
#include "Models/leecher.h"

class DetailsController : public QObject
{
    Q_OBJECT
public:
    explicit DetailsController(QObject *parent = nullptr);
    virtual ~DetailsController();

    Q_INVOKABLE void fetchServerData(QString shopName, QString categoryName);
    Q_INVOKABLE QStringList categories();
    Q_INVOKABLE void fetchDatabaseData(QString shopName, QString categoryName);
    Q_INVOKABLE void saveEditedShopRecord(QString shopName, QString categoryName, QStringList data);
    Q_INVOKABLE void removeShopRecord(QString shopName, QString categoryName, QString productId);
signals:
    void finished(QJsonArray jsonArray);

private slots:
    void shopFinished();

private:
    void shopJsonArrayToDatabase(QJsonArray jsonArray);
};

#endif // DETAILSCONTROLLER_H
