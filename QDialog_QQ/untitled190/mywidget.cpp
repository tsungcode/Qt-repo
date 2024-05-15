#include "mywidget.h"
#include "ui_mywidget.h"
#include <QSqlDatabase>
#include <QtGlobal>
#include <QDebug>
#include <QSlider>
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    qDebug()<<QT_VERSION_STR;
    qDebug()<<db.drivers();
    ////////////////////////////////////////////////////
    ///////////////////////////////////////////////////

    connect(ui->listWidget,&QListWidget::currentRowChanged,ui->tabWidget,&QTabWidget::setCurrentIndex);


}

MyWidget::~MyWidget()
{
    delete ui;
}
