#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    this->resize(600,750);
    QPushButton *btn=new QPushButton("移动",this);
    btn->resize(100,45);
    btn->move(this->width()/2-btn->width()/2,this->height()-btn->height());
    connect(btn,&QPushButton::clicked,[=](){
       this->update();
    });

    QTimer*timer=new QTimer(this);
    timer->start(2000);
    connect(timer,&QTimer::timeout,[=](){
       this->update();
    });
}
MyMainWindow::~MyMainWindow()
{
    delete ui;
}

////////////////////////////绘制背景图片//////////////////////////////
///重写绘图事件
void MyMainWindow::paintEvent(QPaintEvent *)
{
    static int number=111;
    //定义画家
    QPainter*paint=new QPainter(this);
    //定义图片控件
    QPixmap pix;
    switch (number) {
    case 111:
          pix.load(QString(":/image/111.jpg"));
          number+=111;
        break;
    case 222:
        pix.load(QString(":/image/222.jpg"));
        number+=111;
        break;
    case 333:
        pix.load(QString(":/image/333.jpg"));
        number+=111;
        break;
    case 444:
        pix.load(QString(":/image/444.jpg"));
        number=111;
    }
    //pix.load(QString(":/image/222.jpg"));
    pix.scaled(this->width(),this->height());//修改图片和窗体尺寸大小
    //画家在主窗口绘画
    paint->drawPixmap(0,0,this->width(),this->height(),pix);

/////////////////////////////////////////////////////////////////////

//    //定义画家
//    QPainter*paint=new QPainter(this);
//    //定义图片控件
//    QPixmap pix;
//    pix.load(QString(":/image/111.jpg"));
//    pix.scaled(pix.width(),pix.height());//修改图片尺寸大小
//    static int num=0;
//    if(num>=this->width())
//    {
//        num=0;
//    }
//     //画家在主窗口绘画
//    paint->drawPixmap(num,0,pix.width()/10,pix.height()/10,pix);
//    num+=5;
/////////////////////////////////////////////////////////////////////

//    //定义画家
//    QPainter*paint=new QPainter(this);
//    //划线
//    paint->drawLine(100,100,300,300);
//    paint->drawRect(200,200,100,50);













 }
