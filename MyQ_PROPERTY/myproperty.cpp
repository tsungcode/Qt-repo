#include "myproperty.h"
#include "ui_myproperty.h"
#include <QPropertyAnimation>  //属性动画
#include <QDebug>

MyProperty::MyProperty(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyProperty)
{
    ui->setupUi(this);
    //////////////////////////////////////////////
    this->myform=new MyForm(this);
    //**********************************************************************
    //myform->setProperty("number",2000);  //直接属性
    //********************************************************************
    QPropertyAnimation *p=new QPropertyAnimation(myform,"number",this);  //第一个参数为目标对象，第二个参数为属性
    //开始属性动画
    p->setStartValue(1);
    //结束动画
    p->setEndValue(20000);
    //动画时长
    p->setDuration(10000); //10秒
    //动画曲线
    p->setEasingCurve(QEasingCurve::Linear);

    //开始动画
    p->start();

    connect(myform,&MyForm::NumberCharged,this,[=](){
        qDebug()<<"属性的信号";
    });

    //////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    //在窗口提升控件为MyForm类型后使用自定义属性实现动画
    QPropertyAnimation *p1=new QPropertyAnimation(ui->mywidget,"number",this);  //第一个参数为目标对象，第二个参数为属性
    //开始属性动画
    p1->setStartValue(10000);
    //结束动画
    p1->setEndValue(30000);
    //动画时长
    p1->setDuration(10000); //10秒
    //动画曲线
    p1->setEasingCurve(QEasingCurve::Linear);

    //开始动画
    p1->start();



    //////////////////////////////////////
    /// 调用属性的WRITE方法
    ui->widget->setProperty("number",5555);
}

MyProperty::~MyProperty()
{
    delete ui;
}
