#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    /////////////////////////
    this->createDB();     //创建数据库
    this->createTable();  //创建数据库表
    this->queryTable();   //数据查询操作
    /////////////////////////
}

MyDialog::~MyDialog()
{
    delete ui;
}
////////////////////////////////////////////////////
// 创建数据库
void MyDialog::createDB()
{
    //1、添加数据库驱动
    this->db=QSqlDatabase::addDatabase("QSQLITE");
    //2、设置数据库名字（文件名）
    this->db.setDatabaseName("Student.db");  //第一次运行会自动创建
    //3、打开数据库
    if(db.open())
    {
        qDebug()<<"数据库创建/打开成功"<<endl;
    }
    else
    {
        qDebug()<<"数据库创建/打开失败"<<endl;
    }
}
////////////////////////////////////////////////////////
//创建描述学生成绩的数据表
void MyDialog::createTable()
{
    //创建执行Sql语句的query对象
    QSqlQuery query;
    //构建创建表的sql命令语句
    QString str=QString("CREATE TABLE student("
                        "id INT PRIMARY KEY NOT NULL,"
                        "name TEXT NOT NULL,"
                        "score REAL NOT NULL)");
    //执行创建表
    if(query.exec(str)==false)
    {
        qDebug()<<str<<endl;  //创建数据库表失败
    }
    else
    {
        qDebug()<<"创建数据库表成功"<<endl;
    }
}
/////////////////////////////////////////////////////////////////////
//数据的查询操作
void MyDialog::queryTable()
{
    //构建查询数据表中数据的sql命令语句
    QString str=QString("SELECT * FROM student");   //查询表中所有数据命令
    this->model.setQuery(str);   //执行查询命令，将查询的结果集保存在model中
    ui->tableView->setModel(&this->model);  //将查询的结果集显示在Ui控件中
}
////////////////////////////////////////////////////////////////////////////
//排序
void MyDialog::on_sort_Button_clicked()
{
    //获取根据要排序的列名
    QString value=ui->value_comboBox->currentText();
    //获取排序方式
    QString condition;
    if(ui->cond_comboBox->currentIndex()==0)
    {
        condition="ASC";     //升序排列
    }
    else if (ui->cond_comboBox->currentIndex()==1)
    {
        condition="DESC";   //降序排列
    }
    //构建排序的sql命令语句
    QString str=QString("SELECT * FROM student ORDER BY %1 %2").arg(value).arg(condition);
    //查询显示
    this->model.setQuery(str);             //执行排序查询命令，将查询的结果集保存在model中
    ui->tableView->setModel(&this->model); //将查询的结果集更新显示在Ui控件中
}
/////////////////////////////////////////////////////////////////////
//插入
void MyDialog::on_insert_Button_clicked()
{
    //创建执行Sql语句的query对象
    QSqlQuery query;
    //获取界面的数据
    int Id=ui->ID_Edit->text().toInt();
    QString Name=ui->Name_Edit->text();
    double Score=ui->Score_Edit->text().toDouble();
    //构建条插入命令
    QString str=QString("INSERT INTO student(id,name,score) VALUES(%1,'%2',%3)").arg(Id).arg(Name).arg(Score);
    //执行sql插入语句
    if(query.exec(str)==false)
    {
        qDebug()<<str<<endl;  //插入数据失败
    }
    else
    {
        qDebug()<<"插入数据成功"<<endl;
        //调取数据查询函数，插入成功后马上显示出来
        queryTable();
    }
}
////////////////////////////////////////////////////////////////////////////////
//删除数据   根据ID删除一条数据
void MyDialog::on_delete_Button_clicked()
{
    //创建执行Sql语句的query对象
    QSqlQuery query;
    //获取界面的要删除数据的ID数
    int Id=ui->ID_Edit->text().toInt();
    //构建删除的sql命令语句
    QString str=QString("DELETE FROM student WHERE id=%1").arg(Id);
    //执行删除sql语句
    if(query.exec(str)==false)
    {
        qDebug()<<str<<endl;  //删除数据失败
    }
    else
    {
        qDebug()<<"删除数据成功"<<endl;
        //调取数据查询函数，删除成功后马上更新显示出来
        queryTable();
    }
}
////////////////////////////////////////////////////////////
//修改  根据ID修改成绩
void MyDialog::on_update_Button_clicked()
{
    //创建执行Sql语句的query对象
    QSqlQuery query;
    //获取界面的要修改数ID对应的成绩
    int Id=ui->ID_Edit->text().toInt();
    double Score=ui->Score_Edit->text().toDouble();
    //构建修改数据sql命令
    QString str=QString("UPDATE student SET score=%1 WHERE id=%2").arg(Id).arg(Score);
    //执行修改sql语句
    if(query.exec(str)==false)
    {
        qDebug()<<str<<endl;  //修改数据失败
    }
    else
    {
        qDebug()<<"修改数据成功"<<endl;
        //调取数据查询函数，修改成功后马上更新显示出来
        queryTable();
    }
}
