#include "mywidget.h"
#include "ui_mywidget.h"

#include <QTimer>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent,Qt::FramelessWindowHint)  //无边框
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("带缩放功能环形进度条");
    this->resize(600,600);

    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        ui->widget->setValue(ui->widget->value()+1);
    });
    timer->start(1000);
    //*******************背景透明，右键退出***********
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *act=new QAction("退出",this);
    this->addAction(act);
    connect(act,&QAction::triggered,this,[=](){this->close();});
    //**********************************************
}

MyWidget::~MyWidget()
{
    delete ui;
}
