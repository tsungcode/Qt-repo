#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>

class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MyTextEdit(QWidget *parent = nullptr);

signals:
protected:
    //当拖动文件在窗口/控件中进入是触发事件
    void dragEnterEvent(QDragEnterEvent*e)override;
    //当拖动文件在窗口/控件中离开时触发事件
    void dragLeaveEvent(QDragLeaveEvent *e)override;
    //当拖动文件在窗口/控件中移动时触发事件
    void dragMoveEvent(QDragMoveEvent *e)override;
    //当拖动文件在窗口/控件中释放时触发事件
    void dropEvent(QDropEvent *e)override;
    //**实现鼠标滚轮放大字体事件**
    void wheelEvent(QWheelEvent* e)override;
};

#endif // MYTEXTEDIT_H
