/* 
 * File:   Polynom.h
 * Author: fordem
 *
 * Created on June 3, 2015, 11:17 PM
 */

#ifndef POLYNOM_H
#define	POLYNOM_H

#include "IPolynom.h"
#include "RWBufferIterator.h"
#include <cmath>
#include <iostream>
#include "RWBufferManagerSingleton.h"

template <int D> class Polynom : public IPolynom {
public:
    Polynom();
    virtual ~Polynom();
    double evaluate(double);
    void setCoef(int, double);
    double getCoef(int);
    int getOrder();
    IPolynom & operator=(IPolynom&);
    bool operator==(IPolynom&);
    bool operator!=(IPolynom&);
    IPolynom & operator+=(IPolynom&);
    IPolynom & operator-=(IPolynom&);
    IPolynom & operator-();
    void print();
    IRWItem<double> * evalFromTo(double, double, double);
    IRWItem<double> * evalFromToBuffered(double, double, double);
    double distanceFromPoint(double, double);
    IRWItem<double> * distanceFromPoints(IRWItem<double>*, IRWItem<double>*);
    double heightDifference(double x, double y);
    IRWItem<double>* quadraticHeightDifference(IRWItem<double>* X, IRWItem<double>* Y, double &sum);
    IRWItem<double> * heightDifference(IRWItem<double>* X, IRWItem<double>* Y, double & sum);
private:
    int Order;
    double * Coef;
};

template <int D>inline  double Polynom<D>::distanceFromPoint(double x, double y) {
    if (Order == 2) {
        double denominator = sqrt(pow(Coef[1], 2) + 1);
        double numerator = abs(x * Coef[1] + y + Coef[0]);
        return numerator / denominator;
        //        return abs(y - evaluate(x));
    } else {
        return NAN;
    }
}

template <int D>inline IRWItem<double> * Polynom<D>::distanceFromPoints(IRWItem<double>* x, IRWItem<double>* y) {
    if (Order == 2) {
        if (x != NULL && y != NULL) {
            if (x->getNpoints() == y->getNpoints()) {
                double * buffer = new double[x->getNpoints()];
                x->resetIterator();
                y->resetIterator();
                double a, b;
                int i = 0;
                while (x->getNext(a) && y->getNext(b)) {
                    buffer[i] = distanceFromPoint(a, b);
                    i++;
                }
                IRWItem<double> * retorno = new RWDp<double>();
                retorno->receiveData(buffer, x->getNpoints());
                delete buffer;
                return retorno;
            } else {
                std::cerr << "Dimensions from Linear fit are different: X=" << x->getNpoints() << "  Y=" << y->getNpoints() << std::endl << std::endl;
                return NULL;
            }
        } else {
            std::cerr << "Invalid Input." << std::endl;
            return NULL;
        }
    } else {
        return NULL;
    }
}

template <int D>inline IRWItem<double> * Polynom<D>::quadraticHeightDifference(IRWItem<double>* x, IRWItem<double>* y, double & sum) {
    if (Order == 2) {
        if (x != NULL && y != NULL) {
            if (x->getNpoints() == y->getNpoints()) {
                double * buffer = new double[x->getNpoints()];
                x->resetIterator();
                y->resetIterator();
                double a, b;
                int i = 0;
                while (x->getNext(a) && y->getNext(b)) {
                    buffer[i] = heightDifference(a, b);
                    buffer[i] *= buffer[i];
                    sum += buffer[i];
                    i++;
                }
                IRWItem<double> * retorno = new RWDp<double>();
                retorno->receiveData(buffer, x->getNpoints());
                delete buffer;
                return retorno;
            } else {
                std::cerr << "Dimensions from Linear fit are different: X=" << x->getNpoints() << "  Y=" << y->getNpoints() << std::endl << std::endl;
                return NULL;
            }
        } else {
            std::cerr << "Invalid Input." << std::endl;
            return NULL;
        }
    } else {
        return NULL;
    }
}

template <int D>inline double Polynom<D>::heightDifference(double x, double y) {
    if (Order == 2) {
        return abs(y - evaluate(x));
    } else {
        return NAN;
    }
}

template <int D>inline IRWItem<double> * Polynom<D>::heightDifference(IRWItem<double>* x, IRWItem<double>* y, double & sum) {
    if (Order == 2) {
        if (x != NULL && y != NULL) {
            if (x->getNpoints() == y->getNpoints()) {
                double * buffer = new double[x->getNpoints()];
                x->resetIterator();
                y->resetIterator();
                double a, b;
                int i = 0;
                while (x->getNext(a) && y->getNext(b)) {
                    buffer[i] = heightDifference(a, b);
                    sum += buffer[i];
                    i++;
                }
                IRWItem<double> * retorno = new RWDp<double>();
                retorno->receiveData(buffer, x->getNpoints());
                delete buffer;
                return retorno;
            } else {
                std::cerr << "Dimensions from Linear fit are different: X=" << x->getNpoints() << "  Y=" << y->getNpoints() << std::endl << std::endl;
                return NULL;
            }
        } else {
            std::cerr << "Invalid Input." << std::endl;
            return NULL;
        }
    } else {
        return NULL;
    }
}

template <int D>inline void Polynom<D>::print() {
    for (int i = 0; i < Order; i++) {
        std::cout << Coef[i] << " ";
    }
    std::cout << std::endl;
}

inline IPolynom & operator*(IPolynom & op1, double op2) {
    for (int i = 0; i < op1.getOrder(); i++) {
        op1.setCoef(i, op1.getCoef(i) * op2);
    }
    return op1;
}

inline IPolynom & operator/(IPolynom & op1, double op2) {
    for (int i = 0; i < op1.getOrder(); i++) {
        op1.setCoef(i, op1.getCoef(i) / op2);
    }
    return op1;
}

template <int D >inline Polynom<D> & operator+(IPolynom & op1, IPolynom & op2) {
    Polynom<0> ret = op1.getOrder() > op2.getOrder() ? op1 : op2;
    if (ret == op1) {
        for (int i = 0; i < op2.getOrder(); i++) {
            ret.setCoef(i, op1.getCoef(i) + op2.getCoef(i));
        }
    } else {
        for (int i = 0; i < op1.getOrder(); i++) {
            ret.setCoef(i, op1.getCoef(i) + op2.getCoef(i));
        }
    }

    return ret;
}

template <int D >inline Polynom<D> & operator-(IPolynom & op1, IPolynom & op2) {
    Polynom<0> ret = op1.getOrder() > op2.getOrder() ? op1 : op2;
    if (ret == op1) {
        for (int i = 0; i < op2.getOrder(); i++) {
            ret.setCoef(i, op1.getCoef(i) - op2.getCoef(i));
        }
    } else {
        for (int i = 0; i < op1.getOrder(); i++) {
            ret.setCoef(i, op1.getCoef(i) - op2.getCoef(i));
        }
    }

    return ret;
}

template <int D >inline IRWItem<double> * Polynom<D>::evalFromTo(double start, double end, double step) {
    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i] = evaluate(start);
    }
    RWDp<double> * retorno = new RWDp<double>();
    retorno->receiveData(buffer, it);
    delete [] buffer;
    return retorno;
}

template <int D >inline IRWItem<double> * Polynom<D>::evalFromToBuffered(double start, double end, double step) {
    RWBufferManagerSingleton<double> * instance = RWBufferManagerSingleton<double>::getInstance();
    int it = (end - start) / step + 1;
    double * buffer = new double[it];
    for (int i = 0; i < it; start += step, i++) {
        buffer[i] = evaluate(start);
    }
    RWBufferedDp<double> * r = instance->createDpItem(buffer, it);
    RWBufferedDp<double> * retorno = new RWBufferedDp<double>(*r);
    delete r;
    delete [] buffer;
    return retorno;
}

template <int D >inline IPolynom & Polynom<D>::operator-() {
    for (int i = 0; i < Order; i++) {
        Coef[i] = -Coef[i];
    }
    return *this;
}

template <int D >inline IPolynom & Polynom<D>::operator+=(IPolynom & rhs) {
    if (rhs.getOrder() > Order) {
        double * temp = new double[rhs.getOrder()];
        for (int i = 0; i < rhs.getOrder(); i++) {
            temp[i] = rhs.getCoef(i);
        }
        for (int j = 0; j < Order; j++) {
            temp[j] += Coef[j];
        }
        delete [] Coef;
        Coef = temp;
    } else {
        double * temp = new double[Order];
        for (int i = 0; i < Order; i++) {
            temp[i] = Coef[i];
        }
        for (int j = 0; j < rhs.getOrder(); j++) {
            temp[j] += rhs.getCoef(j);
        }
        delete [] Coef;
        Coef = temp;
    }
    return *this;
}

template <int D >inline IPolynom & Polynom<D>::operator-=(IPolynom & rhs) {
    if (rhs.getOrder() > Order) {
        double * temp = new double[rhs.getOrder()];
        for (int i = 0; i < rhs.getOrder(); i++) {
            temp[i] = rhs.getCoef(i);
        }
        for (int j = 0; j < Order; j++) {
            temp[j] -= Coef[j];
        }
        delete [] Coef;
        Coef = temp;
    } else {
        double * temp = new double[Order];
        for (int i = 0; i < Order; i++) {
            temp[i] = Coef[i];
        }
        for (int j = 0; j < rhs.getOrder(); j++) {
            temp[j] -= rhs.getCoef(j);
        }
        delete [] Coef;
        Coef = temp;
    }
    return *this;
}

template <int D>inline bool Polynom<D>::operator==(IPolynom & rhs) {
    if (Order != rhs.getOrder()) {
        return false;
    }
    for (int i = 0; i < Order; i++) {
        if (Coef[i] != rhs.getCoef(i)) {
            return false;
        }
    }
    return true;
}

template <int D>inline bool Polynom<D>::operator!=(IPolynom & rhs) {
    return !(*this == rhs);
}

template <int D >inline IPolynom & Polynom<D>::operator=(IPolynom & rhs) {
    if (*this != rhs) {
        delete [] Coef;
        Order = rhs.getOrder();
        Coef = new double[Order];
        for (int i = 0; i < Order; i++) {
            Coef[i] = rhs.getCoef(i);
        }
    }
    return *this;

}

template <int D >inline Polynom<D>::Polynom() {
    Order = D;
    Coef = new double[D];
    for (int i = 0; i < Order; i++) {
        Coef[i] = 0;
    }
}

template <int D>inline double Polynom<D>::evaluate(double x) {
    double ret = Coef[0];
    for (int i = 1; i < Order; i++) {
        ret += Coef[i] * pow(x, i);
    }
    return ret;
}

template <int D>inline void Polynom<D>::setCoef(int c, double x) {
    if (c < Order) {
        Coef[c] = x;
    }
}

template <int D>inline double Polynom<D>::getCoef(int c) {
    if (c < Order) {
        return Coef[c];
    } else {
        std::cerr << "Erro coeficente maior q ordem." << std::endl;
        //Tratar erro!!!   
    }
    return NAN;
}

template <int D>inline int Polynom<D>::getOrder() {
    return Order;
}

template <int D > Polynom<D>::~Polynom() {
    delete [] Coef;
}

#endif	/* POLYNOM_H */

