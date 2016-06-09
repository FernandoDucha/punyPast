/* 
 * File:   RWPollarDpIntervalBuilder.h
 * Author: fordem
 *
 * Created on August 21, 2015, 8:34 PM
 */

#ifndef RWPOLLARDPINTERVALBUILDER_H
#define	RWPOLLARDPINTERVALBUILDER_H
#include "IRWIntervalBuilder.h"
#include "QPollarF.h"
#include "PollarRwDp.h"
#include "PollarRwDpSet.h"
#include "RWDpBase.h"
#include "RWDpBase.h"
class RWPollarDpIntervalBuilder : public IRWIntervalBuilder<QPollarF> {
public:
    RWPollarDpIntervalBuilder();
    virtual ~RWPollarDpIntervalBuilder();
    IRWSet<QPollarF>* getIntervals(IRWItem<QPollarF>*, uint_32t);
    IRWSet<QPollarF>* getOverlapingIntervals(IRWItem<QPollarF>*, uint_32t);
    IRWSet<QPollarF>* getOverlapingIntervals(IRWItem<QPollarF>*, uint_32t, uint_32t);
    IRWItem<QPollarF>* getIntervalsI(IRWItem<QPollarF> *, uint_32t, uint_32t);
    IRWItem<QPollarF>* getOverlapingIntervalsI(IRWItem<QPollarF>*, uint_32t, uint_32t);
    IRWItem<QPollarF>* getOverlapingIntervalsI(IRWItem<QPollarF>*, uint_32t, uint_32t, uint_32t);
    IRWItem<QPollarF>* produceLinearInterval(double, double, double);
    IRWItem<QPollarF>* produceLogarithmicInterval(double, double, double);
private:

};

inline IRWItem<QPollarF> * RWPollarDpIntervalBuilder::getIntervalsI(IRWItem<QPollarF> * Input, uint_32t N, uint_32t interval) {
    uint_32t p = this->intervals(Input, N);
    if (interval < p) {
        QPollarF* ret = new QPollarF[N];
        IRWItem<QPollarF> * retorno = new PollarRwDp();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + interval * N);
        }
        retorno->receiveData(ret, N);
        delete [] ret;
        return retorno;
    }
    return NULL;
}

inline IRWItem<QPollarF> * RWPollarDpIntervalBuilder::getOverlapingIntervalsI(IRWItem<QPollarF> * Input, uint_32t N, uint_32t interval) {
    uint_32t p = this->overlapingIntervals(Input, N);
    if (interval < p) {
        QPollarF* ret = new QPollarF[N];
        IRWItem<QPollarF> * retorno = new PollarRwDp();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + interval);
        }
        retorno->receiveData(ret, N);
        delete [] ret;
        return retorno;
    }
    return NULL;
}

inline IRWItem<QPollarF> * RWPollarDpIntervalBuilder::getOverlapingIntervalsI(IRWItem<QPollarF> *Input, uint_32t N, uint_32t Increment, uint_32t interval) {
    uint_32t p = this->overlapingIntervals(Input, N, Increment);
    if (interval < p) {
        QPollarF* ret = new QPollarF[N];
        IRWItem<QPollarF> * retorno = new PollarRwDp();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + interval * Increment);
        }
        retorno->receiveData(ret, N);
        delete [] ret;
        return retorno;
    }
    return NULL;
}

inline IRWItem<QPollarF> * RWPollarDpIntervalBuilder::produceLinearInterval(double start, double end, double step) {
    int it = (end - start) / step + 1;
    QPollarF * buffer = new QPollarF[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i].setX(start);
        buffer[i].setY(start);
    }
    IRWItem<QPollarF> * retorno = new PollarRwDp();
    retorno->receiveData(buffer, it);
    delete [] buffer;
    return retorno;
}

inline IRWItem<QPollarF> * RWPollarDpIntervalBuilder::produceLogarithmicInterval(double start, double end, double step) {
    int it = (end - start) / step + 1;
    QPollarF * buffer = new QPollarF[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i].setX(log10(start));
        buffer[i].setY(log10(start));
    }
    IRWItem<QPollarF> * retorno = new PollarRwDp();
    retorno->receiveData(buffer, it);
    delete [] buffer;
    return retorno;
}

inline IRWSet<QPollarF> * RWPollarDpIntervalBuilder::getIntervals(IRWItem<QPollarF> * Input, uint_32t N) {
    uint_32t p = this->intervals(Input, N);
    QPollarF* ret = new QPollarF[N];
    IRWSet<QPollarF> * retorno = new PollarRwDpSet(p);
    for (int i = 0; i < p; i++) {
        IRWItem<QPollarF> * temp = new PollarRwDp();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i * N);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

inline IRWSet<QPollarF> * RWPollarDpIntervalBuilder::getOverlapingIntervals(IRWItem<QPollarF> * Input, uint_32t N) {
    uint_32t p = this->overlapingIntervals(Input, N);
    QPollarF* ret = new QPollarF[N];
    IRWSet<QPollarF> * retorno = new PollarRwDpSet(p);
    for (int i = 0; i < p; i++) {
        IRWItem<QPollarF> * temp = new PollarRwDp();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

inline IRWSet<QPollarF> * RWPollarDpIntervalBuilder::getOverlapingIntervals(IRWItem<QPollarF> * Input, uint_32t N, uint_32t Increment) {
    uint_32t p = this->overlapingIntervals(Input, N, Increment);
    QPollarF* ret = new QPollarF[N];
    IRWSet<QPollarF> * retorno = new PollarRwDpSet(p);
    for (int i = 0; i < p; i++) {
        IRWItem<QPollarF> * temp = new PollarRwDp();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i * Increment);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

inline RWPollarDpIntervalBuilder::RWPollarDpIntervalBuilder() {
}

inline RWPollarDpIntervalBuilder::~RWPollarDpIntervalBuilder() {
}
#endif	/* RWPOLLARDPINTERVALBUILDER_H */

