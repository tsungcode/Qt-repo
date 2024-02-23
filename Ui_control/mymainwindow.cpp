#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QDebug>
#include <QComboBox>
#include <QLabel>
#include <QMovie>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("Ui控件学习"));
    this->resize(650,550);
    //////////////////////////////////////////////////////////
    //ComBox的使用
    ui->comboBox->setGeometry(this->width()/2-ui->comboBox->width()/2,25,120,35); //设置Combox的位置和大小
    ui->comboBox->addItem(QIcon(":/image/1.ico"),"第一");
    ui->comboBox->addItem(QIcon(":/image/2.ico"),"第二");
    ui->comboBox->addItem(QIcon(":/image/3.ico"),"第三");
    ui->comboBox->addItem(QIcon(":/image/4.ico"),"第四");
    ui->comboBox->addItem(QIcon(":/image/5.ico"),"第五");
    ui->comboBox->setCurrentIndex(2);//设置默认显示
    //ComBox获取索引值
    //    void (QComboBox::*ptr)(int) = &QComboBox::currentIndexChanged;
    //    connect(ui->comboBox,ptr,[=](int index){
    //            qDebug()<<index<<endl;
    //    });
    connect(ui->comboBox,&QComboBox::currentTextChanged,[=](QString str){
        qDebug()<<str.toUtf8().data()<<endl;
    });


    ///////////////////////////////////////////////////////////////////////
    //lable设置图片
    ui->label->setFrameShape(QFrame::Box);    //label设置边框
    ui->label->setText("你好哇,李银河");       //label设置文字
    //ui->label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);  //label设置水平和垂直居中
    ui->label->setGeometry(this->width()/2-ui->label->width()/2,85,320,215);   //label设置位置和大小

    //label添加图片
    ui->label->setPixmap(QPixmap(":/image/M.jpg")); //设置图片
    ui->label->setScaledContents(true);             //设置图片自适应lable

    //label添加gif图片
    //ui->label_2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->label_2->setFrameShape(QFrame::Box);          //label设置边框
    ui->label_2->setScaledContents(true);             //设置图片自适应lable
    ui->label_2->setGeometry(this->width()/2-ui->label_2->width()/2,315,320,215);
    QMovie *movie=new QMovie(":/image/K.gif");

    ui->label_2->setMovie(movie);  //设置gif图
    //movie->setSpeed(5);   //设置gif图播放速度
    movie->start();

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

