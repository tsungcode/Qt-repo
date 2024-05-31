#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    bool eventFilter(QObject* watched, QEvent* event);

    // 绘制高低温曲线
    void paintHigh();
    void paintLow();

    // 更新高低温
    void updateTemp();

private:
    Ui::Widget* ui;

    int mHighTemp[7] = {0};  //高温温度
    int mLowTemp[7]  = {0};  //低温温度
};
#endif    // WIDGET_H
