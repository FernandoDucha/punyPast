/* 
 * File:   GSL_CMRG.h
 * Author: fordem
 *
 * Created on November 16, 2015, 6:51 PM
 */

#ifndef GSL_CMRG_H
#define	GSL_CMRG_H
#include <gsl/gsl_rng.h>
#include "IRNG.h"

class GSL_CMRG : public IRNG {
public:
    GSL_CMRG();
    GSL_CMRG(uint64_t s);
    virtual ~GSL_CMRG();
    virtual bool operator==(IRNG&);
    virtual double randd();
    virtual uint64_t randi();
    virtual void resetSeed();
private:
    gsl_rng * thisrng;
};

inline void GSL_CMRG::resetSeed() {
    this->actualSeed = this->seed;
    gsl_rng_set(thisrng, seed);
}

inline GSL_CMRG::GSL_CMRG() {
    this->type = GSLCMRG;
    thisrng = gsl_rng_alloc(gsl_rng_cmrg);
    this->actualSeed = this->seed = 0;
    gsl_rng_set(thisrng, this->seed);
}

inline GSL_CMRG::GSL_CMRG(uint64_t s) {
    this->actualSeed = this->seed = s;
    this->type = GSLCMRG;
    thisrng = gsl_rng_alloc(gsl_rng_cmrg);
    gsl_rng_set(thisrng, s);
}

inline double GSL_CMRG::randd() {
    return gsl_rng_uniform(thisrng);
}

inline uint64_t GSL_CMRG::randi() {
    return gsl_rng_get(thisrng);
}

inline bool GSL_CMRG::operator==(IRNG& lhs) {
    return ((getType() == lhs.getType()) && getSeed() == lhs.getSeed());
}

inline GSL_CMRG::~GSL_CMRG() {
    gsl_rng_free(thisrng);
}
#endif	/* GSL_CMRG_H */

