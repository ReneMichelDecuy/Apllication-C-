#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDisplayMessageButtonClicked()
{

}


void MainWindow::Test()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    qDebug() << "Connecting,..";

    socket->connectToHost("192.168.64.160", 1234);

    if(!socket->waitForDisconnected(1000))
    {
        qDebug() << "Error: " << socket->errorString();
    }

}

void MainWindow::connected()
{
    qDebug() << "Connected!";

    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void MainWindow::disconnected()
{
    qDebug() << "Disconnected!";
}

void MainWindow::bytesWritten(qint64 bytes)
{
    qDebug() << "We wrote: " << bytes;
}

void MainWindow::readyRead()
{
    qDebug() << "Reading...";
    qDebug() << socket->readAll();
}
