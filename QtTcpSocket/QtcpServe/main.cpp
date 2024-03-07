#include "mytcpserve.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTcpServe w;
    w.show();
    return a.exec();
}
