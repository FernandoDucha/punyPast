/* 
 * File:   Tokenizer.h
 * Author: fordem
 *
 * Created on February 1, 2015, 7:54 PM
 */

#ifndef TOKENIZER_H
#define	TOKENIZER_H
#include <QList>
#include <QString>
#include "Token.h"
class Tokenizer {
public:
    Tokenizer();
    virtual ~Tokenizer();
    bool isChar(char ch);
    bool isDigit(char ch);
    bool hasErro();
    QList<Token>  Tokenize(QString Input);
private:
    QList<Token>  Tokens;
    int state;
    bool erro;
    void StartTokenize(QString Input);
};

#endif	/* TOKENIZER_H */

