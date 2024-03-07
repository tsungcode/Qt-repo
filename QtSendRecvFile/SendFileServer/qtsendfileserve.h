#ifndef QTSENDFILESERVE_H
#define QTSENDFILESERVE_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QMessageBox>
#include "recvfile.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class QtSendFileServe; }
QT_END_NAMESPACE

class QtSendFileServe : public QMainWindow
{
    Q_OBJECT

public:
    QtSendFileServe(QWidget *parent = nullptr);
    ~QtSendFileServe();

private slots:
    void on_m_setListen_clicked();

private:
    Ui::QtSendFileServe *ui;
    QTcpServer *m_tcp;  //
};
#endif // QTSENDFILESERVE_H
