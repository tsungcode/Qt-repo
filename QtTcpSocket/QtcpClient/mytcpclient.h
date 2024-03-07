#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QMainWindow>
#include <QMainWindow>
#include <QHostAddress>
#include <QTcpSocket>  //套接字
#include <QLabel>
#include <QPixmap>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MyTcpClient; }
QT_END_NAMESPACE

class MyTcpClient : public QMainWindow
{
    Q_OBJECT

public:
    MyTcpClient(QWidget *parent = nullptr);
    ~MyTcpClient();

private slots:
    void on_m_connect_clicked();

    void on_m_disconnect_clicked();

    void on_m_sendMsg_clicked();

private:
    Ui::MyTcpClient *ui;
    QTcpSocket *m_tcp;  //
    QLabel *m_status;   //
    QDateTime dt;       //
};
#endif // MYTCPCLIENT_H
