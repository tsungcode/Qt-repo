#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private:
    QColor m_background;
    QColor m_foreground;
    QString m_title;
    int m_maxValue, m_minValue;
    int m_startAngle,m_endAngle;
    int m_scaleMajor;
    int m_scaleMinor;
    double m_value;               //*********@********//
    QString m_units;
protected:
    void paintEvent(QPaintEvent *);
    void drawCrown(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawIndicator(QPainter *painter);
    void drawNumericValue(QPainter *painter);
public slots:
    // void setValue(double value); //槽函数设置仪表盘的数值
};
#endif // MYWIDGET_H
