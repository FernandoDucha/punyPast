/* 
 * File:   FileRNG.h
 * Author: fordem
 *
 * Created on March 11, 2015, 11:45 AM
 */

#ifndef FILERNG_H
#define	FILERNG_H
#include "IRNG.h"
#include "FileRawBuffer.h"
#include <sstream>
#include <limits>
using namespace std;
class FileRNG : public IRNG {
public:
    FileRNG(FileRawBuffer * frb, uint64_t seed);
    virtual ~FileRNG();
    virtual double randd();
    virtual uint64_t randi();
    virtual bool operator==(IRNG&);
private:
    FileRawBuffer * thisfrb;
};

#endif	/* FILERNG_H */

