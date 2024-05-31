#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QColorDialog>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //**************************************************************************************************
    // 1. 添加形状

    ui->cboShape->addItem("Point", static_cast<int>(Shape::_Point));      //0
    ui->cboShape->addItem("Line", static_cast<int>(Shape::_Line));        //1

    ui->cboShape->addItem("Polyline", static_cast<int>(Shape::_Polyline));
    ui->cboShape->addItem("Polygon", static_cast<int>(Shape::_Polygon));

    ui->cboShape->addItem("Rectangle", static_cast<int>(Shape::_Rect));    //2
    ui->cboShape->addItem("Rounded Rectangle", static_cast<int>(Shape::_RoundedRect));

    ui->cboShape->addItem("Ellipse", static_cast<int>(Shape::_Ellipse));

    ui->cboShape->addItem("Arc", static_cast<int>(Shape::_Arc));
    ui->cboShape->addItem("Pie", static_cast<int>(Shape::_Pie));
    ui->cboShape->addItem("Chord", static_cast<int>(Shape::_Chord));

    ui->cboShape->addItem("Path", static_cast<int>(Shape::_Path));

    ui->cboShape->addItem("Text", static_cast<int>(Shape::_Text));
    ui->cboShape->addItem("Pixmap", static_cast<int>(Shape::_Pixmap));

    // 2. 设置画笔线宽
    ui->sbPenWidth->setRange(1, 10);

    // 3. 画笔线型
    // 3.1 线型-实线、虚线、点画线等
    ui->cboPenStyle->addItem("Solid", static_cast<int>(Qt::SolidLine));
    ui->cboPenStyle->addItem("Dash", static_cast<int>(Qt::DashLine));
    ui->cboPenStyle->addItem("Dot", static_cast<int>(Qt::DotLine));
    ui->cboPenStyle->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
    ui->cboPenStyle->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));
    ui->cboPenStyle->addItem("None", static_cast<int>(Qt::NoPen));

    // 3.2 画笔线型-线的端点的样式
    ui->cboPenCap->addItem("Flat", static_cast<int>(Qt::FlatCap));
    ui->cboPenCap->addItem("Square", static_cast<int>(Qt::SquareCap));
    ui->cboPenCap->addItem("Round", static_cast<int>(Qt::RoundCap));

    // 3.3 画笔连接-两根线的连接处的样式
    ui->cboPenJoin->addItem("Miter", static_cast<int>(Qt::MiterJoin));
    ui->cboPenJoin->addItem("Bevel", static_cast<int>(Qt::BevelJoin));
    ui->cboPenJoin->addItem("Round", static_cast<int>(Qt::RoundJoin));
    //******************************************************************************************************
    // 4. 画刷样式
    ui->cboBrushStyle->addItem(tr("Linear Gradient"), static_cast<int>(Qt::LinearGradientPattern));
    ui->cboBrushStyle->addItem(tr("Radial Gradient"), static_cast<int>(Qt::RadialGradientPattern));
    ui->cboBrushStyle->addItem(tr("Conical Gradient"), static_cast<int>(Qt::ConicalGradientPattern));
    ui->cboBrushStyle->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->cboBrushStyle->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->cboBrushStyle->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->cboBrushStyle->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->cboBrushStyle->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->cboBrushStyle->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->cboBrushStyle->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->cboBrushStyle->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->cboBrushStyle->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    ui->cboBrushStyle->addItem(tr("None"), static_cast<int>(Qt::NoBrush));
    //*******************************************************************************************************
    // 5. 信号槽
    // 图形形状
    connect(ui->cboShape, SIGNAL(textActivated(QString)), this, SLOT(shapeChanged()));  // 槽的参数可以比信号少
    //*********************************
    // 画笔宽度
    connect(ui->sbPenWidth, SIGNAL(valueChanged(int)), this, SLOT(penChanged()));
    // 画笔颜色
    connect(ui->btnPenColor, SIGNAL(clicked()), this, SLOT(onBtnPenColorClicked()));
    // 画笔样式
    connect(ui->cboPenStyle, SIGNAL(textActivated(QString)), this, SLOT(penChanged()));
    // 画笔末端
    connect(ui->cboPenCap, SIGNAL(textActivated(QString)), this, SLOT(penChanged()));
    // 画笔连接
    connect(ui->cboPenJoin, SIGNAL(textActivated(QString)), this, SLOT(penChanged()));
    //***********************************
    // 画刷颜色
    connect(ui->btnBrushColor, SIGNAL(clicked()), this, SLOT(onBtnBrushColorClicked()));
    // 画刷样式
    connect(ui->cboBrushStyle, SIGNAL(textActivated(QString)), this, SLOT(brushChanged()));
    //***********************************
    // 抗锯齿
    connect(ui->chkAntialiasing, SIGNAL(toggled(bool)), this, SLOT(antialiasChanged()));
    // 平移、旋转、缩放
    connect(ui->chkTransformation, SIGNAL(toggled(bool)), this, SLOT(transformChanged()));

    // 6. 初始化
    this->shapeChanged();

    // 回显画笔颜色在按钮  初始化画笔颜色
    QPalette pal = ui->btnPenColor->palette();
    pal.setColor(QPalette::Button, QColor(255, 0, 0));
    ui->btnPenColor->setPalette(pal);
    ui->btnPenColor->setAutoFillBackground(true);
    ui->btnPenColor->setFlat(true);

    // 回显画刷颜色在按钮  初始化画刷颜色
    pal = ui->btnBrushColor->palette();
    pal.setColor(QPalette::Button, QColor(0, 255, 0));
    ui->btnBrushColor->setPalette(pal);
    ui->btnBrushColor->setAutoFillBackground(true);
    ui->btnBrushColor->setFlat(true);
    //
    this->penChanged();
    this->brushChanged();

    ui->chkAntialiasing->setChecked(true);  //抗锯齿

    setWindowTitle("绘图");
}

MainWidget::~MainWidget()
{
    delete ui;
}

// 设置形状
void MainWidget::shapeChanged()
{
    int index = ui->cboShape->currentIndex();
    Shape shape = (Shape)ui->cboShape->itemData(index).toInt();
    ui->paintWidget->setShape(shape);//传递参数Shape
}

//点击选择设置画笔颜色
void MainWidget::onBtnPenColorClicked()
{
    QColor color = QColorDialog::getColor(QColor(255, 0, 0), this, "画笔颜色");

    if ( !color.isValid() ) {
        return;
    }

    // 回显画笔颜色到按钮
    QPalette pal = ui->btnPenColor->palette();  //调色盘
    pal.setColor(QPalette::Button, color);      //调色盘设置颜色
    ui->btnPenColor->setPalette(pal);           //设置调色盘
    ui->btnPenColor->setAutoFillBackground(true);
    ui->btnPenColor->setFlat(true);    //在qt中，想要去掉按钮的边框，让pushbutton按钮跟背景色融为一体，可以用函数QPushbutton::setFlat(true)来实现

    this->penChanged(); //调用设置画笔槽函数
}

// 设置画笔槽函数
void MainWidget::penChanged()
{
    // 获取画笔宽度
    int width = ui->sbPenWidth->value();

    // 获取画笔颜色
    QPalette pal = ui->btnPenColor->palette();
    QColor color = pal.color(QPalette::Button); //获取颜色
    //获取画笔样式
    int styleIndex = ui->cboPenStyle->currentIndex();
    Qt::PenStyle style = (Qt::PenStyle)ui->cboPenStyle->itemData(styleIndex).toInt();
    //获取端点样式
    int capIndex = ui->cboPenCap->currentIndex();
    Qt::PenCapStyle cap = Qt::PenCapStyle(ui->cboPenCap->itemData(capIndex).toInt());
    //获取连接样式
    int joinIndex = ui->cboPenJoin->currentIndex();
    Qt::PenJoinStyle join = Qt::PenJoinStyle(ui->cboPenJoin->itemData(joinIndex).toInt());

    ui->paintWidget->setPen(QPen(color, width, style, cap, join));  //设置画笔
}

//点击选中设置画刷颜色
void MainWidget::onBtnBrushColorClicked()
{
    QColor color = QColorDialog::getColor(QColor(255, 0, 0), this, "画刷颜色");
    if ( !color.isValid() ) {
        return;
    }

    // 回显画笔颜色到按钮
    QPalette pal = ui->btnBrushColor->palette();
    pal.setColor(QPalette::Button, color);
    ui->btnBrushColor->setPalette(pal);
    ui->btnBrushColor->setAutoFillBackground(true);
    ui->btnBrushColor->setFlat(true);
    //在qt中，想要去掉按钮的边框，让pushbutton按钮跟背景色融为一体，可以用函数QPushbutton::setFlat(true)来实现。

    this->brushChanged(); //调用设置画刷槽函数
}

// 设置画刷槽函数
void MainWidget::brushChanged()
{
    // 1. 获取画刷颜色
    QPalette pal = ui->btnBrushColor->palette();
    QColor color = pal.color(QPalette::Button);

    // 2. 获取画刷样式
    int index = ui->cboBrushStyle->currentIndex();
    Qt::BrushStyle style = (Qt::BrushStyle)ui->cboBrushStyle->itemData(index).toInt();

    // 3. 设置画刷
    if ( style == Qt::LinearGradientPattern ) {
        // 线性渐变
        //        QLinearGradient linearGradient(0, 0, 100, 100);
        QLinearGradient linearGradient(0, 50, 100, 50); //从2个点渐变
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, color);     //设置颜色
        linearGradient.setColorAt(1.0, Qt::black);
        ui->paintWidget->setBrush(linearGradient);
    } else if ( style == Qt::RadialGradientPattern ) {
        // 线径向渐变
        QRadialGradient radialGradient(50, 50, 50, 70, 70);  //圆心，半径，焦点
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        ui->paintWidget->setBrush(radialGradient);
    } else if ( style == Qt::ConicalGradientPattern ) {
        // 锥形渐变
        QConicalGradient conicalGradient(50, 50, 150); //圆心，开始角度
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);
        ui->paintWidget->setBrush(conicalGradient);
    } else if ( style == Qt::TexturePattern ) {
        // 纹理样式
        ui->paintWidget->setBrush(QBrush(QPixmap(":/images/brick.png")));
    } else {
        // 其他
        ui->paintWidget->setBrush(QBrush(color,style));//设置画刷
    }
}

// 设置抗锯齿
void MainWidget::antialiasChanged()
{
    ui->paintWidget->setAntialias(ui->chkAntialiasing->isChecked());
}

// 设置缩放和旋转
void MainWidget::transformChanged()
{
    ui->paintWidget->setTransform(ui->chkTransformation->isChecked());
}
