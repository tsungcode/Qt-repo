#include "newwidget.h"

NewWidget::NewWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("第二窗口");
    this->setFixedSize(QSize(800,800));
    QPushButton *btn=new QPushButton(QString("返回第一窗口"),this);
    btn->resize(250,100);
    btn->move(this->width()/2-btn->width()/2,this->height()/2-btn->height()/2);
    connect(btn,&QPushButton::clicked,[=](){
        emit this->Back();
    });

}
