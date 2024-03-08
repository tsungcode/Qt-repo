#include "qtsendfileclient.h"
#include "ui_qtsendfileclient.h"

QtSendFileClient::QtSendFileClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtSendFileClient)
{
    ui->setupUi(this);

    //初始化窗口界面
    ui->m_ip->setText("127.0.0.1");
    ui->m_port->setText("8989");
    ui->progressBar->setRange(0,100);   //进度条范围 0-100
    ui->progressBar->setValue(0);       //设置进度条当前值 0

    //创建线程对象
    QThread *th=new QThread;
    //创建任务对象
    SendFile *work=new SendFile;
    //将任务对象移动到线程中,任务对象中方法执行时就会在线程中执行
    work->moveToThread(th);
    //启动子线程
    th->start();

    //主窗口接收到要连接服务器的信号后，去任务中执行连接服务器（子线程去执行连接）
    connect(this,&QtSendFileClient::startConnect,work,&SendFile::connectServer);//信号在主线程发出，执行在子线程中
    //主窗口发出发送文件信号，任务在子线程中去处理
    connect(this,&QtSendFileClient::sendFile,work,&SendFile::sendFile);
    //**********以下为处理子线程返回的信号*************
    //主线程处理子线程发出的连接服务器成功的信号
    connect(work,&SendFile::connectOK,this,[=](){
        QMessageBox::information(this,"服务器连接","恭喜,已经成功连接服务器!");
    });
    //主线程处理子线程发出的断开连接信号,进行资源的释放
    connect(work,&SendFile::gameOver,this,[=](){
        th->quit();
        th->wait();
        work->deleteLater(); //释放子线程任务对象
        th->deleteLater();
    });
    //根据任务对象发送的大小更新主窗口进度条
    connect(work,&SendFile::curPercent,ui->progressBar,&QProgressBar::setValue);
}

QtSendFileClient::~QtSendFileClient()
{
    delete ui;
}
//*连接服务器
void QtSendFileClient::on_m_connectServer_clicked()
{
    //获取窗口ip
    QString ip=ui->m_ip->text();
    //获取窗口端口号
    unsigned short port= ui->m_port->text().toUShort();
    //发送信号,让对应任务执行
    emit this->startConnect(port,ip);
}
//*选中文件
void QtSendFileClient::on_m_selFile_clicked()
{
    //获得要发送文件的绝对路径
    QString path=QFileDialog::getOpenFileName();
    if(path.isEmpty())  //判断选则的文件路径是否为空
    {
        QMessageBox::warning(this,"提示","选择的文件路径不能为空！");
        return;
    }
    //将获得的路径设置到当行文本框中显示
    ui->m_filePath->setText(path);
}
//*发送文件
void QtSendFileClient::on_m_sendFile_clicked()
{
    if(ui->m_filePath->text().isEmpty())
    {
        QMessageBox::information(this,"提示","发送的文件不能为空，请选则要发送的文件！");
        return;
    }
    //发送文件信号，让子线程去处理发送文件
    emit this->sendFile(ui->m_filePath->text());
}
