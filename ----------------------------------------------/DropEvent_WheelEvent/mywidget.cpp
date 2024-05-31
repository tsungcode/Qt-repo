#include "mywidget.h"
#include "ui_mywidget.h"
#include <QKeyEvent>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
}

MyWidget::~MyWidget()
{
    delete ui;
}

//键盘按下事件
void MyWidget::keyPressEvent(QKeyEvent *event)
{
    //两个组合键按下
    if((event->modifiers()==Qt::ControlModifier)&&(event->key()==Qt::Key_A))
    {
        qDebug()<<"Ctrl+A";
    }
    if((event->modifiers()==Qt::ShiftModifier) &&(event->key()==Qt::Key_B))
    {
        qDebug()<<"Shift+B";
    }
    if((event->modifiers()==Qt::AltModifier)&&(event->key()==Qt::Key_C))
    {
        qDebug()<<"Alt+C";
    }
    // 三键组合 Ctrl+Shift + D 的实现
    if ( (event->modifiers() == (Qt::ControlModifier|Qt::ShiftModifier )) && (event->key() == Qt::Key_E))
    {
        qDebug() << "CTRL + Shift + E";
    }
}
