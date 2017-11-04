#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port=8010;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slotCreateServer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::slotCreateServer()
{
    server = new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));
    ui->pushButton->setEnabled(false);
}
void MainWindow::updateServer(QString, int)
{
    QMessageBox::warning(NULL, "warning", "No username!", QMessageBox::Yes, QMessageBox::Yes);
    return;
}
