/* 
 * File:   GSL_GFSR4.h
 * Author: fordem
 *
 * Created on November 17, 2015, 5:18 PM
 */

#ifndef GSL_GFSR4_H
#define	GSL_GFSR4_H
#include "IRNG.h"
#include <gsl/gsl_rng.h>
class GSL_GFSR4 : public IRNG{
public:
    GSL_GFSR4();
    GSL_GFSR4(uint64_t s);
    virtual ~GSL_GFSR4();
    virtual bool operator==(IRNG&);
    virtual double randd();
    virtual uint64_t randi();
    virtual void resetSeed();
private:
    gsl_rng * thisrng;
};

inline void GSL_GFSR4::resetSeed() {
    this->actualSeed = this->seed;
    gsl_rng_set(thisrng, seed);
}

inline GSL_GFSR4::GSL_GFSR4() {
    this->type = GSLGFSR4;
    thisrng = gsl_rng_alloc(gsl_rng_gfsr4);
    this->actualSeed = this->seed = 0;
    gsl_rng_set(thisrng, this->seed);
}

inline GSL_GFSR4::GSL_GFSR4(uint64_t s) {
    this->actualSeed = this->seed = s;
    this->type = GSLGFSR4;
    thisrng = gsl_rng_alloc(gsl_rng_gfsr4);
    gsl_rng_set(thisrng, s);
}

inline double GSL_GFSR4::randd() {
    return gsl_rng_uniform(thisrng);
}

inline uint64_t GSL_GFSR4::randi() {
    return gsl_rng_get(thisrng);
}

inline bool GSL_GFSR4::operator==(IRNG& lhs) {
    return ((getType() == lhs.getType()) && getSeed() == lhs.getSeed());
}

inline GSL_GFSR4::~GSL_GFSR4() {
    gsl_rng_free(thisrng);
}
#endif	/* GSL_GFSR4_H */

