#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

private:
    Ui::MyWidget *ui;
    QTimer timer;
    qreal angle{0.0};

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};
#endif // MYWIDGET_H
