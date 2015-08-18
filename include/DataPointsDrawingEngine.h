/* 
 * File:   NormalDrawingEngine.h
 * Author: fordem
 *
 * Created on June 12, 2015, 7:44 PM
 */

#ifndef DATAPOINTSDRAWINGENGINE_H
#define	DATAPOINTSDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include <qwt_plot_curve.h>
#include <limits>

template <class Type> class DataPointsDrawingEngine : public IDrawingEngine<Type> {
public:
    DataPointsDrawingEngine(QwtPlot * plot);
    virtual ~DataPointsDrawingEngine();
    void setNPlots(u_int32_t);
    void setDataSet(IRWSet<Type>*);
    void addToPlot(IRWItem<Type>*);
    void setDataSet(IRWBd*);
    void detach();
    void paintItem(u_int32_t);
    void paintAll();
    void paintFromTo(u_int32_t, u_int32_t);

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
    IRWSet<Type> * dataSet;
    QVector<QColor> colors;
    QMap<u_int32_t, QwtPlotCurve*> curves;
    QwtPlotCurve * quadraticCurve;
};

template <class Type> void DataPointsDrawingEngine<Type>::paintQAverageDistance() {
    auto beg = curves.begin();
    auto end = curves.end();
    IRWItem<Type> * sum = new RWDp<double>();
    int visible = 0;
    for (; beg != end; beg++) {
        if (curves[beg.key()]->plot()) {
            IRWItem<Type> * dp = dataSet->getElement(beg.key());
            IRWItem<Type> * p = dp->power(2);
            *sum += *p;
            delete p;
            visible++;
        }
    }
    *sum = *dynamic_cast<RWDp<double> *> (sum) / visible;
    IRWItem<Type> * t = sum->power(0.5);
    *sum = *t;
    delete t;
    QVector<QPointF> d;
    for (uint64_t k = 0; k < sum->getNpoints(); k++) {
        d.push_back(QPointF(k, sum->getElement(k)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QPen p;
    p.setStyle(Qt::DashDotLine);
    p.setWidth(6);
    if (!quadraticCurve) {
        quadraticCurve = new QwtPlotCurve();
        quadraticCurve->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
        quadraticCurve->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
        p.setColor(randomColor(qrand()));
        quadraticCurve->setPen(p);
        quadraticCurve->setStyle(QwtPlotCurve::Lines);
    } else {
        quadraticCurve->setPen(p);
    }

    quadraticCurve->setData(temp);
    quadraticCurve->attach(this->thisPlot);
    this->thisPlot->replot();
    delete sum;

}

template <class Type> void DataPointsDrawingEngine<Type>::paintItem(u_int32_t i) {
    IRWItem<Type> * a = dataSet->getElement(i);
    QVector<QPointF> d;
    for (uint64_t k = 0; k < a->getNpoints(); k++) {
        d.push_back(QPointF(k, a->getElement(k)));
    }
    QwtPointSeriesData * temp = new QwtPointSeriesData(d);
    QwtPlotCurve * c = new QwtPlotCurve();
    c->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
    c->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
    c->setData(temp);
    c->setStyle(QwtPlotCurve::Lines);
    QPen p;
    p.setColor(colors.at(i));
    p.setWidth(2);
    c->setPen(p);
    c->attach(this->thisPlot);
    curves.insert(i, c);
}

/**
 * If this class is anything else other than BDDataPointsDrawingEngine,BDBinDrawingEngine, this method has no functionality.
 * @param 
 */
template <class Type> void DataPointsDrawingEngine<Type>::setDataSet(IRWBd*) {
    return;
}

template <class Type> void DataPointsDrawingEngine<Type>::detach() {
    auto beg = curves.begin();
    auto end = curves.begin();
    while (curves[beg.key()] != NULL) {
        curves[beg.key()]->detach();
        beg++;
    }
    curves.clear();
}

template <class Type> void DataPointsDrawingEngine<Type>::setNPlots(u_int32_t N) {
    this->Nplots = N;
    colors.clear();
    for (int i = 0; i < this->Nplots; i++) {
        colors.push_back(randomColor(qrand()));
    }
    dataSet = new RWDpSet<Type>(N);
}

template <class Type> void DataPointsDrawingEngine<Type>::paintFromTo(u_int32_t beg, u_int32_t end) {
    for (int i = 0; i < beg; i++) {
        if (curves.contains(i) && curves.value(i)->plot() != NULL) {
            curves.value(i)->detach();
        }
    }
    Type x = dataSet->getElement(0)->getNpoints();
    for (int i = beg; i < end; i++) {
        Type maxt = 0, mint = 0;
        if (!curves.contains(i)) {
            paintItem(i);
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        } else if (curves.value(i)->plot() == NULL) {
            curves.value(i)->attach(this->thisPlot);
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        } else {
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        }
        if (maxt > this->max) {
            this->max = maxt;
        }
        if (mint < this->min) {
            this->min = mint;
        }
    }
    for (int i = end; curves.contains(i); i++) {
        if (curves[i] && curves.value(i)->plot() != NULL) {
            curves.value(i)->detach();
        }
    }
    this->thisPlot->setAxisScale(QwtPlot::yLeft, this->min, this->max);
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, x);
}

template <class Type> void DataPointsDrawingEngine<Type>::setDataSet(IRWSet<Type>* irws) {
    if (dataSet != NULL) {
        delete dataSet;
    }
    setNPlots(irws->getSize());
    dataSet = irws;

}

template <class Type> DataPointsDrawingEngine<Type>::DataPointsDrawingEngine(QwtPlot * plot) : IDrawingEngine<Type>(plot) {
    dataSet = NULL;
    quadraticCurve = NULL;
}

template <class Type> void DataPointsDrawingEngine<Type>::addToPlot(IRWItem<Type>* irwi) {
    Type x;
    bool flag = false;
    for (int i = 0;; i++) {
        Type maxt = numeric_limits<Type>::min(), mint = numeric_limits<Type>::max();
        if (curves[i] == NULL) {
            x = irwi->getNpoints();
            QVector<QPointF> d;
            for (uint64_t i = 0; i < irwi->getNpoints(); i++) {
                d.push_back(QPointF(i, irwi->getElement(i)));
            }
            QwtPointSeriesData * temp = new QwtPointSeriesData(d);
            QwtPlotCurve * c = new QwtPlotCurve();
            c->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
            c->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
            c->setData(temp);
            c->setStyle(QwtPlotCurve::Lines);
            QPen p;
            p.setColor(randomColor(qrand()));
            p.setWidth(2);
            c->setPen(p);
            c->attach(this->thisPlot);
            curves.insert(i, c);
            maxt = c->maxYValue();
            mint = c->minYValue();
            flag = true;
        } else if (curves.value(i)->plot()) {
            maxt = curves.value(i)->maxYValue();
            mint = curves.value(i)->minYValue();
        }
        if (maxt > this->max) {
            this->max = maxt;
        }
        if (mint < this->min) {
            this->min = mint;
        }
        if (flag) break;
    }
    this->thisPlot->setAxisScale(QwtPlot::yLeft, this->min, this->max);
    this->thisPlot->setAxisScale(QwtPlot::xBottom, 0, x);
}

template <class Type> void DataPointsDrawingEngine<Type>::paintAll() {
    paintFromTo(0, this->Nplots);
}

template <class Type> DataPointsDrawingEngine<Type>::~DataPointsDrawingEngine() {

}

#endif	/* NORMALDRAWINGENGINE_H */

