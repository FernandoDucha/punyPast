/* 
 * File:   RNGLinearCong.h
 * Author: fordem
 *
 * Created on February 26, 2015, 9:00 PM
 */

#ifndef RNGLINEARCONG_H
#define	RNGLINEARCONG_H
#include "IRNG.h"
#define iA 843314861ull
#define iB 453816693ull
#define iM 1073741824ull

class RNGLinearCong : public IRNG {
public:
    RNGLinearCong();
    RNGLinearCong(uint64_t s);
    virtual ~RNGLinearCong();
    double randd();
    uint64_t randi();
    bool operator==(IRNG&);
private:

};

#endif	/* RNGLINEARCONG_H */

