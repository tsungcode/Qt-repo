#include "mywidget.h"
#include "ui_mywidget.h"
#include <QMessageBox>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);

    this->serialport=new QSerialPort(this);

    //初始化遍历加载本地串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->m_cobSeriport->addItem(info.portName());
    }

   //////////////////////////////////////////////////////////////////////////
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
        this->serialport->setBaudRate(ui->m_CobBaud->currentText().toInt());
        //设置停止位
        this->serialport->setStopBits(QSerialPort::StopBits(ui->m_cobStop->currentText().toInt()));
        //设置数据位
        this->serialport->setDataBits(QSerialPort::DataBits(ui->m_cobStop->currentText().toInt()));
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

        //*****************************************************
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
        ui->m_cobSeriport->setDisabled(true);
        ui->m_CobBaud->setDisabled(true);
        ui->m_cobData->setDisabled(true);
        ui->m_cobParity->setDisabled(true);
        ui->m_cobStop->setDisabled(true);
        ui->m_btnOpenSerialport->setText("关闭串口");
        ui->m_btnOpenSerialport->setStyleSheet("background-color: rgb(127, 255, 48)");
    }
    else
    {
        //关闭串口
        this->serialport->close();
        ui->m_btnOpenSerialport->setStyleSheet("background-color: rgb(170, 170, 0)");
    }
}

//读取数据槽函数
void MyWidget::readData()
{
    ui->textEdit->append(this->serialport->readAll());
}

//发送数据
void MyWidget::on_m_btnSend_clicked()
{
    this->serialport->write(ui->textEdit_2->toPlainText().toUtf8().data());
    ui->textEdit_2->clear();
}

