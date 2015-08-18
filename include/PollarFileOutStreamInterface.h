/* 
 * File:   PollarFileOutStreamInterface.h
 * Author: fordem
 *
 * Created on August 13, 2015, 10:33 AM
 */

#ifndef POLLARFILEOUTSTREAMINTERFACE_H
#define	POLLARFILEOUTSTREAMINTERFACE_H

#include "FileOutStreamInterface.h"
#include "QPollarF.h"


class PollarFileOutStreamInterface : public  FileOutStreamInterface<QPollarF> {
public:
    PollarFileOutStreamInterface(char * FileName);
    virtual ~PollarFileOutStreamInterface();
    virtual void write(QPollarF);
    virtual void seek(uint64_t n);
    virtual uint64_t goBeg();
    virtual uint64_t goEnd();
    virtual uint64_t fileSize();
    virtual void flush();
    virtual bool canWrite();
    virtual bool canRead();
    virtual void close();
    virtual void open();
private:

};
inline void PollarFileOutStreamInterface::close(){
    this->FileS.close();
}
inline void PollarFileOutStreamInterface::open(){
    this->FileS.open(_file, ios::out | ios::binary);
}
inline PollarFileOutStreamInterface::PollarFileOutStreamInterface(char * FileName):FileOutStreamInterface<QPollarF>(FileName) {
    assert(this->FileS.is_open());
}

inline PollarFileOutStreamInterface::~PollarFileOutStreamInterface() {
    this->FileS.close();
}

inline void PollarFileOutStreamInterface::write(QPollarF a) {
    double x = a.rx();
    this->FileS.write(reinterpret_cast<char*> (&x), sizeof (double));
    double y= a.ry();
    this->FileS.write(reinterpret_cast<char*> (&y), sizeof (double));
}

inline uint64_t PollarFileOutStreamInterface::goBeg() {
    FileS.seekg(ios::beg);
    return FileS.tellg();
}

inline uint64_t PollarFileOutStreamInterface::goEnd() {
    FileS.seekg(ios::end);
    return FileS.tellg();
}

inline uint64_t PollarFileOutStreamInterface::fileSize() {
    uint64_t actual = FileS.tellg();
    uint64_t ret = goEnd() - goBeg();
    FileS.seekg(actual);
    return ret;
}

inline void PollarFileOutStreamInterface::flush() {
    this->FileS.flush();
}

inline void PollarFileOutStreamInterface::seek(uint64_t n) {
    this->FileS.seekg(n);
}
inline bool PollarFileOutStreamInterface::canRead() {
    return false;
}
inline bool PollarFileOutStreamInterface::canWrite() {
    return true;
}
#endif	/* POLLARFILEOUTSTREAMINTERFACE_H */

