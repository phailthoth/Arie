#ifndef SERVER_H
#define SERVER_H

#include "user.h"

#include <QDebug>
#include <QList>
#include <QObject>
#include <QUdpSocket>
#include <QTextStream>
#include <QFile>

class Server  : public QObject{
    Q_OBJECT
    public:
        explicit Server(QObject *parent = 0);
        void setUp();
    public slots:
        void readData();
    private:
        QUdpSocket *socket;
        int port;

        QByteArray loop;
        QList<QString> names;
        QList<QString> addresses;
        QList<User> userList;
        long long sendID;

        void sendData();
};

#endif // SERVER_H
