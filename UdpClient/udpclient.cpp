#include "udpclient.h"
#include <QMessageBox>
#include <QHostAddress>

UdpClient::UdpClient(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("UDP Client"));
    receiveTextEdit = new QTextEdit(this);
    closeBtn  = new QPushButton(tr("Close"),this);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(receiveTextEdit);
    mainLayout->addWidget(closeBtn);

    connect(closeBtn,&QPushButton::clicked,this,&UdpClient::closeBtnClicked);
    port = 5555;
    udpSocket = new QUdpSocket(this);
    connect(udpSocket,&QUdpSocket::readyRead,this,&UdpClient::dataReceived);
    bool result = udpSocket->bind(port);
    if(!result){
        QMessageBox::information(this,tr("error"),tr("udp socket create error"));
        return;
    }
}

UdpClient::~UdpClient()
{
}

void UdpClient::closeBtnClicked(){
    close();
}

void UdpClient::dataReceived(){
    while(udpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QString msg = datagram.data();
        receiveTextEdit->insertPlainText(msg);
    }
}
