#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QTimer>

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
    void on_srverButton_clicked();
    //响应客户端链接请求的槽函数
    void  onNewconnection();
    //接受客户端消息槽函数
    void onReadyRead();
    //实现转发槽函数，将接受到的信息转发给其他客户端
    void sendMessage(const QByteArray &buff);
    //定时器槽函数
    void onTimeout();

private:
    Ui::MyWidget *ui;
    QTcpServer tcpServer;
    quint16 port;
    QList<QTcpSocket*> tcpClientList; //保存所有和客户端通信的套接字
    QTimer timer;
};
#endif // MYWIDGET_H
