#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"

#include <QObject>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QXmlStreamReader>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString line = "http://www.cbr.ru/scripts/XML_daily.asp?date_req=01/06/2021";
    get_url(line);
    ui->cur_show->addItems(values);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    QString line = "http://www.cbr.ru/scripts/XML_daily.asp?date_req=";
    line += date.toString("dd/MM/yyyy");
    get_url(line);
}

void MainWindow::get_url(QString &line){
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::finished);
    QNetworkRequest r(QUrl(line.toUtf8()));
    manager->get(r);
}

void MainWindow::finished(QNetworkReply *reply){
    ui->cur_show->clear();
    Helper helper;
    values.clear();
    QXmlStreamReader xml(reply);
    values = helper.parseXml(xml);
    ui->cur_show->addItems(values);
}

