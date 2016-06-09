/* 
 * File:   GSL_MRG.h
 * Author: fordem
 *
 * Created on November 16, 2015, 6:55 PM
 */

#ifndef GSL_MRG_H
#define	GSL_MRG_H
#include <gsl/gsl_rng.h>
#include "IRNG.h"
class GSL_MRG : public IRNG {
public:
    GSL_MRG();
    virtual ~GSL_MRG();
    GSL_MRG(uint64_t s);
    virtual bool operator==(IRNG&);
    virtual double randd();
    virtual uint64_t randi();
    virtual void resetSeed();
private:
    gsl_rng * thisrng;
};

inline void GSL_MRG::resetSeed() {
    this->actualSeed = this->seed;
    gsl_rng_set(thisrng, seed);
}

inline GSL_MRG::GSL_MRG() {
    this->type = GSLMRG;
    thisrng = gsl_rng_alloc(gsl_rng_mrg);
    this->actualSeed = this->seed = 0;
    gsl_rng_set(thisrng, this->seed);
}

inline GSL_MRG::GSL_MRG(uint64_t s) {
    this->actualSeed = this->seed = s;
    this->type = GSLMRG;
    thisrng = gsl_rng_alloc(gsl_rng_mrg);
    gsl_rng_set(thisrng, s);
}

inline double GSL_MRG::randd() {
    return gsl_rng_uniform(thisrng);
}

inline uint64_t GSL_MRG::randi() {
    return gsl_rng_get(thisrng);
}

inline bool GSL_MRG::operator==(IRNG& lhs) {
    return ((getType() == lhs.getType()) && getSeed() == lhs.getSeed());
}

inline GSL_MRG::~GSL_MRG() {
    gsl_rng_free(thisrng);
}
#endif	/* GSL_MRG_H */

