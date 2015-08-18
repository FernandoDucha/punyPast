/* 
 * File:   BufferedPollarDrawingEngine.h
 * Author: fordem
 *
 * Created on August 14, 2015, 1:06 PM
 */

#ifndef BUFFEREDPOLLARDRAWINGENGINE_H
#define	BUFFEREDPOLLARDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "PollarBufferedRwDpSet.h"

class BufferedPollarDrawingEngine : public IDrawingEngine<QPollarF> {
public:
    BufferedPollarDrawingEngine(QwtPlot * plot);
    virtual ~BufferedPollarDrawingEngine();
    void setNPlots(u_int32_t N);
    void setDataSet(IRWSet<QPollarF>*);
    void setDataSet(IRWBd*);
    void addToPlot(IRWItem<QPollarF>*);
    void detach();
    void paintItem(u_int32_t);
    void paintAll();
    void paintFromTo(u_int32_t, u_int32_t);
    void setDataSet(IPolyfit*);
    void paintQAverageDistance();

    virtual void setMaxForType() {
        this->max.setX(std::numeric_limits<double>::min());
        this->max.setY(std::numeric_limits<double>::min());
    }

    virtual void setMinForType() {
        this->min.setX(std::numeric_limits<double>::max());
        this->min.setY(std::numeric_limits<double>::max());
    }
private:
    IRWSet<QPollarF> * dataSet;
    QVector<QColor> colors;
    QMap<u_int32_t, QwtPlotCurve*> curves;
};

inline BufferedPollarDrawingEngine::BufferedPollarDrawingEngine(QwtPlot * plot) : IDrawingEngine<QPollarF>(plot) {

    dataSet = NULL;
}

inline BufferedPollarDrawingEngine::~BufferedPollarDrawingEngine() {
}

inline void BufferedPollarDrawingEngine::setNPlots(u_int32_t N) {
    this->Nplots = N;
    colors.clear();
    for (int i = 0; i < this->Nplots; i++) {

        colors.push_back(randomColor(qrand()));
    }
    dataSet = new PollarBufferedRwDpSet(N);
}

inline void BufferedPollarDrawingEngine::setDataSet(IRWSet<QPollarF>* irws) {
    if (dataSet != NULL) {

        delete dataSet;
    }
    setNPlots(irws->getSize());
    dataSet = irws;
}

inline void BufferedPollarDrawingEngine::setDataSet(IRWBd*) {

    return;
}

inline void BufferedPollarDrawingEngine::addToPlot(IRWItem<QPollarF>* irwi) {
    bool flag = false;
    setMaxForType();
    setMinForType();
    for (int i = 0;; i++) {
        double maxty, minty;
        double maxtx, mintx;
        if (curves[i] == NULL) {
            QVector<QPointF> d;
            irwi->resetIterator();
            QPollarF next;
            while (irwi->getNext(next)) {
                d.push_back(next);
            }
            irwi->resetIterator();
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
            maxty = c->maxYValue();
            minty = c->minYValue();
            maxtx = c->maxXValue();
            mintx = c->minXValue();

            flag = true;
        } else if (curves.value(i)->plot()) {
            maxty = curves.value(i)->maxYValue();
            minty = curves.value(i)->minYValue();
            maxtx = curves.value(i)->maxXValue();
            mintx = curves.value(i)->minXValue();
        }
        if (maxty>this->max.ry()) {
            this->max.setY(maxty);
        }
        if (maxtx>this->max.rx()) {
            this->max.setX(maxtx);
        }
        if (minty<this->min.ry()) {
            this->min.setY(minty);
        }
        if (mintx<this->min.rx()) {
            this->min.setX(mintx);
        }

        if (flag) break;
    }
    this->thisPlot->setAxisScale(QwtPlot::yLeft, this->min.ry(), this->max.ry());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, this->min.rx(), this->max.rx());
}

inline void BufferedPollarDrawingEngine::detach() {
    auto beg = curves.begin();
    auto end = curves.begin();
    while (curves[beg.key()] != NULL) {

        curves[beg.key()]->detach();
        beg++;
    }
    curves.clear();
}

inline void BufferedPollarDrawingEngine::paintItem(u_int32_t i) {
    IRWItem<QPollarF> * a = dataSet->getElement(i);
    //    a->print();
    QVector<QPointF> d;
    
    a->resetIterator();
    QPollarF next;
    while (a->getNext(next)) {
        
        d.push_back(next);
    }
    a->resetIterator();
    //    auto beg = d.begin();
    //    auto end = d.end();
    //    for(;beg!=end;beg++){
    //        QPointF a = *beg;
    //        std::cout<<a.rx()<<" "<<a.ry()<<std::endl;
    //    }    
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

inline void BufferedPollarDrawingEngine::paintAll() {
    auto beg = curves.begin();
    auto end = curves.begin();
    while (curves[beg.key()] != NULL) {

        curves[beg.key()]->detach();
        beg++;
    }
    curves.clear();
}

inline void BufferedPollarDrawingEngine::paintFromTo(u_int32_t beg, u_int32_t end) {
    for (int i = 0; i < beg; i++) {
        if (curves.contains(i) && curves.value(i)->plot() != NULL) {
            curves.value(i)->detach();
        }
    }
    setMaxForType();
    setMinForType();

    for (int i = beg; i < end; i++) {
        double maxty, minty;
        double maxtx, mintx;
        if (!curves.contains(i)) {
            paintItem(i);
            maxty = curves.value(i)->maxYValue();
            minty = curves.value(i)->minYValue();
            maxtx = curves.value(i)->maxXValue();
            mintx = curves.value(i)->minXValue();

        } else if (curves.value(i)->plot() == NULL) {
            curves.value(i)->attach(this->thisPlot);
            maxty = curves.value(i)->maxYValue();
            minty = curves.value(i)->minYValue();
            maxtx = curves.value(i)->maxXValue();
            mintx = curves.value(i)->minXValue();
        } else {
            maxty = curves.value(i)->maxYValue();
            minty = curves.value(i)->minYValue();
            maxtx = curves.value(i)->maxXValue();
            mintx = curves.value(i)->minXValue();
        }
        if (maxty>this->max.ry()) {
            this->max.setY(maxty);
        }
        if (maxtx>this->max.rx()) {
            this->max.setX(maxtx);
        }
        if (minty<this->min.ry()) {
            this->min.setY(minty);
        }
        if (mintx<this->min.rx()) {
            this->min.setX(mintx);
        }
    }
    for (int i = end; curves.contains(i); i++) {
        if (curves[i] && curves.value(i)->plot() != NULL) {

            curves.value(i)->detach();
        }
    }
    this->thisPlot->setAxisScale(QwtPlot::yLeft, this->min.ry(), this->max.ry());
    this->thisPlot->setAxisScale(QwtPlot::xBottom, this->min.rx(), this->max.rx());
}

inline void BufferedPollarDrawingEngine::setDataSet(IPolyfit*) {

    return;
}

inline void BufferedPollarDrawingEngine::paintQAverageDistance() {

}
#endif	/* BUFFEREDPOLLARDRAWINGENGINE_H */

