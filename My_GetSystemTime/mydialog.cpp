#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("获取系统时间");
    this->m_label=new QLabel(this);
    //设置label的显示效果  ：凹陷面板
    this->m_label->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    this->m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);     //设置水平和垂直居中对齐
    //设置label的字体大小
    QFont font;
    font.setPointSize(20);
    this->m_label->setFont(font);

    //创建button
    this->m_button=new QPushButton("获取当前系统时间",this);
    this->m_button->setFont(font);

    //创建垂直器布局
    QVBoxLayout *vLayout=new QVBoxLayout(this);
    vLayout->addWidget(this->m_label);
    vLayout->addWidget(this->m_button);
    this->setLayout(vLayout);

    //信号和槽实现方法1
    //connect(this->m_button,SIGNAL(clicked(void)),this,SLOT(getTime(void)));

    //自定义信号和槽实现方法2
    qDebug("GetTime");
    qDebug()<<"GetTime"<<endl;
    QTime time=QTime::currentTime(); //获取系统当前时间
    //将获取的系统时间转换为QString字符串形式
    QString str=time.toString("hh:mm:ss");

    connect(this->m_button,&QPushButton::clicked,[=](){emit this->mySignal(str);});
    connect(this,&MyDialog::mySignal,[=](){
        this->m_label->setText(str);
    });

}

MyDialog::~MyDialog()
{
}
/////////////////////////////////////////////////
void MyDialog::getTime()
{
    qDebug("GetTime");
    qDebug()<<"GetTime"<<endl;
    QTime time=QTime::currentTime(); //获取系统当前时间
    //将获取的系统时间转换为QString字符串形式
    QString str=time.toString("hh:mm:ss");
    this->m_label->setText(str);
}

