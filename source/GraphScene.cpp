/* 
 * File:   GraphScene.cpp
 * Author: fernando
 * 
 * Created on 27 de Abril de 2013, 10:04
 */

#include <qgraphicsitem.h>

#include "GraphScene.h"

GraphScene::GraphScene() {
    this->items(Qt::AscendingOrder);
    RwkBinLines = new QVector<LineItem*>();
    RwkLines = new QVector<LineItem*>();
    SumLine = new LineItem();
    visible = 0;
    thisinit = 0;
    thisend = 0;
}

GraphScene::~GraphScene() {
    delete RwkLines;
    delete RwkLines;
}

void GraphScene::setSize(unsigned int size) {
    this->size = size;
}

unsigned int GraphScene::getSize() const {
    return size;
}

void GraphScene::setupRWKl(DataSetInt * dp) {
    removeAllRWKL();
    RwkLines->clear();

    for (unsigned int i = 0; i < dp->getSize(); i++) {
        RwkLines->push_back(new LineItem(dp->getElement(i)));
        //addItem(RwkLines[i]);
    }
    setSize(dp->getSize());
}

void GraphScene::setupRWKbl(RWVSInt * bdp) {
    removeAllRWKBL();
    RwkBinLines->clear();
    for (unsigned int i = 0; i < bdp->getSize(); i++) {
        RwkBinLines->push_back(new LineItem(bdp->getElement(i)));
        // addItem(RwkBinLines[i]);
    }
    RWVInt * a = new RWVInt();
    SumLine = new LineItem(a);
    setSize(bdp->getSize());
}

void GraphScene::setVisibleRWKL(int init, int end) {

    if (init >= 1) {
        for (int i = init - 1;(i>=0)&&(this->items().contains(RwkLines->at(i))); i--) {
            removeItem(RwkLines->at(i));
            visible--;
        }
    }
    if (init == end) {
        if (!items().contains(RwkLines->at(init))) {
            addItem(RwkLines->at(init));
        }
        RwkLines->at(init)->setAxis(RwkLines->at(init)->limits());
        visible = 1;
        for (int i  =0;(i<init)&&(this->items().contains(RwkLines->at(i))); i++) {
            removeItem(RwkLines->at(i));
        }
        for (int i  =init+1 ;(i<RwkLines->size())&&(this->items().contains(RwkLines->at(i))); i++) {
            removeItem(RwkLines->at(i));
        }
        
    } else {
        RwkLines->at(0)->resetAxis();
        for (int i = init; i <= end; i++) {

            if (!items().contains(RwkLines->at(i))) {
                addItem(RwkLines->at(i));
                visible++;
            }

            RwkLines->at(i)->setAxis(RwkLines->at(i)->limits());

        }

        for (int i = end + 1; i < RwkLines->size() && items().contains(RwkLines->at(i)); i++) {
            removeItem(RwkLines->at(i));
            visible--;
        }
    }

}

void GraphScene::setVisibleRWKBL(int init, int end) {
    if (this->items().contains(SumLine)) {
        this->removeItem(SumLine);
    }
    RwkBinLines->at(0)->resetAxis();
    if (init >= 1) {
        for (int i = init - 1; items().contains(RwkBinLines->at(i)); i--) {
            *SumLine->getThisrwv() -= *RwkBinLines->at(i)->getThisrwv();
            //  removeItem(RwkBinLines[i]);
            visible--;
        }
    }
    if (init == end) {
        *SumLine->getThisrwv() = *RwkBinLines->at(init)->getThisrwv();
        SumLine->setAxis(SumLine->limits());
        visible = 1;
    } else {
        SumLine->clear();
        for (int i = init; i <= end; i++) {
            *SumLine->getThisrwv() += *RwkBinLines->at(i)->getThisrwv();
            visible++;
        }
        SumLine->setLineWidth(1.0);
        SumLine->resetAxis();
        SumLine->setAxis(SumLine->limits());
//        qDebug() << SumLine->limits().Hy << "  " << SumLine->limits().Ly << endl;
        addItem(SumLine);
    }

}

void GraphScene::removeAllRWKL() {
    for (int i = 0; i < RwkLines->size(); i++) {
        if (items().contains(RwkLines->at(i))) {
            removeItem(RwkLines->at(i));
        }
    }
    visible = 0;
}

void GraphScene::removeAllRWKBL() {
    for (int i = 0; i < RwkBinLines->size(); i++) {
        if (items().contains(RwkBinLines->at(i))) {
            removeItem(RwkBinLines->at(i));
        }
    }
    SumLine->setThisrwv(new RWVInt());
    visible = 0;
}

unsigned int GraphScene::getVisible() const {
    return visible;
}