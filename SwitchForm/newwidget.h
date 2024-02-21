#ifndef NEWWIDGET_H
#define NEWWIDGET_H

#include <QWidget>
#include <QPushButton>

class NewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewWidget(QWidget *parent = nullptr);

signals:
    void back(); //发出返回信号

};

#endif // NEWWIDGET_H
