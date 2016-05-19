#ifndef TEACHERCLIENT_H
#define TEACHERCLIENT_H

#include <QMainWindow>

namespace Ui {
class teacherClient;
}

class teacherClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit teacherClient(QWidget *parent = 0);
    ~teacherClient();

private:
    Ui::teacherClient *ui;
};

#endif // TEACHERCLIENT_H
