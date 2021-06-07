#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QObject>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QSignalSpy>
#include <iostream>

#include "../currency/mainwindow.h"
#include "../currency/helper.h"

TEST (parse_xml,valid_xml)
{
    char *filename = (char *)malloc(sizeof(char) * 1024);
        sprintf(filename, "%s/1.xml", INPUTDIR);
    QFile inFile(filename);
    inFile.open(QIODevice::ReadWrite);
    QByteArray ba = inFile.readAll();
    QXmlStreamReader xml(ba);
    Helper helper;
    QStringList TestValues = helper.parseXml(xml);
    QString line;
    line = TestValues.at(0);
    QString ans = "(AUD) за 1 Австралийский доллар вы заплатите 21,3659 рублей";
    ASSERT_EQ(TestValues.length(),18);
    ASSERT_STREQ(ans.toStdString().c_str(),line.toStdString().c_str());

}

TEST (parse_xml,not_valid_xml)
{
    char *filename = (char *)malloc(sizeof(char) * 1024);
        sprintf(filename, "%s/2.xml", INPUTDIR);
    QFile inFile(filename);
    inFile.open(QIODevice::ReadWrite);
    QByteArray ba = inFile.readAll();
    QXmlStreamReader xml(ba);
    Helper helper;
    QStringList TestValues = helper.parseXml(xml);
    QString line;
    line = TestValues.at(0);
    QString ans = "";
    ASSERT_EQ(TestValues.length(),0);
    ASSERT_STREQ(ans.toStdString().c_str(),line.toStdString().c_str());
}

TEST (parse_one, valid_xml)
{
    Helper helper;
    char *filename = (char *)malloc(sizeof(char) * 1024);
        sprintf(filename, "%s/1.xml", INPUTDIR);
    QFile inFile(filename);
    inFile.open(QIODevice::ReadWrite);
    QByteArray ba = inFile.readAll();
    QXmlStreamReader xml(ba);
    QString line = "";
    int a = 1;
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
           continue;
        if (token == QXmlStreamReader::StartElement)
        {
            // и это item
            if (xml.name()=="Valute")
                {line=helper.parseOneItem(xml);
                a++;
                if(a==3)
                    break;}
        }
    }
    QString ans = "(GBP) за 1 Фунт стерлингов Соединенного королевства вы заплатите 51,1584 рублей";
    ASSERT_STREQ(ans.toStdString().c_str(),line.toStdString().c_str());
}

TEST (parse_one, not_valid_xml)
{
    Helper helper;
    char *filename = (char *)malloc(sizeof(char) * 1024);
        sprintf(filename, "%s/2.xml", INPUTDIR);
    QFile inFile(filename);
    inFile.open(QIODevice::ReadWrite);
    QByteArray ba = inFile.readAll();
    QXmlStreamReader xml(ba);
    QString line = "";
    line = helper.parseOneItem(xml);
    QString ans = "";
    ASSERT_STREQ(ans.toStdString().c_str(),line.toStdString().c_str());
}

