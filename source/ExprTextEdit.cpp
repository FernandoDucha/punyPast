/* 
 * File:   ExprTextEdit.cpp
 * Author: fordem
 * 
 * Created on February 10, 2015, 8:38 PM
 */

#include <qt5/QtWidgets/qtextedit.h>
#include <qt5/QtGui/qevent.h>

#include "ExprTextEdit.h"

ExprTextEdit::ExprTextEdit(QWidget * Parent) : QTextEdit(Parent) {
    clickedExpression=false;
}
void ExprTextEdit::mousePressEvent(QMouseEvent* event){
    if(event->button()==Qt::LeftButton&&event->modifiers()==Qt::ControlModifier){
        QTextCursor c = cursorForPosition(event->pos());
        clickedExpression=true;
        emit expressionPos(c.position());
    }
}
void ExprTextEdit::mouseReleaseEvent(QMouseEvent*){
    if(clickedExpression){
        clickedExpression=false;
    }
}
ExprTextEdit::~ExprTextEdit() {
}

