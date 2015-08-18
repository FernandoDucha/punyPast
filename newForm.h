/* 
 * File:   newForm.h
 * Author: fordem
 *
 * Created on February 10, 2015, 8:22 AM
 */

#ifndef _NEWFORM_H
#define	_NEWFORM_H

#include "ui_newForm.h"

class newForm : public QWidget {
    Q_OBJECT
public:
    newForm();
    virtual ~newForm();
private:
    Ui::newForm widget;
};

#endif	/* _NEWFORM_H */
