/* 
 * File:   GraphScene.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 10:04
 */

#ifndef GRAPHSCENE_H
#define	GRAPHSCENE_H
#include <qt5/QtWidgets/QGraphicsScene>
#include "DPBase.h"
#include "RWVBase.h"
#include "GeneralUsage.h"
#include "LineItem.h"
#include <QDebug>
#include <QVector>
#include <limits.h>
class GraphScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphScene();
    virtual ~GraphScene();
    void setupRWKl(DataSetInt * dp);
    void setupRWKbl(RWVSInt * bdp);
    void setSize(unsigned int size);
    unsigned int getSize() const;
    void setVisibleRWKL(int init, int end);
    void setVisibleRWKBL(int init, int end);
    void removeAllRWKL();
    void removeAllRWKBL();
    
    unsigned int getVisible() const;
private:
    LineItem * SumLine;
    QVector<LineItem*> * RwkLines;
    QVector<LineItem*> * RwkBinLines;
    int thisinit,thisend;
    int size;
    int visible;
};

#endif	/* GRAPHSCENE_H */

