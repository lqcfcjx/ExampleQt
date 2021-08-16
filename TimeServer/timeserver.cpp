#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"

TimeServer::TimeServer(QObject *parent) : QTcpServer(parent)
{
    dlg = (Dialog*)parent;
}

void TimeServer::incomingConnection(qintptr socketDescriptor){
    TimeThread *thread = new TimeThread(socketDescriptor,0);
    connect(thread,&TimeThread::finished,dlg,&Dialog::slotShow);
    connect(thread,&TimeThread::finished,thread,&QThread::deleteLater);
    thread->start();
}
