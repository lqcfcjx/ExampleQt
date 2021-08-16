#include "tcpserver.h"

TcpServer::TcpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("TCP Server"));
    contentListWidget = new QListWidget;
    portLabel = new QLabel(QString::fromLocal8Bit("端口："));
    portLineEdit = new QLineEdit;
    createBtn = new QPushButton(QString::fromLocal8Bit("创建聊天室"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(portLabel,1,0);
    mainLayout->addWidget(portLineEdit,1,1);
    mainLayout->addWidget(createBtn,2,0,1,2);

    port = 8010;
    portLineEdit->setText(QString::number(port));
    connect(createBtn,&QPushButton::clicked,this,&TcpServer::slotCreateServer);
}

TcpServer::~TcpServer()
{
}

void TcpServer::slotCreateServer(){
    server = new Server(this,port);
    connect(server,&Server::updateServer,this,&TcpServer::updateServer);
    createBtn->setEnabled(false);
}

void TcpServer::updateServer(QString msg, int length){
    contentListWidget->addItem(msg.left(length));
}

