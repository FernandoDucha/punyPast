/* 
 * File:   BufferedPollarRwDp.h
 * Author: fordem
 *
 * Created on August 13, 2015, 9:54 AM
 */

#ifndef BUFFEREDPOLLARRWDP_H
#define	BUFFEREDPOLLARRWDP_H
#include "IRWBufferedItem.h"
#include "PollarFileInStreamInterface.h"
#include "PollarFileOutStreamInterface.h"
#include <iostream>
template <class QPollarF> class IRWBufferedItem;

class BufferedPollarRwDp : public IRWBufferedItem<QPollarF> {
public:
    BufferedPollarRwDp(PollarFileInStreamInterface* in, PollarFileOutStreamInterface * out);
    BufferedPollarRwDp(PollarFileInStreamInterface * in, PollarFileOutStreamInterface * out, RWLocPair lcpair);
    BufferedPollarRwDp(const BufferedPollarRwDp&);
    virtual ~BufferedPollarRwDp();
    virtual bool getNext(QPollarF &);
    virtual QPollarF getElement(unsigned long int pos);
    unsigned long int getNpoints() const;
    virtual void resetIterator();
    virtual void modulo();
    virtual void setNpoints(unsigned long int Npoints);
    virtual IRWItem<QPollarF> & operator+=(IRWItem<QPollarF> &);
    virtual IRWItem<QPollarF> & operator-=(IRWItem<QPollarF>&);
    virtual bool operator==(IRWItem<QPollarF>&);
    virtual bool operator!=(IRWItem<QPollarF>&);
    virtual QPollarF sum();
    virtual unsigned long int getActualPoint()const;
    virtual void print();
    virtual void receiveData(QPollarF * data, long unsigned int n, uint64_t pos);
    virtual void receiveData(QPollarF* data, long unsigned int n);
    virtual uint64_t getFInitPos() const;
    virtual void setFInitPos(uint64_t fpos);
    virtual QPollarF getMin()const;
    virtual QPollarF getMax()const;
    uint_32t getEpsilonN(double);
    double average();
    IRWItem<double> * getIntegral();
    IRWItem<double> * power(double);
    BufferedPollarRwDp& operator=(IRWItem<QPollarF>& rhs);
    QPollarF * data(){
        std::cerr<<"This object is buffered on disk returning NULL."<<std::endl;
        return nullptr;
    }
private:
    virtual QPollarF & operator[](uint32_t a);
    unsigned long int Npoints;
    unsigned long int actualPoint;
};

inline BufferedPollarRwDp& BufferedPollarRwDp::operator=(IRWItem<QPollarF>& rhs) {
    if (this == &rhs) {
        return *this;
    } else if (this->getNpoints() == rhs.getNpoints()) {
        min = rhs.getMin();
        max = rhs.getMax();
        rhs.resetIterator();
        this->resetIterator();
        QPollarF rhsElem;
        for (int i = 0; i < rhs.getNpoints(); i++) {
            rhs.getNext(rhsElem);
            dynamic_cast<PollarFileOutStreamInterface*> (output)->write(rhsElem);
        }
        return *this;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}

inline BufferedPollarRwDp::BufferedPollarRwDp(const BufferedPollarRwDp& clone) : IRWBufferedItem<QPollarF>(clone.getInput(), clone.getOutput()) {
    this->finitpos = clone.getFInitPos();
    this->Npoints = clone.getNpoints();
    this->actualPoint = clone.getActualPoint();
}

inline IRWItem<double> * BufferedPollarRwDp::getIntegral() {
    return NULL;
    //    double avg = average();
    //    double * data = new QPollarF[Npoints];
    //    for (int i = 0; i < Npoints; i++) {
    //        resetIterator();
    //        data[i] = 0;
    //        for (int j = 0; j <= i; j++) {
    //            QPollarF a;
    //            getNext(a);
    //            data[i] += a - avg;
    //        }
    //    }
    //    IRWItem<double> * ret = new RWDp<double>();
    //    ret->receiveData(data, Npoints);
    //    delete [] data;
    //    return ret;
}

inline IRWItem<double> * BufferedPollarRwDp::power(double a) {
    //    double * data = new double[Npoints];
    //    for (int i = 0; i < Npoints; i++) {
    //        resetIterator();
    //        QPollarF elem;
    //        getNext(elem);
    //        data[i] += pow(elem,a);
    //    }
    //    IRWItem<double> * ret = new RWVec<double>();
    //    ret->receiveData(data, Npoints);
    //    delete [] data;
    //    return ret;
    return nullptr;
}

inline BufferedPollarRwDp::BufferedPollarRwDp(PollarFileInStreamInterface* in, PollarFileOutStreamInterface * out, RWLocPair lcpair) : IRWBufferedItem<QPollarF>(in, out) {
    this->finitpos = lcpair[RWLocPair::POS];
    this->Npoints = lcpair[RWLocPair::LEN];
}

inline double BufferedPollarRwDp::average() {
    return NAN;
}

inline BufferedPollarRwDp::BufferedPollarRwDp(PollarFileInStreamInterface * in, PollarFileOutStreamInterface * out) : IRWBufferedItem<QPollarF>(in, out) {
    this->actualPoint = 0;
    this->finitpos = 0;
    min.setX(std::numeric_limits<double>::max());
    min.setY(std::numeric_limits<double>::max());
    max.setX(std::numeric_limits<double>::min());
    max.setY(std::numeric_limits<double>::min());
}

inline BufferedPollarRwDp::~BufferedPollarRwDp() {
}

inline uint_32t BufferedPollarRwDp::getEpsilonN(double e) {
    if (e > 0 && e < 1) {
        uint_32t a = e * getNpoints();
        return a;
    } else {
        std::cerr << "Epsilon menor que 0 ou maior que 1.";
    }
    return NAN;
}

//template <class QPollarF> IRWSet<QPollarF>* BufferedPollarRwDp<QPollarF>::getIntervals(uint_32t N) {
//    uint_32t p = (double) getNpoints() / N;
//    resetIterator();
//    QPollarF* ret = new QPollarF[N];
//    IRWSet<QPollarF> * retorno = new RWDpSet<QPollarF>(p);
//    for (int i = 0; i < p; i++) {
//        IRWItem<QPollarF> * temp = new RWDp<QPollarF>();
//        for (int j = 0; j < N; j++) {
//            ret[j] = this->input->read();
//        }
//        temp->receiveData(ret,N);
//        retorno->put(temp);
//    }
//    delete ret;
//    return retorno;
//}

inline void BufferedPollarRwDp::receiveData(QPollarF * data, long unsigned int n, uint64_t pos) {
    this->finitpos = pos;
    this->Npoints = n;
    this->output->seek(this->finitpos);
    for (unsigned int i = 0; i < Npoints; i++) {
        this->output->write(data[i]);
        if (data[i].x() > this->max.x()) {
            this->max.setX(data[i].x());
        }
        if (data[i].x() < this->min.x()) {
            this->min.setX(data[i].x());
        }
        if (data[i].y() > this->max.y()) {
            this->max.setY(data[i].y());
        }
        if (data[i].y() < this->min.y()) {
            this->min.setY(data[i].y());
        }
    }
    this->output->flush();
}

inline bool BufferedPollarRwDp::getNext(QPollarF & nxt) {

    uint64_t offSet = this->actualPoint * 2 * sizeof (double);
    uint64_t posToSeek = this->finitpos + offSet;
    this->input->seek(posToSeek);
    if (this->actualPoint<this->Npoints) {
        nxt = dynamic_cast<PollarFileInStreamInterface*> (input)->read();
        this->actualPoint++;
        return true;
    } else {
        return false;
    }
}

inline QPollarF BufferedPollarRwDp::getElement(unsigned long int pos) {
    assert(pos<this->Npoints);
    uint64_t offSet = pos * 2 * sizeof (double);
    uint64_t posToSeek = this->finitpos + offSet;
    this->input->seek(posToSeek);
    QPollarF ret = dynamic_cast<PollarFileInStreamInterface*> (input)->read();
    return ret;
}

inline void BufferedPollarRwDp::resetIterator() {
    this->input->seek(this->finitpos);
    this->output->seek(this->finitpos);
    this->actualPoint = 0;
}

inline void BufferedPollarRwDp::modulo() {
    QPollarF * buff = new QPollarF[this->Npoints];
    this->input->seek(this->finitpos);
    for (int i = 0; i<this->Npoints; i++) {
        QPollarF t = dynamic_cast<PollarFileInStreamInterface*> (input)->read();
        buff[i].setX(t.x() > 0 ? t.x() : -t.x());
        buff[i].setY(t.y() > 0 ? t.y() : -t.y());
    }
    this->output->seek(this->finitpos);
    for (int i = 0; i<this->Npoints; i++) {
        this->output->write(buff[i]);
    }
    delete [] buff;
}

inline void BufferedPollarRwDp::setNpoints(unsigned long int Npoints) {
    this->Npoints = Npoints;
}

inline IRWItem<QPollarF> & BufferedPollarRwDp::operator+=(IRWItem<QPollarF> & rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        QPollarF tmin = QPollarF(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        QPollarF tmax = QPollarF(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
        QPollarF * buff = new QPollarF[Npoints];
        this->resetIterator();
        rhs.resetIterator();
        QPollarF temp;
        for (unsigned int i = 0; i < rhs.getNpoints(); i++) {
            this->getNext(buff[i]);
            rhs.getNext(temp);
            buff[i] += temp;
            if (buff[i].x() > tmax.x()) {
                tmax.setX(buff[i].x());
            }
            if (buff[i].x() < tmin.x()) {
                tmin.setX(buff[i].x());
            }
            if (buff[i].y() > tmax.y()) {
                tmax.setY(buff[i].y());
            }
            if (buff[i].y() < tmin.y()) {
                tmin.setY(buff[i].y());
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

//template <class QPollarF>IRWBufferedItem<QPollarF> & IBufferedPollarRwDp<QPollarF>::operator=(IRWBufferedItem<QPollarF> & rhs) {
//    if (this->getNpoints() == rhs.getNpoints()) {
//        QPollarF tmax = 0, tmin = 0;
//        this->output->seek(finitpos);
//        QPollarF temp;
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

inline IRWItem<QPollarF> & BufferedPollarRwDp::operator-=(IRWItem<QPollarF>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        QPollarF tmin = QPollarF(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        QPollarF tmax = QPollarF(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
        QPollarF * buff = new QPollarF[Npoints];
        this->resetIterator();
        rhs.resetIterator();
        QPollarF temp;
        for (unsigned int i = 0; i < rhs.getNpoints(); i++) {
            this->getNext(buff[i]);
            rhs.getNext(temp);
            buff[i] -= temp;
            if (buff[i].x() > tmax.x()) {
                tmax.setX(buff[i].x());
            }
            if (buff[i].x() < tmin.x()) {
                tmin.setX(buff[i].x());
            }
            if (buff[i].y() > tmax.y()) {
                tmax.setY(buff[i].y());
            }
            if (buff[i].y() < tmin.y()) {
                tmin.setY(buff[i].y());
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

inline bool BufferedPollarRwDp::operator==(IRWItem<QPollarF>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        this->resetIterator();
        rhs.resetIterator();
        QPollarF lhs, rhs1;
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

inline bool BufferedPollarRwDp::operator!=(IRWItem<QPollarF>& rhs) {
    bool ret = !(*this == rhs);
    return ret;
}

inline QPollarF & BufferedPollarRwDp::operator[](uint32_t a) {
    QPollarF ret = this->getElement(a);
    return ret;
}

inline QPollarF BufferedPollarRwDp::sum() {
    this->resetIterator();
    QPollarF ret, temp;
    for (unsigned int i = 0; i < getNpoints(); i++) {
        this->getNext(temp);
        ret += temp;
    }
    this->resetIterator();
    return ret;
}

inline unsigned long int BufferedPollarRwDp::getActualPoint()const {
    return actualPoint;
}

inline void BufferedPollarRwDp::print() {
    resetIterator();
    QPollarF t;
    for (unsigned long int i = 0; i < Npoints; i++) {
        getNext(t);
        std::cout << "(" << t.x() << "," << t.y() << ") " << std::endl;
    }
    cout << endl;
    resetIterator();
}

inline uint64_t BufferedPollarRwDp::getFInitPos()const {
    return this->finitpos;
}

inline void BufferedPollarRwDp::setFInitPos(uint64_t fpos) {
    this->finitpos = fpos;
}

inline void BufferedPollarRwDp::receiveData(QPollarF* data, long unsigned int n) {
    receiveData(data, n, this->finitpos);
}

inline QPollarF BufferedPollarRwDp::getMin() const {
    return this->min;
}

inline QPollarF BufferedPollarRwDp::getMax() const {
    return this->max;
}

inline unsigned long int BufferedPollarRwDp::getNpoints() const {
    return Npoints;
}
#endif	/* BUFFEREDPOLLARRWDP_H */

