#include "recvfile.h"

RecvFile::RecvFile(QTcpSocket *tcp,QObject *parent) : QThread(parent)
{
    this->m_tcp=tcp;
}

//重写虚函数
void RecvFile::run()
{
    QFile *file=new QFile("recv.txt");  //服务端收到文件写入当前文件中
    file->open(QFile::WriteOnly);       //文件以只写模式打开
    //套接字接受数据
    connect(this->m_tcp,&QTcpSocket::readyRead,this,[=](){

        static int count=0;
        static int total=0; //存文件大小
        if(count==0)        //第一次读取获取文件的总大小
        {
            this->m_tcp->read((char*)&total,4);
        }
        //读取剩余数据
        QByteArray all=this->m_tcp->readAll();
        count+=all.size();
        //将读取到的数据写入磁盘文件
        file->write(all);

        //判断数据是否收完
        if(count==total)
        {
            //数据收完关闭套接字
            this->m_tcp->close();
            //释放套接字资源
            this->m_tcp->deleteLater();
            //关闭文件
            file->close();
            //释放文件对象资源
            file->deleteLater();
            //给主线程发送接收数据完毕型号
            emit this->over();
        }
    });
    //进入事件循环
    this->exec();
}
