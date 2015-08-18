/* 
 * File:   LinearFit.h
 * Author: fordem
 *
 * Created on June 6, 2015, 12:01 PM
 */

#ifndef LINEARFIT_H
#define	LINEARFIT_H
#include "IPolyfit.h"
#include "include/Polynom.h"
#include <iostream>
#include <gsl/gsl_fit.h>

class LinearFit : public IPolyfit {
public:
    LinearFit(IRWItem<double>*, IRWItem<double>*);
    virtual ~LinearFit();
    MatrixGSL * getCovMatrix();
    IPolynom * getFit();
    void performFit();
    double getChiSquared();
    double getSSE();
    double getN();
    double * getSamplesX();
    double * getSamplesY();
private:
    double sse;
    double chisq;
    MatrixGSL * M;
    Polynom<2> * fit;
    int N;
    double * X;
    double * Y;
};
inline double LinearFit::getN(){
    return N;
}
inline double * LinearFit::getSamplesX(){
    return X;
}
inline double * LinearFit::getSamplesY(){
    return Y;
}

inline LinearFit::LinearFit(IRWItem<double>* x, IRWItem<double>* y) {
    if (x != NULL && y != NULL) {
        if (x->getNpoints() == y->getNpoints()) {
            N = x->getNpoints();
            X = new double[N];
            Y = new double[N];
            x->resetIterator();
            y->resetIterator();
            int i = 0;
            double a, b;
            while (x->getNext(a) && y->getNext(b)) {
                X[i] = a;
                Y[i] = b;
                i++;
            }
            fit = new Polynom<2>();
            M = new MatrixGSL(2, 2);
        } else {
            std::cerr << "Dimensions from Linear fit are different: X=" << x->getNpoints() << "  Y=" << y->getNpoints() << std::endl << std::endl;
            exit(-1);
        }
    } else {
        std::cerr << "Invalid Input." << std::endl;
        exit(-1);
    }

}

inline void LinearFit::performFit() {
    double cov00, cov11, cov01;
    double c0, c1;
    gsl_fit_linear(X, 1, Y, 1, N, &c0, &c1, &cov00, &cov01, &cov11, &chisq);
    M->setElement(0, 0, cov00);
    M->setElement(0, 1, cov01);
    M->setElement(1, 0, cov01);
    M->setElement(1, 1, cov11);
    fit->setCoef(0, c0);
    fit->setCoef(1, c1);
    for (int i = 0; i < N; i++) {
        double curve = fit->evaluate(X[i]);
        sse += pow(Y[i] - curve, 2);
    }
    sse = sqrt(sse);
}

inline MatrixGSL * LinearFit::getCovMatrix() {
    return M;
}

inline IPolynom * LinearFit::getFit() {
    return fit;
}

inline double LinearFit::getChiSquared() {
    return sse;
}

inline double LinearFit::getSSE() {
    return sse;
}

inline LinearFit::~LinearFit() {
    delete M;
    delete [] X;
    delete [] Y;
    delete fit;
}
#endif	/* LINEARFIT_H */

