#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "QDebug"

class DataConfig : public QObject
{
    Q_OBJECT  

public:
    DataConfig();

//    static DataConfig& getInstance() {
//        static DataConfig instance;
//        return instance;
//    }

//    DataConfig(const DataConfig&) {}

//    DataConfig& operator=(const DataConfig&) = delete;

//    QMap<int, QVector<QVector<int>>> getData() {
//        qDebug() << "getdata";
//        qDebug() << _data.size();
//        return _data;
//    }

signals:

public:
    QMap<int, QVector<QVector<int>>> _data;

};

#endif // DATACONFIG_H
