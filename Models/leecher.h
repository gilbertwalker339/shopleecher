#ifndef LEECHER_H
#define LEECHER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlError>
#include "database.h"

class Leecher : public QObject, public Database
{
    Q_OBJECT
public:
    explicit Leecher(QObject *parent = nullptr);
    virtual ~Leecher();

    QJsonArray json();
signals:


    // Database interface
public:
    void install() Q_DECL_OVERRIDE;
    void save() Q_DECL_OVERRIDE;
    void remove() Q_DECL_OVERRIDE;
    void clear() Q_DECL_OVERRIDE;
    bool isExistsRecords() Q_DECL_OVERRIDE;

    const QString &shopName() const;
    void setShopName(const QString &newShopName);

    const QString &categoryName() const;
    void setCategoryName(const QString &newCategoryName);

    const QString &productId() const;
    void setProductId(const QString &newProductId);

    const QString &productName() const;
    void setProductName(const QString &newProductName);

    double price() const;
    void setPrice(double newPrice);

    const QString &screen() const;
    void setScreen(const QString &newScreen);

    const QString &cpu() const;
    void setCpu(const QString &newCpu);

    const QString &ram() const;
    void setRam(const QString &newRam);

    const QString &camera() const;
    void setCamera(const QString &newCamera);

    const QString &pin() const;
    void setPin(const QString &newPin);

    const QDateTime &created_at() const;
    void setCreated_at(const QDateTime &newCreated_at);

    const QDateTime &updated_at() const;
    void setUpdated_at(const QDateTime &newUpdated_at);

private:
    QString m_shopName{QString()};
    QString m_categoryName{QString()};
    QString m_productId{QString()};
    QString m_productName{QString()};
    double m_price{0};
    QString m_screen{QString()};
    QString m_cpu{QString()};
    QString m_ram{QString()};
    QString m_camera{QString()};
    QString m_pin{QString()};
    QDateTime m_created_at{QDateTime()};
    QDateTime m_updated_at{QDateTime()};
};

#endif // LEECHER_H
