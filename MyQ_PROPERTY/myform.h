#ifndef MYFORM_H
#define MYFORM_H

#include <QWidget>

namespace Ui {
class MyForm;
}

class MyForm : public QWidget
{
    Q_OBJECT

    //Q_PROPERTY自定义属性        宏
    Q_PROPERTY(int number READ number WRITE setNumber NOTIFY NumberCharged) //宏

public:
    explicit MyForm(QWidget *parent = nullptr);
    ~MyForm();

    /////////////////
    int number()const;           //READ
    void setNumber(int n);       //WRITE
signals:
    void NumberCharged();   //属性的信号

private:
    Ui::MyForm *ui;
    int num;  //
};

#endif // MYFORM_H
