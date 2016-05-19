#include "user.h"

User::User(QHostAddress a, QString b, QString c, int d){
    address = a;
    name = b;
    type = c;
    teacherID = d;
}

QHostAddress User::returnAddress() const{
    return address;
}

QString User::returnName() const{
    return name;
}

QString User::returnType() const{
    return type;
}

int User::returnTeacherID() const{
    return teacherID;
}
