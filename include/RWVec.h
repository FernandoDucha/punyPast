/* 
 * File:   RandomWalkVector.h
 * Author: fernando
 *
 * Created on 29 de Abril de 2013, 17:36
 */

#ifndef RWVEC_H
#define	RWVEC_H
#include <stdlib.h>
#include <iostream>
#include "GeneralUsage.h"
#include "IRWItem.h"
#include "RWVecSet.h"
#include <assert.h>
#include <limits>
using namespace std;
template <class type> class RWDp;
template <class type> class RWVecSet;

template <class type> class RWVec : public IRWItem<type> {
public:
    RWVec();
    void TransformDataPoints(RWDp<type>* input);
    void receiveData(type * input, unsigned long int s);
    bool getNext(type & a);
    void resetIterator();
    type getElement(unsigned long int i);
    void modulo();
    void setNpoints(unsigned long int Npoints);
    virtual ~RWVec();
    unsigned long int getNpoints() const;

    long unsigned int abs_sum() {
        unsigned int sum = 0;
        for (unsigned int i = 0; i < Npoints; i++) {
            sum += abs(pointsArray[i]);
        }
        return sum;
    }

    type sum() {
        type sum = 0;
        for (unsigned int i = 0; i < Npoints; i++) {
            sum += pointsArray[i];
        }
        return sum;
    }
    type * data() {
        return pointsArray;
    }
    uint_32t getEpsilonN(double);
    //    IRWSet<type>* getIntervals(uint_32t);
    IRWItem<type> & operator=(IRWItem<type>&);
    IRWItem<type> &operator+=(IRWItem<type>&);
    IRWItem<type> & operator-=(IRWItem<type>&);
    bool operator==(IRWItem<type>&);
    bool operator!=(IRWItem<type>&);
    type getMax() const;
    type getMin() const;
    double average();
    IRWItem<double> * getIntegral();
    IRWItem<double> * power(double);

    void print() {
        for (unsigned int i = 0; i < Npoints; i++) {
            cout << pointsArray[i] << " ";
        }
        cout << endl;
    }

    type & operator[](uint32_t a) {
        assert(a < Npoints);
        return pointsArray[a];
    }
    unsigned long int getActualPoint()const;
private:
    type * pointsArray;
    unsigned long int Npoints;
    unsigned long int actualPoint;
    type min, max;
};

template <class type> IRWItem<double> * RWVec<type>::power(double a) {
    double * data = new double[Npoints];
    for (int i = 0; i < Npoints; i++) {
        data[i] = pow(pointsArray[i], a);
    }
    IRWItem<double> * ret = new RWVec<double>();
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}

template <class type> IRWItem<double> * RWVec<type>::getIntegral() {
    double avg = average();
    double * data = new double[Npoints];
    for (int i = 0; i < Npoints; i++) {
        data[i] = 0;
        for (int j = 0; j <= i; j++) {
            data[i] += pointsArray[j] - avg;
        }
    }
    IRWItem<double> * ret = new RWVec<double>();
    ret->receiveData(data, Npoints);
    delete [] data;
    return ret;
}

template <class type> uint_32t RWVec<type>::getEpsilonN(double e) {
    if (e > 0 && e < 1) {
        uint_32t a = e * getNpoints();
        return a;
    } else {
        cerr << "Epsilon menor que 0 ou maior que 1.";
    }
    return NAN;
}

template <class type> double RWVec<type>::average() {
    double ret = (double) 1 / Npoints * sum();
    return ret;
}

//template <class type> IRWSet<type>* RWVec<type>::getIntervals(uint_32t N) {
//    int p = (double) getNpoints() / N;
//    type* ret = new type[N];
//    IRWSet<type> * retorno = new RWVecSet<type>(p);
//    for (int i = 0; i < p; i++) {
//        memcpy(ret, &pointsArray[i * N], N * sizeof (type));
//        IRWItem<type> * temp = new RWVec<type>();
//        temp->receiveData(ret,N);
//        retorno->put(temp);
//    }
//    delete ret;
//    return retorno;
//}

template <class type> void RWVec<type>::modulo() {
    for (int i = 0; i<this->getNpoints(); i++) {
        pointsArray[i] = pointsArray[i] < 0 ? -pointsArray[i] : pointsArray[i];
    }
}

template <class type> unsigned long int RWVec<type>::getActualPoint()const {
    return actualPoint;
}

template <class type> void RWVec<type>::setNpoints(unsigned long int Npoints) {
    this->Npoints = Npoints;
    if (pointsArray) {
        delete pointsArray;
    }
    pointsArray = new type[Npoints];
}

template <class type> RWVec<type> & operator-(RWVec<type>& lop, RWVec<type>&rop) {
    if (lop.getNpoints() == rop.getNpoints()) {
        RWVec<type> * ret = new RWVec<type>();
        type * vec = new type[rop.getNpoints()];
        type a, b;
        rop.resetIterator();
        lop.resetIterator();
        unsigned long int it = 0;
        while (rop.getNext(a) && lop.getNext(b)) {
            vec[it] = a - b;
            it++;
        }
        ret->receiveData(vec, rop.getNpoints());
        return *ret;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}

template <class type>bool RWVec<type>::operator==(IRWItem<type>&rop) {
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

template <class type> bool RWVec<type>::operator!=(IRWItem<type>&rop) {
    return !(*this == rop);
}

template <class type> type RWVec<type>::getMax() const {
    return max;
}

template <class type> type RWVec<type>::getMin() const {
    return min;
}

template <class type> RWVec<type>&operator+(RWVec<type>& lop, RWVec<type>& rop) {
    if (lop.getNpoints() == rop.getNpoints()) {
        RWVec<type> * ret = new RWVec<type>();
        type * vec = new type[rop.getNpoints()];
        type a, b;
        rop.resetIterator();
        lop.resetIterator();
        unsigned long int it = 0;
        while (rop.getNext(a) && lop.getNext(b)) {
            vec[it] = a + b;
            it++;
        }
        ret->receiveData(vec, rop.getNpoints());
        return *ret;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}

template <class type >IRWItem<type> &RWVec<type>::operator+=(IRWItem<type>&rhs) {
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
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
    return *this;
}

template <class type >IRWItem<type> &RWVec<type>::operator-=(IRWItem<type>&rhs) {
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
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
    return *this;
}

template <class type> IRWItem<type> & RWVec<type>::operator=(IRWItem<type>& rhs) {
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

template <class type> unsigned long int RWVec<type>::getNpoints() const {
    return Npoints;
}

template <class type> RWVec<type>::RWVec() {
    pointsArray = NULL;
    Npoints = 0;
    actualPoint = 0;
    min = numeric_limits<type>::max();
    max = numeric_limits<type>::min();
}

template <class type> RWVec<type>::~RWVec() {
    delete [] pointsArray;
}

template <class type> void RWVec<type>::receiveData(type* input, unsigned long int s) {
    if (pointsArray == NULL) {
        pointsArray = new type[s];
    } else {
        delete [] pointsArray;
        pointsArray = new type[s];
    }
    Npoints = s;
    for (unsigned int i = 0; i < Npoints; i++) {
        pointsArray[i] = input[i];
        if (pointsArray[i] > max) {
            max = pointsArray[i];
        } else if (pointsArray[i] < min) {
            min = pointsArray[i];
        }
    }
}

template <class type> void RWVec<type>::resetIterator() {
    this->actualPoint = 0;
}

template <class type> bool RWVec<type>::getNext(type & a) {
    if (actualPoint < Npoints) {
        a = pointsArray[actualPoint];
        actualPoint++;
        return true;
    } else {
        return false;
    }
}

template <class type> void RWVec<type>::TransformDataPoints(RWDp<type>* input) {
    if (pointsArray == NULL) {
        delete [] pointsArray;
    }
    Npoints = input->getNpoints();
    pointsArray = new unsigned long int[input->getNpoints()];
    pointsArray[0] = input->getElement(0);
    for (unsigned int i = 1; i < input->getNpoints(); i++) {
        if (input->getElement(i) > input->getElement(i - 1)) {
            pointsArray[i] = 1;
        } else {
            pointsArray[i] = -1;
        }
        if (pointsArray[i] > max) {
            max = pointsArray[i];
        } else if (pointsArray[i] < min) {
            min = pointsArray[i];
        }
    }

    //    cout<<input->getElement(input->getNpoints()-1)<<endl;
}

template <class type> type RWVec<type>::getElement(unsigned long int i) {
    if (i<this->Npoints) {
        return pointsArray[i];
    } else {
        cout << "Erro: Requisição de elemento fora dos limites do vetor." << endl;
        exit(1);
    }
}
#endif	/* RANDOMWALKVECTOR_H */

