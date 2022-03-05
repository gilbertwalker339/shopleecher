#ifndef THEGIOIDIDONG_H
#define THEGIOIDIDONG_H

#include <QObject>
#include <QNetworkReply>
#include <QByteArray>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QtConcurrent>
#include <QMutex>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QStringList>
#include "Extensions/network.h"
#include "Enums/deviceEnum.h"

class TheGioiDiDong : public QObject
{
    Q_OBJECT
public:
    explicit TheGioiDiDong(QObject *parent = nullptr, DeviceEnum::Value deviceEnum = DeviceEnum::Value::iPhone);
    virtual ~TheGioiDiDong();

    void doStuff();
    QJsonArray jsonArrayData();
    QStringList devices();
signals:
    void finished();

private slots:
    void readReadyMainPage();
    void finishedMainPage();
    void readReadyUrlPage();
    void finishedUrlPage();
    void errorOccurred(QNetworkReply::NetworkError code);

private:
    void matchUrlPageSource();
    void pageSourceUrl(QString url);
    void jsonSourceUrl(QString url);

private:
    DeviceEnum::Value m_deviceEnum{DeviceEnum::Value::iPhone};
    QByteArray m_sourceMainPage{QByteArray()};
    QMap<QString, QByteArray> m_urlSourceMap{QMap<QString, QByteArray>()};
    QJsonArray m_jsonArrayData{QJsonArray()};
    QEventLoop* m_eventLoop{nullptr};
    QMutex m_mutex{QMutex()};
};

#endif // THEGIOIDIDONG_H
