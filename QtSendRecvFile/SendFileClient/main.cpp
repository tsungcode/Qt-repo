#include "qtsendfileclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSendFileClient w;
    w.show();
    return a.exec();
}
