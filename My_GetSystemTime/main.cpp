#include "mydialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDialog w;
    w.show();
    return a.exec();
}
