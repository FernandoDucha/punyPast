/* 
 * File:   ExpressionRandomNumberGenerator.cpp
 * Author: fordem
 * 
 * Created on February 11, 2015, 3:42 PM
 */

#include <qt5/QtCore/qlogging.h>

#include "ExprRNG.h"
#include "GeneralUsage.h"
extern "C" {
    int _parse_string(char*);
    double ans;
}

ExprRNG::ExprRNG() {
    preSeedString = postSeedString = "";
    originalSeed = actualSeed = 0;
    tokenSeedIndex = 0;
    buffer = NULL;
}

ExprRNG::ExprRNG(QList<Token> * Expr) : ExprRNG() {
    receiveNewExpression(Expr);
}

bool ExprRNG::operator==(ExprRNG & _exprRNG) {
    //    qDebug()<<preSeedString<<"---"<<_exprRNG.getPreSeedString();
    bool preseed = preSeedString.compare(_exprRNG.getPreSeedString());
    bool postseed = postSeedString.compare(_exprRNG.getPostSeedString());
    bool origseed = QString::number(originalSeed).compare(_exprRNG.getOriginalSeedString());
    return (!origseed)&&(!postseed)&&(!preseed);
}

QString ExprRNG::getPreSeedString() {
    return preSeedString;
}

QString ExprRNG::getPostSeedString() {
    return postSeedString;
}

QString ExprRNG::getOriginalSeedString() {
    return QString::number(originalSeed);
}

void ExprRNG::resetSeed() {
    originalSeed = actualSeed;
}

void ExprRNG::receiveNewExpression(QList<Token> * Expr) {
    preSeedString = postSeedString = "";
    bool s = false;
    for (int i = 0; i < Expr->size(); i++) {
        Token tk = Expr->at(i);
        if (tk.isSeed()) {
            originalSeed = actualSeed = atoll(tk.getToken().toStdString().c_str());
            tokenSeedIndex = i;
            s = true;
        }
    }
    factorString(Expr);
    QString temp = preSeedString;
    if (s) {
        temp += QString::number(actualSeed);
    }
    temp += postSeedString + "\n";
    if (buffer != NULL) {
        delete buffer;
    }
    buffer = new char[2 * temp.length()];

    strcpy(buffer, temp.toStdString().c_str());
    error = _parse_string(buffer);
}

bool ExprRNG::hasErro() {
    return error;
}

void ExprRNG::copyToBuffer() {
    QString temp = preSeedString;
    temp += QString::number(actualSeed);
    temp += postSeedString + "\n";
    strcpy(buffer, temp.toStdString().c_str());
}

void ExprRNG::factorString(QList<Token> * Expr) {
    if (tokenSeedIndex == 0) {
        preSeedString = "";
        if (Expr->size() > 0) {
            for (int i = 1; i < Expr->size(); i++) {
                Token tk = Expr->at(i);
                postSeedString += tk.getToken();
            }

        } else {
            for (int i = 0; i < Expr->size(); i++) {
                Token tk = Expr->at(i);
                postSeedString += tk.getToken();
            }
        }
    } else {
        for (int i = 0; i < tokenSeedIndex; i++) {
            Token tk = Expr->at(i);
            preSeedString += tk.getToken();
        }
        for (int i = tokenSeedIndex + 1; i < Expr->size(); i++) {
            Token tk = Expr->at(i);
            postSeedString += tk.getToken();
        }
    }
}

long long ExprRNG::generateNumber() {
    _parse_string(buffer);
    actualSeed = ans;
    copyToBuffer();
    return actualSeed;
}

ExprRNG::~ExprRNG() {
    delete [] buffer;
}

void ExprRNG::resetExpressionRNG() {
    preSeedString = postSeedString = "";
    originalSeed = actualSeed = 0;
    tokenSeedIndex = 0;
    if (buffer) {
        delete [] buffer;
        buffer = NULL;
    }
}

