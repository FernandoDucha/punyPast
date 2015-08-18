/* 
 * File:   IRNG.h
 * Author: fordem
 *
 * Created on February 26, 2015, 8:40 PM
 */

#ifndef IRNG_H
#define	IRNG_H
#include <stdint.h>
using namespace std;

enum IRNG_TYPE {
    LCG = 0,FRNG=1
};

class IRNG {
public:

    IRNG();
    virtual ~IRNG();
    virtual void setSeed(uint64_t s);
    virtual uint64_t getSeed();
    virtual void resetSeed();
    virtual double randd() = 0;
    virtual uint64_t randi() = 0;
    virtual bool operator==(IRNG&) = 0;
    virtual IRNG_TYPE getType();
    virtual void setType(IRNG_TYPE);

protected:
    uint64_t actualSeed, seed;
    IRNG_TYPE type;
};

#endif	/* IRNG_H */

