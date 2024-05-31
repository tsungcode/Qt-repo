#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 创建子线程对象
    QThread* t1 = new QThread;
    QThread* t2 = new QThread;
    QThread* t3 = new QThread;

    // 2. 创建任务类的对象
    Generate* gen = new Generate;  //生成随机数
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    // 3. 将任务对象移动到某个子线程中
    gen->moveToThread(t1);    //生成随机数
    bubble->moveToThread(t2); //冒泡排序
    quick->moveToThread(t3);  //快速排序

    //生成随机数
    connect(this, &MainWindow::starting, gen, &Generate::working);
    //启动子线程生成随机数
    connect(ui->start, &QPushButton::clicked, this, [=]()
            {
                emit starting(10000);
                t1->start();
            });

    //生成的随机数发给其他线程进行冒泡和快速排序
    connect(gen, &Generate::sendArray, bubble, &BubbleSort::working);
    connect(gen, &Generate::sendArray, quick, &QuickSort::working);
    // 接收子线程发送的数据
    connect(gen, &Generate::sendArray, this, [=](QVector<int> list){
        t2->start();  //启动冒泡排序线程
        t3->start();  //启动快速排序线程
        for(int i=0; i<list.size(); ++i)
        {
            ui->randList->addItem(QString::number(list.at(i)));
        }
    });
    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> list){
        for(int i=0; i<list.size(); ++i)
        {
            ui->bubbleList->addItem(QString::number(list.at(i)));
        }
    });
    connect(quick, &QuickSort::finish, this, [=](QVector<int> list){
        for(int i=0; i<list.size(); ++i)
        {
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });
    //释放内存空间
    connect(this, &MainWindow::destroyed, this, [=]()
            {
                t1->quit();
                t1->wait();
                t1->deleteLater();  // delete t1;

                t2->quit();
                t2->wait();
                t2->deleteLater();

                t3->quit();
                t3->wait();
                t3->deleteLater();

                gen->deleteLater();
                bubble->deleteLater();
                quick->deleteLater();
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

