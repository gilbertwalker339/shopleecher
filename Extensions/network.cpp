#include "network.h"

Network::Network(QObject *parent)
    : QObject{parent}
{
    m_manager = new QNetworkAccessManager(this);
    initDefaultHeaders();
}

Network::~Network()
{
    m_manager->deleteLater();
}

QNetworkReply *Network::get(QString url, QMap<QString, QString> headerMap)
{
    setHeaders(headerMap);

    m_request.setUrl(QUrl(url));
    return m_manager->get(m_request);
}

QNetworkReply *Network::post(QString url, QMap<QString, QString> headerMap, QByteArray postData)
{
    setHeaders(headerMap);

    m_request.setUrl(QUrl(url));
    return m_manager->post(m_request, postData);
}

void Network::initDefaultHeaders()
{
    m_request.setRawHeader("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:97.0) Gecko/20100101 Firefox/97.0");
    m_request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");
    m_request.setRawHeader("Accept-Language", "en-US,en;q=0.5");
    //m_request.setRawHeader("Accept-Encoding", "gzip, deflate, br");
    //m_request.setRawHeader("Connection", "keep-alive");
    m_request.setRawHeader("Upgrade-Insecure-Requests", "1");
}

void Network::setHeaders(QMap<QString, QString> headerMap)
{
    for(const QString& key : headerMap.keys()) {
        m_request.setRawHeader(key.toUtf8(), headerMap.value(key).toUtf8());
    }
}


