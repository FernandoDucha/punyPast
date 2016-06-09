/* 
 * File:   ExpressionRandomNumberGenerator.h
 * Author: fordem
 *
 * Created on February 11, 2015, 3:42 PM
 */

#ifndef EXPRESSIONRANDOMNUMBERGENERATOR_H
#define	EXPRESSIONRANDOMNUMBERGENERATOR_H
#include <QList>
#include "Token.h"
#include <QDebug>
#include <QMessageBox>
class ExprRNG {
public:
    ExprRNG();
    ExprRNG(QList<Token> * Expr);
    long long generateNumber();
    void receiveNewExpression(QList<Token> * Expr);
    void resetExpressionRNG();
    void resetSeed();
    virtual ~ExprRNG();
    bool operator==(ExprRNG & _exprRNG);
    QString getPreSeedString();
    QString getPostSeedString();
    QString getOriginalSeedString();
    bool hasErro();
private:
    void factorString(QList<Token> * Expr);
    void copyToBuffer();
    long long actualSeed,originalSeed;
    int tokenSeedIndex;
    QString preSeedString,postSeedString;
    char * buffer;
    bool error;
};

#endif	/* EXPRESSIONRANDOMNUMBERGENERATOR_H */

