#include "mywidget.h"
#include <QSlider>  //滑块
#include <QSpinBox> //选值框

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(650,650);
    this->setWindowTitle("QSlider和QSpinBox的信号和槽函数练习");
    //创建滑块
    QSlider *slider1=new QSlider(Qt::Vertical,this);  //垂直滑块
    slider1->move(100,150);
    slider1->resize(80,300);
    slider1->setRange(0,200);  //设置滑块范围
    QSlider *slider2=new QSlider(Qt::Horizontal,this); //水平滑块
    slider2->move(400,200);
    slider2->resize(200,80);
    slider2->setRange(0,200); //设置滑块范围
    //创建选值框
    QSpinBox *spin=new QSpinBox(this);
    spin->move(250,300);
    spin->resize(65,25);
    spin->setRange(0,200); //设置选值框范围
    //信号和槽的连接
    //滑块1移动时
    QObject::connect(slider1,&QSlider::valueChanged,spin,&QSpinBox::setValue);  //改变选值框
    QObject::connect(slider1,&QSlider::valueChanged,slider2,&QSlider::setValue);//改变滑块2

    //滑块2移动时
    connect(slider2,&QSlider::valueChanged,spin,&QSpinBox::setValue);   //改变选值框
    connect(slider2,&QSlider::valueChanged,slider1,&QSlider::setValue); //改变滑块1

    //选值框变动时
    connect(spin,SIGNAL(valueChanged(int)),slider1,SLOT(setValue(int)));  //改变滑块1
    connect(spin,SIGNAL(valueChanged(int)),slider2,SLOT(setValue(int)));  //改变滑块2
}

MyWidget::~MyWidget()
{

}
