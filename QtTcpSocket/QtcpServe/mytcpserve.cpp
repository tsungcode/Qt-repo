#include "mytcpserve.h"
#include "ui_mytcpserve.h"

MyTcpServe::MyTcpServe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyTcpServe)
{
    ui->setupUi(this);
    /////////////////////////////////////////////////////////////////////////////
    this->setWindowTitle("TCP服务端");
    ui->m_port->setText("8899");        // 初始化默认端口号
    ui->m_record->setReadOnly(true);    // 设置接收框为只读模式
    ui->m_sendMsg->setDisabled(true);   // 初始化设置发送按钮不可用
    ui->m_disconnect->setDisabled(true);// 初始化断开连接不可用
    this->m_tcp=Q_NULLPTR;              // 初始化套接字对象为空
    //创建服务端监听对象
    this->m_s=new QTcpServer(this);

    //状态栏
    this->m_status=new QLabel;
    //状态栏添加状态图标
    this->m_status->setPixmap(QPixmap(":/image/1.ico").scaled(30,30));  // scaled设置图片的大小
    //将label添加到状态栏
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    ui->statusbar->addWidget(this->m_status);
    //获取本机ip
    // QHostInfo info = QHostInfo::fromName(QHostInfo::localHostName());
    // QHostAddress localAddress = info.addresses().first();
    ui->statusbar->addPermanentWidget(new QLabel("本机IP:"+getIP()));
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////    
    //等待客户端的连接成功信号
    connect(this->m_s,&QTcpServer::newConnection,this,[=](){
        //服务端监听到后就获得一个套接字对象
        this->m_tcp=this->m_s->nextPendingConnection();
        //客户端连接成功修改状态栏状态图标
        this->m_status->setPixmap(QPixmap(":/image/2.ico").scaled(30,30));  // scaled设置图片的大小
        //连接成功获取连接服务器的客户端IP和端口号
        QString ip=this->m_tcp->peerAddress().toString();
        quint16 port=this->m_tcp->peerPort();
        QString temp=QString("客户端：[IP:%1+Port：%2]:服务端与客户端已成功连接！！！").arg(ip).arg(port);
        ui->m_record->append(temp);
        ui->m_sendMsg->setDisabled(false);    //设置发送按钮可用
        ui->m_disconnect->setDisabled(false);  //设置断开连接可用
        //*********************套接字接收到数据信号****************************
        connect(this->m_tcp,&QTcpSocket::readyRead,this,[=](){
            //接收数据
            QByteArray data=this->m_tcp->readAll();
            //将读取的数据放入记录历史数据的框中
            ui->m_record->append("接收客户端数据："+data);
        });
        //***********************套接字接收到客户端断开连接信号********************
        connect(this->m_tcp,&QTcpSocket::disconnected,this,[=](){
            //套接字断开
            this->m_tcp->close();
            //释放套接字指针指向的内存
            this->m_tcp->deleteLater(); //释放套机字对象的方法，其实就是封装了delete  this->m_tcp;
            //修改状态栏转态图片为未连接转态
            this->m_status->setPixmap(QPixmap(":/image/1.ico").scaled(30,30));  // scaled设置图片的大小
            //客户端断开,设置监听按钮可以用
            ui->m_setListen->setDisabled(false);  // 此步也可以用设置按钮不可用 ui->m_setListen->setEnabled(false);
            ui->m_sendMsg->setDisabled(true);     // 断开连接设置发送按钮不可用
            ui->m_disconnect->setDisabled(true);  // 客户端断开连接设置服务端断开连接不可用
            ui->m_record->append("客户端已断开！！！");
        });
        //右上角关闭窗口时触发事件
        connect(this,&MyTcpServe::destroyed,this,[=](){
            this->m_s->close();      //关闭监听服务器
            this->m_s->deleteLater();  //释放堆资源
            if(this->m_tcp!=Q_NULLPTR)
            {
                this->m_tcp->close();      //关闭套接字对象
                this->m_tcp->deleteLater(); // 释放堆资源
            }
        });
    });

} // 构造结束

MyTcpServe::~MyTcpServe()
{
    delete ui;
}

//点击按钮启动监听服务
void MyTcpServe::on_m_setListen_clicked()
{
    //获取端口号
    unsigned short port=ui->m_port->text().toUShort();
    //启动服务端监听
    this->m_s->listen(QHostAddress::Any,port);
    //启动监听后监听按钮变为不可用状态
    ui->m_setListen->setDisabled(true);  // 此步也可以用设置按钮不可用 ui->m_setListen->setEnabled(false);
    ui->m_disconnect->setDisabled(false); // 设置断开连接可用
    ui->m_record->append("服务端以开始监听！！！");
}
//点击发送数据
void MyTcpServe::on_m_sendMsg_clicked()
{
    //获取当前系统时间
    this->dt=QDateTime::currentDateTime();
    QString strDt=this->dt.toString("yyyy/MM/dd HH:mm:ss ap：");
    //获取发送框中的数据转换为纯文本
    QString msg=strDt+ui->m_msg->toPlainText();
    //发送数据
    this->m_tcp->write(msg.toUtf8());
    //将发送的数据保存显示到历史数据框中
    ui->m_record->append("服务端发送数据："+msg);
    //发送成功清除发送框已发送数据
    ui->m_msg->clear();
}
//点击断开连接
void MyTcpServe::on_m_disconnect_clicked()
{
    this->m_s->close(); // 关闭监听服务器
    if(this->m_tcp!=Q_NULLPTR)
    {
         this->m_tcp->disconnectFromHost();    //关闭套接字   或用：this->m_tcp->close();
    }
    ui->m_setListen->setDisabled(false);  // 断开连接设置监听可用
    ui->m_sendMsg->setDisabled(true);     // 断开连接设置发送按钮不可用
    ui->m_disconnect->setDisabled(true);  //断开连接设置断开连接不可用
}
//获取本机IP方法
QString MyTcpServe::getIP()
{
    foreach (QHostAddress ptr , QNetworkInterface::allAddresses())
    {
        if(ptr.protocol() == QAbstractSocket::IPv4Protocol)
        {// 获取ipv4地址
            if(!ptr.isLoopback()){  // 过滤本地回环127.0.0.1
                return ptr.toString();
            }
        }
    }
    return "无法获取本机IP";
}

