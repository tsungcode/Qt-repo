#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals: //自定义信号函数
    //自定义信号不需要实现
void hungry();
void hungry(QString str);

};

#endif // TEACHER_H
