#ifndef QTSENDFILECLIENT_H
#define QTSENDFILECLIENT_H

#include <QMainWindow>
#include <QThread>
#include "sendfile.h"
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class QtSendFileClient; }
QT_END_NAMESPACE

class QtSendFileClient : public QMainWindow
{
    Q_OBJECT

public:
    QtSendFileClient(QWidget *parent = nullptr);
    ~QtSendFileClient();

private slots:
    void on_m_connectServer_clicked();

    void on_m_selFile_clicked();

    void on_m_sendFile_clicked();

signals:
    void startConnect(unsigned short,QString); //连接成功信号
    void sendFile(QString path);              //发送文件信号

private:
    Ui::QtSendFileClient *ui;
};
#endif // QTSENDFILECLIENT_H
