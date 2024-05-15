#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);//去掉边框
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
}

MyWidget::~MyWidget()
{
    delete ui;
}
