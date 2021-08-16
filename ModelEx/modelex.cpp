#include "modelex.h"

ModelEx::ModelEx(QObject *parent)
    : QAbstractTableModel(parent)
{
    armyMap[1] = QString::fromLocal8Bit("空军");
    armyMap[2] = QString::fromLocal8Bit("海军");
    armyMap[3] = QString::fromLocal8Bit("陆军");
    armyMap[4] = QString::fromLocal8Bit("海军陆战队");
    weaponTypeMap[1] = QString::fromLocal8Bit("轰炸机");
    weaponTypeMap[2] = QString::fromLocal8Bit("战斗机");
    weaponTypeMap[3] = QString::fromLocal8Bit("航空母舰");
    weaponTypeMap[4] = QString::fromLocal8Bit("驱逐舰");
    weaponTypeMap[5] = QString::fromLocal8Bit("直升机");
    weaponTypeMap[6] = QString::fromLocal8Bit("坦克");
    weaponTypeMap[7] = QString::fromLocal8Bit("两栖攻击舰");
    weaponTypeMap[8] = QString::fromLocal8Bit("两栖战车");
    populateModel();
}

void ModelEx::populateModel(){
    header << QString::fromLocal8Bit("军种") << QString::fromLocal8Bit("种类") << QString::fromLocal8Bit("武器");
    army << 1 << 2 << 3 << 4 << 2 << 4 << 3 << 1;
    weaponType << 1 << 3 << 5 << 7 << 4 << 8 << 6 << 2;
    weapon << QString::fromLocal8Bit("尼米兹级") << QString::fromLocal8Bit("阿帕奇") << QString::fromLocal8Bit("黄蜂级")
           << QString::fromLocal8Bit("阿利伯克级") << QString::fromLocal8Bit("AAAV") << QString ::fromLocal8Bit("M1A1")
           << QString::fromLocal8Bit("F-22") << QString::fromLocal8Bit("B-2");
}

int ModelEx::columnCount(const QModelIndex &parent) const{
    return 3;
}

int ModelEx::rowCount(const QModelIndex &parent) const{
    return army.size();
}

QVariant ModelEx::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case 0 :
            return armyMap[army[index.row()]];
            break;
        case 1:
            return weaponTypeMap[weaponType[index.row()]];
            break;
        case 2:
            return weapon[index.row()];
        }
    }
    return QVariant();
}

QVariant ModelEx::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        return header[section];
    }else{
        return QAbstractTableModel::headerData(section,orientation,role);
    }
}
