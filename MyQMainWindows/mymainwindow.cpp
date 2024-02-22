#include "mymainwindow.h"
#include <QDebug>
#include <QMenuBar>   //菜单栏
#include <QMenu>      //菜单
#include <QToolBar>   //工具栏
#include <QStatusBar> //状态栏
#include <QDockWidget> //铆接部件
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(650,650);
    this->setWindowTitle("QMainWindow练习");

    /////////////////////////////创建菜单栏QMenuBar///////////////////////////////
    //1、创建菜单栏
    QMenuBar *menuBar=new QMenuBar(this);

    //2、将菜单栏添加到注窗口
    this->setMenuBar(menuBar);

    //3、创建菜单 QMenu
    QMenu *file=new QMenu("文件",this);
    QMenu *edit=new QMenu("编辑",this);
    QMenu *tool=new QMenu("工具",this);
    QMenu *help=new QMenu("帮助",this);

    //4、菜单栏添加菜单
    menuBar->addMenu(file);
    menuBar->addMenu(edit);
    menuBar->addMenu(tool);
    menuBar->addMenu(help);
    menuBar->addMenu(QString("直接添加菜单")); //直接添加
    menuBar->addMenu(QIcon(":/image/9.ico"),QString("直接加载图标和菜单")); //加载菜单ico图标

    //5、创建菜单项 QAction
    QAction *New=new QAction("新建",this);   //新建菜单项
    QAction *Open=new QAction("打开",this);  //新建菜单项
    QAction *Close=new QAction("关闭",this); //新建菜单项

    //6、菜单QMenu中添加菜单项QAction
    file->addSeparator();    //菜单项直接分割线
    file->addAction(New);
    file->addSeparator();    //菜单项直接分割线
    file->addAction(Open);
    file->addSeparator();    //菜单项直接分割线
    file->addAction(Close);
    file->addSeparator();    //菜单项直接分割线
    file->addAction(QString("直接添加菜单项"));
    file->addAction(QIcon(":/image/7.ico"),QString("直接加载图标和菜单")); //菜单项加载ico图标

    //7、菜单项QAction设置快捷方式
   New->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N)); //给菜单项添加快捷键的第一种写法
   Open->setShortcut(QKeySequence(tr("CTRL+O")));      //给菜单项添加快捷键的第二种写法
   Close->setShortcut(QKeySequence(QKeySequence::Close));//给菜单项添加快捷键的第三种写法

   //菜单项添加图标
   QPixmap pix;               //创建图片控件
   pix.load(":/image/4.ico"); //加载图片
   New->setIcon(QIcon(pix));  //设置菜单项ico
   Open->setIcon(QIcon(":/image/5.ico")); //菜单项直接添加ico方法
   Close->setIcon(QIcon(":/image/6.ico"));


   //8、菜单项QAction的信号和槽使用
   connect(New,&QAction::triggered,[=](){
       qDebug()<<"点击了新建按钮"<<endl;
   });

   /////////////////////////////创建工具栏QToolBar///////////////////////////////
   //1、创建工具栏
    QToolBar *toolBar=new QToolBar("工具栏1",this);

    //2、将工具栏添加到主窗口
    //this->addToolBar(toolBar);
    this->addToolBar(Qt::LeftToolBarArea,toolBar); //将工具栏添加到主窗口，且设置默认工具栏显示在左面

    //3、创建工具栏中的工具项 QAction
    QAction *newTool=new QAction("新建",this);
    QAction *openTool=new QAction("打开",this);
    QAction *quitTool=new QAction("退出",this);
    newTool->setIcon(QIcon(":/image/3.ico"));   //工具项加载ico图标

    //4、将工具项添加到工具栏
    toolBar->addAction(newTool);
    toolBar->addSeparator();    //工具项之间设置分割线
    toolBar->addAction(openTool);
    toolBar->addSeparator();    //工具项之间设置分割线
    toolBar->addAction(quitTool);

    //5、设置工具栏是否在主窗体浮动停留，默认是可以停留
    toolBar->setFloatable(false);   //false则不可以停留

    //6、设置工具栏是否可以移动
    //toolBar->setMovable(false);

    //7、设置工具移动后允许停留的位置
    toolBar->setAllowedAreas(Qt::BottomToolBarArea|Qt::TopToolBarArea); //设置移动后只能停留在上和下
     quitTool->setShortcut(QKeySequence::New); //设置工具项的快捷方式

    /////////////////////////////创建状态栏 QStatusBar ///////////////////////////////
    //1、创建状态栏
     QStatusBar *statusBar=new QStatusBar(this);

     //2、将转态栏添加到主窗口
     this->setStatusBar(statusBar);

     //创建lable
     QLabel *label1=new QLabel("左侧状态：",this);
     QLabel *label2=new QLabel("右侧状态：",this);

     //在状态栏添加label
     statusBar->addWidget(label1);          //添加到左侧
     statusBar->addPermanentWidget(label2); //添加到右侧

     /////////////////////////////创建铆接部件 QDockWidget///////////////////////////////
     //1、创建铆接部件
     QDockWidget *docWidget=new QDockWidget("这是一个铆接部件",this);

     //2、将铆接部件添加到主窗口
     this->addDockWidget(Qt::TopDockWidgetArea,docWidget);

     //3、设置铆接部件后期允许停靠的位置
     docWidget->setAllowedAreas(Qt::TopDockWidgetArea|Qt::BottomDockWidgetArea);

     //4、设置铆接部件移动后自动归位
     docWidget->setFeatures(QDockWidget::DockWidgetMovable);
     //docWidget->setFeatures(QDockWidget::DockWidgetFloatable);

     //5、铆接部件添加文本域
     QTextEdit *textEdit=new QTextEdit("这是铆接部件编辑区",this);
     docWidget->setWidget(textEdit);

     /////////////////////////////中心部件///////////////////////////////
     //1、创建文本域
     QTextEdit *text=new QTextEdit("这是中心部件编辑区",this);

     //2、中心部件添加文本域
     this->setCentralWidget(text);
     //text->setText("举头望明月\n低头思故乡");
}

MyMainWindow::~MyMainWindow()
{
}

