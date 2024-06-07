#include "myprobar.h"

#include <QPainter>

MyProBar::MyProBar(QWidget *parent)
    : QWidget{parent}
{
    this->m_value=0;
    this->m_max=100;
    this->m_min=0;
}

void MyProBar::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    QPainter painter(this);
    QFont font("宋体", 72);//字体大小
    painter.setFont(font);
    painter.translate(width() / 2, height() / 2);           //坐标变换为窗体中心
    int side = qMin(width(), height());
    painter.scale(side/400.0, side/400.0);                  //缩放比例

    //1、绘制最外层圆
    int radius = 200;
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(-radius, -radius, radius << 1, radius << 1);  //绘制最外层圆 (红色底圆)

    //2、绘制扇形，渐变色
    //扇形渐变
    QConicalGradient conical(0,0,90); //扇形渐变，顺时针旋转
    conical.setColorAt(0,Qt::red);
    conical.setColorAt(1,Qt::blue);
    painter.setBrush(conical);
    //画扇形默认是逆时针画，加负号就顺时针画，注意0度在表盘3时位置
    painter.drawPie(-radius, -radius, radius << 1,
                    radius << 1,90*16,
                    -this->m_value*1.0/(this->m_max-this->m_min)*360*16); //第二个参数为起始角度，第三个是结束角度

    //3、绘制中间圆
    painter.setBrush(Qt::green);//中间圆
    //QRect minRect=this->rect().adjusted(50,50,-50,-50); //矩形中，左上角点和右下角点，第一二参数为正向内偏移50像素，三四为负向偏移50像素
    //painter.drawEllipse(minRect);

    painter.drawEllipse(-150, -150, 150 << 1, 150 << 1);
    painter.setPen(Qt::black);
    //4、绘制文字
    painter.drawText(-radius, -radius, radius << 1, radius<<1,
                     Qt::AlignVCenter|Qt::AlignHCenter,
                     QString::number(this->m_value)+"%");
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
