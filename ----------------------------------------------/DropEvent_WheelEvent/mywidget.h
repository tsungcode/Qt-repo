#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

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
    void keyPressEvent(QKeyEvent* event)override;  //键盘按下事件
    //void keyReleaseEvent(QKeyEvent* event)override; //键盘释放事件


private:
    Ui::MyWidget *ui;
};
#endif // MYWIDGET_H
