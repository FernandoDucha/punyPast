/* 
 * File:   GraphPicker.cpp
 * Author: fordem
 * 
 * Created on July 12, 2013, 5:57 AM
 */


#include "GraphPicker.h"

GraphPicker::GraphPicker(QwtPlotCanvas * canvas) : QwtPlotPicker(canvas) {
    setStateMachine(new QwtPickerClickPointMachine);
    this->pointClicked = new QLabel(canvas);
    pointClicked->setStyleSheet("QLabel { background-color : white; color : black; }");
    renewPointSelected();
    this->onlyShiftPressed = false;
    cInd = 0;
}

GraphPicker::~GraphPicker() {
}

//void GraphPicker::widgetKeyPressEvent(QKeyEvent* event) {
//    if (event->key() == Qt::Key_Shift) {
//        onlyShiftPressed = true;
//    } else {
//        onlyShiftPressed = false;
//    }
//}
//
//void GraphPicker::widgetKeyReleaseEvent(QKeyEvent* event) {
//    if (event->key() == Qt::Key_Shift) {
//        onlyShiftPressed = false;
//    } else {
//        onlyShiftPressed = true;
//    }
//}

void GraphPicker::widgetMousePressEvent(QMouseEvent *event) {
    QwtPlotItemList qpil = plot()->itemList(QwtPlotItem::Rtti_PlotCurve);
    if (event->button() == Qt::MouseButton::LeftButton && event->modifiers().testFlag(Qt::ShiftModifier)) {
        int i;
        double dist = 0, bestdist = DBL_MAX;
        int index;
        for (i = 0; i < qpil.size(); i++) {
            index = ((QwtPlotCurve*) (qpil.at(i)))->closestPoint(event->pos(), &dist);
            if (dist < bestdist) {
                bestdist = dist;
                cInd = i;
                indexBest = index;
            }
            QPen p = ((QwtPlotCurve*) qpil.at(i))->pen();
            p.setWidth(2);
            ((QwtPlotCurve*) qpil.at(i))->setPen(p);
            plot()->replot();
        }
        if (qpil.size() > 0) {
            QPointF mousePlotPos = ((QwtPlotCurve*) (qpil.at(cInd)))->sample(indexBest);
            QString temo("( ");
            temo += QString::number(mousePlotPos.x());
            temo += " , ";
            temo += QString::number(mousePlotPos.y());
            temo += " )";
            QPoint actualp = transform(mousePlotPos);
            pointClicked->setText(temo);
            QFontMetrics fmt(pointClicked->font());
            pointClicked->setGeometry(actualp.x() + 3, actualp.y() + 3, fmt.boundingRect(temo).width(), fmt.boundingRect(temo).height());
            pointClicked->setVisible(true);
            QPen p = ((QwtPlotCurve*) qpil.at(cInd))->pen();
            p.setWidth(4);
            QVector<QPointF> ptf;
            ptf.push_back(QPointF(mousePlotPos.x(), mousePlotPos.y()));
            QwtPointSeriesData * temp = new QwtPointSeriesData(ptf);
            pointSelected->detach();
            pointSelected->setData(temp);
            pointSelected->setPen(pselected);
            pointSelected->attach(plot());
            ((QwtPlotCurve*) qpil.at(cInd))->setPen(p);
            plot()->replot();
        }
    } else if (event->button() == Qt::MouseButton::LeftButton && event->modifiers().testFlag(Qt::ControlModifier)) {
        SweepWindow->detach();
        pointSelected->detach();
        QwtPlotItemList qpil = plot()->itemList(QwtPlotItem::Rtti_PlotCurve);
        QVector<QPointF> points;
        int i = 0;
        while (SweepWindowIntersections.size() > 0) {
            QLabel * q = SweepWindowIntersections.takeAt(i);
            q->setVisible(false);
            q->setParent(NULL);
            delete q;
        }
        double dist = 0, bestdist = DBL_MAX;
        int index;
        for (i = 0; i < qpil.size(); i++) {
            index = ((QwtPlotCurve*) (qpil.at(i)))->closestPoint(event->pos(), &dist);
            if (dist < bestdist) {
                bestdist = dist;
                cInd = i;
                indexBest = index;
            }
            QPen p = ((QwtPlotCurve*) qpil.at(i))->pen();
            p.setWidth(2);
            ((QwtPlotCurve*) qpil.at(i))->setPen(p);
            plot()->replot();
        }
        if (qpil.size() > 0) {
            for (int i = 0; i < qpil.size(); i++) {
                QPointF mousePlotPos = ((QwtPlotCurve*) (qpil.at(i)))->sample(indexBest);
                points.push_back(mousePlotPos);
                QString temo("( ");
                temo += QString::number(mousePlotPos.x());
                temo += " , ";
                temo += QString::number(mousePlotPos.y());
                temo += " )";
                QPoint actualp = transform(mousePlotPos);
                QLabel * t = new QLabel(plot());
                t->setText(temo);
                t->setStyleSheet("QLabel { background-color : white; color : black; }");
                QFontMetrics fmt(t->font());
                t->setGeometry(actualp.x() + 3, actualp.y() + 3, fmt.boundingRect(temo).width(), fmt.boundingRect(temo).height());
                t->setVisible(true);
                this->SweepWindowIntersections.push_back(t);
            }
            QwtPointSeriesData * temp = new QwtPointSeriesData(points);
            SweepWindow->setData(temp);
            //            SweepWindow->setPen(pselected);
            SweepWindow->attach(plot());

        }

    } else {
        if (qpil.size() > 0) {
            pointClicked->setVisible(false);
            QPen p = ((QwtPlotCurve*) qpil.at(cInd))->pen();
            p.setWidth(2);
            ((QwtPlotCurve*) qpil.at(cInd))->setPen(p);
            pointSelected->detach();
            plot()->replot();
            SweepWindow->detach();
            while (SweepWindowIntersections.size() > 0) {
                QLabel * q = SweepWindowIntersections.takeAt(0);
                q->setVisible(false);
                q->setParent(NULL);
                delete q;
            }
        }
    }
}

void GraphPicker::widgetMouseMoveEvent(QMouseEvent *event) {

    if ((event->buttons().testFlag(Qt::LeftButton)) && event->modifiers().testFlag(Qt::ShiftModifier)) {
        QwtPlotItemList qpil = plot()->itemList(QwtPlotItem::Rtti_PlotCurve);
        double dist;
        indexBest = ((QwtPlotCurve*) qpil.at(cInd))->closestPoint(event->pos(), &dist);
        QPointF mousePlotPos = ((QwtPlotCurve*) (qpil.at(cInd)))->sample(indexBest);
        QString temo("( ");
        temo += QString::number(mousePlotPos.x());
        temo += " , ";
        temo += QString::number(mousePlotPos.y());
        temo += " )";
        QPoint actualp = transform(mousePlotPos);
        pointClicked->setText(temo);
        QFontMetrics fmt(pointClicked->font());
        pointClicked->setGeometry(actualp.x() + 3, actualp.y() + 3, fmt.boundingRect(temo).width(), fmt.boundingRect(temo).height());
        pointClicked->setVisible(true);
        QVector<QPointF> ptf;
        ptf.push_back(QPointF(mousePlotPos.x(), mousePlotPos.y()));
        QwtPointSeriesData * temp = new QwtPointSeriesData(ptf);
        pointSelected->detach();
        pointSelected->setData(temp);
        pointSelected->setPen(pselected);
        pointSelected->attach(plot());
        plot()->replot();
    }else if((event->buttons().testFlag(Qt::LeftButton)) && event->modifiers().testFlag(Qt::ControlModifier)){
        SweepWindow->detach();
        pointSelected->detach();
        QwtPlotItemList qpil = plot()->itemList(QwtPlotItem::Rtti_PlotCurve);
        QVector<QPointF> points;
        int i = 0;
        while (SweepWindowIntersections.size() > 0) {
            QLabel * q = SweepWindowIntersections.takeAt(i);
            q->setVisible(false);
            q->setParent(NULL);
            delete q;
        }
        double dist = 0, bestdist = DBL_MAX;
        int index;
        for (i = 0; i < qpil.size(); i++) {
            index = ((QwtPlotCurve*) (qpil.at(i)))->closestPoint(event->pos(), &dist);
            if (dist < bestdist) {
                bestdist = dist;
                cInd = i;
                indexBest = index;
            }
            QPen p = ((QwtPlotCurve*) qpil.at(i))->pen();
            p.setWidth(2);
            ((QwtPlotCurve*) qpil.at(i))->setPen(p);
            plot()->replot();
        }
        if (qpil.size() > 0) {
            for (int i = 0; i < qpil.size(); i++) {
                QPointF mousePlotPos = ((QwtPlotCurve*) (qpil.at(i)))->sample(indexBest);
                points.push_back(mousePlotPos);
                QString temo("( ");
                temo += QString::number(mousePlotPos.x());
                temo += " , ";
                temo += QString::number(mousePlotPos.y());
                temo += " )";
                QPoint actualp = transform(mousePlotPos);
                QLabel * t = new QLabel(plot());
                t->setText(temo);
                t->setStyleSheet("QLabel { background-color : white; color : black; }");
                QFontMetrics fmt(t->font());
                t->setGeometry(actualp.x() + 3, actualp.y() + 3, fmt.boundingRect(temo).width(), fmt.boundingRect(temo).height());
                t->setVisible(true);
                this->SweepWindowIntersections.push_back(t);
            }
            QwtPointSeriesData * temp = new QwtPointSeriesData(points);
            SweepWindow->setData(temp);
            //            SweepWindow->setPen(pselected);
            SweepWindow->attach(plot());

        }
    }
}