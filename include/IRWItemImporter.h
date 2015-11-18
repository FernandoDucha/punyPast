/* 
 * File:   IRWItemImporter.h
 * Author: fordem
 *
 * Created on November 9, 2015, 6:53 PM
 */

#ifndef IRWITEMIMPORTER_H
#define	IRWITEMIMPORTER_H
#include "FileInStreamInterface.h"
#include "IRWItem.h"
#include "IImporter.h"
#include <vector>
#include "RWDp.h"
template <class T> class IRWItemImporter : public IImporter
{
public:
    IRWItemImporter(FileInStreamInterface<T> & in);
    virtual ~IRWItemImporter();
    bool addTerm();
    IRWItem<T> * finish();
private:
    vector<T> buffer;
    FileInStreamInterface<T> * input;
};
template <class T> IRWItemImporter<T>::IRWItemImporter(FileInStreamInterface<T>& in){
    input=&in;
}
template <class T> IRWItemImporter<T>::~IRWItemImporter(){
    
}
template <class T> bool IRWItemImporter<T>::addTerm(){
    buffer.push_back(input->read());
}

template <class T> IRWItem<T> * IRWItemImporter<T>::finish(){
    IRWItem<T> * ret = new RWDp<T>();
    ret->receiveData(buffer.data(),buffer.size());
    return ret;
}

#endif	/* IRWITEMIMPORTER_H */

