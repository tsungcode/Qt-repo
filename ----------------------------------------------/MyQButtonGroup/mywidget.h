#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QButtonGroup>
#include <QStackedWidget>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    void InitLeft();
    void InitRight();
private:
    QWidget *LeftWiget;
    QWidget *RightWiget;
    QStackedWidget *stackWidget;
    QButtonGroup *btGroup;
};
#endif // MYWIDGET_H
