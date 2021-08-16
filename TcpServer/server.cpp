#include "server.h"

Server::Server(QObject *parent, int port) : QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void Server::incomingConnection(int socketDescriptor){
    TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
    connect(tcpClientSocket,&TcpClientSocket::updateClients,this,&Server::updateClients);
    connect(tcpClientSocket,&TcpClientSocket::disconnected,this,&Server::slotDisconnected);
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpClientSocketList.append(tcpClientSocket);
}

void Server::updateClients(QString msg,int length){
    emit updateServer(msg,length);
    for(int i=0; i<tcpClientSocketList.size(); i++){
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length){
            continue;
        }
    }
}

void Server::slotDisconnected(int descriptor){
    for(int i=0; i<tcpClientSocketList.size();i++){
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor() == descriptor){
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}
