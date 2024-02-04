#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    //绘图事件
    virtual  void paintEvent(QPaintEvent* event);


signals:
    void back(void);//自定义返回信号

public slots:
};

#endif // MYWIDGET_H
