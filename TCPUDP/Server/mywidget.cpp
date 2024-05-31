#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ////////////////////////////////
    //服务端收到客户端连接
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(onNewconnection()));
    //定时器信号
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
}

MyWidget::~MyWidget()
{
    delete ui;
}

//创建监听服务器
void MyWidget::on_srverButton_clicked()
{
    this->port=ui->serverPortEdit->text().toShort();
    if(this->tcpServer.listen(QHostAddress::Any,this->port))
    {
        QMessageBox::information(this,"提示","服务器创建成功");
        //禁用按钮
        ui->serverPortEdit->setEnabled(false);
        ui->srverButton->setEnabled(false);
        //开启定时器
        this->timer.start(3000);
    }
    else
    {
        //开启监听失败
        QMessageBox::critical(this,"ERROR",this->tcpServer.errorString());
    }
}
//相应客户端连接槽函数
void MyWidget::onNewconnection()
{
    //获取和服务端连接的套接字
    QTcpSocket *tcpSocket=this->tcpServer.nextPendingConnection();
    this->tcpClientList.append(tcpSocket);
    //当客户端向服务端发送信息 readyRead信号
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}
//接受客户端消息槽函数
void MyWidget::onReadyRead()
{
    //遍历套接字容器，看是哪个套接字给服务端发送消息
    for(int i=0;i<this->tcpClientList.size();i++)
    {
        //bytesAvailable()获取当前套接字等待读取信的字节数，返回0表示没有信息
        if(this->tcpClientList.at(i)->bytesAvailable())
        {
            //读取消息并保存
            QByteArray buff=this->tcpClientList.at(i)->readAll();
            //将读取到的信息显示界面
            ui->listWidget->addItem(buff);
            ui->listWidget->scrollToBottom();//滚动条
            //转发信息给其他客户端
            sendMessage(buff);
        }
    }
}
//实现转发槽函数，将接受到的信息转发给其他客户端
void MyWidget::sendMessage(const QByteArray &buff)
{
     for(int i=0;i<this->tcpClientList.size();i++)
    {
        tcpClientList.at(i)->write(buff);
    }
}
//定时器槽函数
void MyWidget::onTimeout()
{
    //遍历删除断开的套接字
    for(int i=0;i<this->tcpClientList.size();i++)
    {
        if(tcpClientList.at(i)->state()==QAbstractSocket::UnconnectedState)
        {
            tcpClientList.removeAt(i);
            i--;
        }
    }
}
