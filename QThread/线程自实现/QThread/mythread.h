#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

//创建线程类
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    virtual void run() override; //重写run
protected:

signals:
    void OK(int num); //信号
};

#endif // MYTHREAD_H
