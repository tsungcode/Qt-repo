#include "student.h"

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::treat(QString str)
{
    qDebug()<<number++<<" "<<"请老师吃饭"<<" "<<"请老师吃："<<str<<endl;

}

void Student::treat()
{
     qDebug()<<number++<<" "<<"请老师吃饭"<<endl;
}
////////////////////////////////////////////////////////////////////
int Student::number=1;
