/* 
 * File:   BDBinDrawingEngine.h
 * Author: fordem
 *
 * Created on June 14, 2015, 12:32 AM
 */

#ifndef BDBINDRAWINGENGINE_H
#define	BDBINDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include "IRWBd.h"
#include <qwt_plot_curve.h>

template<class Type> class BDBinDrawingEngine : public IDrawingEngine<Type> {
public:
    BDBinDrawingEngine(QwtPlot * plot);
    virtual void setNPlots(u_int32_t N);
    virtual void setDataSet(IRWSet<Type>*);
    virtual void setDataSet(IRWBd*);
    virtual void addToPlot(IRWItem<Type>*);
    virtual void detach();
    virtual void paintItem(u_int32_t);
    virtual void paintAll();
    virtual void paintFromTo(u_int32_t, u_int32_t);
    virtual ~BDBinDrawingEngine();

    /**
     * For all classes other than Fitting*DrawingEngine BDFitting*DrawingEngine, this method has no use.
     * @param poly
     */
    virtual void setDataSet(IPolyfit*) {
        return;
    }
    virtual void paintQAverageDistance();
    virtual void setMaxForType(){
        this->max=std::numeric_limits<Type>::min();
    }
    virtual void setMinForType(){
        this->min=std::numeric_limits<Type>::max();
    }
private:
    IRWItem<Type> * noiseLine;
    QwtPlotCurve * NoiseCurve;
    IRWBd * dataSet;
};
template <class Type> void BDBinDrawingEngine<Type>::paintQAverageDistance(){
    return;
}
template <class Type> BDBinDrawingEngine<Type>::BDBinDrawingEngine(QwtPlot * plot) : IDrawingEngine<Type>(plot) {
    noiseLine = NULL;
    NoiseCurve = new QwtPlotCurve();
    dataSet = NULL;
}

template <class Type> BDBinDrawingEngine<Type>::~BDBinDrawingEngine() {
    delete noiseLine;
}

template <class Type> void BDBinDrawingEngine<Type>::paintItem(u_int32_t i) {
    RWVec<Type> t = dataSet->selectBinItem(i);
    *noiseLine = t;
    QVector<QPointF> d;
    for (unsigned int k = 0; k < noiseLine->getNpoints(); k++) {
        d.push_back(QPointF(k, noiseLine->getElement(k)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(Qt::cyan));
    NoiseCurve->setPen(p);
    NoiseCurve->setData(temp);
    NoiseCurve->setStyle(QwtPlotCurve::Lines);
    NoiseCurve->attach(this->thisPlot);
    this->thisPlot->setAxisScale(QwtPlot::yLeft, NoiseCurve->minYValue(), NoiseCurve->maxYValue());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, noiseLine->getNpoints());
    this->thisPlot->replot();
}

template <class Type> void BDBinDrawingEngine<Type>::setDataSet(IRWBd* irwbd) {
    if (dataSet != NULL) {
        delete dataSet;
    }
    setNPlots(irwbd->getNWalks());
    dataSet = irwbd;
}

template <class Type> void BDBinDrawingEngine<Type>::detach() {
    if (NoiseCurve) {
        NoiseCurve->detach();
    }
    delete noiseLine;
    noiseLine = NULL;
}

template <class Type> void BDBinDrawingEngine<Type>::setNPlots(u_int32_t N) {
    this->Nplots = N;
}

template <class Type> void BDBinDrawingEngine<Type>::paintFromTo(u_int32_t beg, u_int32_t end) {
    if (noiseLine) {
        delete noiseLine;
    }
    noiseLine = new RWVec<Type>();
    for (int i = beg; i < end; i++) {
        RWVec<Type> temp = dataSet->selectBinItem(i);
        *noiseLine += temp;
    }
    QVector<QPointF> d;
    for (unsigned int i = 0; i < noiseLine->getNpoints(); i++) {
        d.push_back(QPointF(i, noiseLine->getElement(i)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(Qt::cyan));
    NoiseCurve->setPen(p);
    NoiseCurve->setData(temp);
    NoiseCurve->setStyle(QwtPlotCurve::Lines);
    NoiseCurve->attach(this->thisPlot);
    this->thisPlot->setAxisScale(QwtPlot::yLeft, NoiseCurve->minYValue(), NoiseCurve->maxYValue());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, noiseLine->getNpoints());
    this->thisPlot->replot();

}

/**
 * If this method is called in any Bd Drawing engine it wont matter at all. NO EFFECt.
 * @param irws
 */
template <class Type> void BDBinDrawingEngine<Type>::setDataSet(IRWSet<Type>*) {


}

template <class Type> void BDBinDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi) {
    *noiseLine += *irwi;
    QVector<QPointF> d;
    for (unsigned int i = 0; i < noiseLine->getNpoints(); i++) {
        d.push_back(QPointF(i, noiseLine->getElement(i)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setWidth(2);
    p.setColor(QColor(Qt::cyan));
    NoiseCurve->setPen(p);
    NoiseCurve->setData(temp);
    NoiseCurve->setStyle(QwtPlotCurve::Lines);
    NoiseCurve->attach(this->thisPlot);
    this->thisPlot->setAxisScale(QwtPlot::yLeft, NoiseCurve->minYValue(), NoiseCurve->maxYValue());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, noiseLine->getNpoints());
    this->thisPlot->replot();
}

template <class Type> void BDBinDrawingEngine<Type>::paintAll() {
    paintFromTo(0, this->Nplots);
}

#endif	/* BDBINDRAWINGENGINE_H */

