#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation> //属性动画

QT_BEGIN_NAMESPACE
namespace Ui {
class MyMainWindow;
}
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

private:
    Ui::MyMainWindow *ui;
    QPropertyAnimation *propertyAnimation1; //几何动画
    QPropertyAnimation *propertyAnimation2; //颜色动画
    QPropertyAnimation *propertyAnimation3; //透明度动画
};
#endif // MYMAINWINDOW_H
