/* 
 * File:   GraphPanner.cpp
 * Author: fordem
 * 
 * Created on July 16, 2013, 5:58 AM
 */

#include <qwt_plot_canvas.h>

#include "GraphPanner.h"

GraphPanner::GraphPanner(QwtPlotCanvas * canvas):QwtPlotPanner(canvas) {
    setAbortKey(Qt::Key_Escape);
    setCursor(Qt::CursorShape::DragMoveCursor);
}
GraphPanner::~GraphPanner() {
}

