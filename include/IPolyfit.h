/* 
 * File:   IPolyfit.h
 * Author: fordem
 *
 * Created on June 6, 2015, 11:48 AM
 */

#ifndef IPOLYFIT_H
#define	IPOLYFIT_H
#include "IPolynom.h"
#include "MatrixGSL.h"

class IPolyfit {
public:
    IPolyfit();
    virtual ~IPolyfit();
    virtual MatrixGSL * getCovMatrix() = 0;
    virtual IPolynom * getFit() = 0;
    virtual void performFit() = 0;
    virtual double getChiSquared() = 0;
    virtual double getSSE() = 0;
    virtual double getN() = 0;
    virtual double * getSamplesX() = 0;
    virtual double * getSamplesY() = 0;

private:

};

inline IPolyfit::IPolyfit() {
}

inline IPolyfit::~IPolyfit() {
}
#endif	/* IPOLYFIT_H */

