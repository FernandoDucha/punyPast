/* 
 * File:   FileInStreamInterfaceDecimal.h
 * Author: fordem
 *
 * Created on November 10, 2015, 12:02 AM
 */

#ifndef FILEINSTREAMINTERFACEDECIMAL_H
#define	FILEINSTREAMINTERFACEDECIMAL_H

#include "FileInStreamInterface.h"


template <class T> class FileInStreamInterfaceDecimal: public FileInStreamInterface<T> {
public:
    FileInStreamInterfaceDecimal(char * filename);
    FileInStreamInterfaceDecimal(const FileInStreamInterfaceDecimal& orig);
    virtual ~FileInStreamInterfaceDecimal();
    virtual void open();
    virtual T read();
private:

};

template <class T> FileInStreamInterfaceDecimal<T>::FileInStreamInterfaceDecimal(char * filename):FileInStreamInterface<T>(filename) {
    this->close();
    this->FileS.open(this->_file,ios::in);
    assert(this->FileS.is_open());    
}
template <class T>void FileInStreamInterfaceDecimal<T>::open(){
    this->FileS.open(this->_file,ios::in);
}
template <class T>T FileInStreamInterfaceDecimal<T>::read(){
    T var;
    this->FileS>>var;
    return var;
}

template <class T> FileInStreamInterfaceDecimal<T>::~FileInStreamInterfaceDecimal() {
    
}
#endif	/* FILEINSTREAMINTERFACEDECIMAL_H */

