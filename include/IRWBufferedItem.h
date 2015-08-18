/* 
 * File:   IRWItem.h
 * Author: fordem
 *
 * Created on February 27, 2015, 1:33 PM
 */

#ifndef IRWBUFFEREDITEM_H
#define	IRWBUFFEREDITEM_H
#include <IRWItem.h>
#include <FileInStreamInterface.h>
#include <FileOutStreamInterface.h>
#include <limits>
#include "FileStreamInterface.h"
#include "RWLocPair.h"
template <class Type> class IRWItem;

template <class Type> class IRWBufferedItem : public IRWItem<Type> {
public:
    IRWBufferedItem(FileInStreamInterface<Type>*, FileOutStreamInterface<Type>*);
    IRWBufferedItem(const IRWBufferedItem&);
    virtual ~IRWBufferedItem();
    virtual void setFInitPos(uint64_t)  = 0;
    virtual uint64_t getFInitPos() const= 0;
    virtual void setNpoints(unsigned long int Npoints)=0;
    virtual void receiveData(Type * data, long unsigned int n, uint64_t pos) = 0;
    virtual IRWItem<Type>& operator=(IRWItem<Type>&);
    virtual IRWBufferedItem<Type>& operator=(IRWBufferedItem<Type>&);
    FileInStreamInterface<Type> * getInput()const{
        return input;
    }
    
    FileOutStreamInterface<Type> * getOutput()const{
        return output;
    }
protected:
    FileInStreamInterface<Type> * input;
    FileOutStreamInterface<Type> * output;
    uint64_t finitpos;
    Type max, min;
    int sizeOfType;
};
template <class Type> IRWBufferedItem<Type>::IRWBufferedItem(const IRWBufferedItem<Type>& c){
    input=c.getInput();
    output=c.getOutput();
    this->setNpoints(c.getNpoints());
    finitpos=c.getFInitPos();
    *this=*const_cast<IRWBufferedItem<Type>*>(&c);
}
    
template <class Type> IRWItem<Type>& IRWBufferedItem<Type>::operator=(IRWItem<Type>& rhs) {
    if(this==&rhs){
        return *this;
    }else if (this->getNpoints() == rhs.getNpoints()) {
        min = rhs.getMin();
        max = rhs.getMax();
        rhs.resetIterator();
        this->resetIterator();
        Type rhsElem;
        for (int i = 0; i < rhs.getNpoints(); i++) {
            rhs.getNext(rhsElem);
            output->write(rhsElem);
        }
        return *this;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}

template <class Type> IRWBufferedItem<Type>& IRWBufferedItem<Type>::operator=(IRWBufferedItem<Type>& rhs) {
    if (this->getNpoints() == rhs.getNpoints()) {
        min = rhs.getMin();
        max = rhs.getMax();
        rhs.resetIterator();
        this->resetIterator();
        Type rhsElem;
        for (int i = 0; i < rhs.getNpoints(); i++) {
            rhs.getNext(rhsElem);
            output->write(rhsElem);
        }
        return *this;
    } else {
        fprintf(stderr, "ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}

template <class Type > IRWBufferedItem<Type>::IRWBufferedItem(FileInStreamInterface<Type>* in, FileOutStreamInterface<Type> *out) : IRWItem<Type>() {
    input = in;
    output = out;
    min = numeric_limits<Type>::max();
    max = numeric_limits<Type>::min();
    sizeOfType = sizeof (Type);
}

template <class Type > IRWBufferedItem<Type>::~IRWBufferedItem() {

}

//template <class Type>FileOutStreamInterface<Type> * IRWBufferedItem<Type>::castWrite(FileStreamInterface * stream) {
//    if (stream->canWrite()) {
//        return dynamic_cast<FileOutStreamInterface<Type>*> (stream);
//    } else {
//        return nullptr;
//    }
//}
//
//template <class Type>FileInStreamInterface<Type> * IRWBufferedItem<Type>::castRead(FileStreamInterface * stream) {
//    if (stream->canRead()) {
//        return dynamic_cast<FileInStreamInterface<Type>*> (stream);
//    } else {
//        return nullptr;
//    }
//}
#endif	/* IRWITEM_H */

