#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(QSize(500,500));
    this->setWindowTitle(QString("主窗口"));
    QPushButton *btn=new QPushButton("创建新窗口",this);
    btn->resize(100,40);
    btn->move(200,150);
    //创建新窗体
    this->newForm=new NewWidget;
    connect(btn,&QPushButton::clicked,[=](){
        this->hide();      //隐藏主窗体
        newForm->show();   //显示新窗体
    });
    //接收到新窗体返回信号
    connect(newForm,&NewWidget::back,[=](){
        this->show();     //显示主窗体
    });
}

MyWidget::~MyWidget()
{
}

