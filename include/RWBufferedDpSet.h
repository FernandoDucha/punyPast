/* 
 * File:   IRWBufferedDpSet.h
 * Author: fordem
 *
 * Created on March 4, 2015, 5:58 PM
 */

#ifndef RWBUFFEREDDPSET_H
#define	RWBUFFEREDDPSET_H
#include "IRWSet.h"
#include "RWBufferedDp.h"
template <class Type> class IRWSet;

template<class Type>class RWBufferedDpSet : public IRWSet< Type> {
public:
    RWBufferedDpSet(unsigned long n);
    virtual ~RWBufferedDpSet();
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
    RWBufferedDp<Type> ** list;
    unsigned long int size;
    unsigned long int pos, pos_temp;
};

template<class Type> RWBufferedDpSet<Type>::RWBufferedDpSet(unsigned long n) {
    size = n;
    pos = 0;
    pos_temp = 0;
    list = new RWBufferedDp<Type>*[size];
    setTypeMin();
    setTypeMax();
}

template<class Type> RWBufferedDpSet<Type>::~RWBufferedDpSet() {
    for (int i = 0; i < size; i++) {
        delete list[i];
    }
    delete [] list;
}

template<class Type> void RWBufferedDpSet<Type>::put(IRWItem<Type> * a) {
    if (pos < size) {

        list[pos++] = new RWBufferedDp<Type>(*dynamic_cast<RWBufferedDp<Type>*> (a));
        if (a->getMax() > this->max) {
            this->max = a->getMax();
        }
        if (a->getMin() < this->min) {
            this->min = a->getMin();
        }
    }
}

template<class Type> IRWItem<Type> * RWBufferedDpSet<Type>::getNext() {
    return list[pos_temp++];
}

template<class Type> IRWItem<Type> * RWBufferedDpSet<Type>::getElement(unsigned long int p) {
    if (p < size) {
        return list[p]; // = new RWBufferedDp<Type>(*a);
    }
    return NULL;
}

template<class Type> unsigned long int RWBufferedDpSet<Type>::getSize() const {
    return size;
}

template<class Type> void RWBufferedDpSet<Type>::resetIterator() {
    pos_temp = 0;
}

template<class Type> Type RWBufferedDpSet<Type>::getMin() const {
    return this->min;
}

template<class Type> Type RWBufferedDpSet<Type>::getMax() const {
    return this->max;
}
#endif	/* IRWBUFFEREDDPSET_H */

