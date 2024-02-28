#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QLabel>


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
    void on_m_btnPrev_clicked();

    void on_m_btnNext_clicked();

private:
    virtual void paintEvent(QPaintEvent *)override; //事件

private:
    Ui::MyDialog *ui;
    int m_index; //图片索引
};
#endif // MYDIALOG_H
