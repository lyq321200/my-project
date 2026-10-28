#ifndef FRMBARVOLUME_H
#define FRMBARVOLUME_H
#include <mqtt/qmqttclient.h>
#include <QWidget>
#include <QLabel>
#include <QSerialPort>
//#include <QSerialPortInfo>
#include <QSqlDatabase>//连接和打开数据库类

namespace Ui
{
    class frmBarVolume;
}

class MainWindow;
class frmBarVolume : public QWidget
{
    Q_OBJECT//这是一个Qt特有的宏，用于支持Qt的信号和槽机制，以及Qt的元对象系统（Meta-Object System）。

public:
    explicit frmBarVolume(QWidget *parent = nullptr);
    ~frmBarVolume();
    MainWindow * page1= NULL;
    inline void initForm();
    void setCircle(QLabel* label, int color, int size);

private:
    Ui::frmBarVolume *ui;
    int m_timerCount1=0; // 用于跟踪定时器执行次数的成员变量
    int m_timerCount2=0;
    int m_timerCount3=0;
    int m_timerCount4=0;
    int m_timerCount5=0;
    int m_timerCount6=0;
    int m_timerCount7=0;
    QSerialPort *serial;
    void setupSerialPort();
    //QSqlDatabase db;
    void createDatabase();

private slots:
    void on_pushButton_clicked();
    void comeBackToPrev();
    void readSerialData();
    void startTimerForVolumeBar1(QTimer *timer, int &counter, int maxCount);
    void startTimerForVolumeBar2(QTimer *timer, int &counter, int maxCount);
    void startTimerForVolumeBar3(QTimer *timer, int &counter, int maxCount);
    void startTimerForVolumeBar4(QTimer *timer, int &counter, int maxCount);
    void startTimerForVolumeBar5(QTimer *timer, int &counter, int maxCount);
    void startTimerForVolumeBar6(QTimer *timer, int &counter, int maxCount);
    void startTimerForVolumeBar7(QTimer *timer, int &counter, int maxCount);
    void on_pushButton_2_clicked();
    void processSerialData(const QByteArray &data);
    void Data(unsigned char data);
};

#endif // FRMBARVOLUME_H
