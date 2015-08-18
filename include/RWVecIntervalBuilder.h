/* 
 * File:   RWVecIntervalBuilder.h
 * Author: fordem
 *
 * Created on June 3, 2015, 7:19 PM
 */

#ifndef RWVECINTERVALBUILDER_H
#define	RWVECINTERVALBUILDER_H
#include "IRWIntervalBuilder.h"
#include "IRWSet.h"
#include "RWVec.h"

template <class Type> class RWVecIntervalBuilder : public IRWIntervalBuilder<Type> {
public:
    RWVecIntervalBuilder();
    virtual ~RWVecIntervalBuilder();
    IRWSet<Type>* getIntervals(IRWItem<Type>*, uint_32t);
    IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t);
    IRWSet<Type>* getOverlapingIntervals(IRWItem<Type>*, uint_32t, uint_32t);
    IRWItem<Type>* produceLinearInterval(double, double, double);
    IRWItem<Type>* produceLogarithmicInterval(double, double, double);
private:

};
template <class Type> IRWItem<Type>* RWVecIntervalBuilder<Type>::produceLinearInterval(double start , double end, double step){
    int it =(end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i<it; start += step, i++) {
        buffer[i] = start;
    }
    IRWItem<Type> * retorno = new RWVec<Type>();
    retorno->receiveData(buffer,it);
    delete [] buffer;
    return retorno;
}
template <class Type> IRWItem<Type>* RWVecIntervalBuilder<Type>::produceLogarithmicInterval(double start , double end, double step){
    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i<it; start += step, i++) {
        buffer[i] = log10(start);
    }
    IRWItem<Type> * retorno = new RWVec<Type>();
    retorno->receiveData(buffer,it);
    delete [] buffer;
    return retorno;
}

template <class Type> IRWSet<Type>* RWVecIntervalBuilder<Type>::getIntervals(IRWItem<Type>* Input, uint_32t N) {
    uint_32t p = (double) Input->getNpoints() / N;
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWVecSet<Type>(p);
    for (int i = 0; i < p; i++) {
        RWVec<Type> * temp = new RWVec<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i * N);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

template <class Type> IRWSet<Type>* RWVecIntervalBuilder<Type>::getOverlapingIntervals(IRWItem<Type>* Input, uint_32t N) {
    uint_32t p = Input->getNpoints() - N + 1;
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWVecSet<Type>(p);
    for (int i = 0; i < p; i++) {
        RWVec<Type> * temp = new RWVec<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

template <class Type> IRWSet<Type>* RWVecIntervalBuilder<Type>::getOverlapingIntervals(IRWItem<Type>* Input, uint_32t N, uint_32t Increment) {
    uint_32t p = (double) (Input->getNpoints() - N) / Increment + 1;
    Type* ret = new Type[N];
    IRWSet<Type> * retorno = new RWVecSet<Type>(p);
    for (int i = 0; i < p; i++) {
        RWVec<Type> * temp = new RWVec<Type>();
        for (int j = 0; j < N; j++) {
            ret[j] = Input->getElement(j + i * Increment);
        }
        temp->receiveData(ret, N);
        retorno->put(temp);
    }
    delete [] ret;
    return retorno;
}

template <class Type> RWVecIntervalBuilder<Type>::RWVecIntervalBuilder() {

}

template <class Type> RWVecIntervalBuilder<Type>::~RWVecIntervalBuilder() {

}

#endif	/* RWVECINTERVALBUILDER_H */

