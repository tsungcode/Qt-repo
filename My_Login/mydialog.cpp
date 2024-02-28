#include "mydialog.h"
#include "ui_mydialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDialogButtonBox>
#include <QIntValidator>
MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("MyLogin");
    ui->m_EditPasswd->setValidator(new QIntValidator(this)); //设置int校验
    ///////////////////////////////////////////////////////////////////////////
    //当点击Yes,OK之类发送如下信号
    connect(ui->m_buttonBox,&QDialogButtonBox::accepted,[=](){
        if(ui->m_EditName->text()=="admin"&&ui->m_EditPasswd->text()=="123456")
        {
            qDebug()<<"登录成功"<<endl;
            this->close();  //关闭窗口
        }
        else
        {
            QMessageBox::critical(this,"Error","用户名或密码错误",QMessageBox::Ok);
        }

    });
    //当点击No,Cancle之类发送如下信号
    connect(ui->m_buttonBox,&QDialogButtonBox::rejected,[=](){
        QMessageBox::StandardButton ret;
        ret=QMessageBox::question(this,"登录","是否确定要取消登录",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::Yes)
        {
            this->close();
        }
        else if (ret==QMessageBox::No) {
            //什么也不做
        }
    });
}

MyDialog::~MyDialog()
{
    delete ui;
}

