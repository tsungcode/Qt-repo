#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    this->status=false; //初始化为离线状态
    ///////////////////////////////////////////
    //链接服务器
    connect(&tcpSocket,SIGNAL(connected()),this,SLOT(onConnected()));
    //断开服务器
    connect(&tcpSocket,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    //接收信息
    connect(&tcpSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    //链接通信异常
    connect(&tcpSocket,SIGNAL(errorOccurred(QAbstractSocket::SocketError)),this,SLOT(onError()));
}

MyWidget::~MyWidget()
{
    delete ui;
}

//发送槽函数
void MyWidget::on_sendButton_clicked()
{
    QString msg=ui->messageEdit->text();
    if(msg.isEmpty())
    {
        return; //发送消息不能为空
    }
    msg=this->userName+":"+msg;
    this->tcpSocket.write(msg.toUtf8());
    //清空发送框
    ui->messageEdit->clear();
}

//连接服务器槽函数
void MyWidget::on_connectButton_clicked()
{
    //如果离线状态建立连接,如在线状态断开连接
    if(this->status==false)
    {
        this->serverIP.setAddress(ui->serverIpEdit->text());
        this->serverPort=ui->serverPortEdit->text().toShort();
        this->userName=ui->userNameEdit->text();
        //向服务器发送连接 ,连接成功发送connected信号，失败发送error信号
        this->tcpSocket.connectToHost(this->serverIP,this->serverPort);
    }
    else
    {
        //向服务器发送离开聊天室的信息
        QString msg=this->userName+"：离开了聊天室";
        this->tcpSocket.write(msg.toUtf8());
        //和服务器端断开连接,发送 disconnected信号
        this->tcpSocket.disconnectFromHost();
    }
}
//连接成功槽函数
void MyWidget::onConnected()
{
    //链接成功在线转态
    this->status=true;
    ui->sendButton->setEnabled(true);
    ui->serverIpEdit->setEnabled(false);
    ui->serverPortEdit->setEnabled(false);
    ui->userNameEdit->setEnabled(false);
    ui->connectButton->setText("离开聊天室");
    //向服务器发送进入聊天室的提示信息
    QString msg=this->userName+"：进入了聊天室";
    this->tcpSocket.write(msg.toUtf8());
}
//断开连接槽函数
void MyWidget::onDisconnected()
{
    //断开连接离线转态
    this->status=false;
    ui->sendButton->setEnabled(false);
    ui->serverIpEdit->setEnabled(true);
    ui->serverPortEdit->setEnabled(true);
    ui->userNameEdit->setEnabled(true);
    ui->connectButton->setText("连接服务器");
}
//读槽函数
void MyWidget::onReadyRead()
{
    //返回当前套接字等待读取的套接字节数,如大于0就读取
    if(this->tcpSocket.bytesAvailable())
    {
        //接受消息
        QByteArray buff=this->tcpSocket.readAll();
        //显示消息
        ui->listWidget->addItem(buff);
        //列表窗口回滚显示最低窗口
        ui->listWidget->scrollToBottom();
    }
}
//链接失败槽函数
void MyWidget::onError()
{
    QMessageBox::critical(this,"ERROR",this->tcpSocket.errorString());
}

