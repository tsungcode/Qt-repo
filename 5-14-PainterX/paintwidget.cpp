#include "paintwidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent) : QWidget{parent}
{
    mAntialias = false;
    mTransform = false;

    // Qt中继承QWidget之后，样式表不起作用。需要增加以下代码
    this->setAttribute(Qt::WA_StyledBackground, true);
}

//设置形状
void PaintWidget::setShape(Shape shape)
{
    this->mShape = shape;
    update();
}
//设置笔
void PaintWidget::setPen(const QPen &pen)
{
    this->mPen = pen;
    update();
}
//设置画刷
void PaintWidget::setBrush(const QBrush &brush)
{
    this->mBrush = brush;
    update();
}
//设置抗锯齿
void PaintWidget::setAntialias(bool antialias)
{
    this->mAntialias = antialias;
    update();
}
//平移，旋转，缩放
void PaintWidget::setTransform(bool transform)
{
    this->mTransform = transform;
    update();
}
/////////////////////////////////////////////////////////////////////////////////////
//***********************************************************************************
/////////////////////////////////////////////////////////////////////////////////////
void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    static const QPoint points[4] = {
        QPoint(10, 80),  //
        QPoint(20, 10),  //
        QPoint(80, 30),  //
        QPoint(90, 70)   //
    };

    // QRect(int left, int top, int width, int height)
    QRect rect(10, 20, 80, 60);
    //绘制路径参数
    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);

    //绘制圆弧起始角度和结束角度 参数
    int startAngle = 30 * 16;
    int arcLength = 120 * 16;

    // 创建画家类的对象，参数为绘图设备。指定为this，表示在当前窗口绘制
    QPainter painter(this);
    painter.setPen(mPen);      //设置画笔
    painter.setBrush(mBrush);  //设置画刷
    if ( mAntialias )  //设置抗锯齿
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }

    for ( int x = 0; x < width(); x += 100 )  //安装先绘制第一列在绘制第二列，一列一列进行绘制
    {
        for ( int y = 0; y < height(); y += 100 )
        {
            // 先保存原来的状态
            // (0,0),(0,100),(0,200),(0,300)...(0,600)
            // (100,0),(100,100),(100,200),(100,300)...(100,600)
            // ...
            // (800,0),(800,100),(800,200),(800,300)...(800,600)
            painter.save();
            painter.translate(x, y);  // translate 修改的是坐标系

            if ( mTransform ) //平移旋转缩放
            {
                // 按照如下写法，先缩放再平移，才能达到绕原图中心旋转缩放的效果
                painter.translate(50, 50);
                painter.rotate(90.0);
                painter.scale(0.7, 0.7);  //缩放
                painter.translate(-50, -50);
#if 0 \
    // 按照如下写法，不能达到绕原图中心旋转缩放的效果
                painter.rotate(90.0);
                painter.translate(0, -100);
                painter.scale(0.6, 0.6);

#endif
            }

            switch ( mShape ) {
                // 点、线
            case Shape::_Point:
                painter.drawPoints(points, 4); //绘制4个点
                break;
            case Shape::_Line:
                painter.drawLine(points[0], points[2]);
                break;

                // 多线段、多边形
            case Shape::_Polyline:   //绘制多边线
                painter.drawPolyline(points, 4);
                break;
            case Shape::_Polygon:  //绘制多边形
                painter.drawPolygon(points, 4);
                break;

                // 矩形、椭圆
            case Shape::_Rect:
                painter.drawRect(rect);
                break;
            case Shape::_RoundedRect:  //圆角矩形
                // 第四个参数是一个枚举类型，可指定为：AbsoluteSize 或 RelativeSize
                // 当指定为AbsoluteSize，则2，3参数为圆角大小
                // 当指定为RelativeSize，则2，3参数为圆角百分比
                painter.drawRoundedRect(rect, 25, 25, Qt::AbsoluteSize);
                break;

            case Shape::_Ellipse:
                painter.drawEllipse(rect);
                break;

                // 圆弧、饼图
            case Shape::_Arc:  //圆弧
                //                    painter.drawRect(rect);
                painter.drawArc(rect, startAngle, arcLength);
                break;
            case Shape::_Pie:   //饼图
                painter.drawPie(rect, startAngle, arcLength);
                break;
            case Shape::_Chord:  //弦图
                painter.drawChord(rect, startAngle, arcLength);
                break;
            // 路径
            case Shape::_Path: //路径
                painter.drawPath(path);
                break;
            // 文本、图片
            case Shape::_Text: //文字
                painter.drawText(rect, Qt::AlignCenter, "你好哇\n李银河");
                break;
            case Shape::_Pixmap://图片
                painter.drawPixmap(10, 10, QPixmap(":/images/qt-logo.png"));
            }
            painter.restore();
        }//for end
    }//for end

#if 1
    // 绘制最外侧的矩形边框
    painter.setRenderHint(QPainter::Antialiasing, false);
    //    painter.setPen(QColor(0,0,0));
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    //    painter.drawRect(QRect(0, 0, width(), height()));
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
#endif
}
