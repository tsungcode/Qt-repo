#ifndef MYPROPERTY_H
#define MYPROPERTY_H

#include <QWidget>
#include "myform.h" //

class MyForm;       //

QT_BEGIN_NAMESPACE
namespace Ui {
class MyProperty;
}
QT_END_NAMESPACE

class MyProperty : public QWidget
{
    Q_OBJECT

public:
    MyProperty(QWidget *parent = nullptr);
    ~MyProperty();

private:
    Ui::MyProperty *ui;
    MyForm *myform;
};
#endif // MYPROPERTY_H
