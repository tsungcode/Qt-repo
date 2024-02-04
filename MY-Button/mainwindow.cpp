#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QPushButton *btn=new QPushButton(this);
    MyPushbutton*btn=new MyPushbutton(this);
    btn->resize(200,200);
    //按钮水平居中，垂直方向在3/4位置处
    //计算方式 x=窗口宽度/2-按钮宽度/2  ,y=窗口高度的3/4-按钮高度/2
    btn->move((this->width()/2-btn->width()/2),(this->height()*3/4-btn->height()/2));
    ////////////////////////////////////////////////////////////////
    connect(btn,&QPushButton::clicked,[=](){
        //将按钮设置不可用
        btn->setEnabled(false);
        btn->moveDown();
        //往上走的动画会覆盖之前动画
        //要等待之前动画播放完在调用往下走动画
        QTimer::singleShot(60,[=](){
            btn->moveUp();
        });
        /////////////////////////////////////////////////启动按钮
        QTimer::singleShot(150,[=]{
            btn->setEnabled(true);
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *EVENT)
{
    Q_UNUSED(EVENT);
    QPainter painter(this);
    QPixmap pix(":/image/2.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
