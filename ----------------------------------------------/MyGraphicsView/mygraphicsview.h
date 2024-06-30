#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = nullptr);

signals:
    void mouseMovePoint(QPoint point);   //自实现信号
    void mouseClicked(QPoint point);     //自实现信号

    //重写鼠标按下和鼠标移动
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MYGRAPHICSVIEW_H
