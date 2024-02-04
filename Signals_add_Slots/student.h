#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QDebug>
#include <QString>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:
public slots:
    void treat(QString str);
    void treat();
private:
    static int number;
};

#endif // STUDENT_H
