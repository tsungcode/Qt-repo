#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

#include <QBrush>
#include <QPen>
#include <QPixmap>

enum class Shape {
    _Point,         //点
    _Line,          //线

    _Rect,          //矩形
    _RoundedRect,   //圆角矩形
    _Ellipse,       //椭圆

    _Polyline,      //多边线
    _Polygon,       //多边形

    _Arc,           //
    _Pie,           //
    _Chord,         //

    _Path,          //

    _Text,          //
    _Pixmap
};

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);

public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialias(bool antialiased);
    void setTransform(bool transformed);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Shape mShape;  //形状
    QPen mPen;
    QBrush mBrush;
    bool mAntialias;
    bool mTransform;
};

#endif  // PAINTWIDGET_H
