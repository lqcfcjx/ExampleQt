#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QTimer>

class UdpServer : public QDialog
{
    Q_OBJECT
public:
    UdpServer(QWidget *parent = 0,Qt::WindowFlags f = 0);
    ~UdpServer();

private:
    QLabel *timerLabel;
    QLineEdit *textLineEdit;
    QPushButton *startBtn;
    QVBoxLayout *mainLayout;

    int port;
    bool isStarted;
    QUdpSocket *udpSocket;
    QTimer *timer;

public slots:
    void startBtnClicked();
    void timeout();
};
#endif // UDPSERVER_H
