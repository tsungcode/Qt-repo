#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "mywidget.h"  //加入自定义类的头文件

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    ///////////////////////////////////////////
    //绘图事件
    virtual  void paintEvent(QPaintEvent* event);


private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
