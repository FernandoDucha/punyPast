/* 
 * File:   IRWBufferedDp.h
 * Author: fordem
 *
 * Created on March 3, 2015, 6:40 PM
 */

#ifndef RWBUFFEREDDP_H
#define	RWBUFFEREDDP_H
#include <assert.h>
#include "IRWBufferedItem.h"
#include <iostream>
#include "RWLocPair.h"
#include "RWDpSet.h"
//#include "FileStreamInterface.h"
using namespace std;
template <class Type> class IRWBufferedItem;

template <class Type> class RWBufferedDp : public IRWBufferedItem<Type> {
public:
    RWBufferedDp(FileInStreamInterface<Type> * in, FileOutStreamInterface<Type> * out);
    RWBufferedDp(FileInStreamInterface<Type> * in, FileOutStreamInterface<Type> * out, RWLocPair lcpair);
    RWBufferedDp(const RWBufferedDp<Type>&);
    virtual ~RWBufferedDp();
    virtual bool getNext(Type &);
    virtual Type getElement(unsigned long int pos);
    unsigned long int getNpoints() const;
    virtual void resetIterator();
    virtual void modulo();
    virtual void setNpoints(unsigned long int Npoints);
    virtual IRWItem<Type> & operator+=(IRWItem<Type> &);
    virtual IRWItem<Type> & operator-=(IRWItem<Type>&);
    virtual bool operator==(IRWItem<Type>&);
    virtual bool operator!=(IRWItem<Type>&);
    virtual Type sum();
    virtual unsigned long int getActualPoint()const;
    virtual void print();
    virtual void receiveData(Type * data, long unsigned int n, uint64_t pos);
    virtual void receiveData(Type* data, long unsigned int n);
    virtual uint64_t getFInitPos() const;
    virtual void setFInitPos(uint64_t fpos);
    virtual Type getMin()const;
    virtual Type getMax()const;
    uint_32t getEpsilonN(double);
    //    IRWSet<Type>* getIntervals(uint_32t);
    double average();
    IRWItem<double> * getIntegral();
    IRWItem<double> * power(double);
    Type * data(){
        std::cerr<<"This object is buffered on disk returning NULL."<<std::endl;
        return nullptr;
    }
private:
    virtual Type & operator[](uint32_t a);
    unsigned long int Npoints;
    unsigned long int actualPoint;
};

template <class Type> RWBufferedDp<Type>::RWBufferedDp(const RWBufferedDp<Type>& clone) : IRWBufferedItem<Type>(clone.getInput(), clone.getOutput()) {
    this->finitpos = clone.getFInitPos();
    this->Npoints = clone.getNpoints();
    this->actualPoint = clone.getActualPoint();
}

template <class Type> IRWItem<double> * RWBufferedDp<Type>::getIntegral() {
    double avg = average();
    double * data = new double[Npoints];
    for (int i = 0; i < Npoints; i++) {
        resetIterator();
        data[i] = 0;
        for (int j = 0; j <= i; j++) {
            Type a;
            getNext(a);
            data[i] += a - avg;
        }
    }
    IRWItem<double> * ret = new RWDp<double>();
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}
template <class Type> IRWItem<double> * RWBufferedDp<Type>::power(double a){
    double * data = new double[Npoints];
    for (int i = 0; i < Npoints; i++) {
        resetIterator();
        Type elem;
        getNext(elem);
        data[i] += pow(elem,a);
    }
    IRWItem<double> * ret = new RWVec<double>();
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}
template <class Type> RWBufferedDp<Type>::RWBufferedDp(FileInStreamInterface<Type> * in, FileOutStreamInterface<Type> * out, RWLocPair lcpair) : IRWBufferedItem<Type>(in, out) {
    this->finitpos = lcpair[RWLocPair::POS];
    this->Npoints = lcpair[RWLocPair::LEN];

}

template <class Type> double RWBufferedDp<Type>::average() {
    double ret = (double) 1 / Npoints * sum();
    return ret;
}

template <class Type> RWBufferedDp<Type>::RWBufferedDp(FileInStreamInterface<Type> * in, FileOutStreamInterface<Type> * out) : IRWBufferedItem<Type>(in, out) {
    this->actualPoint = 0;
    this->finitpos = 0;
    this->input = in;
    this->output = out;

}

template <class Type> RWBufferedDp<Type>::~RWBufferedDp() {
}

template <class Type> uint_32t RWBufferedDp<Type>::getEpsilonN(double e) {
    if (e > 0 && e < 1) {
        uint_32t a = e * getNpoints();
        return a;
    } else {
        std::cerr << "Epsilon menor que 0 ou maior que 1.";
    }
    return NAN;
}

//template <class Type> IRWSet<Type>* RWBufferedDp<Type>::getIntervals(uint_32t N) {
//    uint_32t p = (double) getNpoints() / N;
//    resetIterator();
//    Type* ret = new Type[N];
//    IRWSet<Type> * retorno = new RWDpSet<Type>(p);
//    for (int i = 0; i < p; i++) {
//        IRWItem<Type> * temp = new RWDp<Type>();
//        for (int j = 0; j < N; j++) {
//            ret[j] = this->input->read();
//        }
//        temp->receiveData(ret,N);
//        retorno->put(temp);
//    }
//    delete ret;
//    return retorno;
//}

template <class Type> void RWBufferedDp<Type>::receiveData(Type * data, long unsigned int n, uint64_t pos) {
    this->finitpos = pos;
    this->Npoints = n;
    this->output->seek(this->finitpos);
    for (unsigned int i = 0; i < Npoints; i++) {
        this->output->write(data[i]);
        if (data[i] > this->max) {
            this->max = data[i];
        } else if (data[i] < this->min) {
            this->min = data[i];
        }
    }
    this->output->flush();
}

template <class Type> bool RWBufferedDp<Type>::getNext(Type & nxt) {

    uint64_t offSet = this->actualPoint * this->sizeOfType;
    uint64_t posToSeek = this->finitpos + offSet;
    this->input->seek(posToSeek);
    if (this->actualPoint<this->Npoints) {
        nxt = this->input->read();
        this->actualPoint++;
        return true;
    } else {
        return false;
    }
}

template <class Type> Type RWBufferedDp<Type>::getElement(unsigned long int pos) {
    assert(pos<this->Npoints);
    uint64_t offSet = pos * this->sizeOfType;
    uint64_t posToSeek = this->finitpos + offSet;
    this->input->seek(posToSeek);
    Type ret = this->input->read();
    return ret;

}

template <class Type> void RWBufferedDp<Type>::resetIterator() {
    this->input->seek(this->finitpos);
    this->output->seek(this->finitpos);
    this->actualPoint = 0;
}

template <class Type> void RWBufferedDp<Type>::modulo() {
    Type * buff = new Type[this->Npoints];
    this->input->seek(this->finitpos);
    for (int i = 0; i<this->Npoints; i++) {
        Type t = this->input->read();
        buff[i] = t > 0 ? t : -t;
    }
    this->output->seek(this->finitpos);
    for (int i = 0; i<this->Npoints; i++) {
        this->output->write(buff[i]);
    }
    delete [] buff;
}

template <class Type> void RWBufferedDp<Type>::setNpoints(unsigned long int Npoints) {
    this->Npoints = Npoints;
}

template <class Type>IRWItem<Type> & RWBufferedDp<Type>::operator+=(IRWItem<Type> & rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        Type tmax = 0, tmin = 0;
        Type * buff = new Type[Npoints];
        this->resetIterator();
        rhs.resetIterator();
        Type temp;
        for (unsigned int i = 0; i < rhs.getNpoints(); i++) {
            this->getNext(buff[i]);
            rhs.getNext(temp);
            buff[i] += temp;
            if (buff[i] > tmax) {
                tmax = buff[i];
            } else if (buff[i] < tmin) {
                tmin = buff[i];
            }
        }
        this->receiveData(buff, Npoints);
        delete [] buff;
        this->max = tmax;
        this->min = tmin;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
    this->resetIterator();
    rhs.resetIterator();
    return *this;
}

//template <class Type>IRWBufferedItem<Type> & IRWBufferedDp<Type>::operator=(IRWBufferedItem<Type> & rhs) {
//    if (this->getNpoints() == rhs.getNpoints()) {
//        Type tmax = 0, tmin = 0;
//        this->output->seek(finitpos);
//        Type temp;
//        for (unsigned int i = 0; i < rhs.getNpoints(); i++) {
//            rhs.getNext(temp);
//            this->castWrite(this->output)->write(temp);
//            if (temp > tmax) {
//                tmax = temp;
//            } else if (temp < tmin) {
//                tmin = temp;
//            }
//        }
//        max = tmax;
//        min = tmin;
//    } else {
//        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
//        exit(0);
//    }
//    return *this;
//}
//

template <class Type>IRWItem<Type> & RWBufferedDp<Type>::operator-=(IRWItem<Type>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        Type tmax = 0, tmin = 0;
        Type * buff = new Type[Npoints];
        this->resetIterator();
        rhs.resetIterator();
        Type temp;
        for (unsigned int i = 0; i < rhs.getNpoints(); i++) {
            this->getNext(buff[i]);
            rhs.getNext(temp);
            buff[i] -= temp;
            if (buff[i] > tmax) {
                tmax = buff[i];
            } else if (buff[i] < tmin) {
                tmin = buff[i];
            }
        }
        this->receiveData(buff, Npoints);
        delete [] buff;
        this->max = tmax;
        this->min = tmin;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
    this->resetIterator();
    rhs.resetIterator();
    return *this;
}

template <class Type>bool RWBufferedDp<Type>::operator==(IRWItem<Type>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        this->resetIterator();
        rhs.resetIterator();
        Type lhs, rhs1;
        for (unsigned int i = 0; i < rhs.getNpoints(); i++) {
            this->getNext(lhs);
            rhs.getNext(rhs1);
            if (lhs != rhs1) {
                this->resetIterator();
                rhs.resetIterator();
                return false;
            }
        }
        this->resetIterator();
        rhs.resetIterator();
        return true;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}

template <class Type>bool RWBufferedDp<Type>::operator!=(IRWItem<Type>& rhs) {
    bool ret = !(*this == rhs);
    return ret;
}

template <class Type>Type & RWBufferedDp<Type>::operator[](uint32_t a) {
    Type ret = this->getElement(a);
    return ret;
}

template <class Type>Type RWBufferedDp<Type>::sum() {
    this->resetIterator();
    Type ret = 0, temp;
    for (unsigned int i = 0; i < getNpoints(); i++) {
        this->getNext(temp);
        ret += temp;
    }
    this->resetIterator();
    return ret;
}

template <class Type>unsigned long int RWBufferedDp<Type>::getActualPoint()const {
    return actualPoint;
}

template <class Type>void RWBufferedDp<Type>::print() {
    resetIterator();
    Type t;
    for (unsigned long int i = 0; i < Npoints; i++) {
        getNext(t);
        cout << " " << t;
    }
    cout << endl;
    resetIterator();
}

template <class Type> uint64_t RWBufferedDp<Type>::getFInitPos()const {
    return this->finitpos;
}

template <class Type> void RWBufferedDp<Type>::setFInitPos(uint64_t fpos) {
    this->finitpos = fpos;
}

template <class Type> void RWBufferedDp<Type>::receiveData(Type* data, long unsigned int n) {
    receiveData(data, n, this->finitpos);
}

template <class Type> Type RWBufferedDp<Type>::getMin() const {
    return this->min;
}

template <class Type> Type RWBufferedDp<Type>::getMax() const {
    return this->max;
}

template <class Type> unsigned long int RWBufferedDp<Type>::getNpoints() const {
    return Npoints;
}



#endif	/* RWBUFFEREDDP_H */

