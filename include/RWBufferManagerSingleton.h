/* 
 * File:   RWBufferedManagerSingleton.h
 * Author: fordem
 *
 * Created on June 2, 2015, 11:29 AM
 */

#ifndef RWBUFFERMANAGERSINGLETON_H
#define	RWBUFFERMANAGERSINGLETON_H
#include "RWBufferManager.h"
#include "RWBufferIterator.h"
#include <string>
template <class Type> class RWBufferManagerSingleton {
public:
    virtual ~RWBufferManagerSingleton();
    static RWBufferManagerSingleton<Type> * getInstance();
    RWBufferedDp<Type> * createDpItem(Type * data, unsigned long int n);
    RWBufferedVec<Type> * createVecItem(Type * data, unsigned long int n);
    RWBufferIterator<Type, RWBufferedDp<Type>> getDoubleIterator();
private:
    RWBufferManagerSingleton();
    RWBufferManager<Type> * TemporaryBM;
    static RWBufferManagerSingleton<Type> * instance;  
};
template <class Type>RWBufferManagerSingleton<Type> * RWBufferManagerSingleton<Type>::instance = 0;

template <class Type>RWBufferManagerSingleton<Type>::RWBufferManagerSingleton() {
    string  s = typeid(Type).name();
    s+="Temp";
    TemporaryBM = new RWBufferManager<Type>(const_cast<char*>(s.c_str()));
}

template <class Type>RWBufferManagerSingleton<Type> * RWBufferManagerSingleton<Type>::getInstance() {
    if (instance == NULL) {
        instance = new RWBufferManagerSingleton();
    }
    return instance;
}

template <class Type> RWBufferManagerSingleton<Type>::~RWBufferManagerSingleton() {
    TemporaryBM->resetManager();
    delete TemporaryBM;
}

template <class Type>  RWBufferedDp<Type> * RWBufferManagerSingleton<Type>::createDpItem(Type * data, unsigned long int n) {
    RWBufferedDp<Type> * ret = dynamic_cast<RWBufferedDp<double> *>(TemporaryBM->createBufferedDp(data, n));
    return ret;
}
template <class Type> RWBufferedVec<Type>  * RWBufferManagerSingleton<Type>::createVecItem(Type * data, unsigned long int n) {
    RWBufferedVec<Type> * ret =dynamic_cast<RWBufferedDp<double> *>(TemporaryBM->createBufferedVec(data, n));
    return ret;
}


template <class Type> RWBufferIterator<Type, RWBufferedDp<Type>> RWBufferManagerSingleton<Type>::getDoubleIterator() {
    return TemporaryBM->getDpIterator();
}
#endif	/* RWBUFFEREDMANAGERSINGLETON_H */

