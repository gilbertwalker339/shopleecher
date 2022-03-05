#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMap>
#include <QByteArray>

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);
    virtual ~Network();

    QNetworkReply *get(QString url, QMap<QString, QString> headerMap);
    QNetworkReply* post(QString url, QMap<QString, QString> headerMap, QByteArray postData);
signals:

private:
    void initDefaultHeaders();
    void setHeaders(QMap<QString, QString> headerMap);

private:
    QNetworkAccessManager* m_manager{nullptr};
    QNetworkRequest m_request;
};

#endif // NETWORK_H
