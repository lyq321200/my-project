#ifndef SCROLLINGLABEL_H
#define SCROLLINGLABEL_H
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QTimerEvent>
#include <QPainter>

class ScrollingLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ScrollingLabel(QWidget *parent = nullptr);
    void setText(const QString &text); // 设置文本时需要重新启动滚动

    public slots:
        void setSpeed(int speed); // 设置滚动速度

    protected:
        void paintEvent(QPaintEvent *event) override; // 重写绘制事件
        void timerEvent(QTimerEvent *event) override; // 重写定时器事件

    private:
        int timerId; // 定时器ID
        int pos; // 文字滚动的位置
        QString fullText; // 完整的文本内容




};


#endif // SCROLLINGLABEL_H
