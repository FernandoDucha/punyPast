/* 
 * File:   ProbabilityBase.h
 * Author: fernando
 *
 * Created on 8 de Maio de 2013, 10:08
 */

#ifndef PROBABILITYBASE_H
#define	PROBABILITYBASE_H
#include <gsl/gsl_fit.h>
#include <gsl/gsl_math.h>
#include "RWDpBase.h"
#include "RWVBase.h"
#include "IRandomWalk.h"
#include "IProbabilityBase.h"
#include <iostream>
#include "PollarRwDpSet.h"
using namespace std;

class ProbabilityBase : public IProbabilityBase<int, double> {
public:
    ProbabilityBase(IRandomWalk * brwk);
    virtual ~ProbabilityBase();
    void SetDatabinp(IRWSet<int>* databinp);
    IRWSet<int>* GetDatabinp();
    IRWSet<int>* GetDatabinp(u_int64_t ws, u_int64_t ns, char* msg);
    IRWSet<double>* GetDatap(u_int64_t ws, u_int64_t ns, char* msg);
    bool FetchDataOnly(u_int64_t ws, u_int64_t ns, char* msg);
    void SetDatap(IRWSet<double>* datap);
    IRWSet<double>* GetDatap();

    IPolyfit * CurveFitting();
    void clearDataBin();
    void clearDataPoints();
    void clear2DWalks();

    IRWItem<int> * getWalkNByBits(u_int64_t N);
    IRWItem<double> * getWalkNByPoints(u_int64_t N);
    IRWSet<int>* getWalkNByBits(u_int64_t beg, u_int64_t end);
    IRWSet<double>* getWalkNByPoints(u_int64_t beg, u_int64_t end);
    void setNewIRandomWalk(IRandomWalk * irwk);
    IRWItem<double>* getAverageWalkByPoints();

    IRandomWalk* GetThisbrwk() const {
        return thisbrwk;
    }
    virtual IRWItem<double> * buildWeiestrass(double a, double b, double from, double to, uint_32t N);

    virtual IRWItem<QPollarF> * getNext2DWalk();
    virtual IRWSet<QPollarF> * getAll2DWalks();

private:
    DataPointsUInt * pointsFromFitting;
    DataPointsUInt * pointsCurve;
    IRandomWalk * thisbrwk;
    DataSetDouble * datap;
    RWVSInt * databinp;
    PollarRwDpSet * walks2d;
};

#endif	/* PROBABILITYBASE_H */

