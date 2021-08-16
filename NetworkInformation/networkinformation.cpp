#include "networkinformation.h"

NetworkInformation::NetworkInformation(QWidget *parent)
    : QWidget(parent)
{
    hostLabel = new QLabel(QString::fromLocal8Bit("主机名："));
    lineEditLocalHostName = new QLineEdit;
    ipLabel = new QLabel(QString::fromLocal8Bit("IP 地址："));
    lineEditAddress = new QLineEdit;
    detailBtn = new QPushButton(QString::fromLocal8Bit("详细"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(hostLabel,0,0);
    mainLayout->addWidget(lineEditLocalHostName,0,1);
    mainLayout->addWidget(ipLabel,1,0);
    mainLayout->addWidget(lineEditAddress,1,1);
    mainLayout->addWidget(detailBtn,2,0,1,2);
    getHostInformation();
    connect(detailBtn,&QPushButton::clicked,this,&NetworkInformation::slotDetail);
}

NetworkInformation::~NetworkInformation()
{
}

void NetworkInformation::getHostInformation(){
    QString localHostName = QHostInfo::localHostName();
    lineEditLocalHostName->setText(localHostName);
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty()){
        lineEditAddress->setText(listAddress.at(2).toString());
    }
}

void NetworkInformation::slotDetail(){
    QString detail = "";
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int i=0;i<list.size();i++){
        QNetworkInterface interface = list.at(i);
        detail += QString::fromLocal8Bit("设备：") + interface.name() + "\n";
        detail += QString::fromLocal8Bit("硬件地址：") + interface.hardwareAddress() + "\n";
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        for(int j= 0;j<entryList.size();j++){
            QNetworkAddressEntry entry = entryList.at(j);
            detail += "\t" + QString::fromLocal8Bit("IP地址：") + entry.ip().toString() + "\n";
            detail += "\t" + QString::fromLocal8Bit("子网掩码：") + entry.netmask().toString() + "\n";
            detail += "\t" + QString::fromLocal8Bit("广播地址：") + entry.broadcast().toString() + "\n";
        }
    }
    QMessageBox::information(this,tr("Detail"),detail);
}
