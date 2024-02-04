#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>//继承QPusButton
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    //绘图事件
    virtual void paintEvent(QPaintEvent* event);
    //重写鼠标事件
    virtual void enterEvent(QEvent* event);
    virtual void leaveEvent(QEvent* event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
public:
    //声明按钮 MyPushButton的三个状态
    enum MyPushButtonState
    {
        Normal,
        Entered,
        Pressed
    };
private:
    MyPushButtonState state;//声明转态变量

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
