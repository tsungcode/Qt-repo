#include "mywidget.h"

#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/styl.qss");
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QString str=file.readAll();
        qApp->setStyleSheet(str);
        file.close();
    }
    MyWidget w;
    w.show();
    return a.exec();
}
