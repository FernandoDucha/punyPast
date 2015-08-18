/* 
 * File:   PollarRwDpSet.h
 * Author: fordem
 *
 * Created on August 14, 2015, 2:00 PM
 */

#ifndef POLLARRWDPSET_H
#define	POLLARRWDPSET_H
#include "PollarRwDp.h"
#include "IRWSet.h"
#include "QPollarF.h"

class PollarRwDpSet : public IRWSet<QPollarF> {
public:
    PollarRwDpSet(unsigned long int size);
    virtual ~PollarRwDpSet();
    void put(IRWItem<QPollarF> * a);
    IRWItem<QPollarF> * getNext();
    IRWItem<QPollarF> * getElement(unsigned long int p);
    unsigned long int getSize() const;
    void resetIterator();
    QPollarF getMin() const;
    QPollarF getMax() const;

    void setTypeMax() {
        this->max = QPollarF(numeric_limits<double>::min(), numeric_limits<double>::min());
    }

    void setTypeMin() {
        this->min = QPollarF(numeric_limits<double>::max(), numeric_limits<double>::max());
    }
private:
    PollarRwDp ** list;
    unsigned long int size;
    unsigned long int pos, pos_temp;
private:

};
inline void PollarRwDpSet::put(IRWItem<QPollarF> * a) {
    if (pos < size) {
        if(dynamic_cast<PollarRwDp*>(a)==nullptr){
            std::cout<<"Item PollarRwDp no Valid"<<endl;
            exit(1);
        }
        list[pos] = dynamic_cast<PollarRwDp*>(a);
        if (a->getMax().rx() > this->max.rx()) {
            this->max.setX(a->getMax().rx());
        }
        if (a->getMax().ry() > this->max.ry()) {
            this->max.setY(a->getMax().ry());
        }
        if (a->getMin().rx() < this->min.rx()) {
            this->min.setX(a->getMin().rx());
        }
        if (a->getMin().ry() < this->min.ry()) {
            this->min.setY(a->getMin().ry());
        }
        pos++;
    } else {
        fprintf(stderr, "ERRO: Esse conjunto não suporta mais que %lu elementos.", size);
    }
}

inline PollarRwDpSet::PollarRwDpSet(unsigned long int size) {
    list = new PollarRwDp*[size];
    for (unsigned int i = 0; i < size; i++) {
        list[i] = NULL;
    }
    this->size = size;
    pos_temp = pos = 0;
    setTypeMax();
    setTypeMin();
}

inline PollarRwDpSet::~PollarRwDpSet() {
    for(int i=0;i<this->size;i++){
        delete list[i];
    }
    delete [] list;
}

inline IRWItem<QPollarF> * PollarRwDpSet::getNext() {
    if (pos_temp <= pos) {
        int p = pos_temp;
        pos_temp++;
        return list[p];
    } else {
        pos_temp = 0;
        return NULL;
    }
}

inline IRWItem<QPollarF> * PollarRwDpSet::getElement(unsigned long int p) {
    if (p < size) {
        return list[p];
    } else {
        return NULL;
    }
}

inline unsigned long int PollarRwDpSet::getSize() const {
    return size;
}

inline void PollarRwDpSet::resetIterator() {
    pos_temp = 0;
}

inline QPollarF PollarRwDpSet::getMin() const {
    return this->min;
}

inline QPollarF PollarRwDpSet::getMax() const {
    return this->max;
}
#endif	/* POLLARRWDPSET_H */

