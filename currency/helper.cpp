#include "helper.h"
#include <iostream>
#include <QXmlStreamReader>
#include <QSignalSpy>
#include <QObject>
#include <QString>


Helper::Helper(QObject *parent) : QObject(parent)
{

}

QStringList Helper::parseXml(QXmlStreamReader &xml){
    QStringList values;
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
           continue;
        if (token == QXmlStreamReader::StartElement)
        {
            // и это item
            if (xml.name()=="Valute")
                values.append(parseOneItem(xml));
        }
    }
    if(values.isEmpty())
        values.append("");
    return values;
}

QString Helper::parseOneItem(QXmlStreamReader &xml){
    QString s;
    s="";
    xml.readNext();
    while (!((xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Valute") || xml.atEnd())) {
        if (xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "CharCode") {
                xml.readNext();
                QString t = xml.text().toUtf8();
                s += QString("(%1) ").arg(t);
            }
            if (xml.name() == "Name") {
                xml.readNext();
                QString t = xml.text().toUtf8();
                s += QString("%1 ").arg(t);
            }
            if (xml.name() == "Nominal") {
                xml.readNext();
                QString t = xml.text().toUtf8();
                s += QString("за %1 ").arg(t);
            }
            if (xml.name() == "Value") {
                xml.readNext();
                QString t = xml.text().toUtf8();
                s += QString("вы заплатите %1 рублей").arg(t);
            }
        }
        xml.readNext();
    }
    return s;
}

QStringList Helper::get_xml(QString &line){
    get_url(line);
    QStringList ans;
    QSignalSpy spy(this, &Helper::ready);
//    spy.wait(5000);
    ans = Helper::values;
    return ans;
}

void Helper::get_url(QString &line){
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    QSignalSpy spy (manager,&QNetworkAccessManager::finished);
    connect(manager, &QNetworkAccessManager::finished, this, &Helper::finished);
    QNetworkRequest r(QUrl(line.toUtf8()));
    manager->get(r);
//    spy.wait(10000);
//    emit Helper::ready();
}

void Helper::finished(QNetworkReply *reply){
    QXmlStreamReader xml(reply);
    Helper::values = parseXml(xml);
    emit Helper::ready();
}
