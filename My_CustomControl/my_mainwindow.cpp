#include "my_mainwindow.h"
#include "ui_my_mainwindow.h"
#include <QHBoxLayout>
#include <QDebug>

My_MainWindow::My_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::My_MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(600,650);
    ui->mywidget->setGeometry(150,100,300,450);

    //自定义信号和槽的实现
    connect(ui->mywidget,&MyButton::MyMousePressClicked,[=](){
        qDebug()<<"鼠标按下了"<<endl;
    });


    //设置窗口透明
    //this->setWindowFlag(Qt::|Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground,true);

//    QPalette pal = palette();
//    pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
//    setPalette(pal);
//    this->setWindowOpacity(0.2);
}

My_MainWindow::~My_MainWindow()
{
    delete ui;
}

