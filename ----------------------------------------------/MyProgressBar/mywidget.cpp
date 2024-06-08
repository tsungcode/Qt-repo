#include "mywidget.h"
#include "ui_mywidget.h"

#include <QTimer>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("环形进度条");
    this->resize(450,450);


    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        ui->widget->setValue(ui->widget->value()+1);
    });
    timer->start(1000);
}

MyWidget::~MyWidget()
{
    delete ui;
}
