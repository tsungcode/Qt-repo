#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QFont>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

protected:
    void paintEvent(QPaintEvent *e)override;

private:
    Ui::MyWidget *ui;
    QFont font;
    int offset;
    QTimer *timer;
    QString text;    //文字
    int textWidth;   //文字的宽度
public slots:
    void onTimerTimeOut();
};
#endif // MYWIDGET_H
