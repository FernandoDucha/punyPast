/* 
 * File:   PollarFileInStreamInterface.h
 * Author: fordem
 *
 * Created on August 13, 2015, 10:17 AM
 */

#ifndef POLLARFILEINSTREAMINTERFACE_H
#define	POLLARFILEINSTREAMINTERFACE_H

#include "FileInStreamInterface.h"
#include "QPollarF.h"


class PollarFileInStreamInterface : public  FileInStreamInterface<QPollarF> {
public:
    PollarFileInStreamInterface(char * FileName);
    virtual ~PollarFileInStreamInterface();
    virtual QPollarF read();
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
inline void PollarFileInStreamInterface::close(){
    this->FileS.close();
}
inline void PollarFileInStreamInterface::open(){
    this->FileS.open(_file, ios::in | ios::binary);
}
inline PollarFileInStreamInterface::PollarFileInStreamInterface(char * FileName):FileInStreamInterface<QPollarF>(FileName) {
    assert(this->FileS.is_open());
}

inline PollarFileInStreamInterface::~PollarFileInStreamInterface() {
    this->FileS.close();
}

inline QPollarF PollarFileInStreamInterface::read() {
    double x = 0;
    this->FileS.read(reinterpret_cast<char*> (&x), sizeof (double));
    double y = 0;
    this->FileS.read(reinterpret_cast<char*> (&y), sizeof (double));
    QPollarF ret;
    ret.setX(x);
    ret.setY(y);
    return ret;
}

inline uint64_t PollarFileInStreamInterface::goBeg() {
    this->FileS.seekg(ios::beg);
    return FileS.tellg();
}

inline uint64_t PollarFileInStreamInterface::goEnd() {
    this->FileS.seekg(ios::end);
    return FileS.tellg();
}

inline uint64_t PollarFileInStreamInterface::fileSize() {
    uint64_t actual = FileS.tellg();
    uint64_t ret = goEnd() - goBeg();
    this->FileS.seekg(actual);
    return ret;
}

inline void PollarFileInStreamInterface::flush() {
    this->FileS.flush();
}

inline void PollarFileInStreamInterface::seek(uint64_t n) {
    this->FileS.seekg(n);
}
inline bool PollarFileInStreamInterface::canRead() {
    return true;
}
inline bool PollarFileInStreamInterface::canWrite() {
    return false;
}
#endif	/* POLLARFILEINSTREAMINTERFACE_H */

