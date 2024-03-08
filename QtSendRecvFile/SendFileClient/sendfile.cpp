#include "sendfile.h"

SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

//子线程连接服务器
void SendFile::connectServer(unsigned short port, QString ip)
{
    //实例化套接字对象
    this->m_tcp=new QTcpSocket;
    //子线程连接服务器
    this->m_tcp->connectToHost(QHostAddress(ip),port);
    //子线程连接服务器成功会发送一个信号给主线程
    connect(this->m_tcp,&QTcpSocket::connected,this,&SendFile::connectOK);
    //子线程检测到服务器和客户端断开处理释放资源，告诉主线程
    connect(this->m_tcp,&QTcpSocket::disconnected,this,[=](){
        this->m_tcp->close();        //断开套接字
        this->m_tcp->deleteLater();  //释放资源内存
        emit this->gameOver();       //发送信号告诉主线程，服务器和客户端已经断开
    });
}
//子线程发送文件
void SendFile::sendFile(QString path)
{
    //获取文件的大小
    QFileInfo info(path);
    int fileSize=int(info.size()); //获得要发送文件的总大小  注：info.size返回值是qint64强转换为int
    //打开文件
    QFile file(path);
    bool b=  file.open(QFile::ReadOnly); //打开成功为
    if (b)
    {
        //打开成功
        while(!file.atEnd()) //一行一行的读，读完为true
        {
            static int num=0;
            if(num==0)    //判断是第一次发送,先发送文件总大小
            {
                //this->m_tcp->write((char*)&fileSize,4);    //将文件大小转换为字符串发送给服务器,指定大小4字节
                this->m_tcp->write(reinterpret_cast<char*>(&fileSize),4); //C++风格数据转换
            }
            //从第二次发送开始每次读取一行发送服务器
            QByteArray line=file.readLine();
            num+=line.size();    //记录每次发送的大小
            int percent=(num/fileSize)*100;  //更新主窗口进度条
            //给主窗口发送信号
            emit this->curPercent(percent);  //读一行发送一行,且发送一行文件大小信号
            this->m_tcp->write(line);        //套接字一行一行发送读取到的文件给服务器
        }
    }
    else {
        //打开失败
    }
}
