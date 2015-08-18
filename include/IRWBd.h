/* 
 * File:   IRWBd.h
 * Author: fordem
 *
 * Created on June 13, 2015, 4:44 PM
 */

#ifndef IRWBD_H
#define	IRWBD_H
#include "RWDpBase.h"
#include "RWVBase.h"

class IRWBd {
public:
    IRWBd();
    virtual bool open()=0;
    virtual void close()=0;
    virtual bool createDpTable()=0;
    virtual bool createBinTable()=0;
    virtual bool insertItem(DataPointsDouble & dpitem)=0;
    virtual bool insertSet(DataSetDouble & dpset)=0;
    virtual DataPointsDouble selectDpItem(int i)=0;
    virtual DataSetDouble * selectDpItem(int Beg, int End)=0;
    virtual bool insertItem(RWVInt & binitem)=0;
    virtual bool insertSet(RWVSInt & dpset)=0;
    virtual RWVInt selectBinItem(int i)=0;
    virtual RWVSInt * selectBinItem(int Beg, int End)=0;
    virtual bool execMultiple()=0;
    virtual bool commit()=0;
    virtual int getNWalks()=0;
    virtual int getWalkS()=0;
    virtual ~IRWBd();
private:

};

#endif	/* IRWBD_H */

