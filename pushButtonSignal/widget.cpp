#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //鼠标左键按下信号和槽
    connect(ui->pushButton,&MyPushButton::pressed,[=](){
      ui->label->setText("鼠标左键按下了");
    });
   //鼠标左键释放信号和槽
    connect(ui->pushButton,&MyPushButton::released,[=](){
      ui->label->setText("鼠标左键按释放了");
    });
}

Widget::~Widget()
{
    delete ui;
}
