#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class TimeServer;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    QLabel *label1;//显示监听端口
    QLabel *label2;//显示请求次数
    QPushButton *quitBtn;

    TimeServer *timeServer;
    int count;

public slots:
    void slotShow();
};
#endif // DIALOG_H
