#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QVector>

// 生成随机数线程
class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void working(int num);

signals:
    void sendArray(QVector<int> num);
};

////////////////////冒泡排序//////////////////////////////////
class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> list);

signals:
    void finish(QVector<int> num);
};

////////////////////////快速排序///////////////////////////////
class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void working(QVector<int> list);

private:
    void quickSort(QVector<int> &list, int l, int r);

signals:
    void finish(QVector<int> num);
};

#endif // MYTHREAD_H
