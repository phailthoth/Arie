#include <QCoreApplication>
#include <QList>
#include <QDebug>

#include "server.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    qDebug() << "Starting server";
    Server server;
    server.setUp();

    return a.exec();
}
