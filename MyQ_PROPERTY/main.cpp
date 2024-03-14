#include "myproperty.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyProperty w;
    w.show();
    return a.exec();
}
