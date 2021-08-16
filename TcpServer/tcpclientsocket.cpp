#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,&QTcpSocket::readyRead,this,&TcpClientSocket::dataReceived);
    connect(this,&TcpClientSocket::disconnected,this,&TcpClientSocket::slotDisconnected);
}

void TcpClientSocket::dataReceived(){
    while(bytesAvailable()>0){
        int length = bytesAvailable();
        char buf[1024];
        read(buf,length);
        QString msg = buf;
        emit updateClients(msg,length);
    }
}

void TcpClientSocket::slotDisconnected(){
    emit disconnected(this->socketDescriptor());
}
