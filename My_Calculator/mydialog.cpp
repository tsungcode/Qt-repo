#include "mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("计算器");
    this->resize(500,200);

    this->m_editX=new QLineEdit(this);            //左操作数值
    this->m_editX->setAlignment(Qt::AlignCenter); //设置左操作数文本居中对齐
    //设置数字验证器，只能输入数字形式内容,行编辑控件就只能输入数字了,如不能输入文本
    this->m_editX->setValidator(new QDoubleValidator(this));

    this->m_editY=new QLineEdit(this);            //右操作数值
    this->m_editY->setAlignment(Qt::AlignCenter); //设置右操作数文本居中对齐
    //设置数字验证器，只能输入数字形式内容,行编辑控件就只能输入数字了,如不能输入文本
    this->m_editY->setValidator(new QDoubleValidator(this));

    //显示结果
    this->m_editZ=new QLineEdit(this);
    this->m_editZ->setAlignment(Qt::AlignCenter);
    this->m_editZ->setReadOnly(true); //设置为只读

    //操作符
    this->m_label=new QLabel("+",this);

    //计算按钮=
    this->m_button=new QPushButton("=",this);
    this->m_button->setEnabled(false); //设置按钮默认为禁用转态
    //创建布局器
    QHBoxLayout *hLayout=new QHBoxLayout(this);
    //将控件依次添加到布局器中
    hLayout->addWidget(this->m_editX);
    hLayout->addWidget(this->m_label);
    hLayout->addWidget(this->m_editY);
    hLayout->addWidget(this->m_button);
    hLayout->addWidget(this->m_editZ);
    //设置布局器，将布局应用到窗口
    this->setLayout(hLayout);

    //信号和槽函数的连接,左右操作数文本改变时发送信号
    connect(this->m_editX,SIGNAL(textChanged(QString)),this,SLOT(enabelButton(void)));
    connect(this->m_editY,SIGNAL(textChanged(QString)),this,SLOT(enabelButton(void)));
    //点击=计算时信号和槽函数的连接
    connect(this->m_button,SIGNAL(clicked(void)),this,SLOT(calcClicked(void)));
}
//自定义槽函数
void MyDialog::enabelButton()
{
    bool bXOK,bYOK;
    //获取行编辑控件中输入的文本
    //toDouble 将行编辑控件输入的文本转换为double,参数保存转换是否成功
    this->m_editX->text().toDouble(&bXOK);  //做操作数校验
    this->m_editY->text().toDouble(&bYOK);  //右操作数校验
    //设置按钮可用
    this->m_button->setEnabled(bXOK&&bYOK); //左右操作数校验通过设置计算按钮=可用状态
}
//自定义槽函数
void MyDialog::calcClicked()
{
    double ret=this->m_editX->text().toDouble()+this->m_editY->text().toDouble();
    QString str=QString::number(ret);
    this->m_editZ->setText(str);
}

MyDialog::~MyDialog()
{
}

