/* 
 * File:   RandomWalkMatrix.h
 * Author: fernando
 *
 * Created on 30 de Abril de 2013, 09:35
 */

#ifndef RWVECSET_H
#define	RWVECSET_H
#include "IRWSet.h"
#include "RWVec.h"
#include <stdio.h>
#include <stdlib.h>
template <class Type> class IRWSet;

template <class type>class RWVecSet : public IRWSet<type> {
public:
    RWVecSet(unsigned long int s);
    virtual ~RWVecSet();
    void put(IRWItem<type> * a);
    IRWItem<type> * getNext();
    IRWItem<type> * getElement(unsigned long int p);
    unsigned long int getSize() const;
    void resetIterator();
    type getMin() const;
    type getMax() const;

    void setTypeMax() {
        this->max = numeric_limits<type>::min();
    }

    void setTypeMin() {
        this->min = numeric_limits<type>::max();
    }
private:
    IRWItem<type>** list;
    unsigned long int size;
    unsigned long int pos, pos_temp;
};

template <class type>type RWVecSet<type>::getMin() const {
    return this->min;
}

template <class type>type RWVecSet<type>::getMax() const {
    return this->max;
}

template <class type>RWVecSet<type>::RWVecSet(unsigned long int s) {
    size = s;
    list = new IRWItem<type> *[s];
    setTypeMin();
    setTypeMax();
    pos_temp = pos = 0;
}

template <class type> void RWVecSet<type>::put(IRWItem<type> * a) {
    if (pos < size) {
        list[pos] = a;
        if (a->getMax() > this->max) {
            this->max = a->getMax();
        }
        if (a->getMin() < this->min) {
            this->min = a->getMin();
        }
        pos++;
    } else {
        fprintf(stderr, "ERRO: Esse conjunto não pode possuir mais que %lu elementos.", size);
    }

}

template <class type>RWVecSet<type>::~RWVecSet() {
    for (unsigned int i = 0; i < size; i++) {
        IRWItem<type> * a = list[i];
        delete a;
    }
    delete list;
}

template <class type> IRWItem<type> * RWVecSet<type>::getNext() {
    if (pos_temp <= pos) {
        int p = pos_temp;
        pos_temp++;
        return list[p];
    } else {
        pos_temp = 0;
        return NULL;
    }
}

template <class type> IRWItem<type> * RWVecSet<type>::getElement(unsigned long int p) {
    if (p <= size) {
        return list[p];
    } else {
        return NULL;
    }
}

template <class type> unsigned long int RWVecSet<type>::getSize() const {
    return size;
}

template <class type> void RWVecSet<type>::resetIterator() {
    pos_temp = 0;
}
#endif	/* RANDOMWALKMATRIX_H */

