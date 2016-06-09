/* 
 * File:   Tokenizer.cpp
 * Author: fordem
 * 
 * Created on February 1, 2015, 7:54 PM
 */

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
    state = 0;
}

Tokenizer::~Tokenizer() {
}

bool Tokenizer::isChar(char ch) {
    if (((ch >= 'A')&&(ch <= 'Z')) || ((ch >= 'a')&&(ch <= 'z')))
        return true;
    return false;
}

bool Tokenizer::isDigit(char ch) {
    if ((ch >= '0')&&(ch <= '9'))
        return true;
    return false;
}

QList<Token>  Tokenizer::Tokenize(QString Input) {
    Tokens.clear();
    state = 0;
    erro = false;
    StartTokenize(Input);
    return Tokens;
}

bool Tokenizer::hasErro() {
    return erro;
}

void Tokenizer::StartTokenize(QString Input) {
    QString actualToken = "";
    for (int pos = 0; pos < Input.length(); pos++) {
        switch (state) {
            case 0:
                if (isDigit(Input[pos].cell())) {
                    actualToken += Input[pos];
                    state = 2;
                } else if (Input[pos] == QChar('+') || Input[pos] == QChar('-') || Input[pos] == QChar('/') || Input[pos] == QChar('*') || Input[pos] == QChar('%')) {
                    actualToken += Input[pos];
                    Token t(OP, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                } else if (Input[pos] == QChar('(')) {
                    actualToken += Input[pos];
                    Token t(OPENBRACK, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                } else if (Input[pos] == QChar(')')) {
                    actualToken += Input[pos];
                    Token t(CLOSEBRACK, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                } else if (Input[pos] == QChar('^')) {
                    actualToken += Input[pos];
                    state = 1;
                } else if (Input[pos] == QChar('l')) {
                    actualToken += Input[pos];
                    state = 9;
                } else if (Input[pos] == QChar('p')) {
                    actualToken += Input[pos];
                    state = 12;
                } else if (Input[pos] == QChar('s')) {
                    actualToken += Input[pos];
                    state = 13;
                } else if (Input[pos] == QChar('c')) {
                    actualToken += Input[pos];
                    state = 15;
                } else if (Input[pos] == QChar('t')) {
                    actualToken += Input[pos];
                    state = 17;
                } else if (Input[pos] == QChar('a')) {
                    actualToken += Input[pos];
                    state = 19;
                } else if (Input[pos] == QChar('o')) {
                    actualToken += Input[pos];
                    state = 21;
                } else if (Input[pos] == QChar(' ') || Input[pos] == QChar('\t') || Input[pos] == QChar('\n')) {
                    state = 0;
                    actualToken = "";
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                }
                break;

            case 21://or
                if (Input[pos] == QChar('r')) {
                    actualToken += Input[pos];
                    state = 102;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 19://and
                if (Input[pos] == QChar('n')) {
                    actualToken += Input[pos];
                    state = 20;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 20://and
                if (Input[pos] == QChar('d')) {
                    actualToken += Input[pos];
                    state = 102;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 17://tan
                if (Input[pos] == QChar('a')) {
                    actualToken += Input[pos];
                    state = 18;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 18://tan
                if (Input[pos] == QChar('n')) {
                    actualToken += Input[pos];
                    state = 101;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 15://cos
                if (Input[pos] == QChar('o')) {
                    actualToken += Input[pos];
                    state = 16;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 16://cos
                if (Input[pos] == QChar('s')) {
                    actualToken += Input[pos];
                    state = 101;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 13://seno
                if (Input[pos] == QChar('i')) {
                    actualToken += Input[pos];
                    state = 14;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 14://seno
                if (Input[pos] == QChar('n')) {
                    actualToken += Input[pos];
                    state = 101;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 12://pi
                if (Input[pos] == QChar('i')) {
                    actualToken += Input[pos];
                    Token t(CONST, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 9://log
                if (Input[pos] == QChar('o')) {
                    actualToken += Input[pos];
                    state = 10;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 10://log
                if (Input[pos] == QChar('g')) {
                    actualToken += Input[pos];
                    state = 101;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro
                }
                break;
            case 1://xor
                if (Input[pos] == QChar('^')) {
                    actualToken += Input[pos];
                    Token t(OP, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                } else {//potencia
                    pos--; //em dúvida verificar. Transição lambda de merda!
                    Token t(OP, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                }
                break;
            case 2:
                if (isDigit(Input[pos].cell())) {
                    actualToken += Input[pos];
                    state = 2;
                } else if (Input[pos] == QChar('.')) {
                    actualToken += Input[pos];
                    state = 3;
                } else if (Input[pos] == QChar('e') || Input[pos] == QChar('E')) {
                    actualToken += Input[pos];
                    state = 5;
                } else if (isChar(Input[pos].cell())) {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                } else {
                    pos--; //em dúvida verificar. Transição lambda de merda!
                    Token t(NUMBER, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                }
                break;
            case 3:
                if (isDigit(Input[pos].cell())) {
                    actualToken += Input[pos];
                    state = 4;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                    //erro                    
                }
                break;
            case 4:
                if (isDigit(Input[pos].cell())) {
                    actualToken += Input[pos];
                    state = 4;
                } else if (isChar(Input[pos].cell())) {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                } else {
                    pos--; //em dúvida verificar. Transição lambda de merda!
                    Token t(NUMBER, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    state = 0;
                }
                break;
            case 101://encontra funcoes log, seno, cos, tan
                if (!isChar(Input[pos].cell())) {
                    Token t(FUN, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    pos--;
                    state = 0;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                }
                break;
            case 102:
                if (!isChar(Input[pos].cell())) {
                    //depois de or and xor not não pode vir letra tem outros erros pra tratar, mas pelo menos o cara não vai escre orand e vai encontra dois tokens or e and.
                    Token t(OP, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    pos--;
                    state = 0;
                } else {
                    actualToken += Input[pos];
                    Token t(ERRO, actualToken, pos - actualToken.length() + 1, pos + 1);
                    Tokens.append(t);
                    actualToken = "";
                    erro = true;
                    break;
                }
                break;
            default:
                break;

        }
    }
    //Tentando tratar o último token on a string acabou de ser tratada..
}