#ifndef BARVOLUME_H
#define BARVOLUME_H
#include <QWidget>

class BarVolume : public QWidget
{
    Q_OBJECT

public:
    explicit BarVolume(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);//重写paintEvent函数，用于自定义控件的绘制
    void drawBg(QPainter *painter);//绘制控件的背景
    void drawBarBg(QPainter *painter);//绘制进度条背景
    void drawBar(QPainter *painter);//绘制进度条本身

private:
    int value;                      //目标值
    int targetValue;                //更新值
    int step;                       //步长
    int space;                      //间距
    int padding;                    //间隔
    int radius;                     //圆角角度

    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色

    QColor barBgColor;              //进度背景颜色
    QColor barColorStart;           //进度渐变开始颜色
    QColor barColorMid;             //进度渐变中间颜色
    QColor barColorEnd;             //进度渐变结束颜色

public:
    int getValue()                  const;
    int getStep()                   const;
    int getSpace()                  const;
    int getPadding()                const;
    int getRadius()                 const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;

    QColor getBarBgColor()          const;
    QColor getBarColorStart()       const;
    QColor getBarColorMid()         const;
    QColor getBarColorEnd()         const;

public Q_SLOTS:

    //设置目标值
    void setValue(int value);
    //设置步长
    void setStep(int step);
    //设置间距
    void setSpace(int space);
    //设置间隔
    void setPadding(int padding);
    //设置圆角角度
    void setRadius(int radius);
    //设置背景颜色
    void setBgColorStart(QColor bgColorStart);
    void setBgColorEnd(QColor bgColorEnd);
    //设置柱状颜色
    void setBarBgColor(QColor barBgColor);
    void setBarColorStart(QColor barColorStart);
    void setBarColorMid(QColor barColorMid);
    void setBarColorEnd(QColor barColorEnd);
    //更新进度条
    void updateProgress();
};

#endif // BARVOLUME_H
