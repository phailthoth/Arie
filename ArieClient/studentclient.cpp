#include "studentclient.h"
#include "ui_studentclient.h"

studentClient::studentClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::studentClient)
{
    ui->setupUi(this);
}

studentClient::~studentClient()
{
    delete ui;
}
