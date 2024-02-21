#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QDebug>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:

public slots: //自定义槽函数
    void treat();
    void treat(QString str);
private:
    int num1;
    int num2;
};

#endif // STUDENT_H
