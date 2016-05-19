#include "teacherclient.h"
#include "ui_teacherclient.h"

teacherClient::teacherClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::teacherClient){
    ui->setupUi(this);
}

teacherClient::~teacherClient(){
    delete ui;
}
