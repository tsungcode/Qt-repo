#ifndef MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class My_MainWindow; }
QT_END_NAMESPACE

class My_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    My_MainWindow(QWidget *parent = nullptr);
    ~My_MainWindow();

private:
    Ui::My_MainWindow *ui;
};
#endif // MY_MAINWINDOW_H
