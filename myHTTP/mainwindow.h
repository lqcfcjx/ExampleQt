#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>

class QFile;
class QNetworkReply;
class QNetworkAccessManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void startRequest(QUrl url);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl url;
    QFile *file;

private slots:
    void replyFinished(QNetworkReply *);
    void httpFinished();
    void httpReadyRead();
    void updateDataReadProgress(qint64, qint64);

    void on_downLoadButton_clicked();
};
#endif // MAINWINDOW_H
