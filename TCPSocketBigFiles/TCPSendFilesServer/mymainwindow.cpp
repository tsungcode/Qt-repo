#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer> //定时器

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("端口号为8899的服务器");
    ui->m_sendFiles->setEnabled(false);    //初始按钮不可用
    ui->m_selectFiles->setEnabled(false); //初始按钮不可用
    this->timer=new QTimer(this);

    /////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////
    this->m_tcpServer=new QTcpServer(this); //监听服务器
    //绑定开始监听
    this->m_tcpServer->listen(QHostAddress::Any,8899);

    //客户端连接服务端成功触发信号
    connect(this->m_tcpServer,&QTcpServer::newConnection,this,[=](){
        //获取到建立连接好的套接字
        this->m_tcpSocket=this->m_tcpServer->nextPendingConnection();

        //获取到看是谁连接的ip和端口号
        QString ip=this->m_tcpSocket->peerAddress().toString();
        quint16 port=this->m_tcpSocket->peerPort();
        //将IP和端口号组个包
        QString temp=QString("[%1:%2] 成功连接").arg(ip).arg(port);
        //弹窗提醒
        QMessageBox::information(this,"提醒",temp);
        //显示到窗口编辑区
        ui->m_textEdit->setPlainText(temp);

        //成功连接后设置按钮可用
        ui->m_sendFiles->setEnabled(true);    //初始按钮可用
        ui->m_selectFiles->setEnabled(true); //初始按钮可用
    });
    //定时器事件
    connect(timer,&QTimer::timeout,this,[=](){
        this->timer->stop();
        //////////////////////////////////////////////////////////////
        //定时器结束执行发送文件
        this->sendData();
        /////////////////////////////////////////////////////////////
    });
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

//选则要发送的文件路径
void MyMainWindow::on_m_selectFiles_clicked()
{
    //选中的文件对象路径
    QString path= QFileDialog::getOpenFileName(this,"选择文件,""../");
    if(!path.isEmpty())
    {
        //先清空下文件信息
        this->fileName.clear();
        this->fileSize=0;

        //获取要发送的文件信息
        QFileInfo ifo(path);
        this->fileName=ifo.fileName();  //文件名
        this->fileSize=ifo.size();     //文件大小

        this->sendSize=0;  //已发送文件为0

        //只读的方式打开文件
        this->file.setFileName(path);
        //打开文件
        bool isOK=this->file.open(QIODevice::ReadOnly); //只读方式打开
        if(isOK==false)
        {
            qDebug()<<"打开文件失败";
        }
        else
        {
            //将打开文件的路径再追加显示的窗口文本框
            ui->m_textEdit->append(path);
        }
    }
    else
    {
        qDebug()<<"文件路径不能为空";
    }
}

//发送文件
void MyMainWindow::on_m_sendFiles_clicked()
{
    //先发送文件大小和文件名作为发送的头部信息
    QString head=QString("%1##%2").arg(this->fileName).arg(this->fileSize);
    //发送头部信息
    qint64 len=this->m_tcpSocket->write(head.toUtf8()); //发送头部信息返回发送的大小
    if(len>0)
    {
        qDebug()<<"头部信息发送成功";
        //防止发送数据黏包，设置定时器发送头部信息成功后延时20毫秒
        this->timer->start(20);
    }
    else
    {
        //发送失败
        this->file.close();
        //关闭按钮啊
    }
    //再发送数据
}

//发送文件全局函数
void MyMainWindow::sendData()
{
    qint64 len=0;
    do{
        len=0; //每次度初始化为0
        char buff[1024*4]={0}; //每次发送4kb
        //每次读
        len=this->file.read(buff,sizeof(buff)); //返回每次 读取的大小
        //发送数据，度多少发送多少
        len=this->m_tcpSocket->write(buff,len); //返回每次 发送的大小

        //记录累加每次发送的大小
        this->sendSize+=len;
    }
    while(len>0); //每次发送的数据大于0就一直循环读取发送
    //为了安全起见在判断下
    if(this->sendSize==this->fileSize)
    {
        qDebug()<<"发送文件成功";
        ui->m_textEdit->append("文件发送完毕");
        this->file.close();
        this->m_tcpSocket->disconnectFromHost();
        this->m_tcpSocket->close();
    }
}
