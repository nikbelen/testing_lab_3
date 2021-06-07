#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QDateEdit>
#include <QDate>
#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots :


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dateEdit_dateChanged(const QDate &date);
private:
    Ui::MainWindow *ui;
    QStringList values;
    void get_url(QString &line);
    void finished(QNetworkReply *reply);
    QHash<QString,QString> cur_value;
    QString parseOneItem(QXmlStreamReader &xml);

};
#endif // MAINWINDOW_H
