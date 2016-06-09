/* 
 * File:   BufferedProbabilityBase.h
 * Author: fordem
 *
 * Created on March 5, 2015, 8:32 AM
 */

#ifndef BUFFEREDPROBABILITYBASE_H
#define	BUFFEREDPROBABILITYBASE_H
#include "IProbabilityBase.h" 
#include "IRandomWalk.h"
#include "RWBufferedDpBase.h"
#include "RWBufferedVecBase.h"
#include "RWBufferManager.h"
#include "LinearFit.h"
#include "PollarBufferManager.h"
#include "PollarBufferedRwDpSet.h"
class BufferedProbabilityBase : public IProbabilityBase<int, double> {
public:
    BufferedProbabilityBase(IRandomWalk * irwk);
    virtual ~BufferedProbabilityBase();
    virtual void SetDatabinp(IRWSet<int>* databinp);
    virtual IRWSet<int>* GetDatabinp();
    virtual IRWSet<int>* GetDatabinp(u_int64_t ws, u_int64_t ns, char* msg);
    virtual IRWSet<double>* GetDatap(u_int64_t ws, u_int64_t ns, char* msg);
    virtual bool FetchDataOnly(u_int64_t ws, u_int64_t ns, char* msg);
    virtual void SetDatap(IRWSet<double>* datap);
    virtual IRWSet<double>* GetDatap();
    virtual IPolyfit * CurveFitting();
    virtual void clearDataBin();
    virtual void clearDataPoints();
    virtual IRWItem<int> * getWalkNByBits(u_int64_t N);
    virtual IRWItem<double> * getWalkNByPoints(u_int64_t N);
    virtual IRWSet<int>* getWalkNByBits(u_int64_t beg, u_int64_t end);
    virtual IRWSet<double>* getWalkNByPoints(u_int64_t beg, u_int64_t end);
    virtual void setNewIRandomWalk(IRandomWalk * irwk);
    virtual IRandomWalk* GetThisbrwk() const;
    virtual IRWItem<double> * buildWeiestrass(double a, double b, double from, double to, uint_32t N);
    virtual IRWItem<double>* getAverageWalkByPoints();
    virtual IRWItem<QPollarF> * getNext2DWalk();
    virtual IRWSet<QPollarF>* getAll2DWalks();
    virtual void clear2DWalks();

private:
    void fillDatap();
    void fillDataBinp();
    void fill2DWalks();
    BufferedDpSetDouble * datap;
    BufferedVecSetInt * databinp;
    RWBufferManager<int> rwmngrint;
    RWBufferManager<double> rwmngrdouble;
    PollarBufferManager pollar;
    IRandomWalk * thisrwk;
    PollarBufferedRwDpSet * walks2d;
};

#endif	/* BUFFEREDPROBABILITYBASE_H */

