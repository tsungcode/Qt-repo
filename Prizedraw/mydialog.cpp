#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    this->m_index=0;
    this->m_istared=false;
    //设置随机数种子  当前时间
    //qsrand(QTime::currentTime().msec());
    qsrand(static_cast<unsigned>(QTime::currentTime().msec()));
    //加载所有图片到图片容器中
    this->loadImage(":/image");
    qDebug()<<"加载到图片容器中的图片个数："<<m_vecImage.size()<<endl;
}

MyDialog::~MyDialog()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////
//单击实现的槽函数
void MyDialog::on_pushButton_clicked()
{
    if(this->m_istared==false)
    {
        this->m_istared=true;            //摇奖开始
        this->m_timerId=startTimer(10);  //启动定时器
        ui->pushButton->setText("停止");
    }
    else {
        this->m_istared=false;            //摇奖结束
        this->killTimer(this->m_timerId); //关闭定时器
        ui->pushButton->setText("开始");
    }
}
////////////////////////////////////////////////////////////////////////////
//加载图片函数
void MyDialog::loadImage(const QString &path)
{
    QDir dir(path);
    //便利获取当前目录下所有图片
    QStringList list1=dir.entryList(QDir::Files); //获取当前路劲下所有文件,不包括子目录
    for(auto & img:list1)
    {
        QImage image(path+"/"+img);
        this->m_vecImage<<image;                //保存添加图片到图片向量容器中
    }
    //递归便利当前子目录中所有图片
    QStringList list2=dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);//获取当前目录下,和不包括点和点点中不然死递归
    for(auto &img:list2)
    {
        this->loadImage(path+"/"+img);
    }
}
///////////////////////////////////////////////////////////////////////////////////
// 定时器
void MyDialog::timerEvent(QTimerEvent *ev)
{
    Q_UNUSED(ev)
    //随机生成一个随机索引值
    this->m_index=qrand()%this->m_vecImage.size();//图片容器的大小
    this->update();
}
//////////////////////////////////////////////////////////////////////////////////
/// 绘图
void MyDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect=this->ui->frame->frameRect(); //获取rect的位置大小
    rect.translate(ui->frame->pos());        //平移rect坐标从(0,0)到frame位置
    painter.drawImage(rect,this->m_vecImage[this->m_index]);
}
