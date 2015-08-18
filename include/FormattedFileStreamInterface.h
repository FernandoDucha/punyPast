/* 
 * File:   FormattedFileStreamInterface.h
 * Author: fordem
 *
 * Created on June 19, 2015, 9:54 PM
 */

#ifndef FORMATTEDFILESTREAMINTERFACE_H
#define	FORMATTEDFILESTREAMINTERFACE_H
#include "FileStreamInterface.h"
class FormattedFileStreamInterface : public FileStreamInterface {
public:
    FormattedFileStreamInterface();
    virtual ~FormattedFileStreamInterface();
    
private:

};
FormattedFileStreamInterface::FormattedFileStreamInterface() {

}

FormattedFileStreamInterface::~FormattedFileStreamInterface() {
}

#endif	/* FORMATTEDFILESTREAMINTERFACE_H */

