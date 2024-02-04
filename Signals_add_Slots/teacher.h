#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <string>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    void hungry(QString str);
    void hungry();

};

#endif // TEACHER_H
