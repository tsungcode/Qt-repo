#include "widget.h"
#include "ui_widget.h"
#include <QPainter>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("第一窗口");
    this->resize(600,600);
    QPushButton* btn1=new QPushButton("下一页",this);
    btn1->move(500,560);
    //////////////////////////////////////////////////////////
    MyWidget *myWidget=new MyWidget();//创建第二窗体对象，注意不能写this

    connect(btn1,&QPushButton::clicked,[=](){
        myWidget->show();
        this->hide();
    });
    /////////////////////////////////////////////////////////
    connect(myWidget,&MyWidget::back,[=](){
        this->show();//显示主窗口
        myWidget->hide();//隐藏第二窗体
    });
}

Widget::~Widget()
{
    delete ui;

}
//绘制背景图片
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter *painter=new  QPainter(this);
    QPixmap pix;//定义一个图片控件
    pix.load(":/image/1.png");//加载资源图片
    //pix.scaled(this->width(),this->height());//设置图片大小（修改图片大小和窗口一样）
    //画家在主窗口绘图
    painter->drawPixmap(0,0,this->width(),this->height(),pix);//第1和2参数绘制坐标
}
