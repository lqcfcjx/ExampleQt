#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->downLoadprogressBar->hide();
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&MainWindow::replyFinished);
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));
//    qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();
    //https://dldir1.qq.com/weixin/Windows/WeChatSetup.exe
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply){
    QString all = reply->readAll();
    ui->textBrowser->setText(all);
    reply->deleteLater();
}

void MainWindow::startRequest(QUrl url){
    reply = manager->get(QNetworkRequest(url));
    connect(reply,&QNetworkReply::readyRead,this,&MainWindow::httpReadyRead);
    connect(reply,&QNetworkReply::downloadProgress,this,&MainWindow::updateDataReadProgress);
    connect(reply,&QNetworkReply::finished,this,&MainWindow::httpFinished);
}

void MainWindow::httpReadyRead(){
    if(file) file->write(reply->readAll());
}

void MainWindow::updateDataReadProgress(qint64 bytesRead,qint64 totalBytes){
    ui->downLoadprogressBar->setMaximum(totalBytes);
    ui->downLoadprogressBar->setValue(bytesRead);
}

void MainWindow::httpFinished(){
    ui->downLoadprogressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}


void MainWindow::on_downLoadButton_clicked()
{
    url = ui->downLoadlineEdit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    file = new QFile(fileName);
    if(!file->open(QIODevice::WriteOnly)){
        qDebug()<<"file open error";
        delete file;
        file = 0;
        return;
    }
    startRequest(url);
    ui->downLoadprogressBar->setValue(0);
    ui->downLoadprogressBar->show();
}
