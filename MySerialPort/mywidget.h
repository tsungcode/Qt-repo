#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>  //串口信息类

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private slots:
    void on_m_btnOpenSerialport_clicked(bool checked);
    void readData();//读取数据

    void on_m_btnSend_clicked();

    void on_m_btnClearn_clicked();

private:
    Ui::MyWidget *ui;
    QSerialPort *serialport; //
};
#endif // MYWIDGET_H
