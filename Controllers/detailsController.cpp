#include "detailscontroller.h"

DetailsController::DetailsController(QObject *parent)
    : QObject{parent}
{
    //qDebug() << "constructor" << Q_FUNC_INFO;
}

DetailsController::~DetailsController()
{
    //qDebug() << "deconstructor" << Q_FUNC_INFO;
}

void DetailsController::fetchServerData(QString shopName, QString categoryName)
{
    QMetaEnum meta = QMetaEnum::fromType<DeviceEnum::Value>();
    DeviceEnum::Value categoryEnum = static_cast<DeviceEnum::Value>(meta.keyToValue(categoryName.toStdString().c_str()));

    TheGioiDiDong* shop = new TheGioiDiDong(nullptr, categoryEnum);
    QThread* thread = new QThread(this);
    shop->moveToThread(thread);

    connect(thread, &QThread::started, shop, &TheGioiDiDong::doStuff);
    connect(shop, &TheGioiDiDong::finished, this, &DetailsController::shopFinished);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

QStringList DetailsController::categories()
{
    QStringList categoryList;
    QMetaEnum meta = QMetaEnum::fromType<DeviceEnum::Value>();
    for(int i = 0; i < meta.keyCount(); i++) {
        QString key = meta.valueToKey(meta.value(i));
        categoryList.append(key);
    }

    return categoryList;
}

void DetailsController::fetchDatabaseData(QString shopName, QString categoryName)
{
    Leecher leecher;
    leecher.setShopName(shopName);
    leecher.setCategoryName(categoryName);
    QJsonArray jsonArray = leecher.json();
    emit finished(jsonArray);
}

void DetailsController::saveEditedShopRecord(QString shopName, QString categoryName, QStringList data)
{
    if(data.count() != 8) return;
    Leecher leecher;
    QString id = data.value(0);
    QString name = data.value(1);
    double price = data.value(2).toDouble();
    QString screen = data.value(3);
    QString cpu = data.value(4);
    QString ram = data.value(5);
    QString camera = data.value(6);
    QString pin = data.value(7);

    leecher.setShopName(shopName);
    leecher.setCategoryName(categoryName);
    leecher.setProductId(id);
    leecher.setProductName(name);
    leecher.setPrice(price);
    leecher.setScreen(screen);
    leecher.setCpu(cpu);
    leecher.setRam(ram);
    leecher.setCamera(camera);
    leecher.setPin(pin);

    leecher.save();
}

void DetailsController::removeShopRecord(QString shopName, QString categoryName, QString productId)
{
    Leecher leecher;
    leecher.setShopName(shopName);
    leecher.setCategoryName(categoryName);
    leecher.setProductId(productId);
    leecher.remove();
}

void DetailsController::shopFinished()
{
    TheGioiDiDong* shop = qobject_cast<TheGioiDiDong*>(sender());

    QJsonArray jsonArray = shop->jsonArrayData();

    this->shopJsonArrayToDatabase(jsonArray);

    emit finished(jsonArray);

    shop->deleteLater();
}

void DetailsController::shopJsonArrayToDatabase(QJsonArray jsonArray)
{
    Leecher leecher;
    for(const QJsonValue& value : jsonArray) {
        leecher.clear();
        QJsonObject jsonObject = value.toObject();
        QString shopName = jsonObject.value("shopName").toString();
        QString categoryName = jsonObject.value("categoryName").toString();
        QString id = jsonObject.value("id").toString();
        QString name = jsonObject.value("name").toString();
        double price = jsonObject.value("price").toDouble();
        QString screen = jsonObject.value("screen").toString();
        QString cpu = jsonObject.value("cpu").toString();
        QString ram = jsonObject.value("ram").toString();
        QString camera = jsonObject.value("camera").toString();
        QString pin = jsonObject.value("pin").toString();

        leecher.setShopName(shopName);
        leecher.setCategoryName(categoryName);
        leecher.setProductId(id);
        leecher.setProductName(name);
        leecher.setPrice(price);
        leecher.setScreen(screen);
        leecher.setCpu(cpu);
        leecher.setRam(ram);
        leecher.setCamera(camera);
        leecher.setPin(pin);

        leecher.save();
    }
}
