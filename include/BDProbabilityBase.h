/* 
 * File:   BDProbabilityBase.h
 * Author: fordem
 *
 * Created on March 10, 2015, 8:37 PM
 */

#ifndef BDPROBABILITYBASE_H
#define	BDPROBABILITYBASE_H
#include "IProbabilityBase.h" 
#include "IRandomWalk.h"
#include "RWBdManager.h"
#include "LinearFit.h"

class BDProbabilityBase : public IProbabilityBase<int, double> {
public:
    BDProbabilityBase(IRandomWalk *);
    virtual ~BDProbabilityBase();
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
    virtual IRandomWalk* GetThisbrwk()const;
    virtual IRWItem<double> * buildWeiestrass(double a, double b, double from, double to, uint_32t N);
    virtual IRWBd * getBd();
    virtual IRWItem<double>* getAverageWalkByPoints();
    virtual IRWItem<QPollarF>* getNext2DWalk();

    virtual void clear2DWalks() {
        return;
    }
    virtual IRWSet<QPollarF>* getAll2DWalks(){
        return nullptr;
    }


private:
    void fillBinTable();
    void fillDpTable();
    IRandomWalk * thisrwk;
    RWBdManager BdManager;
    int block;
};

#endif	/* BDPROBABILITYBASE_H */

