/* 
 * File:   RWLocationPair.h
 * Author: fordem
 *
 * Created on March 6, 2015, 11:55 PM
 */

#ifndef RWLOCPAIR_H
#define	RWLOCPAIR_H
#include <stdint.h>
class RWLocPair {
public:
    enum LocP{POS=0,LEN=1};
    RWLocPair(uint64_t,uint64_t);
    virtual ~RWLocPair();
    uint64_t & operator[](LocP);
private:
    uint64_t pos,lenght;
};

#endif	/* RWLOCATIONPAIR_H */

