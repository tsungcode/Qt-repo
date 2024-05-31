#include "myqthread.h"
#include "ui_myqthread.h"
#include <QThread>
#include <mythread.h>

MyQThread::MyQThread(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyQThread)
{
    ui->setupUi(this);
    ////////////////////////////////////////////
    //单线程方法
#if 0
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        int num=0;
        while (true) {
            num++;
            if(num==10000000)
            {
                break;
            }
            ui->label->setText(QString::number(num));
        }

    });
#else
    MyThread *t=new MyThread;   //创建线程对象Qt 4.7
    //多线程
    connect(t,&MyThread::OK,this,[=](int a){
        ui->label->setNum(a);
    });
    //启动线程
    connect(ui->pushButton,&QPushButton::clicked,this,[=]()
            {
                t->start(); //子线程执行run方法
            });
    //线程销毁
    connect(this,&MyQThread::destroyed,this,[=]()
            {
                t->quit();
                t->wait();
                t->deleteLater();
            });
#endif
}

MyQThread::~MyQThread()
{
    delete ui;
}

//自实现槽函数
void MyQThread::getnumber(int a)
{
    ui->label->setNum(a);
}

