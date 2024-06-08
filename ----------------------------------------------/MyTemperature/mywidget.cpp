#include "mywidget.h"

#include <QPainter>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{

    this->setWindowTitle("自定义仪表盘");
    m_foreground = Qt::magenta;
    m_background = Qt::black;               //定义背景颜色
    m_title = "T E M P";
    m_startAngle = 45;                      //最小刻度的起始角度（以y轴负半轴为零线）
    m_endAngle = 45;                        //最大刻度的起始角度（以y轴负半轴为零线）
    m_scaleMajor = 10;                      //刻度数量
    m_minValue = 0;                         //最小刻度数值
    m_maxValue = 50;                        //最大刻度数值
    m_scaleMinor = 5;                       //每个刻度分成5个分度
    m_value=0;                              //表盘显示的数据
    m_units = "℃";
}

MyWidget::~MyWidget() {}
void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font("宋体", 14);
    painter.setFont(font);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);           //坐标变换为窗体中心
    int side = qMin(width(), height());
    painter.scale(side/400.0, side/400.0);                  //比例缩放
    drawCrown(&painter);						        	//画表盘边框
    drawScaleNum(&painter);                                 //画刻度数值
    drawScale(&painter);						        	//画刻度线
    drawTitle(&painter);						            //画单位
    drawNumericValue(&painter);                             //画数字显示
    drawIndicator(&painter);	     			    	    //画表针
}
//画表盘边框
void MyWidget ::drawCrown(QPainter *painter)
{
    painter->save();
    int radius = 200;
    painter->setBrush(m_background = QColor(20, 20, 20));
    QLinearGradient lg1(0, -220, 0, 220);                               //设置渐变的界限
    lg1.setColorAt(0, Qt::darkMagenta);                                 //设置渐变的颜色和路径比例
    lg1.setColorAt(1, QColor(20, 20, 20));
    painter->setBrush(lg1);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-radius, -radius, radius << 1, radius << 1);  //绘制紫色圆(-200,-200,400,400)
    painter->setBrush(m_background = QColor(20, 20, 20));
    painter->drawEllipse(-180,-180,360,360);                           //绘制黑色圆
    painter->restore();
}
//画刻度数值
void MyWidget ::drawScaleNum(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(255,255,255)));
    QFontMetricsF fm(this->font());
    int radius = 200;
    int r=(int)(radius*0.8);  //半径160处画文字
    int Angle=45;
    int gap = (360-Angle*2) / 10;  //间隔27度
    for(int i=0; i<=10; i+=1)
    {
        int angle = 90+Angle+gap*i;                                 //角度,每隔10格子画一个刻度值
        float angleArc =( angle % 360) * M_PI / 180;                //转换为弧度
        int x = (r)*cos(angleArc);
        int y = (r)*sin(angleArc);
        QString value =QString( "%1" ).arg(i*5);                    //*********@********//
        //字体大小及位置要微调
        int h = fm.size(Qt::TextSingleLine,value).height();
        x = x -10;
        y = y + h/2;
        painter->drawText(QPointF(x, y),value);
    }
    painter->restore();
}
//画单位
void MyWidget::drawTitle(QPainter *painter)
{
    painter->save();
    painter->setPen(QColor(220,200,200,200));
    QString str(m_title);
    //QFontMetricsF fm(this->font());  //没有用
    painter->drawText(-30, -50, str);
    painter->restore();
}
//画刻度线
void MyWidget ::drawScale(QPainter *painter)
{
    painter->save();
    painter->rotate(m_startAngle);             //坐标系统顺时针旋转45度
    int steps = (m_scaleMajor * m_scaleMinor); //刻度数量10*每个刻度数5    //总刻度数量
    double angleStep = (360.0 - m_startAngle - m_endAngle) / steps;     //每一个份数的角度
    for (int i = 0; i <= steps; i++)           //steps=50
    {
        if (i % m_scaleMinor == 0)            //m_scaleMinor=5          //绘大刻度
        {
            QPen pen ;
            pen.setColor(Qt::green); //Qt::lightGray
            pen.setWidth(2);
            painter->setPen(pen);
            painter->drawLine(0, 125, 0, 145);
        }
        else                                                           //绘小刻度
        {
            QPen pen ;
            pen.setColor(Qt::darkGray);
            pen.setWidth(1);
            painter->setPen(pen);
            painter->drawLine(0, 125, 0, 135);
        }
        painter->rotate(angleStep);     //坐标系统顺时针旋转最小刻度(360-45-45)/50
    }
    painter->restore();
}
//画表针
void MyWidget::drawIndicator(QPainter *painter)
{
    painter->save();
    QPolygon pts;
    pts.setPoints(5, -2,0, -4,30, 0,120, 4,30, 2,0);            //第一个参数是坐标的个数，记下来是坐标
    painter->rotate(m_startAngle);          //顺时针旋转45度指针指向刻度0位置
    //根据m_value的值计算每次旋转度数
    double degRotate =  (360.0 - m_startAngle - m_endAngle)/(m_maxValue - m_minValue)*(m_value - m_minValue);  //*********@********//

    //画指针
    painter->rotate(degRotate); //旋转                           //顺时针旋转坐标系统
    QRadialGradient haloGradient(0, 0, 60, 0, 0);               //辐射渐变
    haloGradient.setColorAt(0, QColor(60,60,60));
    haloGradient.setColorAt(1, QColor(160,160,160));
    painter->setPen(Qt::white);                                 //定义线条文本颜色  设置线条的颜色
    painter->setBrush(haloGradient);                            //刷子定义形状如何填满 填充后的颜色
    painter->drawConvexPolygon(pts);
    painter->restore();

    //画中心点
    QColor niceBlue(150, 150, 200);
    QConicalGradient coneGradient(0, 0, -90.0);                 //角度渐变
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);
    painter->setPen(Qt::NoPen);
    painter->setBrush(coneGradient);
    painter->drawEllipse(-8, -8, 16, 16);
}
//画数字显示
void MyWidget::drawNumericValue(QPainter *painter)
{
    QString str=" ";
    str=str.number(m_value,'g',4);                                //*********@********//
    QFontMetricsF fm(font());
    double w = fm.size(Qt::TextSingleLine,str).width();
    QFont font("times", 40);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(-w-20 , 100, str);
}
