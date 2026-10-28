#include "frmbarvolume.h"
#include "ui_frmbarvolume.h"
#include "barvolume.h"
#include "mainwindow.h"
#include <QSerialPort>
#include <QSqlError>
#include <QSqlQuery>//可以用来真正访问操作数据库类
#include <QByteArray>
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QDebug>

frmBarVolume::frmBarVolume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::frmBarVolume)
{
    ui->setupUi(this);//调用ui对象的setupUi方法来设置界面。
    ui->pushButton_2->setStyleSheet("QPushButton{background-image:url(:/images/8.png);}");
    //ui->textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//垂直不显示滑动条
    //ui->textEdit_2->setStyleSheet("QTextEdit {text-align: center;}");
    //ui->textEdit_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平不显示滑动条
    setCircle(ui->label_3, 0, 41);
    ui->textEdit->setStyleSheet("QTextEdit { "
                                          "background-color: transparent; "
                                          "border: 1px solid black; " // 这里设置边框为黑色，可以根据需要更改颜色
                                          "}");
    this->initForm();//调用initForm方法来初始化表单。
    createDatabase();
    this->serial = new QSerialPort(this);
    this->setupSerialPort(); // 设置串口参数
    this->page1=new MainWindow;
    connect(this->page1,SIGNAL(back()),this,SLOT(comeBackToPrev()));

#if 0
    //定义一条创建表的sql语句
    QString sqlCreate = QString("create table data(id integer primary key autoincrement,name varchar(20),age int);");
    if(!query.exec(sqlCreate))
    {
        qDebug() << "create table error" << db.lastError();
    }
#endif
#if 0
    //插入操作
    QString sqlInsert = QString("insert into staff(name,age) values('歌曲1',20);");
    if(!query.exec(sqlInsert))
    {
         qDebug() << "insert data error" << db.lastError();
    }
#endif

}

void frmBarVolume::createDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("record.db");
    if (!db.open())
    {
        qDebug() << "数据库打开失败！" << db.lastError();
    }
    else
    {
        qDebug() << "Open success";
        QSqlQuery query;
        // 执行其他数据库操作，比如创建表
        if (!query.exec("CREATE TABLE IF NOT EXISTS data1 (id INTEGER PRIMARY KEY, name varchar(20), score float,time DATETIME);"))
        {
            qDebug() << "创建表成功!";
        }
        else
        {
            qDebug() << "创建表失败,表已存在！" << query.lastError();
        }
//        query.exec("SELECT * FROM data");
//        while (query.next())
//        {
//            //QString name = query.value("name").toString();
//            //qDebug() << " name = " << name;
//            QString itemText = query.value("name").toString(); // 假设你想要显示的是第一列
//            QListWidgetItem *item = new QListWidgetItem(itemText);
//            ui->listWidget->addItem(item); // 将item添加到QListWidget中
//            QString itemText1 = query.value("age").toString(); // 假设你想要显示的是第一列
//            QListWidgetItem *item1 = new QListWidgetItem(itemText1);
//            ui->listWidget->addItem(item1); // 将item添加到QListWidget中
//        }
    }
}

void frmBarVolume::initForm()
{
    //为音乐条设置颜色
    ui->barVolume1->setBarColorStart(QColor(162, 45, 45));
    ui->barVolume1->setBarColorMid(QColor(205, 80, 80));
    ui->barVolume1->setBarColorEnd(QColor(246, 178, 151));
    ui->barVolume2->setBarColorStart(QColor(255, 64, 64));
    ui->barVolume2->setBarColorMid(QColor(255, 127, 36));
    ui->barVolume2->setBarColorEnd(QColor(238, 238, 0));
    ui->barVolume3->setBarColorStart(QColor(218, 165, 32));
    ui->barVolume3->setBarColorMid(QColor(240, 230, 140));
    ui->barVolume3->setBarColorEnd(QColor(255, 240, 245));
    ui->barVolume4->setBarColorStart(QColor(46, 139, 87));
    ui->barVolume4->setBarColorMid(QColor(24, 189, 155));
    ui->barVolume4->setBarColorEnd(QColor(140, 238, 237));
    ui->barVolume5->setBarColorStart(QColor(135, 206, 250));
    ui->barVolume5->setBarColorMid(QColor(173, 216, 230));
    ui->barVolume5->setBarColorEnd(QColor(224, 255, 255));
    ui->barVolume6->setBarColorStart(QColor(0, 0, 205));
    ui->barVolume6->setBarColorMid(QColor(65, 105, 225));
    ui->barVolume6->setBarColorEnd(QColor(176, 224, 221));
    ui->barVolume7->setBarColorStart(QColor(138, 43 , 226));
    ui->barVolume7->setBarColorMid(QColor(123, 104, 238));
    ui->barVolume7->setBarColorEnd(QColor(131, 111, 255));
}

void frmBarVolume::setupSerialPort()
{
    //serial = new QSerialPort(this);
    // 配置串口参数
    serial->setPortName("/dev/ttymxc2");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    // 打开串口
    if (!serial->open(QIODevice::ReadWrite))
    {
        //QMessageBox::critical(this, tr("Error"), tr("Cannot open serial port:\n%1").arg(serial->errorString()));
        //return;
        ui->textEdit->append("串口打开失败！！"); // 将数据追加到QTextEdit中显示
    }
    else
    {
        ui->textEdit->append("串口打开成功！！"); // 将数据追加到QTextEdit中显示
    }
    // 连接信号和槽
    connect(serial, &QSerialPort::readyRead, this, &frmBarVolume::readSerialData);
}

void frmBarVolume::readSerialData()
{
    QByteArray data = serial->readAll(); // 读取所有可用数据
    //ui->textEdit->append(data.toHex()+"\n"); // 将数据追加到QTextEdit中显示
    ui->textEdit->append(data.toHex()); // 将数据追加到QTextEdit中显示
    // 处理数据
    processSerialData(data);
    // 清空缓冲区
    //serial->flush();
}

void frmBarVolume::processSerialData(const QByteArray &data)
{
    //extern int value;
    extern QByteArray song;
    unsigned char message_1[5];
    for(unsigned int i=0;i<data.size();i++)
    {
        message_1[i]=data[i];
    }
    if(message_1[0]==0xaa)
    {
        if((message_1[1]==0x01)||(message_1[1]==0x03))
        {
            //value=0;
            //ui->textEdit_2->append(QString::number(value));
            if((message_1[2]==0x01)||(message_1[2]==0x02)||(message_1[2]==0xff))
            {
                if(message_1[3]==0x01)
                {
                    QTimer *timer1 = new QTimer(this);
                    startTimerForVolumeBar1(timer1, m_timerCount1, 6);
                }
                else if(message_1[3]==0x02)
                {
                    QTimer *timer2 = new QTimer(this);
                    startTimerForVolumeBar2(timer2, m_timerCount2, 6);
                }
                else if(message_1[3]==0x04)
                {
                    QTimer *timer3 = new QTimer(this);
                    startTimerForVolumeBar3(timer3, m_timerCount3, 6);
                }
                else if(message_1[3]==0x08)
                {
                    QTimer *timer4 = new QTimer(this);
                    startTimerForVolumeBar4(timer4, m_timerCount4, 6);
                }
                else if(message_1[3]==0x10)
                {
                    QTimer *timer5 = new QTimer(this);
                    startTimerForVolumeBar5(timer5, m_timerCount5, 6);
                }
                else if(message_1[3]==0x20)
                {
                    QTimer *timer6 = new QTimer(this);
                    startTimerForVolumeBar6(timer6, m_timerCount6, 6);
                }
                else if(message_1[3]==0x40)
                {
                    QTimer *timer7 = new QTimer(this);
                    startTimerForVolumeBar7(timer7, m_timerCount7, 6);
                }
            }
        }
        else if(message_1[1]==0x02)
        {
            if((message_1[2]==0x01)||(message_1[2]==0x02))
            {
                song[0]=message_1[2];
                if(message_1[3]==0x01)
                {
                    Data(message_1[3]);
                    QTimer *timer1 = new QTimer(this);
                    startTimerForVolumeBar1(timer1, m_timerCount1, 6);
                }
                else if(message_1[3]==0x02)
                {
                    Data(message_1[3]);
                    QTimer *timer2 = new QTimer(this);
                    startTimerForVolumeBar2(timer2, m_timerCount2, 6);
                }
                else if(message_1[3]==0x04)
                {
                    Data(message_1[3]);
                    QTimer *timer3 = new QTimer(this);
                    startTimerForVolumeBar3(timer3, m_timerCount3, 6);
                }
                else if(message_1[3]==0x08)
                {
                    Data(message_1[3]);
                    QTimer *timer4 = new QTimer(this);
                    startTimerForVolumeBar4(timer4, m_timerCount4, 6);
                }
                else if(message_1[3]==0x10)
                {
                    Data(message_1[3]);
                    QTimer *timer5 = new QTimer(this);
                    startTimerForVolumeBar5(timer5, m_timerCount5, 6);
                }
                else if(message_1[3]==0x20)
                {
                    Data(message_1[3]);
                    QTimer *timer6 = new QTimer(this);
                    startTimerForVolumeBar6(timer6, m_timerCount6, 6);
                }
                else if(message_1[3]==0x40)
                {
                    Data(message_1[3]);
                    QTimer *timer7 = new QTimer(this);
                    startTimerForVolumeBar7(timer7, m_timerCount7, 6);
                }
            }
        }
        else if(message_1[1]==0x04)
        {
            extern float value;
            extern int i;
            extern int z;
            if(song[0]==0x01)
            {
                QSqlQuery query;
                QDateTime currentDateTime = QDateTime::currentDateTime();
                query.prepare("INSERT INTO data1(name,score,time) VALUES (:name,:score,:time)");
                query.bindValue(":name", "歌曲1");
                query.bindValue(":score", QString::number(value));
                query.bindValue(":time", currentDateTime.toString("yyyy-MM-dd hh:mm:ss")); // 将 QDateTime 转换为字符串
                if (!query.exec())
                {
                    qDebug() << "Insert error:" << query.lastError();
                }
                else
                {
                    qDebug() << "Insert successful";
                }
                //QString sqlInsert = QString("insert into data1(name,score) values('歌曲1',%1);").arg(value);
//                if(!query.exec(sqlInsert))
//                {
//                     qDebug() << "insert data error" ;
//                }
                song[0]=0;
            }
            else if(song[0]==0x02)
            {
                QSqlQuery query;
                QDateTime currentDateTime1 = QDateTime::currentDateTime();
                query.prepare("INSERT INTO data1(name,score,time) VALUES (:name,:score,:time)");
                query.bindValue(":name", "歌曲2");
                query.bindValue(":score", QString::number(value));
                query.bindValue(":time", currentDateTime1.toString("yyyy-MM-dd hh:mm:ss")); // 将 QDateTime 转换为字符串
                if(!query.exec())
                {
                     qDebug() << "insert data error:" << query.lastError();;
                }
                else
                {
                    qDebug() << "Insert successful";
                }
                song[0]=0;
            }
            value=0;
            i=0;
            z=0;
            //ui->textEdit_2->clear();
            ui->label_3->clear();
        }
    }
}

void frmBarVolume::Data(unsigned char data)
{
    static bool executed = false;
    unsigned char tone[50];
    extern QByteArray song;
    //static int i = 0;
    //static int z=0;
    extern int i;
    extern int z;
    extern float value;
    extern unsigned char music_1[32];
    extern unsigned char music_2[41];
    tone[i]=data;
    if(song[0]==0x01)
    {
        if(executed=true)
        {
            value=0;
        }
        if(tone[i]==music_1[i])
        {
            ++z;
            value=(z/float(32))*100;
            //ui->textEdit_2->append(QString::number(value));
            ui->label_3->setText(QString::number(value));
        }
        if(i==31)
        {
            QSqlQuery query;
            QDateTime currentDateTime = QDateTime::currentDateTime();
            query.prepare("INSERT INTO data1(name,score,time) VALUES (:name,:score,:time)");
            query.bindValue(":name", "歌曲1");
            query.bindValue(":score", QString::number(value));
            query.bindValue(":time", currentDateTime.toString("yyyy-MM-dd hh:mm:ss")); // 将 QDateTime 转换为字符串
            if(!query.exec())
            {
                 qDebug() << "insert data error:" << query.lastError();;
            }
            else
            {
                qDebug() << "Insert successful";
            }
            z=0;
            i=0;
            executed=true;
        }
        i++;
//        for(int j=0;j<=i;j++)
//        {
//            if(tone[j]!=music_1[j])
//            {
//                z++;
//            }
//            value=(1-z/50)%100;
//            ui->textEdit_2->append(QString::number(value));

//        }
    }
    else if(song[0]==0x02)
    {
        if(executed=true)
        {
            value=0;
        }
        if(tone[i]==music_2[i])
        {
            ++z;
            value=(z/float(41))*100;
            //ui->textEdit_2->append(QString::number(value));
            ui->label_3->setText(QString::number(value));
        }
        if(i==40)
        {
            QSqlQuery query;
            QDateTime currentDateTime1 = QDateTime::currentDateTime();
            query.prepare("INSERT INTO data1(name,score,time) VALUES (:name,:score,:time)");
            query.bindValue(":name", "歌曲2");
            query.bindValue(":score", QString::number(value));
            query.bindValue(":time", currentDateTime1.toString("yyyy-MM-dd hh:mm:ss")); // 将 QDateTime 转换为字符串
            if(!query.exec())
            {
                 qDebug() << "insert data error:" << query.lastError();;
            }
            else
            {
                qDebug() << "Insert successful";
            }
            z=0;
            i=0;
            executed=true;
        }
        i++;
    }
}

void frmBarVolume::startTimerForVolumeBar1(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每40毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume1->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::startTimerForVolumeBar2(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每40毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume2->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::startTimerForVolumeBar3(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每50毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume3->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::startTimerForVolumeBar4(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每50毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume4->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::startTimerForVolumeBar5(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每50毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume5->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::startTimerForVolumeBar6(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每50毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume6->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::startTimerForVolumeBar7(QTimer *timer, int &counter, int maxCount)
{
    timer->start(40); // 每50毫秒更新一次
    connect(timer, &QTimer::timeout, this, [this, timer, &counter, maxCount]()
    {
        ui->barVolume7->updateProgress();
        // 检查是否已经执行了maxCount次
        if (++counter > maxCount)
        {
            timer->stop(); // 停止定时器
            delete timer; // 删除定时器，释放资源
            counter = 0; // 重置计数器
        }
    });
}

void frmBarVolume::on_pushButton_clicked()
{
    QTimer *timer1 = new QTimer(this);
    startTimerForVolumeBar1(timer1, m_timerCount1, 6);
}

void frmBarVolume::comeBackToPrev()
{
    this->page1->hide();
    this->show();
}

void frmBarVolume::on_pushButton_2_clicked()
{
    this->close();
    this->page1->show();
}

//该函数将label控件变成一个圆形，需要指定颜色color以及直径size
void frmBarVolume::setCircle(QLabel* label, int color, int size)
{
    label->setText("");// 将label中的文字清空
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最大宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最大高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "transparent";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    default:
        break;
    }
    //将之前创建的所有样式字符串拼接成一个完整的样式字符串,然后将拼接好的样式字符串应用到传入的QLabel控件上
    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}

frmBarVolume::~frmBarVolume()
{
    delete serial;
    delete ui;
}




//    if (db.open())
//    {
//        qDebug() << "Open success";
//        QSqlQuery query;
//        if (query.exec("SELECT * FROM data"))
//        {
//            while (query.next())
//            {
//                QString name = query.value("name").toString();
//                QString age = query.value("age").toString();
//                QString itemText = QString("%1 - %2").arg(name).arg(age); // 合并名字和年龄
//                QListWidgetItem *item = new QListWidgetItem(itemText);
//                ui->listWidget->addItem(item); // 将合并后的item添加到QListWidget中
//            }
//        }
//        else
//        {
//            qDebug() << "Query failed:" << query.lastError().text();
//        }
//    }
//    else
//    {
//        qDebug() << "Database not open";
//    }




//                     QTimer *timer1 = new QTimer(this);
//                     timer1->start(50); // 每50毫秒更新一次
//                     connect(timer1, &QTimer::timeout, this, [this, timer1]() {
//                         ui->barVolume1->updateProgress();
//                         // 检查是否已经执行了7次
//                         if (++m_timerCount>7) {
//                             timer1->stop(); // 停止定时器
//                             delete timer1; // 删除定时器，释放资源
//                             m_timerCount = 0;// 每次点击按钮时，重置计数器
//                         }
//                     });


