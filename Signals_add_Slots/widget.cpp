#include "widget.h"
#define N 0

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    this->setFixedSize(600,600);
    this->setWindowTitle("Qt自定义槽函数");
    QPushButton *btn=new QPushButton("戳我呀",this);
    btn->resize(250,100);
    btn->move((this->width()-btn->width())/2,(this->height()-btn->height())/2);
    Teacher *t=new Teacher(this);
    Student *s=new Student(this);
    ////////////////////////////////////////////////////
#if N  //无参信号和槽
    connect(btn,&QPushButton::clicked,[=](){
        emit t->hungry();
    });
    void (Teacher::*t1)()= &Teacher::hungry;//无参数信号
    void (Student::*s1)()=&Student::treat;//无参数槽函数
    connect(t,t1,s,s1);
    ////////////////////////////////////////////////////
#else  //有参信号和槽
    connect(btn,&QPushButton::clicked,[=](){
        emit t->hungry(QString("我要吃锅包肉"));
    });
    void (Teacher::*t1)(QString str)= &Teacher::hungry;//带参数信号
    void (Student::*s1)(QString str)=&Student::treat;//带参数槽函数
    connect(t,t1,s,s1);
    /////////////////////////////////////////////////////
#endif
}

Widget::~Widget()
{
}

