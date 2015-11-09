/* 
 * File:   ProbabilityBase.cpp
 * Author: fernando
 * 
 * Created on 8 de Maio de 2013, 10:08
 */

#include <assert.h>
#include <qt5/QtCore/qdebug.h>

#include "ProbabilityBase.h"
#include "LinearFit.h"
#include "PollarRwDp.h"

ProbabilityBase::ProbabilityBase(IRandomWalk * brwk) {
    thisbrwk = brwk;
    datap=nullptr;
    databinp=nullptr;
    walks2d=nullptr;
    
    
    //    this->datap=brwk->performAllWalksByPoints();
    //    this->databinp=brwk->performAllWalksByBits();
}

ProbabilityBase::~ProbabilityBase() {
    delete thisbrwk;
}

void ProbabilityBase::setNewIRandomWalk(IRandomWalk * brwk) {
    clearDataBin();
    clearDataPoints();
    clear2DWalks();
    thisbrwk = brwk;
}

void ProbabilityBase::SetDatabinp(IRWSet<int>* databinp) {
    this->databinp = dynamic_cast<RWVSInt*> (databinp);
}

IRWSet<int>* ProbabilityBase::GetDatabinp() {
    clearDataBin();
    thisbrwk->resetSeed();
    databinp = dynamic_cast<RWVSInt*> (thisbrwk->performAllWalksByBits());
    return databinp;
}

void ProbabilityBase::SetDatap(IRWSet<double>* datap) {
    this->datap = dynamic_cast<DataSetDouble*> (datap);
}

IRWSet<double>* ProbabilityBase::GetDatap() {
    clearDataPoints();
    thisbrwk->resetSeed();
    datap = dynamic_cast<DataSetDouble*> (thisbrwk->performAllWalksByPoints());
    return datap;
}

IRWItem<double> *ProbabilityBase::buildWeiestrass(double a, double b, double from, double to, uint_32t N) {
    IRWIntervalBuilder<double> * interval = new RWDpIntervalBuilder<double>();
    IRWItem<double> * X = interval->produceLinearInterval(from, to, (to - from) / N);
    double * buffer = new double[N];
    for (uint_32t i = 0; i < N; i++) {
        buffer[i] = 0;
        for (int j = -100; j <= 100; j++) {
            buffer[i] += pow(b, -j * a)*(1 - cos(pow(b, j) * X->getElement(i)));
        }
    }
    IRWItem<double>* retorno = new RWDp<double>();
    retorno->receiveData(buffer, N);
    return retorno;
}

IPolyfit * ProbabilityBase::CurveFitting() {
    double * xaxis = new double[thisbrwk->GetNumberRandomWalks()];
    double * yaxis = new double[thisbrwk->GetNumberRandomWalks()];
    RWVInt accumulated;
    for (unsigned int i = 0; i < thisbrwk->GetNumberRandomWalks(); i++) {
        xaxis[i] = log(i + 1);
        accumulated += *databinp->getElement(i);
        yaxis[i] = log((double) accumulated.abs_sum() / thisbrwk->GetNumberRandomWalks());
    }
    IRWItem<double> * x = new RWDp<double>();
    IRWItem<double> * y = new RWDp<double>();
    x->receiveData(xaxis, this->thisbrwk->GetNumberRandomWalks());
    y->receiveData(yaxis, this->thisbrwk->GetNumberRandomWalks());
    LinearFit * lin = new LinearFit(x, y);
    delete x;
    delete y;
    lin->performFit();
    return lin;
}

IRWItem<double>* ProbabilityBase::getAverageWalkByPoints() {
    IRWItem<double>* retorno = new DataPointsDouble();
    *retorno = *getWalkNByPoints(0);
    for (int i = 1; i<this->thisbrwk->GetNumberRandomWalks(); i++) {
        *retorno += *getWalkNByPoints(i);
    }
    *dynamic_cast<DataPointsDouble*> (retorno) / (double) this->thisbrwk->GetNumberRandomWalks();
    return retorno;
}

IRWItem<QPollarF>* ProbabilityBase::getNext2DWalk() {
    return this->thisbrwk->perform2DWalk();
}

IRWSet<QPollarF> * ProbabilityBase::getAll2DWalks() {
    clear2DWalks();
    thisbrwk->resetSeed();
    walks2d = new PollarRwDpSet(thisbrwk->GetNumberRandomWalks());
    for (int i = 0; i < thisbrwk->GetNumberRandomWalks(); i++) {
        walks2d->put(thisbrwk->perform2DWalk());
    }
    return walks2d;
}

IRWSet<int>* ProbabilityBase::GetDatabinp(uint64_t nw, uint64_t ns, char*) {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    } else if (datap) {
        delete datap;
        datap = NULL;
    }
    this->thisbrwk->SetNumberOfWalks(nw);
    this->thisbrwk->SetWalkSize(ns);
    if (this->thisbrwk->canProduceSets()) {
        this->thisbrwk->prepareData();
        this->databinp = dynamic_cast<RWVSInt*> (this->thisbrwk->performAllWalksByBits());
        //        msg = strdup("");
        return this->databinp;
    } else {
        //        msg = strdup("Arquivo selecionado não possui dados suficientes.");
        return NULL;
    }

}

bool ProbabilityBase::FetchDataOnly(u_int64_t ws, u_int64_t ns, char*) {
    if (databinp) {
        delete databinp;
    } else if (datap) {
        delete datap;
    }
    this->thisbrwk->SetNumberOfWalks(ws);
    this->thisbrwk->SetWalkSize(ns);
    if (this->thisbrwk->canProduceSets()) {
        this->thisbrwk->prepareData();
        return true;
    } else {
        return false;
    }
}

IRWSet<double>* ProbabilityBase::GetDatap(uint64_t nw, uint64_t ns, char*) {
    if (datap) {
        delete datap;
        datap = NULL;
    } else if (databinp) {
        delete databinp;
        databinp = NULL;
    }
    this->thisbrwk->SetNumberOfWalks(nw);
    this->thisbrwk->SetWalkSize(ns);
    if (this->thisbrwk->canProduceSets()) {
        this->thisbrwk->prepareData();
        this->datap = dynamic_cast<DataSetDouble*> (this->thisbrwk->performAllWalksByPoints());
        //        msg = strdup("");
        return this->datap;
    } else {
        //        msg = strdup("Arquivo selecionado não possui dados suficientes.");
        return NULL;
    }
}

void ProbabilityBase::clearDataBin() {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    }
}

void ProbabilityBase::clear2DWalks() {
    if (walks2d) {
        delete walks2d;
        walks2d = NULL;
    }
}

void ProbabilityBase::clearDataPoints() {
    if (datap) {
        delete datap;
        datap = NULL;
    }
}

IRWItem<int> * ProbabilityBase::getWalkNByBits(u_int64_t N) {
    return databinp->getElement(N);
}

IRWItem<double> * ProbabilityBase::getWalkNByPoints(u_int64_t N) {
    return datap->getElement(N);
}

IRWSet<int>* ProbabilityBase::getWalkNByBits(u_int64_t beg, u_int64_t end) {
    RWVSInt * ret = new RWVSInt(end - beg + 1);
    for (uint64_t i = beg; i <= end; i++) {
        ret->put(getWalkNByBits(i));
    }
    return ret;
}

IRWSet<double>* ProbabilityBase::getWalkNByPoints(u_int64_t beg, u_int64_t end) {
    assert(beg > end);
    DataSetDouble * ret = new DataSetDouble(end - beg + 1);
    for (uint64_t i = beg; i <= end; i++) {
        ret->put(getWalkNByPoints(i));
    }
    return ret;
}
