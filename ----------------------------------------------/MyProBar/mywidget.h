#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void setCurValue(int newCurValue);//*******************

protected:
    void paintEvent(QPaintEvent *ev)override;
private:
    QTimer *timer;
    int offset;
    int mMax;
    int mMin;
    int mCurValue;
};
#endif // MYWIDGET_H
