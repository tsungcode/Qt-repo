#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QTimer>


MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("QTimer的例子"));
    //设置每个label居中
    ui->label_timer1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->label_Timer2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->label_timer3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->label_timer4->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);


    ///////////////////////////////////////////////////////////////
    //以下为事件启动定时器

    this->id1=startTimer(500);//500毫秒后启动定时器1
    this->id2=startTimer(1000);//1000毫秒后启动定时器2

    /////////////////////////////////////////////////////////////
    //以下为对象启动定时器
    QTimer *t=new QTimer(this);
    connect(ui->btn_start,&QPushButton::clicked,[=](){
        t->start(1); //启动定时器
    });
    connect(ui->btn_stop,&QPushButton::clicked,[=](){
        t->stop(); //暂停定时器
    });
    //触发定时器
    connect(t,&QTimer::timeout,[=]()
    {
        static int num=0;
        ui->label_timer3->setText(QString::number(num++));
    });


    ////////////////////////////////////////////////////////////////
    //一下为信号触发延时
    QTimer::singleShot(1000,[=](){
        ui->label_timer4->setText(QString("这是一个1000毫秒触发的延时"));
        //this->hide();  //关闭窗口
    });

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

//重写事件实现定时器
void MyMainWindow::timerEvent(QTimerEvent *e)
{
    if(e->timerId()==id1)
    {
        static int num=0;
        ui->label_timer1->setText(QString::number(num++));
    }
    else if (e->timerId()==id2)
    {
        static int num=0;
        ui->label_Timer2->setText(QString::number(num++));
    }
}

