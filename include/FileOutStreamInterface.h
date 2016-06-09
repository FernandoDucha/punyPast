/* 
 * File:   FileStreamInterface.h
 * Author: fordem
 *
 * Created on February 27, 2015, 1:50 PM
 */

#ifndef FILEOUTSTREAMINTERFACE_H
#define	FILEOUTSTREAMINTERFACE_H
#include <fstream>
#include <assert.h>
#include <stdint.h>
#include <FileStreamInterface.h>
using namespace std;

template <class Type> class FileOutStreamInterface : public FileStreamInterface {
public:
    FileOutStreamInterface(char * FileName);
    virtual ~FileOutStreamInterface();
    virtual void write(Type);
    virtual void seek(uint64_t n);
    virtual uint64_t goBeg();
    virtual uint64_t goEnd();
    virtual uint64_t fileSize();
    virtual uint64_t tell();
    virtual bool eof();
    virtual void flush();
    virtual bool canWrite();
    virtual bool canRead();
    virtual void close();
    virtual void open();

    virtual bool good();

    protected:
    fstream FileS;
    char * _file;
};

template <class Type> void FileOutStreamInterface<Type>::close() {
    FileS.close();
}
template <class Type> bool FileOutStreamInterface<Type>::good() {
    return FileS.good();
}

template <class Type> bool FileOutStreamInterface<Type>::eof() {
    return FileS.eof();
}
template <class Type> void FileOutStreamInterface<Type>::open() {
    FileS.open(_file, ios::out | ios::binary);
}

template <class Type> FileOutStreamInterface<Type>::FileOutStreamInterface(char * FileName) {
    _file = FileName;
    open();
    assert(FileS.is_open());
}

template <class Type> FileOutStreamInterface<Type>::~FileOutStreamInterface() {
    FileS.close();
}

template <class Type> void FileOutStreamInterface<Type>::write(Type a) {
    FileS.write(reinterpret_cast<const char*> (&a), sizeof (a));
}

template <class Type> uint64_t FileOutStreamInterface<Type>::goBeg() {
    FileS.seekp(ios::beg);
    return FileS.tellp();
}

template <class Type> uint64_t FileOutStreamInterface<Type>::goEnd() {
    FileS.seekp(ios::end);
    return FileS.tellp();
}

template <class Type> uint64_t FileOutStreamInterface<Type>::fileSize() {
    uint64_t actual = FileS.tellp();
    uint64_t ret = goEnd() - goBeg();
    FileS.seekp(actual);
    return ret;
}

template <class Type> uint64_t FileOutStreamInterface<Type>::tell() {
    return FileS.tellp();
}

template <class Type> void FileOutStreamInterface<Type>::flush() {
    FileS.flush();
}

template <class Type> void FileOutStreamInterface<Type>::seek(uint64_t n) {
    FileS.seekp(n);
}

template <class Type> bool FileOutStreamInterface<Type>::canRead() {
    return false;
}

template <class Type> bool FileOutStreamInterface<Type>::canWrite() {
    return true;
}
#endif	/* FILESTREAMINTERFACE_H */

