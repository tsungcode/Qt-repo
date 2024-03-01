#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QSqlDatabase>    //数据库链接
#include <QSqlQuery>       //数据库查询
#include <QSqlQueryModel>  //数据库查询结果集
#include <QSqlError>       //数据库操作错误原因
#include <QDebug>
#include <QMessageBox>

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
    void  createDB();    // 创建数据库
    void createTable();  //创建数据表
    void queryTable();   //数据的查询操作

private slots:
    void on_sort_Button_clicked();

    void on_insert_Button_clicked();

    void on_delete_Button_clicked();

    void on_update_Button_clicked();

private:
    Ui::MyDialog *ui;
    QSqlDatabase db;      //建立Qt和数据库链接
    QSqlQueryModel model; //保存查询的结果集
};
#endif // MYDIALOG_H
