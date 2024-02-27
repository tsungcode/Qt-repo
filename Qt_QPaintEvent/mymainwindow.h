#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

protected:
    //绘图事件
    virtual void paintEvent(QPaintEvent*)override;

private:
    Ui::MyMainWindow *ui;
};
#endif // MYMAINWINDOW_H
