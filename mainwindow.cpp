#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "sender.h"
#include <QObject>
int s_listen=0; // status of listen. If 0, will not listen. If 1, will listen.


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusLabel->setText("Ready to broadcast datagrams on port 45454");
    ui->statusLabel->setWordWrap(true);
    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);
    messageNo = 1;

    ui->statusLabel_2->setText("Listening for broadcasted messages");
    ui->statusLabel_2->setWordWrap(true);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    ui->statusLabel->setText("Transmission stopped..");
    disconnect(timer, SIGNAL(timeout()), this, SLOT(broadcastDatagram()));
    messageNo = 1;
}

void MainWindow::broadcastDatagram()
{
    ui->statusLabel->setText(tr("Now broadcasting datagram %1").arg(messageNo));
    QByteArray datagram = "Broadcast message " + QByteArray::number(messageNo);
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 45454);
    ++messageNo;
}


void MainWindow::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        if(s_listen == 1) ui->statusLabel_2->setText(tr("Received datagram: \"%1\"")
                             .arg(datagram.data()));
    };
}

void MainWindow::on_startButton_clicked()
{
      ui->statusLabel->setText("Transmission started..");
      timer->start(100);
      connect(timer, SIGNAL(timeout()), this, SLOT(broadcastDatagram()));
}

void MainWindow::on_startButton_2_clicked()
{
    s_listen = 1;// listen
    ui->statusLabel_2->setText("Now ready to recieve broadcasts on the ShareAddress of the the subnet");
}

void MainWindow::on_pushButton_2_clicked()
{
    s_listen = 0;//dont listen
    ui->statusLabel_2->setText("Press Start to recieve broadcasts on the ShareAddress of the the subnet");
}

