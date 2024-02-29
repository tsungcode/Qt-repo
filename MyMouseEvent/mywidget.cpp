#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    //////////////////////////////////////////
    this->resize(QSize(700,650));
    this->m_moveFlag=false; //不可移动状态
}

MyWidget::~MyWidget()
{
    delete ui;
}

/////////////////////////////////////////////////////
//鼠标按下
void MyWidget::mousePressEvent(QMouseEvent *event)
{
    //鼠标左键按下
    if(event->button()==Qt::LeftButton)
    {
        //判断按下鼠标的位置是否在label中
        //获取label的大小和宽度
        QRect ret=ui->label->frameRect();
        //移动ret矩形区域到label位置
        ret.translate(ui->label->pos());
        if(ret.contains(event->pos()))
        {
            qDebug()<<"鼠标左键按下";
            //可移动状态
            this->m_moveFlag=true;
            //记录鼠标相对于窗体的位置
            this->m_pose=event->pos()-ui->label->pos();

            ////////////////////////////////////
            qDebug()<<ui->label->pos()<<endl;
            qDebug()<<event->pos()<<endl;
            ////////////////////////////////////
        }
    }
}
//鼠标抬起
void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        //鼠标抬起不可移动
        this->m_moveFlag=false;
    }
}
//鼠标移动
void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(this->m_moveFlag)
    {
        //获取鼠标的新位置
        QPoint newPose=event->pos()-this->m_pose;//
        //获取主窗体的宽高
        QSize s1=this->size();
        //获取label的宽高
        QSize s2=ui->label->size();

        //可移动的区域：X轴：最小为0 最大为窗体宽度减去label的宽度
        if(newPose.x()<0)
        {
            newPose.setX(0);  //设置新位置x位置为0
        }
        else if (newPose.x()>(s1.width()-s2.width()))
        {
            newPose.setX(s1.width()-s2.width()); //设置新位置X
        }

         //可移动的区域：Y轴：最小为0 最大为窗体高度减去label的高度
        if(newPose.y()<0)
        {
            newPose.setY(0);
        }
        else if (newPose.y()>(s1.height()-s2.height()))
        {
            newPose.setY(s1.height()-s2.height());
        }
        ui->label->move(newPose);
    }
}

