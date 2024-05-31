#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 创建子线程对象
    Generate* gen = new Generate;         //生成随机数线程
    BubbleSort* bubble = new BubbleSort;  //冒泡排序线程
    QuickSort* quick = new QuickSort;     //快速排序线程

    connect(this, &MainWindow::starting, gen, &Generate::recvNum);
    // 2. 启动子线程
    connect(ui->start, &QPushButton::clicked, this, [=]()
            {
                emit this->starting(10000);
                gen->start();        //启动生成随机数线程
            });
    //生成的随机数传给冒泡和快速排序
    connect(gen, &Generate::sendArray, bubble, &BubbleSort::recvArray);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recvArray);

    // 接收子线程发送的生成的随机数数据
    connect(gen, &Generate::sendArray, this, [=](QVector<int> list){   //接收子线程生成的随机数显示的主窗口
        bubble->start(); //启动冒泡排序线程
        quick->start();  //启动快速排序线程
        for(int i=0; i<list.size(); ++i)  //
        {
            ui->randList->addItem(QString::number(list.at(i)));
        }
    });

    //冒泡排序完成将排序好数据发主线程
    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> list){
        for(int i=0; i<list.size(); ++i)
        {
            ui->bubbleList->addItem(QString::number(list.at(i)));
        }
    });
    //快速排序完成将排序好的数据发主线程
    connect(quick, &QuickSort::finish, this, [=](QVector<int> list){
        for(int i=0; i<list.size(); ++i)
        {
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });

    //点击关闭窗口释放内存
    connect(this, &MainWindow::destroyed, this, [=]()
            {
                gen->quit();
                gen->wait();
                gen->deleteLater();  // delete t1;

                bubble->quit();
                bubble->wait();
                bubble->deleteLater();

                quick->quit();
                quick->wait();
                quick->deleteLater();
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

