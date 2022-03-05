#include "thegioididong.h"

TheGioiDiDong::TheGioiDiDong(QObject *parent, DeviceEnum::Value deviceEnum)
    : QObject{parent}, m_deviceEnum(deviceEnum)
{

}

TheGioiDiDong::~TheGioiDiDong()
{
    m_eventLoop->deleteLater();
}

void TheGioiDiDong::doStuff()
{
    while(m_jsonArrayData.count() > 0) {
        m_jsonArrayData.removeAt(0);
    }
    m_sourceMainPage.clear();
    m_urlSourceMap.clear();

    if(m_eventLoop == nullptr) m_eventLoop = new QEventLoop(this);

    QString url = QString();
    if(m_deviceEnum == DeviceEnum::Value::iPhone) {
        url = "https://www.thegioididong.com/dtdd-apple-iphone";
    }
    else if(m_deviceEnum == DeviceEnum::Value::iPad) {
        url = "https://www.thegioididong.com/may-tinh-bang-apple-ipad";
    }
    else if(m_deviceEnum == DeviceEnum::Value::MacBook) {
        url = "https://www.thegioididong.com/laptop-apple-macbook";
    }

    Network* network = new Network(this);
    QNetworkReply* reply = network->get(url, QMap<QString, QString>());
    reply->setParent(network);

    connect(reply, &QNetworkReply::readyRead, this, &TheGioiDiDong::readReadyMainPage);
    connect(reply, &QNetworkReply::finished, this, &TheGioiDiDong::finishedMainPage);

    m_eventLoop->exec();

    emit finished();
    QThread::currentThread()->quit();
}

void TheGioiDiDong::readReadyMainPage()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    m_sourceMainPage.append(reply->readAll());
}

void TheGioiDiDong::finishedMainPage()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->parent()->deleteLater();
    reply->deleteLater();

    this->matchUrlPageSource();
}

void TheGioiDiDong::readReadyUrlPage()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString url = reply->url().url();
    m_urlSourceMap[url].append(reply->readAll());
}

void TheGioiDiDong::finishedUrlPage()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString url = reply->url().url();
    reply->parent()->deleteLater();
    reply->deleteLater();

    jsonSourceUrl(url);
}

void TheGioiDiDong::errorOccurred(QNetworkReply::NetworkError code)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString url = reply->url().url();
}

void TheGioiDiDong::matchUrlPageSource()
{
    QString data(m_sourceMainPage);

    QRegularExpression re("<a href='(.*?)'");
    QRegularExpressionMatchIterator iterator = re.globalMatch(data);
    QString path = QString();
    QString url = QString();
    while(iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        path = match.captured(1);
        if(!path.contains("https://www.thegioididong.com")) {
            url = "https://www.thegioididong.com" + path;
        }
        m_urlSourceMap.insert(url, QByteArray());
        pageSourceUrl(url);
    }
}

void TheGioiDiDong::pageSourceUrl(QString url)
{
    Network* network = new Network(this);
    QNetworkReply* reply = network->get(url, QMap<QString, QString>());
    reply->setParent(network);

    connect(reply, &QNetworkReply::readyRead, this, &TheGioiDiDong::readReadyUrlPage);
    connect(reply, &QNetworkReply::finished, this, &TheGioiDiDong::finishedUrlPage);
    connect(reply, &QNetworkReply::errorOccurred, this, &TheGioiDiDong::errorOccurred);
}

void TheGioiDiDong::jsonSourceUrl(QString url)
{
    if(!m_urlSourceMap.keys().contains(url)) return;
    QByteArray buffer = m_urlSourceMap.value(url);
    QString sourceData = QString(buffer);

    QString id = QString();
    QString name = QString();
    double price = 0;
    QString screen = QString();
    QString cpu = QString();
    QString ram = QString();
    QString camera = QString();
    QString pin = QString();

    QString capture = QString();
    QRegularExpression re;
    QRegularExpressionMatch match;

    //name="inputProductId" value="213031"
    re.setPattern("name=\"inputProductId\" value=\"(.*?)\"");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         id = capture;
    }

    re.setPattern("<p class=\"box-price-present(?! black$).*\">(.*?)&#x20AB;");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         capture = capture.replace(".", "");
         price = capture.toDouble();
    }

    re.setPattern("<h1>.*((iPhone|iPad|MacBook).*?)</h1>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         name = capture;
    }

    re.setPattern("M&#xE0;n h&#xEC;nh:</p>[\\s\\S]*?<span class=\"\">(.*?)</span>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         screen = capture;
    }

    re.setPattern("(Chip|CPU):</p>[\\s\\S]*?<span class=\"\">(.*?)</span>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(2);
         cpu = capture;
    }

    re.setPattern("RAM:</p>[\\s\\S]*?<span class=\"\">(.*?)</span>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         ram = capture;
    }

    QString camera1 = QString();
    QString camera2 = QString();
    re.setPattern("Camera sau:</p>[\\s\\S]*?<span class=\"\">(.*?)</span>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         camera1 = capture;
    }
    re.setPattern("Camera tr&#x1B0;&#x1EDB;c:</p>[\\s\\S]*?<span class=\"\">(.*?)</span>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         camera2 = capture;
    }
    camera = camera1 + " * " + camera2;

    re.setPattern("Pin, S&#x1EA1;c:</p>[\\s\\S]*?<span class=\"comma\">(.*?)</span>");
    match = re.match(sourceData);
    capture.clear();
    if(match.hasMatch()) {
         capture = match.captured(1);
         pin = capture;
    }

    QMetaEnum meta = QMetaEnum::fromType<DeviceEnum::Value>();

    QJsonObject jsonObject;
    jsonObject.insert("shopName", this->metaObject()->className());
    jsonObject.insert("categoryName", meta.valueToKey(m_deviceEnum));
    jsonObject.insert("id", id);
    jsonObject.insert("name", name);
    jsonObject.insert("price", price);
    jsonObject.insert("screen", screen);
    jsonObject.insert("cpu", cpu);
    jsonObject.insert("ram", ram);
    jsonObject.insert("camera", camera);
    jsonObject.insert("pin", pin);

    m_mutex.lock();
    m_jsonArrayData.push_back(jsonObject);

    if(m_jsonArrayData.count() == m_urlSourceMap.keys().count()) {
        m_eventLoop->quit();
    }
    m_mutex.unlock();
}

QJsonArray TheGioiDiDong::jsonArrayData()
{
    return m_jsonArrayData;
}

QStringList TheGioiDiDong::devices()
{
    QMetaEnum e = QMetaEnum::fromType<DeviceEnum::Value>();
    QStringList deviceList;

    for (int k = 0; k < e.keyCount(); k++)
    {
       QString device = e.valueToKey(e.value(k));
       deviceList.append(device);
    }

    return deviceList;
}
