#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTime>  //获取系统时间类
#include <QDebug>
#include <QFont>  //字体


class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
public slots:
    //获取系统时间的槽函数
    void getTime(void);

signals:
    //自定义信号，只需要申明不需要实现
    void mySignal(const QString &);
private:
    QLabel *m_label;       //显示时间
    QPushButton *m_button; //获取时间

};
#endif // MYDIALOG_H
