/* 
 * File:   BDProbabilityBase.cpp
 * Author: fordem
 * 
 * Created on March 10, 2015, 8:37 PM
 */

#include <qt5/QtCore/qlogging.h>

#include "BDProbabilityBase.h"

IRWItem<double> * BDProbabilityBase::buildWeiestrass(double a, double b, double from, double to, uint_32t N) {
    IRWIntervalBuilder<double> * interval = new RWDpIntervalBuilder<double>();
    IRWItem<double> * X = interval->produceLinearInterval(from, to, (to - from) / N);
    double * buffer = new double[N];
    for (uint_32t i = 0; i < N; i++) {
        buffer[i] = 0;
        for (int j = 0; j < 100; j++) {
            buffer[i] += pow(a, j) * cos(pow(b, j) * M_PI * X->getElement(i));
        }
    }
    IRWItem<double>* retorno = new RWDp<double>();
    retorno->receiveData(buffer, N);
    return retorno;
}

IRWItem<double>* BDProbabilityBase::getAverageWalkByPoints() {
    IRWItem<double> * retorno = new DataPointsDouble();
    IRWItem<double> * temp = getWalkNByPoints(0);
    *retorno = *temp;
    delete temp;
    int nW = this->BdManager.getNWalks();
    for (int i = 1; i < nW; i++) {
        temp = getWalkNByPoints(i);
        *retorno += *temp;
        delete temp;
    }
    *dynamic_cast<DataPointsDouble*> (retorno) / (double) nW;
    return retorno;
}

IRWItem<QPollarF>* BDProbabilityBase::getNext2DWalk() {
    return thisrwk->perform2DWalk();
}

BDProbabilityBase::BDProbabilityBase(IRandomWalk * irwk) : BdManager("database.db3") {
    BdManager.open();
    thisrwk = irwk;
    block = 100;

}

void BDProbabilityBase::fillBinTable() {
    thisrwk->resetSeed();
    BdManager.createBinTable();
    int count = thisrwk->GetNumberRandomWalks() / block;
    int rest = thisrwk->GetNumberRandomWalks() % block;
    while (count > 0) {
        BdManager.prepareInsBinSetTo500(block);
        for (int i = 0; i < block; i++) {
            RWVInt * dp = dynamic_cast<RWVInt*> (thisrwk->performOneWalkByBits());
            BdManager.bindValueMultBinItem(*dp, i);
            delete dp;
        }
        BdManager.execMultiple();
        count--;
    }
    if (rest) {
        BdManager.prepareInsBinSetTo500(rest);
        for (int i = 0; i < rest; i++) {
            RWVInt * dp = dynamic_cast<RWVInt*> (thisrwk->performOneWalkByBits());
            BdManager.bindValueMultBinItem(*dp, i);
            //            dp->print();
            delete dp;
        }
        BdManager.execMultiple();
    }
}

IRWBd * BDProbabilityBase::getBd() {
    return &BdManager;
}

void BDProbabilityBase::fillDpTable() {
    thisrwk->resetSeed();
    BdManager.createDpTable();
    int count = thisrwk->GetNumberRandomWalks() / block;
    int rest = thisrwk->GetNumberRandomWalks() % block;
    while (count > 0) {
        BdManager.prepareInsDpSetTo500(block);
        for (int i = 0; i < block; i++) {
            DataPointsDouble * dp = dynamic_cast<DataPointsDouble*> (thisrwk->performOneWalkByPoints());
            BdManager.bindValueMultDpItem(*dp, i);
            delete dp;
        }
        BdManager.execMultiple();
        count--;
    }
    if (rest) {
        BdManager.prepareInsDpSetTo500(rest);
        for (int i = 0; i < rest; i++) {
            DataPointsDouble * dp = dynamic_cast<DataPointsDouble*> (thisrwk->performOneWalkByPoints());
            BdManager.bindValueMultDpItem(*dp, i);
            delete dp;
        }
        BdManager.execMultiple();
    }
}

void BDProbabilityBase::fillD2Table() {
    thisrwk->resetSeed();
    BdManager.createD2RwTable();
    int count = thisrwk->GetNumberRandomWalks() / block;
    int rest = thisrwk->GetNumberRandomWalks() % block;
    while (count > 0) {
        BdManager.prepareInsD2SetTo500(block);
        for (int i = 0; i < block; i++) {
            PollarRwDp * dp = dynamic_cast<PollarRwDp*> (thisrwk->perform2DWalk());
            BdManager.bindValueMultD2Item(*dp, i);
            delete dp;
        }
        BdManager.execMultiple();
        count--;
    }
    if (rest) {
        BdManager.prepareInsD2SetTo500(rest);
        for (int i = 0; i < rest; i++) {
            PollarRwDp * dp = dynamic_cast<PollarRwDp*> (thisrwk->perform2DWalk());
            BdManager.bindValueMultD2Item(*dp, i);
            delete dp;
        }
        BdManager.execMultiple();
    }
}

void BDProbabilityBase::SetDatabinp(IRWSet<int>*) {

}

IRWSet<int>* BDProbabilityBase::GetDatabinp() {
    fillBinTable();
    return BdManager.selectBinItem(0, thisrwk->GetNumberRandomWalks());
}

IRWSet<int>* BDProbabilityBase::GetDatabinp(u_int64_t ws, u_int64_t ns, char*) {
    thisrwk->SetWalkSize(ws);
    thisrwk->SetNumberOfWalks(ns);
    fillBinTable();
    return GetDatabinp();
}

IRWSet<double>* BDProbabilityBase::GetDatap(u_int64_t ws, u_int64_t ns, char*) {
    thisrwk->SetWalkSize(ws);
    thisrwk->SetNumberOfWalks(ns);
    fillDpTable();
    return GetDatap();
}

bool BDProbabilityBase::FetchDataOnly(u_int64_t, u_int64_t, char*) {
    return true;
}

void BDProbabilityBase::SetDatap(IRWSet<double>*) {

}

IRWSet<double>* BDProbabilityBase::GetDatap() {
    fillDpTable();
    return BdManager.selectDpItem(0, thisrwk->GetNumberRandomWalks());
}

IRWSet<QPollarF>* BDProbabilityBase::getAll2DWalks() {
    fillD2Table();
    return BdManager.selectD2Item(0, thisrwk->GetNumberRandomWalks());
}

IPolyfit * BDProbabilityBase::CurveFitting() {
    double * xaxis = new double[thisrwk->GetNumberRandomWalks()];
    double * yaxis = new double[thisrwk->GetNumberRandomWalks()];
    RWVInt accumulated;
    for (unsigned int i = 0; i < thisrwk->GetNumberRandomWalks(); i++) {
        xaxis[i] = log(i + 1);
        RWVInt t = BdManager.selectBinItem(i);
        accumulated += t;
        yaxis[i] = log((double) accumulated.abs_sum() / thisrwk->GetNumberRandomWalks());
    }
    IRWItem<double> * x = new RWDp<double>();
    IRWItem<double> * y = new RWDp<double>();
    x->receiveData(xaxis, BdManager.getWalkS());
    y->receiveData(yaxis, BdManager.getWalkS());
    LinearFit * lin = new LinearFit(x, y);
    delete x;
    delete y;
    lin->performFit();
    return lin;
}

void BDProbabilityBase::clearDataBin() {
    BdManager.createBinTable();
}
void BDProbabilityBase::clear2DWalks(){
    BdManager.createD2RwTable();
}

void BDProbabilityBase::clearDataPoints() {
    BdManager.createDpTable();
}

IRWItem<int> * BDProbabilityBase::getWalkNByBits(u_int64_t N) {
    RWVInt * ret = new RWVInt();
    RWVInt t = BdManager.selectBinItem(N);
    *dynamic_cast<IRWItem<int>*> (ret) = *dynamic_cast<IRWItem<int>*> (&t);
    return ret;
}

IRWItem<double> * BDProbabilityBase::getWalkNByPoints(u_int64_t N) {
    DataPointsDouble * ret = new DataPointsDouble();
    DataPointsDouble t = BdManager.selectDpItem(N);
    *dynamic_cast<IRWItem<double>*> (ret) = *dynamic_cast<IRWItem<double>*> (&t);
    return ret;
}

IRWSet<int>* BDProbabilityBase::getWalkNByBits(u_int64_t beg, u_int64_t end) {
    return BdManager.selectBinItem(beg, end);
}

IRWSet<double>* BDProbabilityBase::getWalkNByPoints(u_int64_t beg, u_int64_t end) {
    return BdManager.selectDpItem(beg, end);
}

void BDProbabilityBase::setNewIRandomWalk(IRandomWalk * irwk) {
    clearDataBin();
    clearDataPoints();
    thisrwk = irwk;
    fillDpTable();
    fillBinTable();
}

IRandomWalk* BDProbabilityBase::GetThisbrwk() const {
    return thisrwk;
}

BDProbabilityBase::~BDProbabilityBase() {
    delete thisrwk;
    BdManager.close();
}

