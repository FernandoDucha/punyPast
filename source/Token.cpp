/* 
 * File:   Token.cpp
 * Author: fordem
 * 
 * Created on February 10, 2015, 1:41 AM
 */

#include "Token.h"
#include <QDebug>
const char Token::Color[7][100] = {"<font color=\"#0EB306\"", 
                                    "<font color=\"#e1e734\"", 
                                    "<font color=\"#34e77b\"", 
                                    "<font color=\"#34e77b\"", 
                                    "<font color=\"#063759\"", "<font color=\"#3438e7\"", "<font color=\"#FF0000\""};

Token::Token(TOKEN_TYPE TT, QString Tk, int start, int end) {
    this_TT = TT;
    _Token = Tk;
    strInputStart = start;
    strInputEnd = end;
    hasBackground = false;
}

QString Token::getToken() {
    return _Token;
}
bool Token::operator ==(Token& Tk){
    if(this_TT==Tk.getTOKEN_TYPE()){
        return _Token.compare(Tk.getToken());
    }else{
        return false;
    }
}
TOKEN_TYPE Token::getTOKEN_TYPE() {
    return this_TT;
}

int Token::getStrInputStart() {
    return strInputStart;
}

int Token::getStrInputEnd() {
    return strInputEnd;
}

void Token::setToken(QString Token) {
    _Token = Token;
}

void Token::setTOKEN_TYPE(TOKEN_TYPE TT) {
    this_TT = TT;
}

void Token::setStrInputStart(int start) {
    strInputStart = start;
}

void Token::setStrInputEnd(int end) {
    strInputEnd = end;
}

QString Token::getFormattedString() {
    //    qDebug()<<_Token;
    QString ret = "";
    if (hasBackground) {
        ret = Color[this_TT] + QString(" style=\"BACKGROUND-COLOR:#c1c1c1\">") + _Token + "</font>";
    } else {
        ret = Color[this_TT] +QString(">")+ _Token + "</font>";
    }


    return ret;
}
void Token::setSeed(bool hasBG){
    hasBackground=hasBG;
}
bool Token::isSeed(){
    return hasBackground;
}

Token::~Token() {
}

