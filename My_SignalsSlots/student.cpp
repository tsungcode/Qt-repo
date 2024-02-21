#include "student.h"

Student::Student(QObject *parent) : QObject(parent)
{
    this->num1=0;
    this->num2=0;

}
void Student::treat()
{
    num1++;
    qDebug()<<num1<<" 下课了，请老师吃饭"<<endl;
}
//自定义有参槽函数
void Student::treat(QString str)
{
    num2++;
    qDebug()<<num2<<" 下课了，请老师吃饭"<<">>"<<str.toUtf8().data()<<endl;
}
