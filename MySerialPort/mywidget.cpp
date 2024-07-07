#include "mywidget.h"
#include "ui_mywidget.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    this->setPalette(QPalette(Qt::white));
    this->setAutoFillBackground(true);
    ui->Rec_textEdit->setReadOnly(true);

    this->serialport=new QSerialPort(this);  //创建串口对象

    //初始化遍历加载本地串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort _comPort;
        _comPort.setPort(info);
        if(_comPort.open(QIODevice::ReadWrite))
        {
             _comPort.close();
            ui->m_cobSeriport->addItem(info.portName());
        }
        //////////////////////////////////////////////////////////////////////////
    }
    connect(this->serialport,&QSerialPort::readyRead,this,&MyWidget::readData);
}
MyWidget::~MyWidget()
{
    delete ui;
}
//打开串口
void MyWidget::on_m_btnOpenSerialport_clicked(bool checked)
{
    if(checked)
    {
        //设置要打开的串口
        this->serialport->setPortName(ui->m_cobSeriport->currentText());//当前选中的串口
        //设置波特率
        this->serialport->setBaudRate(ui->m_cobBaud->currentText().toInt());
        //设置停止位
        this->serialport->setStopBits(QSerialPort::StopBits(ui->m_cobStop->currentText().toInt()));
        //设置数据位
        this->serialport->setDataBits(QSerialPort::DataBits(ui->m_cobData->currentText().toInt()));
        //设置校验位
        switch (ui->m_cobParity->currentIndex())
        {
        case 0:
            this->serialport->setParity(QSerialPort::NoParity);
            break;
        case 1:
            this->serialport->setParity(QSerialPort::EvenParity);
            break;
        case 2:
            this->serialport->setParity(QSerialPort::OddParity);
            break;
        case 3:
            this->serialport->setParity(QSerialPort::SpaceParity);
            break;
        case 4:
            this->serialport->setParity(QSerialPort::MarkParity);
            break;
        default:
            break;
        }

        //*******************初始化参数*************************
        // serialport->setBaudRate(QSerialPort::Baud9600);
        // serialport->setDataBits(QSerialPort::Data8);
        // serialport->setStopBits(QSerialPort::OneStop);
        // serialport->setParity(QSerialPort::NoParity);
        //*****************************************************

        //设置流控为无
        this->serialport->setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        if(!this->serialport->open(QIODevice::ReadWrite))
        {
            QMessageBox::information(this,"提示","打开串口失败");
            return;
        }
        //打开成功
        ui->m_btnOpenSerialport->setText("关闭串口");
        ui->m_cobSeriport->setDisabled(true);
        ui->m_cobBaud->setDisabled(true);
        ui->m_cobData->setDisabled(true);
        ui->m_cobParity->setDisabled(true);
        ui->m_cobStop->setDisabled(true);
        //ui->m_btnOpenSerialport->setStyleSheet("background-color: rgb(127, 255, 48)");
        QString str=QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
        ui->Rec_textEdit->append(str+":串口已经打开");
    }
    else
    {
        //关闭串口
        this->serialport->close();
        ui->m_btnOpenSerialport->setText("打开串口");
        ui->m_cobSeriport->setDisabled(false);
        ui->m_cobBaud->setDisabled(false);
        ui->m_cobData->setDisabled(false);
        ui->m_cobParity->setDisabled(false);
        ui->m_cobStop->setDisabled(false);
        //ui->m_btnOpenSerialport->setStyleSheet("background-color: rgb(55, 167, 255)");
        QString str=QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm:ss");
        ui->Rec_textEdit->append(str+":串口已经关闭");
    }
}

//读取数据槽函数
void MyWidget::readData()
{
    ui->Rec_textEdit->append(this->serialport->readAll());
}
//发送数据
void MyWidget::on_m_btnSend_clicked()
{
    if(ui->Send_textEdit->toPlainText().isEmpty())
    {
        return;
    }
    this->serialport->write(ui->Send_textEdit->toPlainText().toUtf8().data());
    ui->Send_textEdit->clear();
}
void MyWidget::on_m_btnClearn_clicked()
{
    ui->Rec_textEdit->clear();
}

