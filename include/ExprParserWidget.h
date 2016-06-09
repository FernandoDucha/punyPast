/* 
 * File:   ExpressionParserWidget.h
 * Author: fordem
 *
 * Created on February 21, 2015, 6:54 AM
 */

#ifndef EXPRESSIONPARSERWIDGET_H
#define	EXPRESSIONPARSERWIDGET_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QIntValidator>
#include <QTextEdit>
#include <QCheckBox>
#include <QPixmap>
#include "Overlay.h"
#include "ExprRNG.h"
#include "Tokenizer.h"
#include "IRandomWalk.h"
#include "ExprBinaryRandomWalk.h"
#include "IInputWidget.h"

class ExprParserWidget : public IInputWidget {
    Q_OBJECT
public:
    ExprParserWidget(QWidget * parent);
    virtual ~ExprParserWidget();
    void setOverlay(Overlay * Over);
    Overlay * getOverlay();
    QParallelAnimationGroup *getAnimation();
    virtual void clear();
protected slots:
    void runTimeParse();
    void enableExprEditing(int);
    void enableNwWsEditing(bool);
    void attemptToCreateRWK();
    void setMeInvisible();
private:
    Tokenizer * Toker;
    ExprRNG * _exprRNG;
    QGridLayout *qGrdLayTexBox;
    QLabel * linCongTitle;
    QTextEdit * linCongInput;
    QLabel * lChkExpr;
    QCheckBox * chkExpr;
    QLabel * okNoLabel;
    Overlay * ThisOverLay;
    ExprBinaryRandomWalk * _exprBRWK;
    QWidget * textBox;
    

};

#endif	/* EXPRESSIONPARSERWIDGET_H */

