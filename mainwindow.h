#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "server.h"
#include <QMainWindow>
#include <QMap>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
int port;
    Server *server;
public slots:
void slotCreateServer();
void updateServer(QString,int);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
