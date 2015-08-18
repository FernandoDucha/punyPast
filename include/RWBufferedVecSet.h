/* 
 * File:   RWBufferedVecSet.h
 * Author: fordem
 *
 * Created on March 6, 2015, 10:45 AM
 */

#ifndef RWBUFFEREDVECSET_H
#define	RWBUFFEREDVECSET_H
#include "IRWSet.h"
#include "RWBufferedVec.h"
template <class Type> class IRWSet;

template <class Type> class RWBufferedVecSet : public IRWSet<Type> {
public:
    RWBufferedVecSet(unsigned long n);
    virtual ~RWBufferedVecSet();
    virtual void put(IRWItem<Type> * a);
    virtual IRWItem<Type> * getNext();
    virtual IRWItem<Type> * getElement(unsigned long int p);
    virtual unsigned long int getSize() const;
    virtual void resetIterator();
    virtual Type getMin() const;
    virtual Type getMax() const;

    void setTypeMax() {
        this->max = numeric_limits<Type>::min();
    }

    void setTypeMin() {
        this->min = numeric_limits<Type>::max();
    }
private:
    RWBufferedVec<Type> ** list;
    unsigned long int size;
    unsigned long int pos, pos_temp;
};

template<class Type> RWBufferedVecSet<Type>::RWBufferedVecSet(unsigned long n) {
    size = n;
    pos = 0;
    pos_temp = 0;
    list = new RWBufferedVec<Type>*[size];
    setTypeMin();
    setTypeMax();
}

template<class Type> RWBufferedVecSet<Type>::~RWBufferedVecSet() {
    for (int i = 0; i < size; i++) {
        delete list[i];
    }
    delete [] list;
}

template<class Type> void RWBufferedVecSet<Type>::put(IRWItem<Type> * a) {
    if (pos < size) {
        list[pos++] = new RWBufferedVec<Type>(*dynamic_cast<RWBufferedVec<Type>*> (a));
        if (a->getMax() > this->max) {
            this->max = a->getMax();
        }
        if (a->getMin() < this->min) {
            this->min = a->getMin();
        }
    }
}

template<class Type> IRWItem<Type> * RWBufferedVecSet<Type>::getNext() {
    return list[pos_temp++];
}

template<class Type> IRWItem<Type> * RWBufferedVecSet<Type>::getElement(unsigned long int p) {
    if (p < size) {
        return list[p]; // = new RWBufferedDp<Type>(*a);
    }
    return NULL;
}

template<class Type> unsigned long int RWBufferedVecSet<Type>::getSize() const {
    return size;
}

template<class Type> void RWBufferedVecSet<Type>::resetIterator() {
    pos_temp = 0;
}

template<class Type> Type RWBufferedVecSet<Type>::getMin() const {
    return this->min;
}

template<class Type> Type RWBufferedVecSet<Type>::getMax() const {
    return this->max;
}

#endif	/* RWBUFFEREDVECSET_H */

