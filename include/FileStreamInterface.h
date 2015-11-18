/* 
 * File:   FileStreamInterface.h
 * Author: fordem
 *
 * Created on March 3, 2015, 11:04 PM
 */

#ifndef FILESTREAMINTERFACE_H
#define	FILESTREAMINTERFACE_H
#include <stdint.h>

#include "dieharder/brg_types.h"
using namespace std;
class FileStreamInterface {
public:
    FileStreamInterface(){};
    virtual ~FileStreamInterface(){};
    virtual void seek(uint64_t n)=0;
    virtual uint64_t goBeg()=0;
    virtual uint64_t goEnd()=0;
    virtual uint64_t fileSize()=0;
    virtual uint64_t tell()=0;
    virtual bool eof()=0;
    virtual void flush()=0;
    virtual bool canWrite()=0;
    virtual bool canRead()=0;
    virtual void close()=0;
    virtual void open()=0;
    virtual bool good()=0;
private:
};


#endif	/* FILESTREAMINTERFACE_H */

