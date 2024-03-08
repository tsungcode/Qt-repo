#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>       //操作文件
#include <QFileInfo>   //文件的大小

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port,QString ip);
    //发送文件
    void sendFile(QString path);
signals:
    void connectOK(); //服务器连接成功发送信号
    void gameOver();  //服务器和客户端已经断开信号
    void curPercent(int num); //发送百分比信号
private:
    QTcpSocket *m_tcp; //

};

#endif // SENDFILE_H
