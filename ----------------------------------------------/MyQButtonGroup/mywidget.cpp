#include "mywidget.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{

    //1、整体水平布局框架
    QHBoxLayout *HLayout=new QHBoxLayout(this);
    HLayout->setSpacing(0);
    HLayout->setContentsMargins(0,0,0,0);

    //2、左侧窗体
    this->LeftWiget=new QWidget(this);

    //3、右测窗体
    this->RightWiget=new QWidget(this);
    RightWiget->setMinimumWidth(450);    //最小宽度
    this->stackWidget=new QStackedWidget(RightWiget);
    QVBoxLayout *Rv=new QVBoxLayout(RightWiget);
    Rv->setSpacing(0);
    Rv->setContentsMargins(0,0,0,0);
    Rv->addWidget(stackWidget);  //垂直布局中加入stackWidget

    //整体布局
    HLayout->addWidget(this->LeftWiget);
    HLayout->addWidget(this->RightWiget);

    InitLeft();
    InitRight();
}

MyWidget::~MyWidget() {}
/////////////////////////////////////////
void MyWidget::InitLeft()
{
    this->btGroup=new QButtonGroup(this->LeftWiget);  //分组
    QVBoxLayout *VLayout=new QVBoxLayout(LeftWiget);
    VLayout->setSpacing(0);
    VLayout->setContentsMargins(0,0,0,0);
    QStringList list;
    list<<"按钮1"
         <<"按钮2"
         <<"按钮3"
         <<"按钮4"
         <<"按钮5";
    for(int i=0;i<list.count();i++)
    {
        QPushButton*btn=new QPushButton(LeftWiget);
        btn->setText(QString("%1").arg(list.at(i))); //设置按钮文字
        btn->setMinimumHeight(65);                   //设置最小高度
        btn->setMinimumWidth(100);                   //设置最小宽度
        btn->setCheckable(true);                     //可选中状态
        btn->setStyleSheet(R"(
                              QPushButton{font:15px;
                                          text-align:Left;
                                          color:red;
                            })");
        this->btGroup->addButton(btn,i);             //加入组
        VLayout->addWidget(btn);
        ///////////////////////////////////////////////////////////////////////////
        connect(btn,&QPushButton::clicked,this,[=](){
            qDebug()<<"按钮获取索引:"<<btGroup->checkedId();
        });
    }
    /////////////////////////////////////////////////////////////////////////////////
    connect(btGroup,&QButtonGroup::idClicked,this,[=](int id){
        this->stackWidget->setCurrentIndex(id);    //换右侧页面
        qDebug()<<id<<Qt::endl;
    });
    connect(btGroup,&QButtonGroup::buttonClicked,this,[=](QAbstractButton *button){
        qDebug()<<button->text()<<Qt::endl;
    });
    ////////////////////////////////////////////////////////////////////////////////
}

void MyWidget::InitRight()
{
    QStringList list;
    list<<"Label1"
         <<"Label2"
         <<"Label3"
         <<"Label4"
         <<"Label5";
    for(int i=0;i<list.count();i++)
    {
        QLabel *label=new QLabel(stackWidget);
        label->setText(QString("%1").arg(list.at(i)));
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("QLabel{color:green;font:15px;}");
        label->move(this->width()/2,this->height()/2);
        this->stackWidget->addWidget(label);
    }
}
