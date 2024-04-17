#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

//重写Run方法
void MyThread::run()
{
    static int num=0;
    while (true)
    {
        emit this->OK(num++); //发送信号
        if(num==10000000)
        {
            break;
        }
        QThread::usleep(2);
    }
}
