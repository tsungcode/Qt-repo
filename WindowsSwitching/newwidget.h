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
    void Back();

};

#endif // NEWWIDGET_H
