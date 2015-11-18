/* 
 * File:   IPolynom.h
 * Author: fordem
 *
 * Created on June 3, 2015, 11:22 PM
 */

#ifndef IPOLYNOM_H
#define	IPOLYNOM_H
#include "IRWItem.h"

class IPolynom {
public:
    IPolynom();
    IPolynom(IPolynom&);
    virtual ~IPolynom();
    virtual double evaluate(double) = 0;
    virtual void setCoef(int, double) = 0;
    virtual double getCoef(int) = 0;
    virtual int getOrder() = 0;
    virtual void print() = 0;
    virtual IRWItem<double> * evalFromTo(double, double, double) = 0;
    virtual IRWItem<double> * evalFromToBuffered(double, double, double) = 0;
    virtual double distanceFromPoint(double, double) = 0;
    virtual IRWItem<double> * distanceFromPoints(IRWItem<double>*, IRWItem<double>*) = 0;
    virtual double heightDifference(double, double) = 0;
    virtual IRWItem<double> * heightDifference(IRWItem<double>*, IRWItem<double>*,double & sum) = 0;
    virtual IRWItem<double> * quadraticHeightDifference(IRWItem<double>*, IRWItem<double>*,double &sum) = 0;

    virtual IPolynom & operator=(IPolynom&) = 0;
    virtual IPolynom & operator+=(IPolynom&) = 0;
    virtual IPolynom & operator-=(IPolynom&) = 0;
    virtual IPolynom & operator-() = 0;
    virtual bool operator==(IPolynom&) = 0;
    virtual bool operator!=(IPolynom&) = 0;

private:

};

#endif	/* IPOLYNOM_H */

