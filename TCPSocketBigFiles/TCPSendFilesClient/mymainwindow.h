#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>  //
#include <QFileDialog>
#include <QFile>


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

private slots:
    void on_m_connect_clicked();

private:
    Ui::MyMainWindow *ui;
    QTcpSocket *m_tcpSocket;   //套接字
    QFile file;              //文件对象
    QString fileName;        //文件名字
    qint64 fileSize;         //文件大小
    qint64 reciveSize;         //已经接收文件的大小
    bool isStart;             //第一次接收标志位
};
#endif // MYMAINWINDOW_H
