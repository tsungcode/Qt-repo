#ifndef MYQTHREAD_H
#define MYQTHREAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MyQThread; }
QT_END_NAMESPACE

class MyQThread : public QMainWindow
{
    Q_OBJECT
public:
    MyQThread(QWidget *parent = nullptr);
    ~MyQThread();
signals:
    void  calc();  //发出计算信号
public slots:
    void getnumber(int a);

private:
    Ui::MyQThread *ui;
};
#endif // MYQTHREAD_H
