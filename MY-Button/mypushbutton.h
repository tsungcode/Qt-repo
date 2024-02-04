#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>//继承QPusButton


class MyPushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushbutton(QWidget *parent = nullptr);
    //绘图事件
    virtual void paintEvent(QPaintEvent *event);
    //自定义函数
    void moveDown();
    void moveUp();

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
