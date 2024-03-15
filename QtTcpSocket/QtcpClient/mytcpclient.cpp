#include "mytcpclient.h"
#include "ui_mytcpclient.h"

MyTcpClient::MyTcpClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyTcpClient)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP客户端");
    ui->m_port->setText("8899");          // 初始化默认端口号
    ui->m_ipAddr->setText("127.0.0.1");   // 初始化默认IP
    ui->m_record->setReadOnly(true);      // 接收数据框为只读模式
    ui->m_disconnect->setDisabled(true);  // 初始化断开连接按钮不可用
    ui->m_sendMsg->setEnabled(false);     // 初始化发送按钮不可用
    //创建客户端套接字对象
    this->m_tcp=new QTcpSocket(this);

    //状态栏
    this->m_status=new QLabel;
    //状态栏添加状态图标
    this->m_status->setPixmap(QPixmap(":/image/1.ico").scaled(30,30));  // scaled设置图片的大小
    //将label添加到状态栏
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(this->m_status);
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //连接服务端成功信号
    connect(this->m_tcp,&QTcpSocket::connected,this,[=]{
        //修改状态栏
        this->m_status->setPixmap(QPixmap(":/image/2.ico").scaled(30,30));  // scaled设置图片的大小
        ui->m_record->append("客户端连与服务端已成功连接！！！");
        //客户端和服务端连接成功设置断开连接按钮可用
        ui->m_disconnect->setDisabled(false);
        //客户端和服务端连接成功设置连接按钮不可用
        ui->m_connect->setDisabled(true);
        //客户端和服务端连接成,设置发送按钮可用
        ui->m_sendMsg->setDisabled(false);
    });
    //客户端接收到数据信号
    connect(this->m_tcp,&QTcpSocket::readyRead,this,[=]{
        //接收数据
        QByteArray data=this->m_tcp->readAll();
        //将读取的数据放入记录历史数据的框中
        ui->m_record->append("接收服务端数据："+data);
    });
    //客户端接收到服务端断开连接
    connect(this->m_tcp,&QTcpSocket::disconnected,this,[=](){
        //接受服务器断开后客户端套接字也断开
        this->m_tcp->close();
        //释放套接字指针指向的内存，前面创建对象时已经指定了付对象this所以此处可以不用释放
        this->m_tcp->deleteLater(); //释放套机字对象的方法，其实就是封装了delete  this->m_tcp;
        //修改状态栏转态图片为未连接转态
        this->m_status->setPixmap(QPixmap(":/image/1.ico").scaled(30,30));  // scaled设置图片的大小
        ui->m_record->append("服务端已经断开！！！");
        //断开连接设置断开连接按钮不可用
        ui->m_disconnect->setDisabled(true);
        //断开连接设置连接成功设置连接按钮可用
        ui->m_connect->setDisabled(false);
        //断开连接设置发送按钮不可用
        ui->m_sendMsg->setDisabled(true);
    });
    //右上角关闭窗口时
    connect(this,&MyTcpClient::destroyed,this,[=](){
        this->m_tcp->close();        //关闭套接字对象
        this->m_tcp->deleteLater();  // 释放堆资源
    });
}

MyTcpClient::~MyTcpClient()
{
    delete ui;
}
////////////////////////////////////////////////////////////
//点击按钮链接服务器
void MyTcpClient::on_m_connect_clicked()
{
    //获取窗口输入的端口号
    unsigned short port=ui->m_port->text().toUShort();  //或写为quint16 port=ui->m_port->text().toInt();
    //获取窗口输入的ip
    QString ip=ui->m_ipAddr->text();

    //***连接服务器***
    this->m_tcp->connectToHost(QHostAddress(ip),port);
}
//点击按钮断开连接
void MyTcpClient::on_m_disconnect_clicked()
{
    //断开连接让套接字对象断开
    this->m_tcp->close();  //this->m_tcp->disconnectFromHost();  //断开套接字对象的另一种写法,close关闭时也会调用此方法
    //连接按钮可用
    ui->m_connect->setDisabled(false);
    //断开连接按钮不可用
    ui->m_disconnect->setDisabled(true);
    //断开按钮设置发送按钮不可用
    ui->m_sendMsg->setDisabled(true);
}
//点击按钮发送数据
void MyTcpClient::on_m_sendMsg_clicked()
{
    //获取当前系统时间
    this->dt=QDateTime::currentDateTime();
    QString strDt=this->dt.toString("yyyy/MM/dd HH:mm:ss ap：");
    //获取发送框中的数据转换为纯文本
    QString msg=strDt+ui->m_msg->toPlainText();
    //发送数据
    this->m_tcp->write(msg.toUtf8());
    //将发送的数据保存显示到历史数据框中
    ui->m_record->append("客户端发送数据："+msg);
    //发送成功清除发送框已发送数据
    ui->m_msg->clear();
}
