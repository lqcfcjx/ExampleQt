#include "datedelegate.h"
#include "combodelegate.h"
#include "spindelegate.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QTableView>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStandardItemModel model(4,4);
    QTableView tableView;
    tableView.setModel(&model);
    DateDelegate dateDelegate;
    ComboDelegate comboDelegate;
    SpinDelegate spinDelegate;
    tableView.setItemDelegateForColumn(1,&dateDelegate);
    tableView.setItemDelegateForColumn(2,&comboDelegate);
    tableView.setItemDelegateForColumn(3,&spinDelegate);
    model.setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("姓名"));
    model.setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("生日"));
    model.setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("职业"));
    model.setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("收入"));
    QFile file("test.txt");
    if(file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        QString line;
        model.removeRows(0,model.rowCount(QModelIndex()),QModelIndex());
        int row = 0;
        do{
            line = stream.readLine();
            if(!line.isEmpty()){
                model.insertRows(row,1,QModelIndex());
                QStringList piece = line.split(",",QString::SkipEmptyParts);
                model.setData(model.index(row,0,QModelIndex()),piece.value(0));
                model.setData(model.index(row,1,QModelIndex()),piece.value(1));
                model.setData(model.index(row,2,QModelIndex()),piece.value(2));
                model.setData(model.index(row,3,QModelIndex()),piece.value(3));
                row++;
            }
        }while(!line.isEmpty());
        file.close();
    }
    tableView.setWindowTitle(QObject::tr("Delegate"));
    tableView.show();
    return a.exec();
}
