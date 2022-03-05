#include "leecher.h"

Leecher::Leecher(QObject *parent)
    : QObject{parent}
{
    setTableName("leechers");
    Leecher::install();
}

Leecher::~Leecher()
{

}

QJsonArray Leecher::json()
{
    QJsonArray jsonArray = QJsonArray();

    QString sql = "SELECT `productId`, `productName`, `productPrice`, `productScreen`, `productCpu`, `productRam`, `productCamera`, `productPin` FROM `" + m_tableName + "` WHERE `shopName`=:shopName AND `categoryName`=:categoryName";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":shopName", m_shopName);
    query.bindValue(":categoryName", m_categoryName);
    exec(query);
    while(query.next()) {
        QString productId = query.value("productId").toString();
        QString productName = query.value("productName").toString();
        float productPrice = query.value("productPrice").toFloat();
        QString productScreen = query.value("productScreen").toString();
        QString productCpu = query.value("productCpu").toString();
        QString productRam = query.value("productRam").toString();
        QString productCamera = query.value("productCamera").toString();
        QString productPin = query.value("productPin").toString();

        QJsonObject jsonObject;
        jsonObject.insert("id", productId);
        jsonObject.insert("name", productName);
        jsonObject.insert("price", productPrice);
        jsonObject.insert("screen", productScreen);
        jsonObject.insert("cpu", productCpu);
        jsonObject.insert("ram", productRam);
        jsonObject.insert("camera", productCamera);
        jsonObject.insert("pin", productPin);

        jsonArray.append(jsonObject);
    }

    return jsonArray;
}

void Leecher::install()
{
    QSqlDatabase database = QSqlDatabase::database();

    if(!database.tables().contains(m_tableName)) {
        QString sql = "CREATE TABLE `" + m_tableName + "`(`shopName` VARCHAR(50) NOT NULL, `categoryName` VARCHAR(50) NOT NULL, `productId` VARCHAR(50) NOT NULL, `productName` VARCHAR(100) NULL DEFAULT NULL, `productPrice` DOUBLE NULL DEFAULT NULL, `productScreen` VARCHAR(50) NULL DEFAULT NULL, `productCpu` VARCHAR(50) NULL DEFAULT NULL, `productRam` VARCHAR(50) NULL DEFAULT NULL, `productCamera` VARCHAR(50) NULL DEFAULT NULL, `productPin` VARCHAR(50) NULL DEFAULT NULL, `created_at` TIMESTAMP NULL DEFAULT NULL, `updated_at` TIMESTAMP NULL DEFAULT NULL ) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci; ALTER TABLE leechers ADD PRIMARY KEY(`shopName`, `categoryName`, `productId`);";
        QSqlQuery query;
        query.prepare(sql);
        exec(query);
    }
}

void Leecher::save()
{
    QString sql = QString();
    if(this->isExistsRecords())
    {
        sql = "UPDATE `" + m_tableName + "` "
                        "SET `productName`=:productName, `productPrice`=:productPrice, `productScreen`=:productScreen, "
                                                 "`productCpu`=:productCpu, `productRam`=:productRam, `productCamera`=:productCamera, `productPin`=:productPin "
                        "WHERE shopName=:shopName AND categoryName=:categoryName AND productId=:productId";
    }
    else {
        sql = "INSERT INTO `" + m_tableName + "` VALUES(:shopName, :categoryName, :productId, :productName, :productPrice, :productScreen, :productCpu, :productRam, :productCamera, :productPin, :created_at, NULL)";
    }

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":productName", m_productName);
    query.bindValue(":productPrice", m_price);
    query.bindValue(":productScreen", m_screen);
    query.bindValue(":productCpu", m_cpu);
    query.bindValue(":productRam", m_ram);
    query.bindValue(":productCamera", m_camera);
    query.bindValue(":productPin", m_pin);
    query.bindValue(":shopName", m_shopName);
    query.bindValue(":categoryName", m_categoryName);
    query.bindValue(":productId", m_productId);
    query.bindValue(":created_at", QDateTime::currentDateTimeUtc());
    exec(query);
}

void Leecher::remove()
{
    QString sql = "DELETE FROM `" + m_tableName + "` WHERE shopName=:shopName AND categoryName=:categoryName AND productId=:productId";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":shopName", m_shopName);
    query.bindValue(":categoryName", m_categoryName);
    query.bindValue(":productId", m_productId);
    exec(query);

    qDebug() << query.lastError().text();
}

void Leecher::clear()
{
    m_shopName.clear();
    m_categoryName.clear();
    m_productId.clear();
    m_productName.clear();
    m_price = 0;
    m_screen = 0;
    m_cpu.clear();
    m_ram.clear();
    m_camera.clear();
    m_pin.clear();
}

bool Leecher::isExistsRecords()
{
    QString sql = "SELECT productId FROM " + m_tableName + " WHERE shopName=:shopName AND categoryName=:categoryName AND productId=:productId LIMIT 1";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":shopName", m_shopName);
    query.bindValue(":categoryName", m_categoryName);
    query.bindValue(":productId", m_productId);
    exec(query);

    return query.next();
}

const QString &Leecher::shopName() const
{
    return m_shopName;
}

void Leecher::setShopName(const QString &newShopName)
{
    m_shopName = newShopName;
}

const QString &Leecher::categoryName() const
{
    return m_categoryName;
}

void Leecher::setCategoryName(const QString &newCategoryName)
{
    m_categoryName = newCategoryName;
}

const QString &Leecher::productId() const
{
    return m_productId;
}

void Leecher::setProductId(const QString &newProductId)
{
    m_productId = newProductId;
}

const QString &Leecher::productName() const
{
    return m_productName;
}

void Leecher::setProductName(const QString &newProductName)
{
    m_productName = newProductName;
}

double Leecher::price() const
{
    return m_price;
}

void Leecher::setPrice(double newPrice)
{
    m_price = newPrice;
}

const QString &Leecher::screen() const
{
    return m_screen;
}

void Leecher::setScreen(const QString &newScreen)
{
    m_screen = newScreen;
}

const QString &Leecher::cpu() const
{
    return m_cpu;
}

void Leecher::setCpu(const QString &newCpu)
{
    m_cpu = newCpu;
}

const QString &Leecher::ram() const
{
    return m_ram;
}

void Leecher::setRam(const QString &newRam)
{
    m_ram = newRam;
}

const QString &Leecher::camera() const
{
    return m_camera;
}

void Leecher::setCamera(const QString &newCamera)
{
    m_camera = newCamera;
}

const QString &Leecher::pin() const
{
    return m_pin;
}

void Leecher::setPin(const QString &newPin)
{
    m_pin = newPin;
}

const QDateTime &Leecher::created_at() const
{
    return m_created_at;
}

void Leecher::setCreated_at(const QDateTime &newCreated_at)
{
    m_created_at = newCreated_at;
}

const QDateTime &Leecher::updated_at() const
{
    return m_updated_at;
}

void Leecher::setUpdated_at(const QDateTime &newUpdated_at)
{
    m_updated_at = newUpdated_at;
}
