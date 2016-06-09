/* 
 * File:   IImporter.h
 * Author: fordem
 *
 * Created on November 9, 2015, 8:20 PM
 */

#ifndef IIMPORTER_H
#define	IIMPORTER_H
#include "IRWItem.h"
class IImporter {
public:
    IImporter();
    virtual ~IImporter();
    virtual bool addTerm()=0;
private:

};
inline IImporter::IImporter() {
}


inline IImporter::~IImporter() {
}
#endif	/* IIMPORTER_H */

