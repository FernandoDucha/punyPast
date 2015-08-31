/* 
 * File:   PollarDrawingEngine.h
 * Author: fordem
 *
 * Created on August 14, 2015, 1:06 PM
 */

#ifndef POLLARDRAWINGENGINE_H
#define	POLLARDRAWINGENGINE_H
#include "IDrawingEngine.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "PollarRwDpSet.h"
#include "qwt_symbol.h"

class PollarDrawingEngine : public IDrawingEngine<QPollarF> {
public:
    PollarDrawingEngine(QwtPlot * plot);
    virtual ~PollarDrawingEngine();
    void setNPlots(u_int32_t N);
    void setDataSet(IRWSet<QPollarF>*);
    void setDataSet(IRWBd*);
    void addToPlot(IRWItem<QPollarF>*);
    void addToPlot(IRWItem<QPollarF>*, QColor);
    void detach();
    void paintItem(u_int32_t);
    void paintAll();
    void paintFromTo(u_int32_t, u_int32_t);
    void setDataSet(IPolyfit*);
    void paintQAverageDistance();

    virtual void setMaxForType() {
        this->max.setX(-std::numeric_limits<qreal>::max());
        this->max.setY(-std::numeric_limits<qreal>::max());
    }

    virtual void setMinForType() {
        this->min.setX(std::numeric_limits<qreal>::max());
        this->min.setY(std::numeric_limits<qreal>::max());
    }
private:
    IRWSet<QPollarF> * dataSet;
    QVector<QColor> colors;
    QMap<u_int32_t, QwtPlotCurve*> curves;
};

inline PollarDrawingEngine::PollarDrawingEngine(QwtPlot * plot) : IDrawingEngine<QPollarF>(plot) {

    dataSet = NULL;
}

inline PollarDrawingEngine::~PollarDrawingEngine() {
}

inline void PollarDrawingEngine::setNPlots(u_int32_t N) {
    this->Nplots = N;
    colors.clear();
    for (int i = 0; i < this->Nplots; i++) {

        colors.push_back(randomColor(qrand()));
    }
    dataSet = new PollarRwDpSet(N);
}

inline void PollarDrawingEngine::setDataSet(IRWSet<QPollarF>* irws) {
    if (dataSet != NULL) {

        delete dataSet;
    }
    setNPlots(irws->getSize());
    dataSet = irws;
}

inline void PollarDrawingEngine::setDataSet(IRWBd*) {

    return;
}

inline void PollarDrawingEngine::addToPlot(IRWItem<QPollarF>* irwi, QColor color) {
    bool flag = false;
    setMaxForType();
    setMinForType();
    for (int i = 0;; i++) {
        double maxty, minty;
        double maxtx, mintx;
        if (curves[i] == NULL) {
            QVector<QPointF> d;
            for (uint64_t i = 0; i < irwi->getNpoints(); i++) {
                d.push_back(irwi->getElement(i));
            }
            QwtPointSeriesData * temp = new QwtPointSeriesData(d);
            QwtPlotCurve * c = new QwtPlotCurve();
            c->setPaintAttribute(QwtPlotCurve::PaintAttribute::ClipPolygons, true);
            c->setRenderHint(QwtPlotCurve::RenderHint::RenderAntialiased, true);
            c->setData(temp);
            c->setStyle(QwtPlotCurve::Lines);
            QPen p;
            p.setColor(color);
            p.setCapStyle(Qt::RoundCap);
            p.setJoinStyle(Qt::RoundJoin);
            p.setWidthF(2);
            c->setPen(p);
            
            QPen p1;
            p1.setColor(color);
            p1.setWidthF(2 * 3);
            p1.setCapStyle(Qt::RoundCap);
            QBrush b(color);
            QPainterPath path;
            path.addEllipse(0,0,2,2);
            QwtSymbol * qsym = new QwtSymbol(path,b,p1);
            c->setSymbol(qsym);
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

inline void PollarDrawingEngine::addToPlot(IRWItem<QPollarF>* irwi) {
    addToPlot(irwi, randomColor(qrand()));
}

inline void PollarDrawingEngine::detach() {
    auto beg = curves.begin();
    while (curves[beg.key()] != NULL) {

        curves[beg.key()]->detach();
        delete curves[beg.key()];
        beg++;
    }
    curves.clear();
}

inline void PollarDrawingEngine::paintItem(u_int32_t i) {
    IRWItem<QPollarF> * a = dataSet->getElement(i);

    QVector<QPointF> d;
    for (uint64_t k = 0; k < a->getNpoints(); k++) {

        d.push_back(a->getElement(k));
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

inline void PollarDrawingEngine::paintAll() {
    auto beg = curves.begin();
    auto end = curves.begin();
    while (curves[beg.key()] != NULL) {

        curves[beg.key()]->detach();
        beg++;
    }
    curves.clear();
}

inline void PollarDrawingEngine::paintFromTo(u_int32_t beg, u_int32_t end) {
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

inline void PollarDrawingEngine::setDataSet(IPolyfit*) {

    return;
}

inline void PollarDrawingEngine::paintQAverageDistance() {

}
#endif	/* POLLARDRAWINGENGINE_H */

