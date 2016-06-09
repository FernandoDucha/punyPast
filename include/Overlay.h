/* 
 * File:   Overlay.h
 * Author: fordem
 *
 * Created on February 9, 2015, 11:56 PM
 */

#ifndef OVERLAY_H
#define	OVERLAY_H
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include "Token.h"
#include "ExprTextEdit.h"

class Overlay : public QWidget {
    Q_OBJECT
public:
    Overlay(QWidget * Parent);
    void setTokenList(QList<Token>  a);
    QList<Token>  getTokenList();
    virtual ~Overlay();
    bool hasSeed();
public slots:
    void ExpressionClicked(int Pos);
protected:
    //    void paintEvent(QPaintEvent* event);
private:
    QList<Token>  tk;
    QWidget * temp;
    QGridLayout * thisLayout_2;
    QVBoxLayout * thisLayout;
    ExprTextEdit * ExpressionMessage;
    QLabel * ErrorMessage;
    QLabel * InsructionsMessage;
    bool hSeed;
signals:
    void foundSeed(bool);
};

#endif	/* OVERLAY_H */

