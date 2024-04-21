#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QLCDNumber>
#include <QTimerEvent>
#include <QPoint>

class MyDialog : public QLCDNumber
{
    Q_OBJECT
private:
    QPoint dragPos;
    bool showFlog;

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

    void timerEvent(QTimerEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void keyPressEvent(QKeyEvent *event)override;
    void showTime();

};
#endif // MYDIALOG_H
