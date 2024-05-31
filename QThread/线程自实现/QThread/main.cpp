#include "myqthread.h"

#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyQThread w;
    w.show();
    qDebug()<<QSqlDatabase::drivers();
    return a.exec();
}
