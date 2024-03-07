#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket *tcp,QObject *parent = nullptr);
protected:
    //重写QThread的修函数
    virtual void run() override;
signals:
    void over();  //子线程通知主线程信号
private:
    QTcpSocket *m_tcp; //

};

#endif // RECVFILE_H
