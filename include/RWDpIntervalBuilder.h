/* 
 * File:   RWDpIntervalBuilder.h
 * Author: fordem
 *
 * Created on June 3, 2015, 8:11 PM
 */

#ifndef RWDPINTERVALBUILDER_H
#define	RWDPINTERVALBUILDER_H
#include "IRWIntervalBuilder.h"
#include "RWDp.h"

template <class Type >class RWDpIntervalBuilder : public IRWIntervalBuilder<Type> {
public:
    RWDpIntervalBuilder();
    virtual ~RWDpIntervalBuilder();
    IRWSet<Type>* getIntervals(IRWItem<Type>*, uint_32t);
    IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t);
    IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t, uint_32t);
    IRWItem<Type>* produceLinearInterval(double, double, double);
    IRWItem<Type>* produceLogarithmicInterval(double, double, double);
    IRWItem<Type>* getIntervalsI(IRWItem<Type>*, uint_32t, uint_32t);
    IRWItem<Type>* getOverlapingIntervalsI(IRWItem<Type>*, uint_32t, uint_32t);
    IRWItem<Type>* getOverlapingIntervalsI(IRWItem<Type>*, uint_32t, uint_32t, uint_32t);
private:

};

template <class Type> IRWItem<Type>* RWDpIntervalBuilder<Type>::getIntervalsI(IRWItem<Type>* Input, uint_32t N, uint_32t interval) {
    uint_32t p = this->intervals(Input,N);
    if (interval < p) {
        Type* ret = new Type[N];
        RWDp<Type> * retorno = new RWDp<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + interval * N);
        }
        retorno->receiveData(ret, N);
        delete [] ret;
        return retorno;
    }
    return NULL;
}

template <class Type> IRWItem<Type>* RWDpIntervalBuilder<Type>::getOverlapingIntervalsI(IRWItem<Type>* Input, uint_32t N, uint_32t interval) {
    uint_32t p = this->overlapingIntervals(Input,N);
    if (interval < p) {
        Type* ret = new Type[N];
        RWDp<Type> * retorno = new RWDp<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + interval);
        }
        retorno->receiveData(ret, N);
        delete [] ret;
        return retorno;
    }
    return NULL;
}

template <class Type> IRWItem<Type>* RWDpIntervalBuilder<Type>::getOverlapingIntervalsI(IRWItem<Type>*Input, uint_32t N, uint_32t Increment, uint_32t interval) {
    uint_32t p = this->overlapingIntervals(Input,N,Increment);
    if (interval < p) {
        Type* ret = new Type[N];
        RWDp<Type> * retorno = new RWDp<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + interval*Increment);
        }
        retorno->receiveData(ret, N);
        delete [] ret;
        return retorno;
    }
    return NULL;
}

template <class Type> IRWItem<Type>* RWDpIntervalBuilder<Type>::produceLinearInterval(double start, double end, double step) {
    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i] = start;
    }
    IRWItem<Type> * retorno = new RWDp<Type>();
    retorno->receiveData(buffer, it);
    delete [] buffer;
    return retorno;
}

template <class Type> IRWItem<Type>* RWDpIntervalBuilder<Type>::produceLogarithmicInterval(double start, double end, double step) {
    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i] = log10(start);
    }
    IRWItem<Type> * retorno = new RWDp<Type>();
    retorno->receiveData(buffer, it);
    delete [] buffer;
    return retorno;
}

template <class Type> IRWSet<Type>* RWDpIntervalBuilder<Type>::getIntervals(IRWItem<Type>* Input, uint_32t N) {
    uint_32t p = this->intervals(Input,N);
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWDpSet<Type>(p);
    for (int i = 0; i < p; i++) {
        RWDp<Type> * temp = new RWDp<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i * N);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

template <class Type> IRWSet<Type>* RWDpIntervalBuilder<Type>::getOverlapingIntervals(IRWItem<Type>* Input, uint_32t N) {
    uint_32t p = this->overlapingIntervals(Input,N);
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWDpSet<Type>(p);
    for (int i = 0; i < p; i++) {
        RWDp<Type> * temp = new RWDp<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

template <class Type> IRWSet<Type>* RWDpIntervalBuilder<Type>::getOverlapingIntervals(IRWItem<Type>* Input, uint_32t N, uint_32t Increment) {
    uint_32t p = this->overlapingIntervals(Input,N,Increment);
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWDpSet<Type>(p);
    for (int i = 0; i < p; i++) {
        RWDp<Type> * temp = new RWDp<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i * Increment);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

template<class Type> RWDpIntervalBuilder<Type>::RWDpIntervalBuilder() {

}

template<class Type> RWDpIntervalBuilder<Type>::~RWDpIntervalBuilder() {
}


#endif	/* RWDPINTERVALBUILDER_H */

