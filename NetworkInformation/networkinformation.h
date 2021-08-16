#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QHostInfo>
#include <QNetworkInterface>

class NetworkInformation : public QWidget
{
    Q_OBJECT
public:
    NetworkInformation(QWidget *parent = nullptr);
    ~NetworkInformation();

    void getHostInformation();

private:
    QLabel *hostLabel;
    QLineEdit *lineEditLocalHostName;
    QLabel *ipLabel;
    QLineEdit *lineEditAddress;
    QPushButton *detailBtn;
    QGridLayout *mainLayout;

public slots:
    void slotDetail();
};
#endif // NETWORKINFORMATION_H
