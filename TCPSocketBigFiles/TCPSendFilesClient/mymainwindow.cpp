#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QMessageBox>
#include <QDebug>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    ui->m_ip->setText("127.0.0.1");
    ui->m_port->setText("8899");
    this->setWindowTitle("客户端");
    this->isStart=true;   //第一次接受标志位
    ui->progressBar->setValue(0);//初始化进度条为0
    /////////////////////////////////////////////////
    //创建套接字对象
    this->m_tcpSocket=new QTcpSocket(this);

    //连接服务器成功信号
    connect(this->m_tcpSocket,&QTcpSocket::connected,this,[=](){
        QMessageBox::information(this,"提示","客户端和服务器连接成功");
    });

    //读取服务器发送过来的数据
    connect(this->m_tcpSocket,&QTcpSocket::readyRead,this,[=](){

        QByteArray buff=this->m_tcpSocket->readAll();
        if(this->isStart==true)  //读取首次发送的文件信息
        {
            this->isStart=false;
            //解析头部信息他，拆包
            this->fileName=QString(buff).section("##",0,0);  ////文件名字
            this->fileSize=QString(buff).section("##",1,1).toInt();
            this->reciveSize=0;  //记录接受的数据大小

            //打开文件
            this->file.setFileName(this->fileName);
            bool isOK=this->file.open(QIODevice::WriteOnly); //只写的方式打开
            if(isOK==false)
            {
                qDebug()<<"打开出错";
            }

            //设置进度条最小值和最大值
            ui->progressBar->setMaximum(this->fileSize/1024);
            ui->progressBar->setMinimum(0);
        }
        else
        {
            qint64 len=this->file.write(buff);  //返回写入的大小
            //累加大小
            this->reciveSize+=len;
            //更新进度条
            ui->progressBar->setValue(this->reciveSize/1024);//更新进度条
            if(this->reciveSize==this->fileSize)
            {
                qDebug()<<"接收数据完成";
                this->file.close();
                this->m_tcpSocket->disconnectFromHost();
                this->m_tcpSocket->close();
                QMessageBox::information(this,"提示","接收数据完成");
            }
        }
    });

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

//客户端链接服务器
void MyMainWindow::on_m_connect_clicked()
{
    //获取窗体输入的ip和端口号
    QString ip=ui->m_ip->text();
    quint16 port=ui->m_port->text().toInt();
    this->m_tcpSocket->connectToHost(QHostAddress(ip),port);  //链接服务器
}

