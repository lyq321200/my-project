#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <mqtt/qmqttclient.h>
#include <QSqlDatabase>//连接和打开数据库类
#include <QSqlQuery>//可以用来真正访问操作数据库类
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals://信号
    void back();

private:
    Ui::MainWindow *ui;
    void performDatabaseOperations();
};

#endif // MAINWINDOW_H
