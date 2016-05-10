#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QUdpSocket>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTimer>
//#include "sender.h"

namespace Ui {
class MainWindow;
class Sender;
}


class Sender : public QObject{

        Q_OBJECT

        public:
            Sender(QObject *parent=0);
            void SendMessage();

        signals:

        public slots:
//            void startBroadcasting();
//            void broadcastDatagram();

        private slots:


        private:
            QLabel *statusLabel;
            QPushButton *startButton;
            QPushButton *quitButton;
            QDialogButtonBox *buttonBox;
            QUdpSocket *udpSocket;
            QTimer *timer;
            int messageNo;

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SendMessage();

private slots:
    void on_pushButton_clicked(bool checked);

    void on_startButton_clicked();
    void broadcastDatagram();
    void processPendingDatagrams();

    void on_startButton_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QTimer *timer;
    int messageNo;



};




#endif // MAINWINDOW_H
