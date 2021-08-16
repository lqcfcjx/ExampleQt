﻿#ifndef TIMESERVER_H
#define TIMESERVER_H

#include <QTcpServer>

class Dialog;

class TimeServer : public QTcpServer
{
    Q_OBJECT
public:
    TimeServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    Dialog *dlg;
};

#endif // TIMESERVER_H
