#include "mytextedit.h"

#include <QApplication>
#include <QDragEnterEvent>
#include <QFile>
#include <QMimeData>//**

MyTextEdit::MyTextEdit(QWidget *parent)
    : QTextEdit{parent}
{
    this->setAcceptDrops(true); //允许接收drop事件
}
//**********************************************************************
//**********************************************************************
//当拖动文件在窗口/控件中进入是触发事件
void MyTextEdit::dragEnterEvent(QDragEnterEvent *e)
{
    //默认情况下窗口不接受拖动，设置允许拖动事件
    //默认情况下,窗口部件是不接受拖动的。Qt会自动改变光标来向用户说明这个窗口部件是不是有效的放下点
    e->acceptProposedAction();
    qDebug()<<"进入事件";
}
//当拖动文件在窗口/控件中离开时触发事件
void MyTextEdit::dragLeaveEvent(QDragLeaveEvent *e)
{
    Q_UNUSED(e);
    qDebug()<<"离开事件";
}
//当拖动文件在窗口/控件中移动时触发事件
void MyTextEdit::dragMoveEvent(QDragMoveEvent *e)
{
    Q_UNUSED(e);
    qDebug()<<"移动事件";
}
//当拖动文件在窗口/控件中释放时触发事件
void MyTextEdit::dropEvent(QDropEvent *e)
{
    qDebug()<<"释放事件";

    QList<QUrl> urls = e->mimeData()->urls();
    if ( urls.isEmpty() ) {
        return;
    }
    QString fileName = urls.first().toLocalFile();  //获取文件名
    QFile file(fileName);
    if ( file.open(QIODevice::ReadOnly) )
    {
        this->setPlainText(file.readAll());
    }
}
//********************************************************
//**实现鼠标滚轮放大字体事件**
void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    if ( QApplication::keyboardModifiers() == Qt::ControlModifier ) {  // 按下ctrl键的判断
        //多数鼠标类型的工作步长为15度，在这种情况下，delta值是120的倍数；即120单位* 1/8 = 15度
        // zoomIn/zoomOut可以直接修改字体大小
        if ( e->angleDelta().y() / 8 > 0 ) {  // 滚轮远离使用者, 进行放大
            this->zoomIn();
        } else {
            this->zoomOut();  // 进行缩小
        }
    } else {
        QTextEdit::wheelEvent(e);  // 调用父类的，否则无法实现文本的上下滚动。
    }
}
