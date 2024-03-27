#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE


class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_sendButton_clicked();

    void on_connectButton_clicked();

    //和服务器连接成功槽函数
    void onConnected();
    //和服务器断开连接槽函数
    void onDisconnected();
    //接收消息槽函数
    void onReadyRead();
    //连接异常槽函数
    void onError();

private:
    Ui::MyWidget *ui;
    bool status; //标记当前服务器状态   在线/离线
    QTcpSocket tcpSocket;
    QHostAddress serverIP;  //服务器地址
    quint16 serverPort;     //服务器端口
    QString userName; //昵称
};
#endif // MYWIDGET_H
