#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                        QMainWindow(parent),
                        ui(new Ui::MainWindow){
    ui->setupUi(this);

    setUp();

    sendID = 0;

    socket = new QUdpSocket(this);
    socket -> bind(QHostAddress::Any, port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

MainWindow::~MainWindow(){
    delete ui;
}

/*
 * For future additions, look at the ini file set up, it looks more efficient than this jumble.
 */

void MainWindow::setUp(){
    QFile configFile("./config.cfg");

    if(!configFile.open(QIODevice::ReadOnly)){
        ui->label->setText("Configuration file error - Not read.");
    }

    QTextStream configStream(&configFile);

    while(!configStream.atEnd()){
        QList<QString> item = configStream.readLine().split(" ");

        if(item.at(0).contains("ip-address") ||
           item.at(0).contains("port") ||
           item.at(0).contains("teacherID")){
               if(item.at(0).contains("ip-address")){
                   server = QHostAddress(item.at(1));
               }
               else if(item.at(0).contains("port")){
                   port = item.at(1).toInt();
               }
               else{
                   teacherID = item.at(1).toInt();
               }
        }
    }
}

void MainWindow::on_submitButton_clicked(){
    QByteArray data;
    if(!ui->lineEdit->text().contains("ID ") && !ui->lineEdit->text().contains(" ")){
        data.append(ui -> lineEdit -> text());
        data.append(" S ");
        data.append(QByteArray::number(teacherID, 10));
    }
    else{
        ui->lineEdit->text() = "Bad option.";
    }
    //data.append("test");

    //socket -> writeDatagram(data, QHostAddress::LocalHost, 4422);
    socket -> writeDatagram(data, server, port);
    ui->lineEdit->setText("");
}


void MainWindow::on_removeButton_clicked(){
    for(int remove = 0; remove < ui->listWidget->selectedItems().count(); remove++){
        QByteArray data;
        data.append("remove ");
        data.append(ui->listWidget->selectedItems().at(remove)->text());
        data.append(" S ");
        data.append(QByteArray::number(teacherID, 10));
        socket -> writeDatagram(data, server, port);
        delete ui->listWidget->selectedItems().at(remove);
    }
}

/*
 * Need to add something to implement a connected check. Resend the name and stuff of that ilk.
 */

void MainWindow::readData(){
    while(socket -> hasPendingDatagrams()){
        QByteArray buffer;
        buffer.resize(socket -> pendingDatagramSize());

        socket -> readDatagram(buffer.data(), buffer.size());

        QString bufferData = buffer.data();

        if(bufferData.contains("ID ")){
            if(bufferData.mid(bufferData.indexOf(" ")+1, bufferData.size()).toLongLong() > sendID){
                ui->listWidget->clear();
                sendID = bufferData.mid(bufferData.indexOf(" ")+1, bufferData.size()).toLongLong();
                ui->label->setText("Status: In The Queue");
            }
        }
        else if(bufferData.contains("remove")){
            ui->label->setText("Status: Not in the Queue");
        }
        else{
            if(!userListContains(QString(buffer))){
                ui -> listWidget -> addItem(buffer);
            }
        }
    }
}
 

bool MainWindow::userListContains(QString a){
    for(int u = 0; u < ui->listWidget->count(); u++){
        if(QString(ui->listWidget->item(u)->text()) == a){
            return true;
        }
    }
    return false;
}
