#include "myform.h"
#include "ui_myform.h"

MyForm::MyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyForm)
{
    ui->setupUi(this);

     //初始值
    // this->num=1000;
    // ui->label->setText(QString::number(this->num));
}

MyForm::~MyForm()
{
    delete ui;
}

//READ
int MyForm::number() const
{
    return this->num;
}
//WRITE
void MyForm::setNumber(int n)
{
    this->num=n;
    ui->label->setText(QString::number(this->num));
    emit this->NumberCharged();  //触发属性的信号
}
