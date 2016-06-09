/* 
 * File:   IInputWidget.h
 * Author: fordem
 *
 * Created on February 26, 2015, 7:06 PM
 */

#ifndef IINPUTWIDGET_H
#define	IINPUTWIDGET_H
#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QIntValidator>
#include "IRandomWalk.h"
class IInputWidget : public QWidget {
    Q_OBJECT
public:
    IInputWidget(QWidget * parent);
    IInputWidget(const IInputWidget& orig);
    virtual ~IInputWidget();
    void setMeVisible(bool visible);
    virtual void clear();
signals:
    void createdRWK(IRandomWalk*);
private:

protected:
    QLineEdit * NWalks;
    QLineEdit * WSize;
    QLabel * lNWalks;
    QLabel * lWSize;
    QPropertyAnimation *animationMin, *animationMax;
    QPropertyAnimation *_animationMin, *_animationMax;
    QParallelAnimationGroup * groupAnim, *_groupAnim;
    bool fNWalks, fWSize;
    QGridLayout * qGrdLay;
protected slots:
    void numwalksEdit(QString);
    void numstepsEdit(QString);
    virtual void setMeInvisible();

};

#endif	/* IINPUTWIDGET_H */

