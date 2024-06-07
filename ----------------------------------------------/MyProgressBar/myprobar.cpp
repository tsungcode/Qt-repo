#include "myprobar.h"

#include <QPainter>

MyProBar::MyProBar(QWidget *parent)
    : QWidget{parent}
{
    this->m_value=0;
    this->m_max=100;
    this->m_min=0;
}
//绘图
void MyProBar::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    QPainter painter(this);
    QFont font("宋体", this->width()/5);//字体大小
    painter.setFont(font);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(this->rect());//画圆  (红色底圆）

    //扇形渐变
    QConicalGradient conical(this->rect().center(),90); //扇形渐变，顺时针旋转
    conical.setColorAt(0,Qt::red);
    conical.setColorAt(1,Qt::blue);
    painter.setBrush(conical);
    //画扇形默认是逆时针画，加负号就顺时针画，注意0度在表盘3时位置
    painter.drawPie(this->rect(),90*16,-this->m_value*1.0/(this->m_max-this->m_min)*360*16); //第二个参数wield起始角度，第三个是结束角度

    painter.setBrush(Qt::green);//中间圆
    QRect minRect=this->rect().adjusted(50,50,-50,-50); //矩形中，左上角点和右下角点，第一二参数为正向内偏移50像素，三四为负向偏移50像素
    painter.drawEllipse(minRect);
    painter.setPen(Qt::black);
    //绘制文字
    painter.drawText(this->rect(),Qt::AlignCenter,QString::number(this->m_value)+"%");
}
//获取当前值
int MyProBar::value() const
{
    return m_value;
}
//设置当前值
void MyProBar::setValue(int newValue)
{
    if(newValue>this->m_max)     //传入的值比最大值大时
    {
        this->m_value=this->m_max;
    }
    else if(newValue<this->m_min) //传入值值比最小值小
    {
        this->m_value=this->m_min;
    }
    else
    {
        m_value = newValue;
    }
    this->update(); //绘制重画
}
