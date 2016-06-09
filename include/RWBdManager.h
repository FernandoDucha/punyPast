/* 
 * File:   RWBdManager.h
 * Author: fordem
 *
 * Created on March 9, 2015, 1:29 PM
 */

#ifndef RWBDMANAGER_H
#define	RWBDMANAGER_H
#include <sstream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QList>
#include <QString>
#include <QByteArray>
#include <stdint.h>
#include <QDebug>
#include <IRWSet.h>
#include <RWBdManager.h>
#include <RWDpBase.h>
#include <QMap>
#include "IRWBd.h"
#include "RWVBase.h"
#include "QPollarF.h"
#include "PollarRwDp.h"
#include "PollarRwDpSet.h"
using namespace std;

class RWBdManager : public IRWBd {

    enum CMULT {
        DP = 8, BIN = 4,D2RW=16
    };
public:
    RWBdManager(char * dbfile);
    virtual ~RWBdManager();
    bool open();
    void close();
    bool createDpTable();
    bool createBinTable();
    bool createD2RwTable();
    bool insertItem(DataPointsDouble & dpitem);
    bool insertSet(DataSetDouble & dpset);
    DataPointsDouble selectDpItem(int i);
    DataSetDouble * selectDpItem(int Beg, int End);
    void prepareInsDpSetTo500(int N);
    bool bindValueMultDpItem(DataPointsDouble & dpitem, int elem);
    bool insertItem(RWVInt & binitem);
    bool insertSet(RWVSInt & dpset);
    RWVInt selectBinItem(int i);
    RWVSInt * selectBinItem(int Beg, int End);
    void prepareInsBinSetTo500(int N);
    bool bindValueMultBinItem(RWVInt & dpitem, int elem);
    bool insertItem(PollarRwDp & d2item);
    bool insertSet(PollarRwDpSet & d2item);
    PollarRwDp selectD2Item(int i);
    PollarRwDpSet * selectD2Item(int Beg, int End);
    void prepareInsD2SetTo500(int N);
    bool bindValueMultD2Item(PollarRwDp & dpitem, int elem);
    
    bool execMultiple();
    bool commit();
    int getNWalks();
    int getWalkS();

private:
    QSqlDatabase db;
    QString dbfile;
    QString dptable, rwvtable, qptable;
    uint64_t ncols, nrows;
    bool setIsPrepared;
    QMap<QString, QVariant> _map;
    QString ins_string;
    bool isprepared;
};

#endif	/* RWBDMANAGER_H */

