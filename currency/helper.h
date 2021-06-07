#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QVector>
#include <QXmlStreamReader>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);
    QStringList values;

signals:
    void ready();
public slots:
     QString parseOneItem(QXmlStreamReader &xml);
     void get_url(QString &line);
     void finished(QNetworkReply *reply);
     QStringList parseXml(QXmlStreamReader &xml);
     QStringList get_xml(QString &line);

};

#endif // HELPER_H
