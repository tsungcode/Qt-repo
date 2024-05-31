#include "mywidget.h"
#include "ui_mywidget.h"

#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    //***************************************************************************************
    // 1. 初始化列表控件
    // 1.1 共有4列，并添加列的名称
    ui->twStudent->setColumnCount(4);

    QStringList horizontalHeader;
    horizontalHeader << "姓名";
    horizontalHeader << "性别";
    horizontalHeader << "年龄";
    horizontalHeader << "籍贯";
    ui->twStudent->setHorizontalHeaderLabels(horizontalHeader);

    // 1.2 设置列的宽度
    // 先设置自适应宽度，再单独设置某一列的宽度规则
    ui->twStudent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //行拉伸填充满tableWidget
        // 先自适应宽度
    // 然后，可以单独设置某一列根据内容调整宽度
    //    ui->twStudent->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    // 或者，可以单独设置某一列为固定宽度
    //    ui->twStudent->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    //    ui->twStudent->setColumnWidth(0, 80);

    // 1.3 添加几行初始化数据
    this->appendOneRow("李雷",  "男", 12, "广东");
    this->appendOneRow("韩梅梅", "女", 11, "北京");
    this->appendOneRow("林涛",  "男", 13, "上海");

    //***************************************************************************************
    // 2. 设置行表头是否显示
    // 首先根据在属性窗口中设置的属性，初始化复选框
    if (ui->twStudent->horizontalHeader()->isHidden())//行表头隐藏为true时
    {
        ui->cboHHeader->setChecked(false);
    } else {
        ui->cboHHeader->setChecked(true);
    }

    // 点击复选框时，显示或者隐藏行表头
    connect(ui->cboHHeader, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            ui->twStudent->horizontalHeader()->show();
        } else if (state == Qt::Unchecked) {
            ui->twStudent->horizontalHeader()->hide();
        }
    });

    //***************************************************************************************
    // 3. 设置列表头是否显示
    // 首先根据在属性窗口中设置的属性，初始化复选框
    if (ui->twStudent->verticalHeader()->isHidden())
    {
        ui->cboVHeader->setChecked(false);
    } else {
        ui->cboVHeader->setChecked(true);
    }

    // 点击复选框时，显示或者隐藏列表头
    connect(ui->cboVHeader, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            ui->twStudent->verticalHeader()->show();
        } else if (state == Qt::Unchecked) {
            ui->twStudent->verticalHeader()->hide();
        }
    });

    //***************************************************************************************
    // 4. 交替显示行的背景色
    // 首先根据在属性窗口中设置的属性，初始化复选框
    if (ui->twStudent->alternatingRowColors()) {
        ui->cboAlternate->setChecked(true);
    } else {
        ui->cboAlternate->setChecked(false);
    }

    // 点击复选框时，使能或者禁能交替背景色
    connect(ui->cboAlternate, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            ui->twStudent->setAlternatingRowColors(true);
        } else if (state == Qt::Unchecked) {
            ui->twStudent->setAlternatingRowColors(false);
        }
    });

    //***************************************************************************************
    // 5. 设置单元格是否可编辑
    // 首先根据在属性窗口中设置的属性，初始化复选按钮       AbstractItemView::NoEditTriggers 0 不可编辑
    int trigger = ui->twStudent->editTriggers();

    if (trigger == QAbstractItemView::NoEditTriggers) {
        ui->cboEditCell->setChecked(false);
    } else {
        ui->cboEditCell->setChecked(true);
    }

    // 点击复选按钮时，使能或者禁能单元格编辑
    connect(ui->cboEditCell, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            // 当双击单元格/选中单元格然后单击/按下编辑键F2，都可以编辑单元格。
            ui->twStudent->setEditTriggers(QAbstractItemView::DoubleClicked |
                                           QAbstractItemView::SelectedClicked |
                                           QAbstractItemView::EditKeyPressed);  //  按F2编辑
        } else if (state == Qt::Unchecked) {
            ui->twStudent->setEditTriggers(QAbstractItemView::NoEditTriggers); //不能编辑
        }
    });

    //***************************************************************************************
    // 6. 设置行选择还是单元格选择
    // 首先根据在属性窗口中设置的属性，初始化单选按钮的选中状态
    int selectionBehavior = ui->twStudent->selectionBehavior();

    if (selectionBehavior == QAbstractItemView::SelectItems)
    {
        ui->rbCell->setChecked(true);
    } else if (selectionBehavior == QAbstractItemView::SelectRows)
    {
        ui->rbRow->setChecked(true);
    }
    else if(selectionBehavior == QAbstractItemView::SelectColumns)
    {
        ui->rbCol->setChecked(true);
    }

    // 点击单选按钮时，使能单元格选中或者行选中
    this->mButtonGroupSelection = new QButtonGroup(this);
    this->mButtonGroupSelection->addButton(ui->rbCell, 0);  //单元格
    this->mButtonGroupSelection->addButton(ui->rbRow,  1);  //行
    this->mButtonGroupSelection->addButton(ui->rbCol,  2);  //列
    connect(ui->rbCell, &QRadioButton::clicked,this,&MyWidget::onSelectionRadioButtonClicked); //单元格
    connect(ui->rbRow,&QRadioButton::clicked,this,&MyWidget::onSelectionRadioButtonClicked);   //行
    connect(ui->rbCol,&QRadioButton::clicked,this,&MyWidget::onSelectionRadioButtonClicked);  //列

    //***************************************************************************************
    // 7. 点击单元格时，将对应行的数据显示到文本框
    connect(ui->twStudent,&QTableWidget::itemClicked,this,&MyWidget::onItemClicked);
}

/*************************
**************************/
MyWidget::~MyWidget()
{
    delete ui;
}

//********添加数据
void MyWidget::appendOneRow(QString name, QString gender, int age, QString province)
{
    // 获取当前行数
    int count = ui->twStudent->rowCount();

    qDebug() << "current count:" << count;

    // 设置当前行数
    ui->twStudent->setRowCount(count + 1);

    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *genderItem = new QTableWidgetItem(gender);
    QTableWidgetItem *ageItem = new QTableWidgetItem(QString::number(age));
    QTableWidgetItem *provinceItem = new QTableWidgetItem(province);

    nameItem->setTextAlignment(Qt::AlignCenter);
    genderItem->setTextAlignment(Qt::AlignCenter);
    ageItem->setTextAlignment(Qt::AlignCenter);
    provinceItem->setTextAlignment(Qt::AlignCenter);

    ui->twStudent->setItem(count, 0,     nameItem);  //第一列
    ui->twStudent->setItem(count, 1,   genderItem);  //第二列
    ui->twStudent->setItem(count, 2,      ageItem);  //第三列
    ui->twStudent->setItem(count, 3, provinceItem);  //第四列
}
//*********插入数据
void MyWidget::insertOneRow(int row,QString name,QString gender,int age,QString province)
{
    ui->twStudent->insertRow(row); //插入空行

    // 上面 insertRow 只是插入一个空行，需要手动添加每个单元格的内容
    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *genderItem = new QTableWidgetItem(gender);
    QTableWidgetItem *ageItem = new QTableWidgetItem(QString::number(age));
    QTableWidgetItem *provinceItem = new QTableWidgetItem(province);

    nameItem->setTextAlignment(Qt::AlignCenter);
    genderItem->setTextAlignment(Qt::AlignCenter);
    ageItem->setTextAlignment(Qt::AlignCenter);
    provinceItem->setTextAlignment(Qt::AlignCenter);

    ui->twStudent->setItem(row, 0,     nameItem);
    ui->twStudent->setItem(row, 1,   genderItem);
    ui->twStudent->setItem(row, 2,      ageItem);
    ui->twStudent->setItem(row, 3, provinceItem);
}

//***点击添加行
void MyWidget::on_btnAppend_clicked()
{
    QString name = ui->leName->text();
    QString gender = ui->leGender->text();
    int     age = ui->leAge->text().toInt();
    QString province = ui->leProvince->text();

    appendOneRow(name, gender, age, province);
}
//***点击插入行
void MyWidget::on_btnInsert_clicked()
{
    QString name = ui->leName->text();
    QString gender = ui->leGender->text();
    int     age = ui->leAge->text().toInt();
    QString province = ui->leProvince->text();

    // 获取当前选中的行号
    int currentRow = ui->twStudent->currentRow();

    insertOneRow(currentRow, name, gender, age, province); //插入为选中的行
}
//***删除当前行
void MyWidget::on_btnDelete_clicked()
{
    // 获取当前选中的行号
    int currentRow = ui->twStudent->currentRow();

    ui->twStudent->removeRow(currentRow); //删除选中的行
}
//***修改当前行
void MyWidget::on_btnModify_clicked()
{
    QString name = ui->leName->text();
    QString gender = ui->leGender->text();
    int     age = ui->leAge->text().toInt();
    QString province = ui->leProvince->text();

    // 获取当前选中的行号
    int currentRow = ui->twStudent->currentRow();

    QTableWidgetItem *nameItem = new QTableWidgetItem(name);
    QTableWidgetItem *genderItem = new QTableWidgetItem(gender);
    QTableWidgetItem *ageItem = new QTableWidgetItem(QString::number(age));
    QTableWidgetItem *provinceItem = new QTableWidgetItem(province);

    nameItem->setTextAlignment(Qt::AlignCenter);
    genderItem->setTextAlignment(Qt::AlignCenter);
    ageItem->setTextAlignment(Qt::AlignCenter);
    provinceItem->setTextAlignment(Qt::AlignCenter);

    ui->twStudent->setItem(currentRow, 0,     nameItem);
    ui->twStudent->setItem(currentRow, 1,   genderItem);
    ui->twStudent->setItem(currentRow, 2,      ageItem);
    ui->twStudent->setItem(currentRow, 3, provinceItem);
}

//*****选中的单元格显示在QLineEdit中
void MyWidget::onItemClicked(QTableWidgetItem *item)
{
    int row = item->row();  //获取选中的行数号

    QString name = ui->twStudent->item(row, 0)->text();
    QString gender = ui->twStudent->item(row, 1)->text();
    QString age = ui->twStudent->item(row, 2)->text();
    QString province = ui->twStudent->item(row, 3)->text();

    ui->leName->setText(name);
    ui->leGender->setText(gender);
    ui->leAge->setText(age);
    ui->leProvince->setText(province);
}
//*********************************************************************
//样式表设置
void MyWidget::on_btnStyleSheet_clicked()
{
    //单元格样式
   const QString cellStyle =
        R"(
        QTableView
        {
            text-align:center;
            background-color: rgba(255, 255, 255, 0);
            alternate-background-color:#e3edf9;
            font:14px "微软雅黑";
            color:#677483;
            gridline-color: #ccddf0;
        }
    )";
   //行表头样式
    const QString horizontalHeaderStyle =
        R"(
        QHeaderView::section {
            color: black;
            font:bold 14px "微软雅黑";
            text-align:center;
            height:32px;
            background-color: #d1dff0;
            border:1px solid #8faac9;
            border-left:none;
        }
    )";
    //列表头样式
    const QString verticalHeaderStyle =
        R"(
        QHeaderView::section {
            color: black;
            font:bold 14px "微软雅黑";
            width:60px;
            text-align:center;
            background-color: #d1dff0;
            border:1px solid #8faac9;
            border-left:none;
        }
    )";

    ui->twStudent->setStyleSheet(cellStyle);
    ui->twStudent->horizontalHeader()->setStyleSheet(horizontalHeaderStyle);
    ui->twStudent->verticalHeader()->setStyleSheet(verticalHeaderStyle);
}

//单元格选中还是行选中槽函数
void MyWidget::onSelectionRadioButtonClicked()
{
    int checkedId = mButtonGroupSelection->checkedId();

    if (checkedId == 0) //单元格选中
    {
        ui->twStudent->setSelectionMode(QAbstractItemView::SingleSelection);//设置选中模式为单行选中
        ui->twStudent->setSelectionBehavior(QAbstractItemView::SelectItems);
    } else if (checkedId == 1) //单元格所在行选中
    {
        ui->twStudent->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->twStudent->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
    else if(checkedId==2)  //单元格所在列选中
    {
        ui->twStudent->setSelectionMode(QAbstractItemView::MultiSelection);  //选中模式为多行或多列
        ui->twStudent->setSelectionBehavior(QAbstractItemView::SelectColumns);
    }
}
