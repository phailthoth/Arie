#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void readData();


private:
    Ui::MainWindow *ui;

    QUdpSocket *socket;
    QHostAddress server;
    int port;

    long long sendID;
    int teacherID;

    bool userListContains(QString a);

    void setUp();

private slots:
    void on_submitButton_clicked();
    void on_removeButton_clicked();
};

#endif // MAINWINDOW_H
