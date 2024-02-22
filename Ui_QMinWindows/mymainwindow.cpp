#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPalette>
#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>


MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    //ui中设置窗体标题
    this->setWindowTitle(" Ui窗体QMainWindows");
    this->setWindowIcon(QIcon(":/image/13.ico"));
    ////////////////////////////////////////////////
    //Ui中手动加的菜单项的信号和槽使用
    int newNum=0;
    QObject::connect(ui->New,&QAction::triggered,[&](){
        newNum++;
        qDebug()<<newNum<<":点击了New控件"<<endl;
    });
    //
    connect(ui->Open,&QAction::triggered,[=](){
        qDebug()<<"打开了文件"<<endl;
    });

    //代码生成QPushButton
    QPushButton *btn=new QPushButton("第一个按钮",this); //QPushButton
    btn->move(300,200);
    QLabel *label=new  QLabel("这是一个QLable控件啊控件",this); //Qlabel
    label->move(300,300);
    label->resize(200,200);
    connect(btn,&QPushButton::clicked,[&](){
        QPalette ple;
        ple.setColor(QPalette::WindowText,Qt::red);  //获取并设置为红色
        label->setPalette(ple);  //设置label

        this->setPalette(QPalette(Qt::green));//设置主窗口为绿色
    });
    ////////////////一下为测试代码函数///////////////////////////////////
//    QDialogFun();
//    QMessageBoxFun();
//    QFontDialogFun();
//    QColorDialogFun();
//    QFileDialogFun();
    ///////////////////////////////////////////////////////////////////
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//QDialog的测试代码
void MyMainWindow::QDialogFun()
{
    QDialog *dl=new QDialog(this);
    dl->resize(800,800);
    dl->show();
    QMainWindow *mw=new QMainWindow(this);
    mw->resize(300,300);
    mw->show();
}

//QMessageBox实现
void MyMainWindow::QMessageBoxFun()
{
    QMessageBox::StandardButton ret;
    ret=QMessageBox::information(this,"消息title","消息内容xxxxxxxxx",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(ret==QMessageBox::No)
    {
        this->setPalette(QPalette(Qt::red));
        this->setAttribute(Qt::WA_DeleteOnClose);
    }
}

//QFontDialog的测试代码
void MyMainWindow::QFontDialogFun()
{
    bool flag;
    QFont font=QFontDialog::getFont(&flag,QFont("微软雅黑"),this);
    if(flag==true)
    {
        qDebug()<<flag<<endl;
        qDebug()<<"字体是："<<font.family()<<"字体大小："<<font.pointSize()<<" "<<font.pointSizeF()<<endl;
    }
}
//QColorDialog的测试代码
void MyMainWindow::QColorDialogFun()
{
    QColor color;
    color=QColorDialog::getColor();
    qDebug()<<"red="<<color.red()<<" "<<"green="<<color.green()<<" "<<"blue="<<color.blue()<<endl;
}

//QFileDialog的测试代码
void MyMainWindow::QFileDialogFun()
{
    QString fileName;
    fileName=QFileDialog::getOpenFileName(this,"打开文件","一个默认打开路径","(*.txt)");
}

