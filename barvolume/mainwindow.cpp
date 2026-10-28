#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlError>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(2, 190);
    this->setStyleSheet("QMainWindow{background-image:url(:/images/7.jpg);}");
    //ui->listWidget->setStyleSheet("QListWidget{background:transparent; }");
    ui->pushButton->setStyleSheet("QPushButton{background-image:url(:/images/6.png);}");
    ui->pushButton_2->setStyleSheet("QPushButton{background-image:url(:/images/3.png);}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-image:url(:/images/4.png);}");
    ui->pushButton_4->setStyleSheet("QPushButton{background-image:url(:/images/5.png);}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-image:url(:/images/9.png);}");
    performDatabaseOperations();
}

void MainWindow::performDatabaseOperations()
{
    // 获取已经打开的数据库连接
    QSqlDatabase db = QSqlDatabase::database(); // 注意：这里没有指定数据库名称，它会返回最后一个使用的数据库连接
    if (db.isOpen())
    {
        qDebug() << "Open success";
    }
    else
    {
        qDebug() << "Database is not open" ;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->listWidget->clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0); // 重置行数为0
    emit this->back();
}

void MainWindow::on_pushButton_2_clicked()
{
    //ui->listWidget->clear();
    // 执行查询操作
    // 清空之前的表格内容    
//    QHeaderView *headerView = ui->tableWidget->horizontalHeader();
//    headerView->setSectionResizeMode(QHeaderView::Stretch); // 使列宽自适应内容
//    while (query.next())
//    {
//        //QString name = query.value("name").toString();
//        //qDebug() << " name = " << name;
//        QString itemText = query.value("name").toString(); // 假设你想要显示的是第一列
//        QListWidgetItem *item = new QListWidgetItem(itemText);
//        ui->listWidget->addItem(item); // 将item添加到QListWidget中
//        QString itemText1 = query.value("score").toString(); // 假设你想要显示的是第一列
//        QListWidgetItem *item1 = new QListWidgetItem(itemText1);
//        ui->listWidget->addItem(item1); // 将item添加到QListWidget中
//    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0); // 重置行数为0
    QSqlQuery query;
    query.exec("SELECT * FROM data1");
    while (query.next())
    {
//        for (int i = 0; i < query.record().count(); ++i)
//        {
//            // 检查是否需要添加新行
//            if (tableWidget->rowCount() == 0 || tableWidget->rowCount() <= i / query.record().count())
//            {
//                tableWidget->insertRow(tableWidget->rowCount());
//            }
//            // 将查询结果放入QTableWidgetItem，并添加到QTableWidget中
//            QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
//            tableWidget->setItem(tableWidget->rowCount() - 1, i % query.record().count(), item);
//        }
        // 获取第一列的值
        QString itemText = query.value("name").toString(); // 假设"name"是第一列的字段名
        // 获取第二列的值
        QString itemText1 = query.value("score").toString(); // 假设"score"是第二列的字段名
        // 如果你还有第三列，假设字段名为"time"
        QString itemText2 = query.value("time").toString(); // 获取第三列的值
        // 插入新行
        int newRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(newRow);
        // 将值添加到新的行和第一列
        ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(itemText));
        // 将值添加到新的行和第二列
        ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(itemText1));
        // 将值添加到新的行和第三列
        ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(itemText2));
//            //ui->centralLayout->addWidget(tableWidget);
//            // 调整列宽以适应内容
//            ui->tableWidget->resizeColumnToContents(2);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0); // 重置行数为0
    QSqlQuery query;
    query.exec("SELECT * FROM data1 ORDER BY id DESC LIMIT 1;");
    if(query.next())
    {
        QString name = query.value("name").toString();
        QString score = query.value("score").toString();
        QString time = query.value("time").toString();
        int newRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(newRow);
        ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(name));
        ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(score));
        ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(time));
        qDebug() << "最新得分添加到表格：" << name << " - " << score << " - " << time;
    }
    else
    {
        qDebug() << "查询最新得分失败";
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0); // 重置行数为0
    QSqlQuery query;
    QString sqlDelete = QString("delete from data1");
    if(query.exec(sqlDelete))
    {
         qDebug() << "表数据清空成功";
    }
    else
    {
        qDebug() << "清空表数据失败";
    }
}


//void MainWindow::on_pushButton_2_clicked()
//{
//    ui->listWidget->clear();
//    // 执行查询操作
//    QSqlQuery query;
//    query.exec("SELECT * FROM data1");
////    while (query.next())
////    {
////        //QString name = query.value("name").toString();
////        //qDebug() << " name = " << name;
////        QString itemText = query.value("name").toString(); // 假设你想要显示的是第一列
////        QListWidgetItem *item = new QListWidgetItem(itemText);
////        ui->listWidget->addItem(item); // 将item添加到QListWidget中
////        QString itemText1 = query.value("score").toString(); // 假设你想要显示的是第一列
////        QListWidgetItem *item1 = new QListWidgetItem(itemText1);
////        ui->listWidget->addItem(item1); // 将item添加到QListWidget中
////    }
//    while (query.next())
//    {
//        QString name = query.value("name").toString();
//        QString score = query.value("score").toString();
//        QString time = query.value("time").toString();
//        QString itemText = QString("%1 - %2 - %3").arg(name).arg(score).arg(time); //合并名字和年龄
//        QListWidgetItem *item = new QListWidgetItem(itemText);
//        ui->listWidget->addItem(item); // 将合并后的item添加到QListWidget中
//    }
//}

//void MainWindow::on_pushButton_3_clicked()
//{
//    ui->listWidget->clear();
//    QSqlQuery query;
//    query.exec("SELECT * FROM data1 ORDER BY id DESC LIMIT 1;");
//    if(query.next())
//    {
////        QString lastMessage = query.value("name").toString();
////        QListWidgetItem *item1 = new QListWidgetItem(lastMessage);
//        QString name = query.value("name").toString();
//        QString score = query.value("score").toString();
//        QString time = query.value("time").toString();
//        QString itemText = QString("%1 - %2 - %3").arg(name).arg(score).arg(time); //合并名字和年龄
//        QListWidgetItem *item1 = new QListWidgetItem(itemText);
//        ui->listWidget->addItem(item1);
//        qDebug() << "最新得分是：" << itemText;
//    }
//    else
//    {
//        qDebug() << "查询最新得分失败";
//    }
//}


