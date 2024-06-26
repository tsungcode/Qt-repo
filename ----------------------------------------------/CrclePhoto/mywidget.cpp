#include "mywidget.h"
#include "ui_mywidget.h"

#include <QPaintEvent>
#include <QPainter>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("旋转头像");
    this->resize(450,450);

    connect(&timer,&QTimer::timeout,this,[=]
            {
                angle += 1.0;
                if(angle == 360)
                    angle = 0.0;
                update();
            });
    timer.start(40);


}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen); //丢掉画笔

    painter.setRenderHint(QPainter::Antialiasing, true);  //抗锯齿
    QPoint centerPoint = rect().center();
    painter.save();
    painter.translate(centerPoint);

    int radius = (qMin(width(),height()) - 15 * 2 ) / 2;   //圆形距离边框15像素
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(0, 0), radius, radius);      //画圆


    QRect rect = QRect(-radius, -radius,radius*2, radius*2);  //绘制图形的矩形区域
    pen.setColor(Qt::blue);
    painter.setPen(pen);

    //绘制圆弧
    painter.drawArc(rect.adjusted(-5,-5,5,5),0,static_cast<int>(angle * 16));  //逆时针画圆弧
    //裁剪区域
    QRegion region(rect, QRegion::Ellipse);  //区域
    painter.setClipRegion(region);
    painter.rotate(angle);   //坐标系统顺时针旋转一个角度

    painter.drawPixmap(rect,QPixmap(":/image/2024.png"));
    painter.restore();
}
