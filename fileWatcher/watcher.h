#ifndef WATCHER_H
#define WATCHER_H

#include <QWidget>
#include <QLabel>
#include <QFileSystemWatcher>

class Watcher : public QWidget
{
    Q_OBJECT
public:
    Watcher(QWidget *parent = 0);
    ~Watcher();

public slots:
    void directoryChanged(QString path);

private:
    //监视当前目录，不能监视当前目录下的子目录中文件变化
    QLabel *pathLabel;
    QFileSystemWatcher fsWatcher;
};
#endif // WATCHER_H
