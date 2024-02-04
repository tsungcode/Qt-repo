#include "mywidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
   this->setWindowTitle("第二窗体");
   this->resize(700,700);
   QPushButton*btn2=new QPushButton("返回上一页",this);
   btn2->move(600,650);
   ///////////////////////////////////////
   connect(btn2,&QPushButton::clicked,[=](){
       emit back();
   });

}
//绘制背景图片
void MyWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   QPixmap pix(":/image/2.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
