#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QResizeEvent>
#include <QDebug>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    //
    this->labViewCord=new QLabel("View坐标:");
    this->setMinimumWidth(200);
    ui->statusbar->addWidget(this->labViewCord);
    //
    this->labSceneCord=new QLabel("Scene坐标:");
    this->labSceneCord->setMinimumWidth(200);
    ui->statusbar->addWidget(this->labSceneCord);
    //
    this->labItemCord=new QLabel("Item坐标:");
    this->labItemCord->setMidLineWidth(200);
    ui->statusbar->addWidget(this->labItemCord);

    //设置光标
    ui->graphicsView->setCursor(Qt::CrossCursor); //设置view中鼠标状态为十字架形状
    ui->graphicsView->setMouseTracking(true);

    //信号和槽连接
    connect(ui->graphicsView,SIGNAL(mouseMovePoint(QPoint)),
            this,SLOT(on_mouseMove(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseClicked(QPoint)),
            this,SLOT(on_mouseClicked(QPoint)));
    ////////////////////////////////////////////////////
    initGraphics();
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::initGraphics()
{
    QRectF rect(-200,-100,400,200);          //设置Scene的区域大小
    this->Scene=new QGraphicsScene(rect);    //创建场景对象
    ui->graphicsView->setScene(this->Scene); //视图关联场景
    QGraphicsRectItem *item1=new QGraphicsRectItem(rect);  //矩形item
    item1->setFlags(QGraphicsItem::ItemIsFocusable|
                    QGraphicsItem::ItemIsSelectable);//设置itme是可聚焦和可选中的
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(Qt::red));
    pen.setStyle(Qt::SolidLine);
    item1->setPen(pen);
    //场景中加入item
    this->Scene->addItem(item1);

    //椭圆item
    QGraphicsEllipseItem *item2=new QGraphicsEllipseItem(-100,-50,200,100);
    item2->setBrush(QBrush(Qt::green));
    item2->setFlags(QGraphicsItem::ItemIsFocusable|
                    QGraphicsItem::ItemIsSelectable|
                    QGraphicsItem::ItemIsMovable);    //设置itme是可聚焦,可选中,可移动
    this->Scene->addItem(item2);

    //圆item
    QGraphicsEllipseItem *item3=new QGraphicsEllipseItem(-50,-50,100,100);
    item3->setBrush(QBrush(Qt::blue));
    item3->setPos(rect.right(),rect.bottom());        //设置item3的位置在一rect中心为坐标的，rect的宽和高位置处集右下角
    item3->setFlags(QGraphicsItem::ItemIsFocusable|
                    QGraphicsItem::ItemIsSelectable|
                    QGraphicsItem::ItemIsMovable);    //设置itme是可聚焦,可选中,可移动
    this->Scene->addItem(item3);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MyMainWindow::on_mouseMove(QPoint point)
{
    this->labViewCord->setText(QString::asprintf("View坐标：%d,%d",
                                                 point.x(),
                                                 point.y()));
    QPointF pointScene=ui->graphicsView->mapToScene(point);         //把View坐标转换为Scene坐标
    this->labSceneCord->setText(QString::asprintf("Scene坐标:%.0f,%.0f",
                                                  pointScene.x(),
                                                  pointScene.y()));
}

void MyMainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene=ui->graphicsView->mapToScene(point);             //view坐标转为Scene坐标
    QGraphicsItem *item=nullptr;
    item=this->Scene->itemAt(pointScene,ui->graphicsView->transform()); //获取当前Scene坐标有下没有itme
    if(item!=nullptr)  //如当前坐标下有item
    {
        QPointF pointItem=item->mapFromScene(pointScene);  //当前Scene坐标下有item,将Scene坐标转换为item坐标
        this->labItemCord->setText(QString::asprintf("Item坐标:%.0f,%.0f",
                                                     pointItem.x(),
                                                     pointItem.y()));
    }
    else  //如当前Scene坐标下没有item
    {
        this->labItemCord->setText("Item坐标:");
    }
}
//重写窗口大小变化
void MyMainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    ui->LabViewSize->setText(QString::asprintf("GraphicsView坐标:宽=%d,高=%d",
                                               ui->graphicsView->width(),
                                               ui->graphicsView->height()));
    QRectF rect=ui->graphicsView->sceneRect();  //获取SceneRect大小
    ui->LabSceneRect->setText(QString::asprintf("GraphicsView::SceneRect=(L,R,W,H)=%.0f,%.0f,%.0f,%.0f",
                                                rect.left(),
                                                rect.top(),
                                                rect.width(),
                                                rect.height()));
}

