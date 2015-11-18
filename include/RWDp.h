/* 
 * File:   DataPoints.h
 * Author: fernando
 *
 * Created on 24 de Abril de 2013, 14:52
 */

#ifndef RWDP_H
#define	RWDP_H
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "GeneralUsage.h"
#include "RWVec.h"
#include "IRWItem.h"
#include <limits>
using namespace std;
template <class type> class RWDpSet;

template <class type> class RWDp : public IRWItem<type> {
private:
    type * pointsArray;
    unsigned long int Npoints;
    unsigned long int actualPoint;
    type max, min;
public:
    RWDp();
    void receiveData(type * data, long unsigned int n);
    bool getNext(type &);
    type getElement(unsigned long int pos);
    unsigned long int getNpoints() const;
    void resetIterator();
    virtual ~RWDp();
    type getMin() const;
    type getMax() const;
    void modulo();
    void setNpoints(unsigned long int Npoints);
    void exportPointsFromSet(string fname);
    IRWItem<type> & operator+=(IRWItem<type> &);
    IRWItem<type> & operator-=(IRWItem<type> &);
    IRWItem<type> & operator=(IRWItem<type> &);
    bool operator==(IRWItem<type>&);
    bool operator!=(IRWItem<type>&);
    double average();
    IRWItem<double> * getIntegral();
    IRWItem<double> * power(double);

    type & operator[](uint32_t a) {
        assert(a < Npoints);
        return pointsArray[a];
    }
    uint_32t getEpsilonN(double);
    //    IRWSet<type>* getIntervals(uint_32t);

    type sum() {
        type ret = 0;
        for (unsigned int i = 0; i < Npoints; i++) {
            ret += pointsArray[i];
        }
        return ret;
    }
    unsigned long int getActualPoint()const;

    void print() {
        for (unsigned int i = 0; i < Npoints; i++) {
            cout << pointsArray[i] << " " << endl;
        }
    }
    template <class T> friend T * copyInterval(RWDp<T> * t, int s, int e);
    template <class T> friend RWDp<T> * subDuplicate(RWDp<T> * t, int s, int e);
};

template <class T> inline RWDp<T> * subDuplicate(RWDp<T> * t, int s, int e) {
    if (t) {
        int n = e - s;
        RWDp<T> * ret= new RWDp<T>();
        ret->receiveData(&t->pointsArray[s],n);
        return ret;
    } else {
        return nullptr;
    }
}

template <class T> inline T * copyInterval(RWDp<T> * t, int s, int e) {
    if (t) {
        int n = e - s + 1;
        T * ret = new T[n];
        memcpy(ret, &t->pointsArray[s], sizeof (T) * n);
        return ret;
    } else {
        return nullptr;
    }
}

template <class type> IRWItem<double> * RWDp<type>::power(double a) {
    double * data = new double[Npoints];
    for (int i = 0; i < Npoints; i++) {
        data[i] = pow(pointsArray[i], a);
    }
    IRWItem<double> * ret = new RWDp<double>();
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}

template <class type> IRWItem<double> * RWDp<type>::getIntegral() {
    double avg = average();
    double * data = new double[Npoints];
    for (int i = 0; i < Npoints; i++) {
        data[i] = 0;
        for (int j = 0; j <= i; j++) {
            data[i] += pointsArray[j] - avg;
        }
    }
    IRWItem<double> * ret = new RWDp<double>();
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}

template <class type> uint_32t RWDp<type>::getEpsilonN(double e) {
    if (e > 0 && e < 1) {
        uint_32t a = e * getNpoints();
        return a;
    } else {
        cerr << "Epsilon menor que 0 ou maior que 1.";
    }
    return NAN;
}

template <class type> double RWDp<type>::average() {
    double ret = (double) 1 / Npoints * sum();
    return ret;
}

//template <class type> IRWSet<type>* RWDp<type>::getIntervals(uint_32t N) {
//    int p = (double) getNpoints() / N;
//    type* ret = new type[N];
//    IRWSet<type> * retorno = new RWDpSet<type>(p);
//    for (int i = 0; i < p; i++) {
//        memcpy(ret, &pointsArray[i * N], N * sizeof (type));
//        IRWItem<type> * temp = new RWDp<type>();
//        temp->receiveData(ret,N);
//        retorno->put(temp);
//    }
//    delete ret;
//    return retorno;
//}

template <class type> IRWItem<type> & RWDp<type>::operator=(IRWItem<type>& rhs) {
    if (this == &rhs) {
        return *this;
    } else if (pointsArray == NULL) {
        pointsArray = new type[rhs.getNpoints()];
    } else {
        delete [] pointsArray;
        pointsArray = new type[rhs.getNpoints()];
    }
    Npoints = rhs.getNpoints();
    min = rhs.getMin();
    max = rhs.getMax();
    rhs.resetIterator();
    type a;
    while (rhs.getNext(a)) {
        pointsArray[actualPoint] = a;
        actualPoint++;
    }
    return *this;
}

template <class type> RWDp<type> & operator/(RWDp<type> & dps, double a) {
    for (int i = 0; i < dps.getNpoints(); i++) {
        dps[i] /= a;
    }
    return dps;
}

template <class type>bool RWDp<type>::operator==(IRWItem<type>&rop) {
    if (Npoints != rop.getNpoints()) {
        return false;
    } else {
        rop.resetIterator();
        int count = 0;
        type a;
        while (rop.getNext(a)) {
            if (pointsArray[count] != a) {
                return false;
            }
            count++;
        }
        return true;
    }
}

template <class type> bool RWDp<type>::operator!=(IRWItem<type>&rop) {
    return !(*this == rop);
}

template <class type> void RWDp<type>::exportPointsFromSet(string fname) {
    ofstream out(fname, ios::app);
    for (int i = 0; i < getNpoints(); i++) {
        out << getElement(i) << " ";
    }
    out << '\n';
    out.close();
}

template <class type> RWDp<type> & operator+(RWDp<type> & a, RWDp<type> & b) {
    RWDp<type> *ret = new RWDp<type>();
    *ret += a;
    *ret += b;
    return *ret;
}

template <class type> bool operator==(RWDp<type> & a, RWDp<type> & b) {
    if (a.getNpoints() != b.getNpoints()) {
        return false;
    } else if ((a.getMax() != b.getMax()) || (a.getMin() != b.getMin())) {
        return false;
    } else {
        for (unsigned int i = 0; i < a.getNpoints(); i++) {
            if (a.getElement(i) != b.getElement(i)) {
                return false;
            }
        }
    }
    return true;
}

template <class type> bool operator!=(RWDp<type> & a, RWDp<type> & b) {
    return !(a == b);
}

template <class type> void RWDp<type>::modulo() {
    for (int i = 0; i<this->getNpoints(); i++) {
        pointsArray[i] = pointsArray[i] < 0 ? -pointsArray[i] : pointsArray[i];
    }
}

template <class type> IRWItem<type>& RWDp<type>::operator+=(IRWItem<type>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        type tmax = numeric_limits<type>::min(), tmin = numeric_limits<type>::max();
        this->resetIterator();
        rhs.resetIterator();
        type next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] += next;
            if (pointsArray[c] > tmax) {
                tmax = pointsArray[c];
            } else if (pointsArray[c] < tmin) {
                tmin = pointsArray[c];
            }
            c++;
        }
        max = tmax;
        min = tmin;
    } else if (this->pointsArray == NULL) {
        this->pointsArray = new type[rhs.getNpoints()];
        type tmax = numeric_limits<type>::min(), tmin = numeric_limits<type>::max();
        this->resetIterator();
        rhs.resetIterator();
        type next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] = 0;
            pointsArray[c] += next;
            if (pointsArray[c] > tmax) {
                tmax = pointsArray[c];
            } else if (pointsArray[c] < tmin) {
                tmin = pointsArray[c];
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

template <class type> IRWItem<type>& RWDp<type>::operator-=(IRWItem<type>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        type tmax = numeric_limits<type>::min(), tmin = numeric_limits<type>::max();
        this->resetIterator();
        rhs.resetIterator();
        type next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] -= next;
            if (pointsArray[c] > tmax) {
                tmax = pointsArray[c];
            } else if (pointsArray[c] < tmin) {
                tmin = pointsArray[c];
            }
            c++;
        }
        max = tmax;
        min = tmin;
    } else if (this->pointsArray == NULL) {
        this->pointsArray = new type[rhs.getNpoints()];
        type tmax = numeric_limits<type>::min(), tmin = numeric_limits<type>::max();
        this->resetIterator();
        rhs.resetIterator();
        type next;
        uint64_t c = 0;
        while (rhs.getNext(next)) {
            pointsArray[c] = 0;
            pointsArray[c] -= next;
            if (pointsArray[c] > tmax) {
                tmax = pointsArray[c];
            } else if (pointsArray[c] < tmin) {
                tmin = pointsArray[c];
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

template<class type> type RWDp<type>::getElement(unsigned long int pos) {
    if (pos<this->Npoints) {
        return pointsArray[pos];
    } else {
        cout << "Erro: Requisição de elemento fora dos limites do vetor." << endl;
        exit(1);
    }
}

template<class type> unsigned long int RWDp<type>::getActualPoint()const {
    return actualPoint;
}

template<class type> RWDp<type>::RWDp() {
    Npoints = 0;
    this->pointsArray = NULL;
    actualPoint = 0;
    min = numeric_limits<type>::max();
    max = numeric_limits<type>::min();
}

template<class type> RWDp<type>::~RWDp() {
    delete [] pointsArray;
}

template<class type> type RWDp<type>::getMin() const {
    return min;
}

template<class type> type RWDp<type>::getMax() const {
    return max;
}

template<class type> unsigned long int RWDp<type>::getNpoints() const {
    return Npoints;
}

template <class type> void RWDp<type>::setNpoints(unsigned long int Npoints) {
    this->Npoints = Npoints;
    if (pointsArray) {
        delete pointsArray;
    }
    pointsArray = new type[Npoints];
}

template<class type> void RWDp<type>::receiveData(type* data, long unsigned int n) {
    if (this->pointsArray != NULL) {
        delete [] pointsArray;
        pointsArray = new type[n];
    } else {
        pointsArray = new type[n];
    }
    actualPoint = 0;
    Npoints = n;
    for (unsigned long int i = 0; i < n; i++) {
        pointsArray[i] = data[i];
        //cout<<i<<" Valores: "<<data[i]<<"#-#"<<pointsArray[i]<<endl;
        if (data[i] > max) {
            max = data[i];
        }
        if (data[i] < min) {
            min = data[i];
        }
    }
    //    delete [] data;
}

template<class type> bool RWDp<type>::getNext(type& n) {
    if (actualPoint < Npoints) {
        n = pointsArray[actualPoint];
        actualPoint++;
        return true;
    } else {
        actualPoint = 0;
        return false;
    }
}

template <class type >void RWDp<type>::resetIterator() {
    actualPoint = 0;
}
#endif	/* DATAPOINTS_H */

