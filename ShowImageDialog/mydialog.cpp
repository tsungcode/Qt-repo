#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    this->m_index=111;//初始化索引
}

MyDialog::~MyDialog()
{
    delete ui;
}
/////////////////////////////////////////////////////
//通过点击实现的槽函数   上一张
void MyDialog::on_m_btnPrev_clicked()
{
    if(this->m_index==111)
    {
        this->m_index=444;
    }
    else
    {
        this->m_index-=111;
    }
    ui->label->setText("第"+QString::number(this->m_index/111)+"图");
    this->update();
}
//通过点击实现的槽函数   下一张
void MyDialog::on_m_btnNext_clicked()
{
    if(this->m_index==444)
    {
        this->m_index=111;
    }
    else
    {
        this->m_index+=111;
    }
    ui->label->setText("第"+QString::number(this->m_index/111)+"图");
    this->update();
}
//绘图事件
void MyDialog::paintEvent(QPaintEvent *)
{
    qDebug()<<"绘图事件触发"<<endl;
    //1、创建画家
    QPainter painter(this);
    //2、获取绘图所在的矩形区域
    QRect rect=ui->frame->frameRect();

    qDebug()<<"平移前"<<rect<<endl;    //平移前 QRect(0,0 774x532)
    //3、坐标值平移，让painter和rect使用相同的坐标系 ,解决绘制的图片和实际frame有些错位问题
    rect.translate(ui->frame->pos());
    qDebug()<<"平移后"<<rect<<endl;   //平移后 QRect(13,13 774x532)

    //4、构建要绘制的图形对象
    QImage image(":/image/"+QString::number(m_index)+".jpg");
    //5、画家将image图片画到Rect区域
    painter.drawImage(rect,image);

    ///////////////////////////////////////////////////////////////
    //显示页数
    ui->label->setText("第"+QString::number(this->m_index/111)+"图");
}
