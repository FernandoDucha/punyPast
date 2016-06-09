/* 
 * File:   ExprTextEdit.h
 * Author: fordem
 *
 * Created on February 10, 2015, 8:38 PM
 */

#ifndef EXPRTEXTEDIT_H
#define	EXPRTEXTEDIT_H
#include <QTextEdit>
#include <QDebug>

class ExprTextEdit : public QTextEdit {
    Q_OBJECT
public:
    ExprTextEdit(QWidget * Parent);
    virtual ~ExprTextEdit();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    bool clickedExpression;
signals:
    void expressionPos(int p);
};

#endif	/* EXPRTEXTEDIT_H */

