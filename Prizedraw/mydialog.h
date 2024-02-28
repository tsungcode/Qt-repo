#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPainter>
#include <QDir>
#include <QTime>
#include <QVector>
#include <QImage>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MyDialog; }
QT_END_NAMESPACE

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_pushButton_clicked();

private:
    //加载图片到容器
    void loadImage(const QString &path);
    virtual void timerEvent(QTimerEvent *ev)override;  //定时器
    virtual void paintEvent(QPaintEvent *)override;  //绘图

private:
    Ui::MyDialog *ui;
    QVector<QImage> m_vecImage;  //图片容器
    int m_index;                 //图片在容器中的索引
    int m_timerId;               //定时器id
    bool m_istared;              //按钮状态
};
#endif // MYDIALOG_H
