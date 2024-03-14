#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QChart>         //图表
#include <QChartView>     //视图
#include <QValueAxis>     //坐标
#include <QLineSeries>    //折线
#include <QSplineSeries>  //曲线
#include <QPen>

//QT_CHARTS_USE_NAMESPACE  //加入命名空间

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    //QChartView继承自QGraphicsVie,所以将窗口QGraphicsVie控件提升为QChartView

    //1、创建图表视图，ui控件已经有
    //2、创建图表
    QChart *chart=new QChart();

    //3、创建坐标轴
    QValueAxis *valueAxisX=new QValueAxis();
    QValueAxis *valueAxisY=new QValueAxis();

    //4、设置坐标轴的范围
    valueAxisX->setRange(0,5000);
    valueAxisY->setRange(0,300);

    //5、设置坐标轴标题和显示格式
    valueAxisX->setTitleText("时间/ms");
    valueAxisY->setTitleText("温度/度");
    //显示格式
    valueAxisX->setLabelFormat("%d"); //整数显示
    valueAxisY->setLabelFormat("%f"); //小数显示
    valueAxisX->setTickCount(10);    //将X轴间隔设置为10

    //6、图表添加坐标轴
    chart->createDefaultAxes(); //可不写
    chart->addAxis(valueAxisX,Qt::AlignBottom);//对齐方式为底部
    chart->addAxis(valueAxisY,Qt::AlignLeft);

    //7、设置图表标题,和图例
    chart->setTitle("温度与时间曲线");
    chart->legend()->setVisible(true);//设置图例可见

    //8、创建曲线对象添加点
    QSplineSeries *splineSeries=new QSplineSeries();
    //设置曲线名称
    splineSeries->setName("热力学第二定律");
    //曲线上添加点
    splineSeries->append(0,50);
    splineSeries->append(1000,150);
    splineSeries->append(2000,100);
    splineSeries->append(3000,50);
    splineSeries->append(4000,250);
    splineSeries->append(5000,150);

    //设置线的颜色
    QPen pen(QColor("blue"));

    //9、图表添加曲线
    chart->addSeries(splineSeries);

    //10、将曲线数据和坐标轴联系起来(曲线添加了数据和坐标轴关联起来)
    splineSeries->attachAxis(valueAxisX);
    splineSeries->attachAxis(valueAxisY);

    //11、将图表添加到视图中
    ui->chartView->setChart(chart);



}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}
