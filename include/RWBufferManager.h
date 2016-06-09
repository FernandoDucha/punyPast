/* 
 * File:   IRWBufferManager.h
 * Author: fordem
 *
 * Created on March 4, 2015, 3:40 PM
 */

#ifndef RWBUFFERMANAGER_H
#define	RWBUFFERMANAGER_H
#include "FileInStreamInterface.h"
#include "FileOutStreamInterface.h"
#include "RWBufferedDp.h"
#include "RWBufferedVec.h"
#include "RWLocPair.h"
#include "RWBufferIterator.h"
#include <vector>
using namespace std;

template <class Type> class RWBufferManager {
public:
    typedef RWBufferIterator<Type, RWBufferedDp<Type>> vecBufIt;
    typedef RWBufferIterator<Type, RWBufferedVec<Type>> dpBufIt;

    RWBufferManager(char * File);
    virtual ~RWBufferManager();
    virtual IRWBufferedItem<Type> * createBufferedDp(Type * data, unsigned long int n);
    virtual IRWBufferedItem<Type> *  createBufferedVec(Type * data, unsigned long int n);
    virtual IRWBufferedItem<Type> * createBufferedDp(unsigned long int n);
    virtual IRWBufferedItem<Type> * createBufferedVec(unsigned long int n);
    virtual void resetManager();
    virtual RWBufferIterator<Type, RWBufferedDp<Type>> getDpIterator();
    virtual RWBufferIterator<Type, RWBufferedVec<Type>> getVecIterator();
protected:
    RWBufferManager();
    FileStreamInterface * output;
    FileStreamInterface * input;
    uint64_t fpos;
    vector<RWLocPair> fPosDpIndex;
    vector<RWLocPair> fPosVecIndex;
    char * _file;
};

template <class Type> RWBufferIterator<Type, RWBufferedDp<Type>> RWBufferManager<Type>::getDpIterator() {
    return RWBufferIterator<Type, RWBufferedDp<Type>>(fPosDpIndex.begin(), fPosDpIndex.end(), dynamic_cast<FileInStreamInterface<Type>*>(input), dynamic_cast<FileOutStreamInterface<Type>*>(output));
}

template <class Type> RWBufferIterator<Type, RWBufferedVec<Type>> RWBufferManager<Type>::getVecIterator() {
    return RWBufferIterator<Type, RWBufferedVec<Type>>(fPosVecIndex.begin(), fPosVecIndex.end(), dynamic_cast<FileInStreamInterface<Type>*>(input), dynamic_cast<FileOutStreamInterface<Type>*>(output));
}
template <class Type> RWBufferManager<Type>::RWBufferManager(){
    output = NULL;
    input = NULL;
    _file = NULL;
}
template <class Type> RWBufferManager<Type>::RWBufferManager(char * File) : fpos(0) {
    output = new FileOutStreamInterface<Type>(File);
    input = new FileInStreamInterface<Type>(File);
    _file = File;
}

template <class Type> RWBufferManager<Type>::~RWBufferManager() {
}

template <class Type> IRWBufferedItem<Type> * RWBufferManager<Type>::createBufferedDp(Type* data, unsigned long int n) {
    IRWBufferedItem<Type>* ret = new RWBufferedDp<Type>(dynamic_cast<FileInStreamInterface<Type>*>(input), dynamic_cast<FileOutStreamInterface<Type>*>(output));
    ret->receiveData(data, n, fpos);
    fPosDpIndex.push_back(RWLocPair(fpos, n));
    fpos += n * sizeof (Type);
    return ret;
}

template <class Type> IRWBufferedItem<Type> *  RWBufferManager<Type>::createBufferedVec(Type* data, unsigned long int n) {
    IRWBufferedItem<Type>* ret = new RWBufferedVec<Type>(dynamic_cast<FileInStreamInterface<Type>*>(input), dynamic_cast<FileOutStreamInterface<Type>*>(output));
    ret->receiveData(data, n, fpos);
    fPosVecIndex.push_back(RWLocPair(fpos, n));
    fpos += n * sizeof (Type);
    return ret;
}

template <class Type> IRWBufferedItem<Type> * RWBufferManager<Type>::createBufferedDp(unsigned long int n) {
    IRWBufferedItem<Type>* ret = new RWBufferedDp<Type>(dynamic_cast<FileInStreamInterface<Type>*>(input), dynamic_cast<FileOutStreamInterface<Type>*>(output));
    Type * data = new Type[n]; 
    ret->receiveData(data, n, fpos);
    delete data;
    fPosDpIndex.push_back(RWLocPair(fpos, n));
    fpos += n * sizeof (Type);
    return ret;
}

template <class Type> IRWBufferedItem<Type> * RWBufferManager<Type>::createBufferedVec(unsigned long int n) {
    IRWBufferedItem<Type>* ret = new RWBufferedVec<Type>(dynamic_cast<FileInStreamInterface<Type>*>(input), dynamic_cast<FileOutStreamInterface<Type>*>(output));
    Type * data = new Type[n]; 
    ret->receiveData(data, n, fpos);
    delete data;
    fPosVecIndex.push_back(RWLocPair(fpos, n));
    fpos += n * sizeof (Type);
    return ret;
}

template <class Type> void RWBufferManager<Type>::resetManager() {
    fpos = 0;
    fPosDpIndex.clear();
    fPosVecIndex.clear();
    output->close();
    output->open();
    input->close();
    input->open();
}

#endif	/* IRWBUFFERMANAGER_H */

