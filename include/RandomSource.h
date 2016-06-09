/* 
 * File:   RandomSource.h
 * Author: fordem
 *
 * Created on February 20, 2015, 7:14 PM
 */

#ifndef RANDOMSOURCE_H
#define	RANDOMSOURCE_H
#include <QDialog>
#include <QTreeWidget>
#include <QGridLayout>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QWidget>
#include <QKeyEvent>
#include <QAbstractButton>
#include <QPushButton>

#include "MemAllocWidget.h"

enum RS_TYPES {
    NONE = -1, FA_QRNG = 0, RNG_EP = 1, RNG_CD = 2,WEIES=3
};

class RandomSource : public QDialog {
    Q_OBJECT
public:
    RandomSource(QWidget * parent);
    virtual ~RandomSource();
    void keyPressEvent(QKeyEvent *e);
protected slots:
    void okPressed();
    void noPressed();
    void memChoiceSel(MEM_ALLOC);
private:
    QTreeWidget * qTW;
    QGridLayout * qGrdLay;
    QTreeWidgetItem * FileAnalysis, *RandomGenerators, *RNGcd,*NonDiff;
    QTreeWidgetItem * QRNGItem, *ExprParser, *CommonLinCong,*Weiestrass;
    QPushButton * okBt, * noBt;
    MemAllocWidget * allocChoice;
    MEM_ALLOC memChoice;
signals:
    void choiceType(RS_TYPES random_source);
    void memAlloc(MEM_ALLOC);
};

#endif	/* RANDOMSOURCE_H */

