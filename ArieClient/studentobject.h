#ifndef STUDENTOBJECT_H
#define STUDENTOBJECT_H

#include <QWidget>
#include <QString>
#include <QDateTime>

namespace Ui {
class studentObject;
}

class studentObject : public QWidget
{
    Q_OBJECT

public:
    explicit studentObject(QWidget *parent = 0);
    ~studentObject();

    void setName(QString n);
    void setTime(QDateTime t);

private:
    Ui::studentObject *ui;

    QString name;
    QDateTime time;

};

#endif // STUDENTOBJECT_H
