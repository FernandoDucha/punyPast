/* 
 * File:   RWBufferedIntervalBuilder.h
 * Author: fordem
 *
 * Created on June 2, 2015, 11:18 PM
 */

#ifndef RWBUFFEREDDPINTERVALBUILDER_H
#define	RWBUFFEREDDPINTERVALBUILDER_H
#include "IRWIntervalBuilder.h"
#include "RWBufferedDpSet.h"
#include "RWBufferManagerSingleton.h"
template <class Type> class RWBufferedDpIntervalBuilder : public IRWIntervalBuilder<Type> {
public:
    RWBufferedDpIntervalBuilder();
    virtual ~RWBufferedDpIntervalBuilder();
    IRWSet<Type>* getIntervals(IRWItem<Type>*, uint_32t);
    IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t);
    IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t, uint_32t);
    IRWItem<Type>* produceLinearInterval(double, double, double);
    IRWItem<Type>* produceLogarithmicInterval(double, double, double);
private:

};
template <class Type> IRWItem<Type>* RWBufferedDpIntervalBuilder<Type>::produceLinearInterval(double start, double end, double step) {
    RWBufferManagerSingleton<Type> * rwbfs = RWBufferManagerSingleton<Type>::getInstance();

    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i] = start;
    }
    IRWItem<Type> * retorno = new RWBufferedDp<Type>(rwbfs->createDpItem(buffer, it));
    delete [] buffer;
    return retorno;
}

template <class Type> IRWItem<Type>* RWBufferedDpIntervalBuilder<Type>::produceLogarithmicInterval(double start, double end, double step) {
    RWBufferManagerSingleton<Type> * rwbfs = RWBufferManagerSingleton<Type>::getInstance();

    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i] = start;
    }
    IRWItem<Type> * retorno = new RWBufferedDp<Type>(rwbfs->createDpItem(buffer, it));
    delete [] buffer;
    return retorno;
}
template <class Type> RWBufferedDpIntervalBuilder<Type>::RWBufferedDpIntervalBuilder() {
}

template <class Type> RWBufferedDpIntervalBuilder<Type>::~RWBufferedDpIntervalBuilder() {
}

template <class Type> IRWSet<Type>* RWBufferedDpIntervalBuilder<Type>::getIntervals(IRWItem<Type>* Input, uint_32t N) {
    Type * buffer = new Type[Input->getNpoints()];
    Type t;
    int j = 0;
    while (Input->getNext(t)) {
        buffer[j++] = t;
    }
    uint_32t p = (double) Input->getNpoints() / N;
    Input->resetIterator();
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWBufferedDpSet<Type>(p);
    RWBufferManagerSingleton<Type> * rwbfs = RWBufferManagerSingleton<Type>::getInstance();
    for (int i = 0; i < p; i++) {
        memcpy(ret, &buffer[i * N], N * sizeof (Type));
        RWBufferedDp<Type> temp = rwbfs->createDpItem(ret, N);
        retorno->put(&temp);
    }
    delete [] buffer;
    delete [] ret;
    return retorno;
}

template <class Type> IRWSet<Type>* RWBufferedDpIntervalBuilder<Type>::getOverlapingIntervals(IRWItem<Type>* Input, uint_32t N) {
    Type * buffer = new Type[Input->getNpoints()];
    Type t;
    int j = 0;
    while (Input->getNext(t)) {
        buffer[j++] = t;
    }
    uint_32t p = Input->getNpoints() - N + 1;
    Input->resetIterator();
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWBufferedDpSet<Type>(p);
    RWBufferManagerSingleton<Type> * rwbfs = RWBufferManagerSingleton<Type>::getInstance();
    for (int i = 0; i < p; i++) {
        memcpy(ret, &buffer[i], N * sizeof (Type));
        RWBufferedDp<Type> temp = rwbfs->createDpItem(ret, N);
        retorno->put(&temp);
    }
    delete [] buffer;
    delete [] ret;
    return retorno;
}

template <class Type> IRWSet<Type>* RWBufferedDpIntervalBuilder<Type>::getOverlapingIntervals(IRWItem<Type>* Input, uint_32t N, uint_32t Increment) {
    Type * buffer = new Type[Input->getNpoints()];
    Type t;
    int j = 0;
    while (Input->getNext(t)) {
        buffer[j++] = t;
    }
    uint_32t p = (double) (Input->getNpoints() - N) / Increment + 1;
    Input->resetIterator();
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWBufferedDpSet<Type>(p);
    RWBufferManagerSingleton<Type> * rwbfs = RWBufferManagerSingleton<Type>::getInstance();
    for (int i = 0; i < p; i++) {
        memcpy(ret, &buffer[i * Increment], N * sizeof (Type));
        RWBufferedDp<Type> temp = rwbfs->createDpItem(ret, N);
        retorno->put(&temp);
    }
    delete [] buffer;
    delete [] ret;
    return retorno;
}


#endif	/* RWBUFFEREDINTERVALBUILDER_H */

