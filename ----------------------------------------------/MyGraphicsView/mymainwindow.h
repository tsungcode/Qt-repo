#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include <QGraphicsScene>

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
private:
    QLabel *labViewCord;     //状态栏显示View坐标
    QLabel *labSceneCord;    //状态栏显示Scene坐标
    QLabel *labItemCord;     //状态栏显示Item坐标
    QGraphicsScene *Scene;   //场景对象

    void initGraphics();
private slots:
    void on_mouseMove(QPoint point);    //自实现槽函数
    void on_mouseClicked(QPoint point); //自实现槽函数
private:
    Ui::MyMainWindow *ui;

    // QWidget interface

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;  //重写个窗口大小变化
};
#endif // MYMAINWINDOW_H
