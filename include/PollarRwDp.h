/* 
 * File:   PollarRwDp.h
 * Author: fordem
 *
 * Created on August 12, 2015, 8:27 PM
 */

#ifndef POLLARRWDP_H
#define	POLLARRWDP_H
#include "IRWItem.h"
#include "QPollarF.h"
#include "RWDpBase.h"
#include <iostream>
#include <limits>
#include <assert.h>
#include <cmath>

class PollarRwDp : public IRWItem<QPollarF> {
public:
    PollarRwDp();
    virtual ~PollarRwDp();
    virtual void receiveData(QPollarF * data, long unsigned int n);
    virtual bool getNext(QPollarF &);
    virtual QPollarF getElement(unsigned long int pos);
    virtual unsigned long int getNpoints() const;
    virtual void resetIterator();
    virtual QPollarF getMin() const;
    virtual QPollarF getMax() const;
    virtual void modulo();
    virtual void setNpoints(unsigned long int Npoints);
    virtual IRWItem<QPollarF> & operator+=(IRWItem<QPollarF> &);
    virtual IRWItem<QPollarF> & operator=(IRWItem<QPollarF> &);
    virtual IRWItem<QPollarF> & operator-=(IRWItem<QPollarF>&);
    virtual bool operator==(IRWItem<QPollarF>&);
    virtual bool operator!=(IRWItem<QPollarF>&);
    virtual QPollarF & operator[](uint32_t a);
    virtual QPollarF sum();
    virtual unsigned long int getActualPoint()const;
    virtual void print();
    virtual uint_32t getEpsilonN(double);
    //    virtual IRWSet<Type>* getIntervals(uint_32t)=0;
    virtual double average();
    virtual IRWItem<double> * getIntegral();
    virtual IRWItem<double> * power(double);

    QPollarF * data() {
        return pointsArray;
    }
private:
    QPollarF * pointsArray;
    unsigned long int Npoints;
    unsigned long int actualPoint;
    QPollarF max, min;
};

inline PollarRwDp::PollarRwDp() {
    Npoints = 0;
    this->pointsArray = NULL;
    actualPoint = 0;
    min.setX(std::numeric_limits<double>::max());
    min.setY(std::numeric_limits<double>::max());
    max.setX(std::numeric_limits<double>::min());
    max.setY(std::numeric_limits<double>::min());
}

inline PollarRwDp::~PollarRwDp() {
    delete [] pointsArray;
}

inline void PollarRwDp::receiveData(QPollarF * data, long unsigned int n) {
    if (this->pointsArray != NULL) {
        delete [] pointsArray;
        pointsArray = new QPollarF[n];
    } else {
        pointsArray = new QPollarF[n];
    }
    actualPoint = 0;
    Npoints = n;
    for (unsigned long int i = 0; i < n; i++) {
        pointsArray[i] = data[i];
        //cout<<i<<" Valores: "<<data[i]<<"#-#"<<pointsArray[i]<<endl;
        if (data[i].x() > max.x()) {
            max.setX(data[i].x());
        }
        if (data[i].x() < min.x()) {
            min.setX(data[i].x());
        }
        if (data[i].y() > max.y()) {
            max.setY(data[i].y());
        }
        if (data[i].y() < min.y()) {
            min.setY(data[i].y());
        }
    }
}

inline bool PollarRwDp::getNext(QPollarF & n) {
    if (actualPoint < Npoints) {
        n = pointsArray[actualPoint];
        actualPoint++;
        return true;
    } else {
        actualPoint = 0;
        return false;
    }
}

inline QPollarF PollarRwDp::getElement(unsigned long int pos) {
    if (pos<this->Npoints) {
        return pointsArray[pos];
    } else {
        std::cout << "Erro: Requisição de elemento fora dos limites do vetor." << std::endl;
        exit(1);
    }
}

inline unsigned long int PollarRwDp::getNpoints() const {
    return Npoints;
}

inline void PollarRwDp::resetIterator() {
    actualPoint = 0;
}

inline QPollarF PollarRwDp::getMin() const {
    return min;
}

inline QPollarF PollarRwDp::getMax() const {
    return max;
}

inline void PollarRwDp::modulo() {
    for (int i = 0; i<this->getNpoints(); i++) {
        pointsArray[i].setX(pointsArray[i].x() < 0 ? -pointsArray[i].x() : pointsArray[i].x());
        pointsArray[i].setY(pointsArray[i].y() < 0 ? -pointsArray[i].y() : pointsArray[i].y());
    }
}

inline void PollarRwDp::setNpoints(unsigned long int N) {
    Npoints = N;
}

inline IRWItem<QPollarF> & PollarRwDp::operator+=(IRWItem<QPollarF> & rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        QPollarF tmin = QPollarF(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        QPollarF tmax = QPollarF(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
        this->resetIterator();
        rhs.resetIterator();
        QPollarF next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] += next;
            if (pointsArray[c].x() > tmax.x()) {
                tmax.setX(pointsArray[c].x());
            }
            if (pointsArray[c].x() < tmin.x()) {
                tmin.setX(pointsArray[c].x());
            }
            if (pointsArray[c].y() > tmax.y()) {
                tmax.setY(pointsArray[c].y());
            }
            if (pointsArray[c].y() < tmin.y()) {
                tmin.setY(pointsArray[c].y());
            }
            c++;
        }
        max = tmax;
        min = tmin;
    } else if (this->pointsArray == NULL) {
        this->pointsArray = new QPollarF[rhs.getNpoints()];
        QPollarF tmin = QPollarF(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        QPollarF tmax = QPollarF(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
        this->resetIterator();
        rhs.resetIterator();
        QPollarF next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] += next;
            if (pointsArray[c].x() > tmax.x()) {
                tmax.setX(pointsArray[c].x());
            }
            if (pointsArray[c].x() < tmin.x()) {
                tmin.setX(pointsArray[c].x());
            }
            if (pointsArray[c].y() > tmax.y()) {
                tmax.setY(pointsArray[c].y());
            }
            if (pointsArray[c].y() < tmin.y()) {
                tmin.setY(pointsArray[c].y());
            }
            c++;
        }
        max = tmax;
        min = tmin;
        Npoints = rhs.getNpoints();
    } else {
        fprintf(stderr, "ERRO: DataPoints precisam de ter a mesma dimensão - Npoint.");
    }
    return *this;
}

inline IRWItem<QPollarF> & PollarRwDp::operator=(IRWItem<QPollarF> & rhs) {
    if (this == &rhs) {
        return *this;
    } else if (pointsArray == NULL) {
        pointsArray = new QPollarF[rhs.getNpoints()];
    } else {
        delete [] pointsArray;
        pointsArray = new QPollarF[rhs.getNpoints()];
    }
    Npoints = rhs.getNpoints();
    min = rhs.getMin();
    max = rhs.getMax();
    rhs.resetIterator();
    QPollarF a;
    while (rhs.getNext(a)) {
        pointsArray[actualPoint] = a;
        actualPoint++;
    }
    return *this;
}

inline IRWItem<QPollarF> & PollarRwDp::operator-=(IRWItem<QPollarF>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        QPollarF tmin = QPollarF(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        QPollarF tmax = QPollarF(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
        this->resetIterator();
        rhs.resetIterator();
        QPollarF next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] -= next;
            if (pointsArray[c].x() > tmax.x()) {
                tmax.setX(pointsArray[c].x());
            }
            if (pointsArray[c].x() < tmin.x()) {
                tmin.setX(pointsArray[c].x());
            }
            if (pointsArray[c].y() > tmax.y()) {
                tmax.setY(pointsArray[c].y());
            }
            if (pointsArray[c].y() < tmin.y()) {
                tmin.setY(pointsArray[c].y());
            }
            c++;
        }
        max = tmax;
        min = tmin;
    } else if (this->pointsArray == NULL) {
        this->pointsArray = new QPollarF[rhs.getNpoints()];
        QPollarF tmin = QPollarF(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
        QPollarF tmax = QPollarF(std::numeric_limits<double>::min(), std::numeric_limits<double>::min());
        this->resetIterator();
        rhs.resetIterator();
        QPollarF next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] -= next;
            if (pointsArray[c].x() > tmax.x()) {
                tmax.setX(pointsArray[c].x());
            }
            if (pointsArray[c].x() < tmin.x()) {
                tmin.setX(pointsArray[c].x());
            }
            if (pointsArray[c].y() > tmax.y()) {
                tmax.setY(pointsArray[c].y());
            }
            if (pointsArray[c].y() < tmin.y()) {
                tmin.setY(pointsArray[c].y());
            }
            c++;
        }
        max = tmax;
        min = tmin;
        Npoints = rhs.getNpoints();
    } else {
        fprintf(stderr, "ERRO: DataPoints precisam de ter a mesma dimensão - Npoint.");
    }
    return *this;
}

inline bool PollarRwDp::operator==(IRWItem<QPollarF>& rop) {
    if (Npoints != rop.getNpoints()) {
        return false;
    } else {
        rop.resetIterator();
        int count = 0;
        QPollarF a;
        while (rop.getNext(a)) {
            if (pointsArray[count] != a) {
                return false;
            }
            count++;
        }
        return true;
    }
}

template <class type> PollarRwDp & operator/(PollarRwDp & dps, double a) {
    for (int i = 0; i < dps.getNpoints(); i++) {
        dps[i] /= a;
    }
    return dps;
}

template <class type> PollarRwDp & operator+(PollarRwDp & a, PollarRwDp & b) {
    PollarRwDp *ret = new PollarRwDp();
    *ret += a;
    *ret += b;
    return *ret;
}

inline bool PollarRwDp::operator!=(IRWItem<QPollarF>& rop) {
    return !(*this == rop);
}

inline QPollarF & PollarRwDp::operator[](uint32_t a) {
    assert(a < Npoints);
    return pointsArray[a];
}

inline QPollarF PollarRwDp::sum() {
    QPollarF ret;
    for (uint_64t i = 0; i < Npoints; i++) {
        ret += pointsArray[i];
    }
    return ret;
}

inline unsigned long int PollarRwDp::getActualPoint()const {
    return actualPoint;
}

inline void PollarRwDp::print() {
    for (unsigned int i = 0; i < Npoints; i++) {
        std::cout << pointsArray[i].x() << " " << pointsArray[i].y() << " " << std::endl;
    }
    std::cout << std::endl;
}

inline uint_32t PollarRwDp::getEpsilonN(double e) {
    if (e > 0 && e < 1) {
        uint_32t a = e * getNpoints();
        return a;
    } else {
        std::cerr << "Epsilon menor que 0 ou maior que 1.";
    }
    return NAN;
}
//    virtual IRWSet<Type>* getIntervals(uint_32t)=0;

inline double PollarRwDp::average() {
    std::cout << "It doesn't apply look for a specific function in the class." << std::endl;
    return NAN;
}

inline IRWItem<double> * PollarRwDp::getIntegral() {
    std::cout << "It doesn't apply look for a specific function in the class." << std::endl;
    return NULL;
}

inline IRWItem<double> * PollarRwDp::power(double a) {
    IRWItem<double> * ret = new DataPointsDouble();
    QPollarF Origin;
    Origin.setX(0);
    Origin.setY(0);
    double * data = new double [Npoints];
    for (int i = 0; i < Npoints; i++) {
        data[i] = pow(pointsArray[i].distQPollarF(Origin), a);
    }
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}
#endif	/* POLLARRWDP_H */

