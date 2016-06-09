/* 
 * File:   BufferedProbabilityBase.cpp
 * Author: fordem
 * 
 * Created on March 5, 2015, 8:32 AM
 */

#include "BufferedProbabilityBase.h"
#include "PollarRwDp.h"

IRWItem<double> *BufferedProbabilityBase::buildWeiestrass(double a, double b, double from, double to, uint_32t N) {
    IRWIntervalBuilder<double> * interval = new RWDpIntervalBuilder<double>();
    IRWItem<double> * X = interval->produceLinearInterval(from, to, (to - from) / N);
    double * buffer = new double[N];
    for (uint_32t i = 0; i < N; i++) {
        buffer[i] = 0;
        for (int j = 0; j < 100; j++) {
            buffer[i] += pow(a, j) * cos(pow(b, j) * M_PI * X->getElement(i));
        }
    }
    RWBufferManagerSingleton<double> * instance = RWBufferManagerSingleton<double>::getInstance();
    RWBufferedDp<double> * t = instance->createDpItem(buffer, N + 1);
    IRWItem<double>* retorno = new RWBufferedDp<double>(*t);
    delete t;
    retorno->receiveData(buffer, N);
    return retorno;
}

IRWItem<QPollarF> * BufferedProbabilityBase::getNext2DWalk() {
    IRWItem<QPollarF> * _2wk = this->thisrwk->perform2DWalk();
    IRWItem<QPollarF> * _2wkr = pollar.createBufferedDp(thisrwk->GetWalkSize());
    *_2wkr = *_2wk;
    delete _2wk;
    return _2wkr;
}

IRWItem<double>* BufferedProbabilityBase::getAverageWalkByPoints() {
    IRWItem<double> * retorno = new DataPointsDouble();
    *retorno = *getWalkNByPoints(0);
    for (int i = 1; i<this->thisrwk->GetNumberRandomWalks(); i++) {
        *retorno += *getWalkNByPoints(i);
    }
    *dynamic_cast<DataPointsDouble*> (retorno) / (double) this->thisrwk->GetNumberRandomWalks();
    return retorno;
}

BufferedProbabilityBase::BufferedProbabilityBase(IRandomWalk * irwk) : rwmngrint("binp"), rwmngrdouble("doublep"), pollar("pollarp") {
    datap = NULL;
    databinp = NULL;
    walks2d = NULL;
    thisrwk = irwk;
}

void BufferedProbabilityBase::fillDatap() {
    if (datap) {
        delete datap;
        datap = NULL;
    }
    this->thisrwk->resetSeed();
    datap = new BufferedDpSetDouble(thisrwk->GetNumberRandomWalks());
    for (unsigned int i = 0; i < thisrwk->GetNumberRandomWalks(); i++) {
        DataPointsDouble * dp = dynamic_cast<DataPointsDouble*> (thisrwk->performOneWalkByPoints());
        BufferedDpDouble * bdp = dynamic_cast<BufferedDpDouble *> (rwmngrdouble.createBufferedDp(thisrwk->GetWalkSize()));
        *dynamic_cast<IRWItem<double>*> (bdp) = *dynamic_cast<IRWItem<double>*> (dp);
        datap->put(bdp);
        //        dp->print();
        delete bdp;
        delete dp;
    }
}

void BufferedProbabilityBase::fill2DWalks() {
    if (walks2d) {
        delete walks2d;
        walks2d = NULL;
    }
    this->thisrwk->resetSeed();
    walks2d = new PollarBufferedRwDpSet(thisrwk->GetNumberRandomWalks());
    for (unsigned int i = 0; i < thisrwk->GetNumberRandomWalks(); i++) {
        PollarRwDp * bin = dynamic_cast<PollarRwDp*> (thisrwk->perform2DWalk());
        BufferedPollarRwDp * bbin = dynamic_cast<BufferedPollarRwDp*> (pollar.createBufferedDp(thisrwk->GetWalkSize()));
        *dynamic_cast<IRWItem<QPollarF>*> (bbin) = *dynamic_cast<IRWItem<QPollarF>*> (bin);
        //        bbin->print();
        walks2d->put(bbin);
        //        bin->print();
        //        bbin.print();
        delete bbin;
        delete bin;
    }
//    walks2d->getElement(0)->print();

}

void BufferedProbabilityBase::fillDataBinp() {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    }
    this->thisrwk->resetSeed();
    databinp = new BufferedVecSetInt(thisrwk->GetNumberRandomWalks());
    for (unsigned int i = 0; i < thisrwk->GetNumberRandomWalks(); i++) {
        RWVInt * bin = dynamic_cast<RWVInt*> (thisrwk->performOneWalkByBits());
        BufferedVecInt * bbin = dynamic_cast<BufferedVecInt*> (rwmngrint.createBufferedVec(thisrwk->GetWalkSize()));
        *dynamic_cast<IRWItem<int>*> (bbin) = *dynamic_cast<IRWItem<int>*> (bin);
        databinp->put(bbin);
        //        bin->print();
        //        bbin.print();
        delete bbin;
        delete bin;
    }
}

BufferedProbabilityBase::~BufferedProbabilityBase() {
    rwmngrdouble.resetManager();
    rwmngrint.resetManager();
    pollar.resetManager();
    if (databinp) {
        delete databinp;
    }
    if (datap) {
        delete datap;
    }
    if (walks2d) {
        delete walks2d;
    }

    delete thisrwk;
}

void BufferedProbabilityBase::SetDatabinp(IRWSet<int>* databinp) {
    this->databinp = dynamic_cast<BufferedVecSetInt*> (databinp);
}

IRWSet<int>* BufferedProbabilityBase::GetDatabinp() {
    fillDataBinp();
    return databinp;
}

IRWSet<int>* BufferedProbabilityBase::GetDatabinp(u_int64_t ws, u_int64_t ns, char*) {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    }
    this->thisrwk->SetNumberOfWalks(ws);
    this->thisrwk->SetWalkSize(ns);
    this->rwmngrint.resetManager();
    fillDataBinp();
    //    msg = strdup("");
    return this->databinp;
}

IRWSet<double>* BufferedProbabilityBase::GetDatap(u_int64_t ws, u_int64_t ns, char*) {
    if (datap) {
        delete datap;
        datap = NULL;
    }
    this->thisrwk->SetNumberOfWalks(ws);
    this->thisrwk->SetWalkSize(ns);
    this->rwmngrdouble.resetManager();
    fillDatap();
    //    msg = strdup("");
    return this->datap;
}

bool BufferedProbabilityBase::FetchDataOnly(u_int64_t, u_int64_t, char*) {
    return true;
}

void BufferedProbabilityBase::SetDatap(IRWSet<double>* datap) {
    this->datap = dynamic_cast<BufferedDpSetDouble*> (datap);
}

IRWSet<double>* BufferedProbabilityBase::GetDatap() {
    fillDatap();
    return datap;
}

IPolyfit * BufferedProbabilityBase::CurveFitting() {
    double * xaxis = new double[thisrwk->GetNumberRandomWalks()];
    double * yaxis = new double[thisrwk->GetNumberRandomWalks()];
    RWVInt accumulated;
    for (unsigned int i = 0; i < thisrwk->GetNumberRandomWalks(); i++) {
        xaxis[i] = log(i + 1);
        accumulated += *databinp->getElement(i);
        yaxis[i] = log((double) accumulated.abs_sum() / thisrwk->GetNumberRandomWalks());
    }
    IRWItem<double> * x = new RWDp<double>();
    IRWItem<double> * y = new RWDp<double>();
    x->receiveData(xaxis, this->thisrwk->GetNumberRandomWalks());
    y->receiveData(yaxis, this->thisrwk->GetNumberRandomWalks());
    LinearFit * lin = new LinearFit(x, y);
    delete x;
    delete y;
    lin->performFit();
    return lin;
}

void BufferedProbabilityBase::clearDataBin() {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    }
}

void BufferedProbabilityBase::clearDataPoints() {
    if (datap) {
        delete datap;
        datap = NULL;
    }
}

void BufferedProbabilityBase::clear2DWalks() {
    if (walks2d) {
        delete walks2d;
        walks2d = NULL;
    }
}

IRWSet<QPollarF> * BufferedProbabilityBase::getAll2DWalks() {
    fill2DWalks();
    return (walks2d);
}

IRWItem<int> * BufferedProbabilityBase::getWalkNByBits(u_int64_t N) {
    return databinp->getElement(N);
}

IRWItem<double> * BufferedProbabilityBase::getWalkNByPoints(u_int64_t N) {
    return datap->getElement(N);
}

IRWSet<int>* BufferedProbabilityBase::getWalkNByBits(u_int64_t beg, u_int64_t end) {
    RWVSInt * ret = new RWVSInt(end - beg + 1);
    for (uint64_t i = beg; i <= end; i++) {
        ret->put(getWalkNByBits(i));
    }
    return ret;
}

IRWSet<double>* BufferedProbabilityBase::getWalkNByPoints(u_int64_t beg, u_int64_t end) {
    assert(beg > end);
    DataSetDouble * ret = new DataSetDouble(end - beg + 1);
    for (uint64_t i = beg; i <= end; i++) {
        ret->put(getWalkNByPoints(i));
    }
    return ret;
}

void BufferedProbabilityBase::setNewIRandomWalk(IRandomWalk * irwk) {
    clearDataBin();
    clearDataPoints();
    clear2DWalks();
    thisrwk = irwk;
    fillDataBinp();
    fillDatap();
    fill2DWalks();
}

IRandomWalk * BufferedProbabilityBase::GetThisbrwk() const {
    return thisrwk;
}
