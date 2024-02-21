#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{

    //自定义信号和槽实现有参和无参函数

    this->setWindowTitle("自定义信号和槽函数的实现");
    this->setFixedSize(QSize(500,500));
    Teacher *th=new Teacher(this);
    Student *stu=new Student(this);
//////////////////////////////////////////////////////////////////
    //1、无参的自定义信号和槽函数实现
    QPushButton *btn1=new QPushButton("触发无参信号",this);
    btn1->resize(100,50);
    btn1->move(200,100);
    void (Teacher::*pth1)()=&Teacher::hungry;      //无参信号
    void (Student::*pstu1)()=&Student::treat;      //无参槽函数
    //发出信号第一种写法
    connect(btn1,&QPushButton::clicked,[=](){
        emit th->hungry();
    });
    //发出信号第二种写法
    //connect(btn1,&QPushButton::clicked,th,pth1);   //发出无参信号
    connect(th,pth1,stu,pstu1);                      //无参信号连接无参槽函数

//////////////////////////////////////////////////////////////////
    //2、有参的自定义信号和槽函数实现
    QPushButton *btn2=new QPushButton;
    btn2->setParent(this);
    btn2->setText("触发有参信号");
    btn2->resize(100,50);
    btn2->move(200,200);
    void (Teacher::*pth2)(QString str)=&Teacher::hungry;      //有参信号
    void (Student::*pstu2)(QString str)=&Student::treat;      //有参槽函数
    connect(btn2,&QPushButton::clicked,[=](){
        emit th->hungry("红烧肉");
    });                                                     //发出无参信号
    connect(th,pth2,stu,pstu2);                                //无参信号连接无参槽函数
}

MyWidget::~MyWidget()
{
}

