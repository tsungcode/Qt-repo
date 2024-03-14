#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QGraphicsColorizeEffect> //颜色属性作用效果
#include <QGraphicsOpacityEffect>  //透明度

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    //////////////////////////////////////////////////////////////
    //1、创建几何动画
    this->propertyAnimation1=new QPropertyAnimation(ui->jihe,"geometry");

    //设置动画的起始值
    this->propertyAnimation1->setStartValue(QRect(0,0,50,50));
    //设置动画的某个时间段的值
    this->propertyAnimation1->setKeyValueAt(0.5,QRect(500,0,300,300));  //中间只能设置0到1之间，我们设置为0.5
    //设置动画结束值
    this->propertyAnimation1->setEndValue(QRect(550,350,200,200));
    //设置动画运行时长
    this->propertyAnimation1->setDuration(2000); //2000毫秒
    //设置动画的循环周期
    this->propertyAnimation1->setLoopCount(3);  //循环执行3次
    //设置动画缓和的曲线（动画运行）默认是匀速的
    this->propertyAnimation1->setEasingCurve(QEasingCurve::OutCubic);//QEasingCurve::OutCubic是个枚举类型
    ///////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    //2、创建颜色动画化
    //创建颜色效果对象，作用在窗体对应组件中
    QGraphicsColorizeEffect *graphicsColorizeEffect=new QGraphicsColorizeEffect(this);//颜色效果对象
    ui->yanse->setGraphicsEffect(graphicsColorizeEffect);
    //创建颜色动画化
    this->propertyAnimation2=new QPropertyAnimation(graphicsColorizeEffect,"color");
    //设置动画起始值
    this->propertyAnimation2->setStartValue(QColor(Qt::green));
    //设置动画结束值
    this->propertyAnimation2->setEndValue(QColor(Qt::red));
    //设置动画运行时长
    this->propertyAnimation2->setDuration(2000); //2000毫秒
    ///////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////
    //3、创建不透明度动画
    QGraphicsOpacityEffect *graphicsOpacityEffect=new QGraphicsOpacityEffect(this);
    ui->touming->setGraphicsEffect(graphicsOpacityEffect);  //设置图形效果
    //创建颜色动画化
    this->propertyAnimation3=new QPropertyAnimation(graphicsOpacityEffect,"opacity");
    //设置动画起始值
    this->propertyAnimation3->setStartValue(0.0);
    //设置动画结束值
    this->propertyAnimation3->setEndValue(1.0);
    //设置动画运行时长
    this->propertyAnimation3->setDuration(5000); //5000毫秒
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

//启动几何动画
void MyMainWindow::on_btn1_clicked()
{
    this->propertyAnimation1->start();
}

//启动颜色动画
void MyMainWindow::on_btn2_clicked()
{
    this->propertyAnimation2->start();
}

//启动透明度动画
void MyMainWindow::on_btn3_clicked()
{
    this->propertyAnimation3->start();
}


