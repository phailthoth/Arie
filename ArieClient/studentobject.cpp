#include "studentobject.h"
#include "ui_studentobject.h"

studentObject::studentObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentObject){

    name = "";
    time = QDateTime();

    ui->setupUi(this);
}

studentObject::~studentObject()
{
    delete ui;
}

void studentObject::setName(QString n){
    name = n;
}

void studentObject::setTime(QDateTime t){
    time = t;
}
