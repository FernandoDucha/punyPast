/* 
 * File:   IProbabilityBase.h
 * Author: fordem
 *
 * Created on March 4, 2015, 8:17 PM
 */

#ifndef IPROBABILITYBASE_H
#define	IPROBABILITYBASE_H
#include "IRWItem.h"
#include "IRWSet.h"
#include "IRandomWalk.h"
#include "IRWIntervalBuilder.h"
#include "RWDpIntervalBuilder.h"
#include "IPolyfit.h"
template <class VecType,class SetType> class IProbabilityBase {
public:
    IProbabilityBase(){};
    virtual ~IProbabilityBase(){};
    virtual void SetDatabinp(IRWSet<VecType>* databinp)= 0;
    virtual IRWSet<VecType>* GetDatabinp()= 0;
    virtual IRWSet<VecType>* GetDatabinp(u_int64_t ws, u_int64_t ns, char* msg)= 0;
    virtual IRWSet<SetType>* GetDatap(u_int64_t ws, u_int64_t ns, char* msg)= 0;
    virtual bool FetchDataOnly(u_int64_t ws, u_int64_t ns, char* msg)= 0;
    virtual void SetDatap(IRWSet<SetType>* datap)= 0;
    virtual IRWSet<SetType>* GetDatap()= 0;
    virtual IPolyfit * CurveFitting()= 0;
    virtual void clearDataBin()= 0;
    virtual void clearDataPoints()= 0;
    virtual void clear2DWalks()=0;
    virtual IRWItem<VecType> * getWalkNByBits(u_int64_t N)= 0;
    virtual IRWItem<SetType> * getWalkNByPoints(u_int64_t N)= 0;
    virtual IRWSet<VecType>* getWalkNByBits(u_int64_t beg, u_int64_t end)= 0;
    virtual IRWSet<SetType>* getWalkNByPoints(u_int64_t beg, u_int64_t end)= 0;
    virtual IRWItem<SetType>* getAverageWalkByPoints()= 0;
    virtual void setNewIRandomWalk(IRandomWalk * irwk) = 0;
    virtual IRWItem<SetType> * buildWeiestrass(double a,double b,double from,double to,uint_32t N)=0;
    virtual IRandomWalk* GetThisbrwk() const = 0;
    virtual IRWItem<QPollarF> * getNext2DWalk()= 0;
    virtual IRWSet<QPollarF> * getAll2DWalks()=0;
private:

};


#endif	/* IPROBABILITYBASE_H */

