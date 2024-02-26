#ifndef MYLABLE_H
#define MYLABLE_H

#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

class MyLable : public QLabel
{
    Q_OBJECT
public:
    explicit MyLable(QWidget *parent = nullptr);

public:
    virtual void enterEvent(QEvent*e) override;   //鼠标进入事件
    virtual void leaveEvent(QEvent*e) override;    //鼠标离开事件
    virtual void mouseMoveEvent(QMouseEvent *ev) override;  //鼠标移动
    virtual void mousePressEvent(QMouseEvent*ev) override; //鼠标按下事件

    //事迹分发器
    virtual bool event(QEvent *e) override;  //事件分发器

    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

signals:

};

#endif // MYLABLE_H
