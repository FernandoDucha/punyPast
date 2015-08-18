/* 
 * File:   FileInStreamInterface.h
 * Author: fordem
 *
 * Created on February 27, 2015, 4:08 PM
 */

#ifndef FILEINSTREAMINTERFACE_H
#define	FILEINSTREAMINTERFACE_H
#include <fstream>
#include <assert.h>
#include <stdint.h>

#include "FileStreamInterface.h"
using namespace std;

template <class Type> class FileInStreamInterface : public FileStreamInterface {
public:
    FileInStreamInterface(char * FileName);
    virtual ~FileInStreamInterface();
    virtual Type read();
    virtual void seek(uint64_t n);
    virtual uint64_t goBeg();
    virtual uint64_t goEnd();
    virtual uint64_t fileSize();
    virtual void flush();
    virtual bool canWrite();
    virtual bool canRead();
    virtual void close();
    virtual void open();
protected:
    char * _file;
    fstream FileS;
};
template <class Type>  void FileInStreamInterface<Type>::close(){
    FileS.close();
}
template <class Type>  void FileInStreamInterface<Type>::open(){
    FileS.open(_file, ios::in | ios::binary);
}
template <class Type> FileInStreamInterface<Type>::FileInStreamInterface(char * FileName) {
    _file=FileName;
    open();
    assert(FileS.is_open());
}

template <class Type> FileInStreamInterface<Type>::~FileInStreamInterface() {
    FileS.close();
}

template <class Type> Type FileInStreamInterface<Type>::read() {
    Type a;
    FileS.read(reinterpret_cast<char*> (&a), sizeof (a));
    return a;
}

template <class Type> uint64_t FileInStreamInterface<Type>::goBeg() {
    FileS.seekg(ios::beg);
    return FileS.tellg();
}

template <class Type> uint64_t FileInStreamInterface<Type>::goEnd() {
    FileS.seekg(ios::end);
    return FileS.tellg();
}

template <class Type> uint64_t FileInStreamInterface<Type>::fileSize() {
    uint64_t actual = FileS.tellg();
    uint64_t ret = goEnd() - goBeg();
    FileS.seekg(actual);
    return ret;
}

template <class Type> void FileInStreamInterface<Type>::flush() {
    FileS.flush();
}

template <class Type> void FileInStreamInterface<Type>::seek(uint64_t n) {
    FileS.seekg(n);
}
template <class Type> bool FileInStreamInterface<Type>::canRead() {
    return true;
}
template <class Type> bool FileInStreamInterface<Type>::canWrite() {
    return false;
}
#endif	/* FILEINSTREAMINTERFACE_H */

