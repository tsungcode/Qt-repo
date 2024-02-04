#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800,800);
    this->setWindowTitle(QString("窗口切换主窗口"));
    QPushButton *btn=new QPushButton(QString("切换下一窗口"),this);
    btn->resize(QSize(350,200));
    btn->move(this->width()/2-btn->width()/2,this->height()/2-btn->height()/2);
    //切换窗口实现
    NewWidget *newForm=new NewWidget;
    connect(btn,&QPushButton::clicked,[=](){
        this->hide();
        newForm->show();
    });
    connect(newForm,&NewWidget::Back,[=](){
        this->show();
        newForm->close();
    });
}

Widget::~Widget()
{
}

