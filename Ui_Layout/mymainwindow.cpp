#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QRadioButton>
#include <QPalette>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTableWidget>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    //ui->pushButton_login->setText("Login");


    //单击登录获取密码
    connect(ui->pushButton_login,&QPushButton::clicked,[=](){
        if(ui->lineEdit_Name->text()==""|ui->lineEdit_Passward->text()=="")
        {
            qDebug()<<"用户名和密码不能为空"<<endl;
        }
        else
        {
            qDebug()<<"用户密码=："<<ui->lineEdit_Passward->text().toUtf8().data()<<endl;
        }

    });
    //单击退出关闭窗口
    connect(ui->pushButton_quit,&QPushButton::clicked,[=](){
        this->close();
    });

    ui->plainTextEdit->setPlainText("关关难过关关过，事事难成事事成。");
    //改变字体颜色
    connect(ui->radioButton_red,&QRadioButton::clicked,[=](){
        QPalette ple=ui->radioButton_red->palette();
        ple.setColor(QPalette::Text,Qt::red);
        ui->plainTextEdit->setPalette(ple);
    });
    connect(ui->radioButton_green,&QRadioButton::clicked,[=](){
        QPalette ple=ui->radioButton_green->palette();
        ple.setColor(QPalette::Text,Qt::green);
        ui->plainTextEdit->setPalette(ple);
    });
    connect(ui->radioButton_yellow,&QRadioButton::clicked,[=](){
        QPalette ple=ui->radioButton_yellow->palette();
        ple.setColor(QPalette::Text,Qt::yellow);
        ui->plainTextEdit->setPalette(ple);
    });

    //QListWidgetItem的使用
    QListWidgetItem *itme=new QListWidgetItem("你好哇李银河");
    ui->listWidget->addItem(itme);
    itme->setTextAlignment(Qt::AlignHCenter);
    ui->listWidget->addItem("举头望明月");
    ui->listWidget->addItem("低头思故乡");

    //***QStringList的使用***
    QStringList list({"海内存知己","天涯若比邻","AAAAAAAAAA"});
    ui->listWidget->addItems(list);
    connect(ui->listWidget,&QListWidget::itemClicked,[=]( QListWidgetItem *itme){
        qDebug()<<itme->text()<<endl;
    });

    //QTreeWidget的使用
    connect(ui->treeWidget,&QTreeWidget::itemClicked,[=](QTreeWidgetItem *item,int num){
        qDebug()<<item->text(num).toUtf8().data()<<endl;
    });

    //QTableWidget的使用
    connect(ui->tableWidget,&QTableWidget::itemClicked,[=](QTableWidgetItem*item){
        qDebug()<<item->text().toUtf8().data()<<endl;
    });
    //QTableWidget的行列
    connect(ui->tableWidget,&QTableWidget::cellClicked,[=](int row,int col){
        qDebug()<<"行坐标："<<row<<"\t"<<"列坐标"<<col<<endl;
    });


}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

