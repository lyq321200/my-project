#include "scrollinglabel.h"

ScrollingLabel::ScrollingLabel(QWidget *parent) : QLabel (parent),timerId(-1), pos(0)
{
    // 初始化时不处理
}
void ScrollingLabel::setText(const QString &newText)
{
    QLabel::setText(newText); // 调用基类的setText
    fullText = newText; // 保存文本内容
    pos = width(); // 重置滚动位置
    if (timerId == -1)
    { // 如果定时器未启动，则启动定时器
        timerId = startTimer(25); // 每100毫秒触发一次定时器事件
    }
    QLabel::clear();// 清空当前显示的文本，因为我们将在paintEvent中绘制
}

void ScrollingLabel::setSpeed(int speed)
{
    killTimer(timerId); // 停止当前定时器
    timerId = startTimer(speed); // 启动新的定时器，设置新的速度
}

void ScrollingLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QFontMetrics fm = painter.fontMetrics();
    //int textWidth = fm.width(fullText);
    //int x = pos - textWidth; // 从最右侧开始绘制
    int x =pos;
    // 绘制文本，使其从右向左滚动
    painter.drawText(x, height() / 2 + fm.ascent() / 2, fullText);
}

void ScrollingLabel::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerId)
    {
        pos -= 1; // 每次定时器事件减少1像素
//      if (pos < -width())
//      {
        // 如果文本已经完全滚动出视图，则重置位置
//          pos = width();
//      }
        if (pos + fontMetrics().width(fullText) < 0)
        {
            // 如果文本已经完全滚动出视图，则重置位置
            pos = width();
        }
        update(); // 重绘Label
    }
}
