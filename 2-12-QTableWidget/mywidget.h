#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

#include <QTableWidgetItem>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget {
    Q_OBJECT

public:

    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

public:

    void appendOneRow(QString name,
                      QString gender,
                      int     age,
                      QString province);

    void insertOneRow(int     row,
                      QString name,
                      QString gender,
                      int     age,
                      QString province);
private slots:

    void on_btnAppend_clicked();
    void on_btnInsert_clicked();
    void on_btnDelete_clicked();
    void on_btnModify_clicked();

    void onItemClicked(QTableWidgetItem *item);
    void on_btnStyleSheet_clicked();

    void onSelectionRadioButtonClicked();

private:

    Ui::MyWidget *ui;

    QButtonGroup *mButtonGroupSelection;
};
#endif // MYWIDGET_H
