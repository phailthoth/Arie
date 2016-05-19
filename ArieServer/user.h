#ifndef USER_H
#define USER_H

#include <QUdpSocket>

class User{
public:
   User(QHostAddress a, QString b, QString c, int d);
   QHostAddress returnAddress() const;
   QString returnName() const;
   QString returnType() const;
   int returnTeacherID() const;

   bool operator==(const User& other) const{
       if(returnType() == other.returnType() &&
          returnName() == other.returnName() &&
          returnTeacherID() == other.returnTeacherID()){
           return true;
       }
       return false;
   }

private:
    QHostAddress address;
    QString name;
    QString type;
    int teacherID;
};

#endif // CLIENT_H
