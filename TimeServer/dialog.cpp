#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "timeserver.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QString::fromLocal8Bit("多线程时间服务器"));
    label1 = new QLabel(QString::fromLocal8Bit("服务器端口："));
    label2 = new QLabel;
    quitBtn = new QPushButton(QString::fromLocal8Bit("退出"));
    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addStretch(1);
    BtnLayout->addWidget(quitBtn);
    BtnLayout->addStretch(1);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label1);
    mainLayout->addWidget(label2);
    mainLayout->addLayout(BtnLayout);
    connect(quitBtn,&QPushButton::clicked,this,[=](){ close(); });

    count = 0;
    timeServer = new TimeServer(this);
    if(!timeServer->listen()){
        QMessageBox::critical(this,QString::fromLocal8Bit("多线程时间服务器"),QString::fromLocal8Bit("无法启动服务器：%1.").arg(timeServer->errorString()));
        close();
        return;
    }
    label1->setText(QString::fromLocal8Bit("服务器端口：%1.").arg(timeServer->serverPort()));
}

Dialog::~Dialog()
{
}

void Dialog::slotShow(){
    label2->setText(QString::fromLocal8Bit("第 %1次请求完毕。").arg(++count));
}
