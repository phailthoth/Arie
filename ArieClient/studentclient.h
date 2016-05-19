#ifndef STUDENTCLIENT_H
#define STUDENTCLIENT_H

#include <QMainWindow>

namespace Ui {
class studentClient;
}

class studentClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentClient(QWidget *parent = 0);
    ~studentClient();

private:
    Ui::studentClient *ui;
};

#endif // STUDENTCLIENT_H
