#include "server.h"

//QTextStream out(stdout);

Server::Server(QObject *parent) : QObject(parent){
    sendID = 0;
}

void Server::setUp(){
    QFile configFile("./config.cfg");

    if(!configFile.open(QIODevice::ReadOnly)){
        qDebug() << "Configuration file error - Not read.";
    }

    QTextStream configStream(&configFile);

    while(!configStream.atEnd()){
        QList<QString> item = configStream.readLine().split(" ");

        if( item.at(0).contains("port")){
               port = item.at(1).toInt();
        }
    }

    socket = new QUdpSocket(this);
    socket -> bind(QHostAddress::Any, port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

    qDebug() << "Socket initiatied";
}

void Server::readData(){
    while(socket -> hasPendingDatagrams()){

        QByteArray buffer;
        buffer.resize(socket -> pendingDatagramSize());

        QHostAddress sender;

        socket -> readDatagram(buffer.data(), buffer.size(), &sender);

        QList<QString> nt = QString(buffer).split(' ');

        if(nt.size() == 3){
            if(!userList.contains(User(sender, nt.at(0), nt.at(1), nt.at(2).toInt()))){
                userList.push_back(User(sender, nt.at(0), nt.at(1), nt.at(2).toInt()));
                sendData();
            }
        }
        else if(nt.size() == 4){
            if(nt.at(0) == "remove"){
                for(int u = 0; u < userList.size(); u++){
                    if(userList.at(u).returnName() == nt.at(1) &&
                       userList.at(u).returnType() == nt.at(2) &&
                       userList.at(u).returnTeacherID() == nt.at(3).toInt()){
                           socket -> writeDatagram(QByteArray(QString("remove").toUtf8()), userList.at(u).returnAddress(), port);
                           userList.removeAt(u);
                           u = userList.size();
                           sendData();
                    }
                }

                /*
                if(userList.contains(User(sender, nt.at(1), nt.at(2), nt.at(3).toInt()))){
                    userList.removeAt(userList.indexOf(User(sender, nt.at(1), nt.at(2), nt.at(3).toInt())));
                }
                */
            }
        }

        qDebug() << buffer;

        /*
        //if(!list -> contains(Client(sender, 10))){
        //    list -> push_back(Client(sender, 10));
        //}

        qDebug() << buffer;

        if(!addresses.contains(sender.toString())){
            addresses.push_back(sender.toString());
        }


        //socket -> writeDatagram(loop, sender, 4422);
        if(!QString(buffer).contains("connected ")){
            if(!names.contains(buffer)){
                names.push_back(buffer);
            }
            sendData();
        }
        */
    }
}

void Server::sendData(){
    /*
    sendID++;

    QList<User> sendList = QList<User>(userList);
    userList.clear();
    */

    sendID++;

    for(int send = 0; send < userList.size(); send++){
        socket -> writeDatagram(QByteArray(QString("ID "+QString::number(sendID)).toUtf8()), userList.at(send).returnAddress(), port);
        for(int user = 0; user < userList.size(); user++){
            if(userList.at(send).returnTeacherID() == userList.at(user).returnTeacherID()){ // checks if they're the same to make sure broadcast doesn't reach to another group.
                socket -> writeDatagram(QByteArray(userList.at(user).returnName().toUtf8()), userList.at(send).returnAddress(), port);
            }
        }
    }

    /*
    for(int add = 0; add < sendList.size(); add++){
        //socket -> writeDatagram(QByteArray(QString("ID "+QString::number(sendID)).toUtf8()), sendList.at(add).returnAddress(), 4422);
        for(int send = 0; send < sendList.size(); send++){
            socket -> writeDatagram(QByteArray(sendList.at(send).returnName().toUtf8()), sendList.at(add).returnAddress(), 4422);
            qDebug() << "send " << sendList.at(send).returnName() << " " << sendList.at(add).returnAddress();
        }
        sendList.removeAt(add);
        add--;
    }
    */

    /*
    QList<QString> addSend = QList<QString>(addresses);
    addresses.clear();
    int size = addSend.size();
    for(int add = 0; add < size; add++){
        socket -> writeDatagram(QByteArray(QString("ID "+QString::number(sendID)).toUtf8()), QHostAddress(addSend.at(add)), 4422);
        for(int send = 0; send < names.size(); send++){
            socket -> writeDatagram(QByteArray(names.at(send).toUtf8()), QHostAddress(addSend.at(add)), 4422);
            qDebug() << "send " << names.at(send) << " " << addSend.at(add);
        }
        addSend.removeAt(add);
        add--;
    }
    */
}
