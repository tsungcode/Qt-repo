#include "qtsendfileserve.h"
#include "ui_qtsendfileserve.h"

QtSendFileServe::QtSendFileServe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtSendFileServe)
{
    ui->setupUi(this);
    ui->m_port->setText("8989");   //初始化端口号
    //打印主线程ID
    qDebug()<<"服务器主线程ID="<<QThread::currentThreadId()<<endl;
    //监听服务器对象
    this->m_tcp=new QTcpServer(this);

    //监听到客户端连接信号会获取socket对象
    connect(this->m_tcp,&QTcpServer::newConnection,this,[=]()
    {
        //获取到套接字对象
        QTcpSocket *tcp=this->m_tcp->nextPendingConnection();
        //创建子线程对象
        RecvFile* subThread=new RecvFile(tcp);
        subThread->start();

        //子线程接收完数据信号，主线程进行资源释放
        connect(subThread,&RecvFile::over,this,[=]()
        {
            subThread->exit();
            subThread->wait();
            subThread->deleteLater(); //释放
            QMessageBox::information(this,"文件接收","文件已经接收完毕！！！");
        });
    });
}

QtSendFileServe::~QtSendFileServe()
{
    delete ui;
}

//服务器启动监听
void QtSendFileServe::on_m_setListen_clicked()
{
    if(ui->m_port->text().isEmpty())
    {
        QMessageBox::warning(this,"警告","端口号不能为空！！！");
        return;
    }
    //获取窗口端口信息
    unsigned short port=ui->m_port->text().toUShort();
    //监听
    this->m_tcp->listen(QHostAddress::Any,port);
}
