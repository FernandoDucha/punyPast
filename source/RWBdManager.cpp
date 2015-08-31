/* 
 * File:   RWBdManager.cpp
 * Author: fordem
 * 
 * Created on March 9, 2015, 1:29 PM
 */


#include "RWBdManager.h"

RWBdManager::RWBdManager(char * dbfile) {
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
    } else {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    this->dbfile = QString(dbfile);
    db.setDatabaseName(this->dbfile);
    dptable = "dp";
    rwvtable = "bin";
    qptable = "d2rw";
}

bool RWBdManager::open() {
    return db.open();
}

void RWBdManager::close() {
    db.close();
}

bool RWBdManager::createDpTable() {
    db.exec("drop table " + dptable + ";");
    QString sql = "create table " + dptable + "(key integer primary key, _" + dptable + " blob);";
    db.exec(sql);
    if (db.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::createD2RwTable() {
    db.exec("drop table " + qptable + ";");
    QString sql = "create table " + qptable + "(key integer primary key, _" + qptable + " blob);";
    db.exec(sql);
    if (db.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::commit() {
    return db.commit();
}

bool RWBdManager::createBinTable() {
    db.exec("drop table " + rwvtable + ";");
    QString sql = "create table " + rwvtable + "(key integer primary key,_" + rwvtable + " blob)";
    db.exec(sql);
    if (db.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::insertItem(DataPointsDouble & dpitem) {
    QSqlQuery q;
    q.prepare("insert into " + dptable + "(key, _" + dptable + ") values(:key,:_" + dptable + ")");
    QByteArray ba;
    char* _ba = new char[dpitem.getNpoints() * DP];
    double * buffer = new double[dpitem.getNpoints()];
    stringstream stream(stringstream::binary | stringstream::in | stringstream::out);
    for (uint32_t i = 0; i < dpitem.getNpoints(); i++) {
        buffer[i] = dpitem.getElement(i);
    }
    stream.write(reinterpret_cast<char*> (buffer), dpitem.getNpoints() * DP);
    stream.read(_ba, dpitem.getNpoints() * DP);
    ba.append(_ba, dpitem.getNpoints() * DP);
    delete [] _ba;
    delete [] buffer;
    q.bindValue(":_" + dptable, ba);
    q.exec();
    if (q.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::insertItem(PollarRwDp & d2item) {
    QSqlQuery q;
    q.prepare("insert into " + qptable + "(key, _" + qptable + ") values(:key,:_" + qptable + ")");
    QByteArray ba;
    char* _ba = new char[d2item.getNpoints() * D2RW];
    double * buffer = new double[d2item.getNpoints() * 2];
    stringstream stream(stringstream::binary | stringstream::in | stringstream::out);
    for (uint32_t i = 0; i < d2item.getNpoints(); i++) {
        buffer[2 * i] = d2item.getElement(i).rx();
        buffer[2 * i + 1] = d2item.getElement(i).ry();
    }
    stream.write(reinterpret_cast<char*> (buffer), d2item.getNpoints() * D2RW);
    stream.read(_ba, d2item.getNpoints() * D2RW);
    ba.append(_ba, d2item.getNpoints() * D2RW);
    delete [] _ba;
    delete [] buffer;
    q.bindValue(":_" + qptable, ba);
    q.exec();
    if (q.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::insertSet(PollarRwDpSet & d2set) {
    for (uint32_t i = 0; i < d2set.getSize(); i++) {
        if (!insertItem(*dynamic_cast<PollarRwDp*> (d2set.getElement(i)))) {
            return false;
        }
    }
    return true;
}

PollarRwDp RWBdManager::selectD2Item(int i) {
    QSqlQuery sq;
    if (i == 0) {
        sq.exec("select * from " + qptable + " limit 1;");
    } else {
        QString s_i = QString::number(i);
        sq.exec("select * from " + qptable + " limit " + s_i + ", 1 ;");
    }
    PollarRwDp ret;
    while (sq.next()) {
        QByteArray ba = sq.value(1).toByteArray();
        double * data = reinterpret_cast<double*> (ba.data());
        int size=ba.size()/D2RW;
        QPollarF * _temp = new QPollarF[size];
        for(int i=0;i<size;i++){
            _temp[i].setX(data[i*2]);
            _temp[i].setY(data[i*2+1]);
            
        }
        delete [] _temp;
        ret.receiveData(_temp,size);
    }
    return ret;
}
PollarRwDpSet * RWBdManager::selectD2Item(int Beg, int End){
    QSqlQuery sq;
    int N = End - Beg;
    QString _n = QString::number(N);
    if (Beg == 0) {
        sq.exec("select * from " + qptable + " limit " + _n + ";");
    } else {
        QString s_i = QString::number(Beg);
        sq.exec("select * from " + qptable + " limit " + s_i + ", " + _n + ";");
    }
    PollarRwDpSet * ret = new PollarRwDpSet(N);
    while (sq.next()) {
        PollarRwDp * d = new PollarRwDp();
        QByteArray ba = sq.value(1).toByteArray();
        double * data = reinterpret_cast<double*> (ba.data());
        int size=ba.size()/D2RW;
        QPollarF * _temp = new QPollarF[size];
        for(int i=0;i<size;i++){
            _temp[i].setX(data[i*2]);
            _temp[i].setY(data[i*2+1]);
            
        }
        d->receiveData(_temp,size);
        delete [] _temp;
        ret->put(d);
    }
    return ret;
}
void RWBdManager::prepareInsD2SetTo500(int N){
    QString basic_v = "";
    int i = 0;
    for (; i < N - 1; i++)
        basic_v += " ( :key" + QString::number(i) + " , :_" + qptable + QString::number(i) + " ) , ";
    basic_v += "(:key" + QString::number(i) + ",:_" + qptable + QString::number(i) + ")";
    ins_string = "insert into " + qptable + "(key, _" + qptable + ") values" + basic_v;
    isprepared = true;
}
bool RWBdManager::bindValueMultD2Item(PollarRwDp & d2item, int elem){
    if (isprepared) {
        QByteArray ba;
        char* _ba = new char[d2item.getNpoints() * D2RW];
        double * buffer = new double[d2item.getNpoints()*2];
        stringstream stream(stringstream::binary | stringstream::in | stringstream::out);
        for (uint32_t i = 0; i < d2item.getNpoints(); i++) {
            buffer[2*i] = d2item.getElement(i).rx();
            buffer[2*i+1] = d2item.getElement(i).ry();
        }
        stream.write(reinterpret_cast<char*> (buffer), d2item.getNpoints() * D2RW);
        stream.read(_ba, d2item.getNpoints() * D2RW);
        ba.append(_ba, d2item.getNpoints() * D2RW);
        QString v = ":_" + qptable + QString::number(elem);
        _map[v] = ba;
        delete [] _ba;
        delete [] buffer;
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::insertSet(DataSetDouble & dpset) {
    for (uint32_t i = 0; i < dpset.getSize(); i++) {
        if (!insertItem(*dynamic_cast<DataPointsDouble*> (dpset.getElement(i)))) {
            return false;
        }
    }
    return true;
}

DataPointsDouble RWBdManager::selectDpItem(int i) {
    QSqlQuery sq;
    if (i == 0) {
        sq.exec("select * from " + dptable + " limit 1;");
    } else {
        QString s_i = QString::number(i);
        sq.exec("select * from " + dptable + " limit " + s_i + ", 1 ;");
    }
    DataPointsDouble ret;
    while (sq.next()) {
        QByteArray ba = sq.value(1).toByteArray();
        ret.receiveData(reinterpret_cast<double*> (ba.data()), ba.size() / DP);
    }
    return ret;
}

DataSetDouble * RWBdManager::selectDpItem(int Beg, int End) {
    QSqlQuery sq;
    int N = End - Beg;
    QString _n = QString::number(N);
    if (Beg == 0) {
        sq.exec("select * from " + dptable + " limit " + _n + ";");
    } else {
        QString s_i = QString::number(Beg);
        sq.exec("select * from " + dptable + " limit " + s_i + ", " + _n + ";");
    }
    DataSetDouble * ret = new DataSetDouble(N);
    while (sq.next()) {
        DataPointsDouble * d = new DataPointsDouble();
        QByteArray ba = sq.value(1).toByteArray();
        d->receiveData(reinterpret_cast<double*> (ba.data()), ba.size() / DP);
        ret->put(d);
    }
    return ret;
}

void RWBdManager::prepareInsDpSetTo500(int N) {
    QString basic_v = "";
    int i = 0;
    for (; i < N - 1; i++)
        basic_v += " ( :key" + QString::number(i) + " , :_" + dptable + QString::number(i) + " ) , ";
    basic_v += "(:key" + QString::number(i) + ",:_" + dptable + QString::number(i) + ")";
    ins_string = "insert into " + dptable + "(key, _" + dptable + ") values" + basic_v;
    isprepared = true;
}

bool RWBdManager::bindValueMultDpItem(DataPointsDouble& dpitem, int elem) {
    if (isprepared) {
        QByteArray ba;
        char* _ba = new char[dpitem.getNpoints() * DP];
        double * buffer = new double[dpitem.getNpoints()];
        stringstream stream(stringstream::binary | stringstream::in | stringstream::out);
        for (uint32_t i = 0; i < dpitem.getNpoints(); i++) {
            buffer[i] = dpitem.getElement(i);
        }
        stream.write(reinterpret_cast<char*> (buffer), dpitem.getNpoints() * DP);
        stream.read(_ba, dpitem.getNpoints() * DP);
        ba.append(_ba, dpitem.getNpoints() * DP);
        QString v = ":_" + dptable + QString::number(elem);
        _map[v] = ba;
        delete [] _ba;
        delete [] buffer;
        return true;
    } else {
        return false;
    }
}

bool RWBdManager::execMultiple() {
    QSqlQuery q;
    if (isprepared) {
        q.prepare(ins_string);
        for (int i = 0; i < _map.keys().size(); i++) {
            q.bindValue(_map.keys().at(i), _map.values().at(i));
        }
        q.exec();
        _map.clear();
        if (q.lastError().type() == QSqlError::NoError) {
            isprepared = false;
            return true;
        } else {
            qDebug() << q.lastError();
            return false;
        }
    } else {
        return false;
    }
}

bool RWBdManager::insertItem(RWVInt & binitem) {
    QSqlQuery q;
    q.prepare("insert into " + rwvtable + "(key, _" + rwvtable + ") values(:key,:_" + rwvtable + ")");
    QByteArray ba;
    char* _ba = new char[binitem.getNpoints() * DP];
    int * buffer = new int[binitem.getNpoints()];
    stringstream stream(stringstream::binary | stringstream::in | stringstream::out);
    for (uint32_t i = 0; i < binitem.getNpoints(); i++) {
        buffer[i] = binitem.getElement(i);
    }
    stream.write(reinterpret_cast<char*> (buffer), binitem.getNpoints() * DP);
    stream.read(_ba, binitem.getNpoints() * DP);
    ba.append(_ba, binitem.getNpoints() * DP);
    delete [] _ba;
    delete [] buffer;
    q.bindValue(":_" + rwvtable, ba);
    q.exec();
    if (q.lastError().type() == QSqlError::NoError) {
        return true;
    } else {
        return false;
    }
}

int RWBdManager::getNWalks() {
    QSqlQuery sq;
    sq.exec("SELECT Count(*) FROM " + dptable + ";");
    sq.next();
    return sq.value(0).toReal();
}

int RWBdManager::getWalkS() {
    return selectDpItem(0).getNpoints();
}

bool RWBdManager::insertSet(RWVSInt & binset) {
    for (uint32_t i = 0; i < binset.getSize(); i++) {
        if (!insertItem(*dynamic_cast<RWVInt*> (binset.getElement(i)))) {
            return false;
        }
    }
    return true;
}

RWVInt RWBdManager::selectBinItem(int i) {
    QSqlQuery sq;
    if (i == 0) {
        sq.exec("select * from " + rwvtable + " limit 1;");
    } else {
        QString s_i = QString::number(i);
        sq.exec("select * from " + rwvtable + " limit " + s_i + ", 1 ;");
    }
    RWVInt ret;
    while (sq.next()) {
        QByteArray ba = sq.value(1).toByteArray();
        ret.receiveData(reinterpret_cast<int*> (ba.data()), ba.size() / DP);
    }
    return ret;
}

RWVSInt * RWBdManager::selectBinItem(int Beg, int End) {
    QSqlQuery sq;
    int N = End - Beg;
    QString _n = QString::number(N);
    if (Beg == 0) {
        sq.exec("select * from " + rwvtable + " limit " + _n + ";");
    } else {
        QString s_i = QString::number(Beg);
        sq.exec("select * from " + rwvtable + " limit " + s_i + ", " + _n + ";");
    }
    RWVSInt * ret = new RWVSInt(N);
    while (sq.next()) {
        RWVInt * d = new RWVInt();
        QByteArray ba = sq.value(1).toByteArray();
        d->receiveData(reinterpret_cast<int*> (ba.data()), ba.size() / DP);
        ret->put(d);
    }
    return ret;
}

void RWBdManager::prepareInsBinSetTo500(int N) {
    QString basic_v = "";
    int i = 0;
    for (; i < N - 1; i++)
        basic_v += " ( :key" + QString::number(i) + " , :_" + rwvtable + QString::number(i) + " ) , ";
    basic_v += "(:key" + QString::number(i) + ",:_" + rwvtable + QString::number(i) + ")";
    ins_string = "insert into " + rwvtable + "(key, _" + rwvtable + ") values" + basic_v;
    isprepared = true;
}

bool RWBdManager::bindValueMultBinItem(RWVInt & binitem, int elem) {
    if (isprepared) {
        QByteArray ba;
        char* _ba = new char[binitem.getNpoints() * DP];
        int * buffer = new int[binitem.getNpoints()];
        stringstream stream(stringstream::binary | stringstream::in | stringstream::out);
        for (uint32_t i = 0; i < binitem.getNpoints(); i++) {
            buffer[i] = binitem.getElement(i);
        }
        stream.write(reinterpret_cast<char*> (buffer), binitem.getNpoints() * DP);
        stream.read(_ba, binitem.getNpoints() * DP);
        ba.append(_ba, binitem.getNpoints() * DP);
        QString v = ":_" + rwvtable + QString::number(elem);
        _map[v] = ba;
        delete [] _ba;
        delete [] buffer;
        return true;
    } else {
        return false;
    }
}

RWBdManager::~RWBdManager() {
}

