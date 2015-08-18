/* 
 * File:   PollarBufferManager.h
 * Author: fordem
 *
 * Created on August 13, 2015, 2:44 PM
 */

#ifndef POLLARBUFFERMANAGER_H
#define	POLLARBUFFERMANAGER_H

#include "RWBufferManager.h"
#include "QPollarF.h"
#include "PollarFileOutStreamInterface.h"
#include "PollarFileInStreamInterface.h"
#include "BufferedPollarRwDp.h"
#include "BufferedPollarRwVec.h"

class PollarBufferManager {
public:
    PollarBufferManager(char * File);
    virtual ~PollarBufferManager();
    virtual IRWBufferedItem<QPollarF> * createBufferedDp(QPollarF * data, unsigned long int n);
    virtual IRWBufferedItem<QPollarF> * createBufferedVec(QPollarF * data, unsigned long int n);
    virtual IRWBufferedItem<QPollarF> * createBufferedDp(unsigned long int n);
    virtual IRWBufferedItem<QPollarF> * createBufferedVec(unsigned long int n);
    virtual void resetManager();
    virtual RWBufferIterator<QPollarF, IRWBufferedItem<QPollarF>*> getDpIterator();
    virtual RWBufferIterator<QPollarF, IRWBufferedItem<QPollarF>*>getVecIterator();
private:
    PollarBufferManager();
    FileStreamInterface * output;
    FileStreamInterface * input;
    uint64_t fpos;
    vector<RWLocPair> fPosDpIndex;
    vector<RWLocPair> fPosVecIndex;
    char * _file;
};

inline PollarBufferManager::PollarBufferManager(char * File) {
    this->output = new PollarFileOutStreamInterface(File);
    this->input = new PollarFileInStreamInterface(File);
    this->_file = File;
    this->fpos = 0;
}

inline PollarBufferManager::~PollarBufferManager() {
    output->close();
    input->close();
}

inline IRWBufferedItem<QPollarF> * PollarBufferManager::createBufferedDp(QPollarF * data, unsigned long int n) {
    IRWBufferedItem<QPollarF>* ret = new BufferedPollarRwDp(dynamic_cast<PollarFileInStreamInterface*> (input), dynamic_cast<PollarFileOutStreamInterface*> (output));
    ret->receiveData(data, n, fpos);
    fPosDpIndex.push_back(RWLocPair(fpos, n));
    fpos += n * 2 * sizeof (double);
    return ret;
}

inline IRWBufferedItem<QPollarF> * PollarBufferManager::createBufferedVec(QPollarF * data, unsigned long int n) {
    IRWBufferedItem<QPollarF>* ret = new BufferedPollarRwVec(dynamic_cast<PollarFileInStreamInterface*> (input), dynamic_cast<PollarFileOutStreamInterface*> (output));
    ret->receiveData(data, n, fpos);
    fPosVecIndex.push_back(RWLocPair(fpos, n));
    fpos += n * 2 * sizeof (double);
    return ret;
}

inline IRWBufferedItem<QPollarF> * PollarBufferManager::createBufferedDp(unsigned long int n) {
    IRWBufferedItem<QPollarF>* ret = new BufferedPollarRwDp(dynamic_cast<PollarFileInStreamInterface*> (input), dynamic_cast<PollarFileOutStreamInterface*> (output));
    QPollarF * data = new QPollarF[n];
    ret->receiveData(data, n, fpos);
    delete [] data;
    fPosVecIndex.push_back(RWLocPair(fpos, n));
    fpos += n * 2 * sizeof (double);
    return ret;
}

inline IRWBufferedItem<QPollarF> * PollarBufferManager::createBufferedVec(unsigned long int n) {
    IRWBufferedItem<QPollarF>* ret = new BufferedPollarRwVec(dynamic_cast<PollarFileInStreamInterface*> (input), dynamic_cast<PollarFileOutStreamInterface*> (output));
    QPollarF * data = new QPollarF[n];
    ret->receiveData(data, n, fpos);
    delete [] data;
    fPosVecIndex.push_back(RWLocPair(fpos, n));
    fpos += n * 2 * sizeof (double);
    return ret;
}

inline void PollarBufferManager::resetManager() {
    fpos = 0;
    fPosDpIndex.clear();
    fPosVecIndex.clear();
    output->close();
    output->open();
    input->close();
    input->open();
}

inline RWBufferIterator<QPollarF, IRWBufferedItem<QPollarF>*> PollarBufferManager::getDpIterator() {

}

inline RWBufferIterator<QPollarF, IRWBufferedItem<QPollarF>*> PollarBufferManager::getVecIterator() {

}
#endif	/* POLLARBUFFERMANAGER_H */

