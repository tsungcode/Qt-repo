#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>//设置继承QLabel

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

    //绘图事件
    virtual void paintEvent(QPaintEvent *event);
    //鼠标事件
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

public:
    enum MyLabelStat
    {
        Normal,//正常
        Entered,//进入
        Leaved,//离开
        Pressed,//按下
        Released//释放
    };
    MyLabelStat state;

signals:

public slots:
};

#endif // MYLABEL_H
