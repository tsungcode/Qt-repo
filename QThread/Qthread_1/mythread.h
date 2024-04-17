#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>

// 生成随机数
class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);
public slots:
    void recvNum(int num);  //槽函数
protected:
    void run() override;
signals:
    void sendArray(QVector<int> num);
private:
    int m_num;
};

/////////////////////////冒泡排序/////////////////////////////
class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
public slots:
    void recvArray(QVector<int> list);
protected:
    void run() override;
signals:
    void finish(QVector<int> num);
private:
    QVector<int> m_list;
};

///////////////////////快速排序////////////////////////////////
class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
public slots:
    void recvArray(QVector<int> list);
protected:
    void run() override;
private:
    void quickSort(QVector<int> &list, int l, int r);
signals:
    void finish(QVector<int> num);
private:
    QVector<int> m_list;
};

#endif // MYTHREAD_H
