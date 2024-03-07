#ifndef MYTCPSERVE_H
#define MYTCPSERVE_H

#include <QMainWindow>
#include <QTcpServer>  // 服务端
#include <QTcpSocket>  //套接字
#include <QLabel>
#include <QPixmap>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MyTcpServe; }
QT_END_NAMESPACE

class MyTcpServe : public QMainWindow
{
    Q_OBJECT

public:
    MyTcpServe(QWidget *parent = nullptr);
    ~MyTcpServe();

private slots:
    void on_m_setListen_clicked();

    void on_m_sendMsg_clicked();

private:
    Ui::MyTcpServe *ui;
    QTcpServer *m_s;    //
    QTcpSocket *m_tcp;  //
    QLabel *m_status;   //
    QDateTime dt;
};
#endif // MYTCPSERVE_H
