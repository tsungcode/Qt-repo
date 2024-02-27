#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>       //行编辑控件
#include <QLabel>
#include <QHBoxLayout>     //水平布局器
#include <QDoubleValidator>  //验证器

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private:
    QLineEdit *m_editX;   //左操作数
    QLineEdit *m_editY;   //右操作数
    QLineEdit *m_editZ;   //结果
    QLabel *m_label;      //+
    QPushButton *m_button;//=
public slots:
    void enabelButton(void);//自定义槽函数，使能等号按钮禁用的槽函数

    void calcClicked(void);//自定义槽函数，计算结果和显示的槽函数
};
#endif // MYDIALOG_H
