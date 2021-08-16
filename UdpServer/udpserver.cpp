#include "udpserver.h"
#include <QHostInfo>

UdpServer::UdpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle(tr("UDP Serve"));
    timerLabel = new QLabel(QString::fromLocal8Bit("计时器："),this);
    textLineEdit = new QLineEdit(this);
    startBtn = new QPushButton(QString::fromLocal8Bit("开始"),this);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(timerLabel);
    mainLayout->addWidget(textLineEdit);
    mainLayout->addWidget(startBtn);

    connect(startBtn,&QPushButton::clicked,this,&UdpServer::startBtnClicked);
    port = 5555;
    isStarted = false;
    udpSocket = new QUdpSocket(this);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&UdpServer::timeout);
}

UdpServer::~UdpServer()
{
}

void UdpServer::startBtnClicked(){
    if(!isStarted){
        startBtn->setText(QString::fromLocal8Bit("停止"));
        timer->start(1000);
        isStarted = true;
    }else{
        startBtn->setText(QString::fromLocal8Bit("开始"));
        isStarted = false;
        timer->stop();
    }
}

void UdpServer::timeout(){
    QString msg = textLineEdit->text();
    int length = 0;
    if(msg == ""){
        return;
    }
    if((length = udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::Broadcast,port))!=msg.length()){
        return;
    }
}
