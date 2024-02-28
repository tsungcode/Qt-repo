#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MyDialog; }
QT_END_NAMESPACE

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private:
    Ui::MyDialog *ui;
};
#endif // MYDIALOG_H
