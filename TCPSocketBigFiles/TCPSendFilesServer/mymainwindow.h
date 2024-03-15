#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>   //服务器
#include <QTcpSocket>   //套接字
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>  //文件信息类
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyMainWindow;
}
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();

    void sendData();//发送文件全局函数

private slots:
    void on_m_selectFiles_clicked();

    void on_m_sendFiles_clicked();

private:
    Ui::MyMainWindow *ui;
    QTcpServer*m_tcpServer;  //服务器
    QTcpSocket *m_tcpSocket; //套接字
    QFile file;              //文件对象
    QString fileName;        //文件名字
    qint64 fileSize;         //文件大小
    qint64 sendSize;         //已经发送文件的大小
    QTimer *timer;           //定时器
};
#endif // MYMAINWINDOW_H
