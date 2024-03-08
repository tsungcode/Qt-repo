#include "qtsendfileserve.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSendFileServe w;
    w.show();
    return a.exec();
}
