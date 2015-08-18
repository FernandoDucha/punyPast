/* 
 * File:   FileQBRWWidget.h
 * Author: fordem
 *
 * Created on February 22, 2015, 10:59 PM
 */

#ifndef FILEQBRWWIDGET_H
#define	FILEQBRWWIDGET_H
#include <QGridLayout>
#include <FileQTreeWidget.h>
#include <FileRawBuffer.h>
#include <BinaryRandomWalk.h>
#include "IInputWidget.h"
class FileQBRWWidget : public IInputWidget {
    Q_OBJECT
public:
    FileQBRWWidget(QWidget * parent);
    FileQBRWWidget(const FileQBRWWidget& orig);
    virtual ~FileQBRWWidget();
    QParallelAnimationGroup *getAnimation();
    virtual void clear();
protected slots:
    void attemptToCreateRWK();
    void enableNwWsBox();
private:
    QGridLayout * qGrdLay;
    FileQTreeWidget * fileWid;
    BinaryRandomWalk * brwk;
};

#endif	/* FILEQBRWWIDGET_H */

