#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MyMainWindow; }
QT_END_NAMESPACE

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow();
public:
    void QMessageBoxFun();
    void QDialogFun();
    void QFontDialogFun();
    void QColorDialogFun();
    void QFileDialogFun();

private:
    Ui::MyMainWindow *ui;
};
#endif // MYMAINWINDOW_H
