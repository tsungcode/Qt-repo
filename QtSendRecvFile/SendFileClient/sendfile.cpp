#include "sendfile.h"

SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

//连接服务器
void SendFile::connectServer(unsigned short port, QString ip)
{
    //实例化套接字对象
    this->m_tcp=new QTcpSocket;
    //连接服务器
    this->m_tcp->connectToHost(QHostAddress(ip),port);
    //连接成功会发送一个信号
    connect(this->m_tcp,&QTcpSocket::connected,this,&SendFile::connectOK);
    //检测服务器和客户端断开
    connect(this->m_tcp,&QTcpSocket::disconnected,this,[=](){
        this->m_tcp->close();  //断开套接字
        this->m_tcp->deleteLater(); //释放资源内存
        //发送信号告诉主线程，服务器和客户端已经断开
        emit this->gameOver();
    });
}
//发送文件
void SendFile::sendFile(QString path)
{
    //获取文件的大小
    QFileInfo info(path);
    int fileSize=info.size();  //文件的大小
    //打开文件
    QFile file(path);
    bool b=  file.open(QFile::ReadOnly); //打开成功为
    if (b)
    {
        //打开成功
        while(!file.atEnd()) //一行一行的读，读完为true
        {
            static int num=0;
            if(num==0)
            {
                this->m_tcp->write((char*)fileSize,4);
            }
            //每次读取一行发送服务器
            QByteArray line=file.readLine();
            num+=line.size(); //记录每次发送的大小
            int percent=(num*100/fileSize);
            //给主窗口发送信号
            emit this->curPercent(percent);

            //套接字一行一行发送读取到的文件给服务器
            this->m_tcp->write(line);
        }
    }
    else {
        //打开失败
    }

}
