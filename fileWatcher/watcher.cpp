#include "watcher.h"
#include <QVBoxLayout>
#include <QDir>
#include <QMessageBox>
#include <QApplication>

Watcher::Watcher(QWidget *parent)
    : QWidget(parent)
{
    QStringList args = qApp->arguments();
    QString path;
    if(args.count() > 1){
        path = args[1];
    }else{
        path = QDir::currentPath();
    }
    pathLabel = new QLabel;
    pathLabel->setText(QString::fromLocal8Bit("监视的目录：")+path);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(pathLabel);
    fsWatcher.addPath(path);
    connect(&fsWatcher,&QFileSystemWatcher::directoryChanged,this,&Watcher::directoryChanged);
}

Watcher::~Watcher()
{
}

void Watcher::directoryChanged(QString path){
    QMessageBox::information(this,QString::fromLocal8Bit("目录发生变化"),path);
}
