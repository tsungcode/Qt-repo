#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
protected:
    void paintEvent(QPaintEvent *ev)override;
private:
    int angle;
    QTimer *timer;
};
#endif // MYWIDGET_H
