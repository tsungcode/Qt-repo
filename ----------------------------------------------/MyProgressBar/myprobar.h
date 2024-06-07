#ifndef MYPROBAR_H
#define MYPROBAR_H

#include <QWidget>

class MyProBar : public QWidget
{
    Q_OBJECT
public:
    explicit MyProBar(QWidget *parent = nullptr);
    int value() const;            //获取当前值
    void setValue(int newValue);  //设置当前值

signals:
protected:
    void paintEvent(QPaintEvent *ev)override;
private:
    int m_value;     //当前值
    int m_max;       //最大值
    int m_min;       //最小值
};

#endif // MYPROBAR_H
