#include "mywidget.h"
#include "ui_mywidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setPalette(QPalette(Qt::white)); //设置窗口底色
    this->setAutoFillBackground(true);  //马上生效，自动刷新，不用等paintEvent()
    this->resize(600,600);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::TextAntialiasing,true);
    QFont font;
    font.setPixelSize(10);
    painter.setFont(font);

    QPen penLine;
    penLine.setWidth(2);
    penLine.setColor(Qt::blue);

    penLine.setStyle(Qt::SolidLine);     //实线
    penLine.setCapStyle(Qt::FlatCap);    //帽子
    penLine.setJoinStyle(Qt::BevelJoin); //连接处
    painter.setPen(penLine);

    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    //***************************************************
    qreal R=100;  //半径
    qreal deg= (360.0/5)* M_PI/180;   //计算弧度
    QPoint points[5]=
        {
            QPoint(R,0),
            QPoint(R*qCos(deg),-R*qSin(deg)),
            QPoint(R*qCos(2*deg),-R*qSin(2*deg)),
            QPoint(R*qCos(3*deg),-R*qSin(3*deg)),
            QPoint(R*qCos(4*deg),-R*qSin(4*deg)),
        };
    QPainterPath startPath;
    startPath.moveTo(points[0]);
    startPath.lineTo(points[2]);
    startPath.lineTo(points[4]);
    startPath.lineTo(points[1]);
    startPath.lineTo(points[3]);
    startPath.closeSubpath();   //封闭

    startPath.addText(points[0],font,"0");
    startPath.addText(points[1],font,"1");
    startPath.addText(points[2],font,"2");
    startPath.addText(points[3],font,"3");
    startPath.addText(points[4],font,"4");
    painter.save();

    //绘制
    painter.translate(250,120);
    painter.drawPath(startPath);
    painter.drawText(0,0,"S1");
    //移动画家绘制第二个
    painter.restore();              //恢复上一次状态
    painter.translate(250,280);
    painter.scale(0.6,0.6);        //缩放
    painter.rotate(90);            //旋转坐标0
    painter.drawPath(startPath);
    painter.drawText(0,0,"S2");
    //移动画家绘制第三个
    painter.resetTransform();     //复位所有坐标变换
    painter.translate(250,465);
    painter.scale(1.5,1.5);
    painter.drawPath(startPath);
    painter.drawText(0,0,"S3");
    event->accept();
}
