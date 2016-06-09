/* 
 * File:   GSL_MST.h
 * Author: fordem
 *
 * Created on November 15, 2015, 8:20 AM
 */

#ifndef GSL_MST_H
#define	GSL_MST_H
#include "IRNG.h"
#include "gsl/gsl_rng.h"

class GSL_MST : public IRNG {
public:
    GSL_MST();
    GSL_MST(uint64_t s);
    double randd();
    uint64_t randi();
    void resetSeed();
    bool operator==(IRNG&);
    virtual ~GSL_MST();
private:
    gsl_rng * thisrng;
};
inline void GSL_MST::resetSeed(){
    this->actualSeed = this->seed;
    gsl_rng_set(thisrng, seed);
}
inline GSL_MST::GSL_MST() {
    this->type = GSLMST;
    thisrng = gsl_rng_alloc(gsl_rng_mt19937);
    this->actualSeed = this->seed = 0;
    gsl_rng_set(thisrng, this->seed);
}

inline GSL_MST::GSL_MST(uint64_t s) {
    this->actualSeed = this->seed = s;
    this->type = GSLMST;
    thisrng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(thisrng, s);
}

inline double GSL_MST::randd() {
    return gsl_rng_uniform(thisrng);
}

inline uint64_t GSL_MST::randi() {
    return gsl_rng_get(thisrng);
}

inline bool GSL_MST::operator==(IRNG& lhs) {
    return ((getType()==lhs.getType())&&getSeed()==lhs.getSeed());
}

inline GSL_MST::~GSL_MST() {
    gsl_rng_free(thisrng);
}
#endif	/* GSL_MST_H */

