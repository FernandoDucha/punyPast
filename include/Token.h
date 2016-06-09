/* 
 * File:   Token.h
 * Author: fordem
 *
 * Created on February 10, 2015, 1:41 AM
 */

#ifndef TOKEN_H
#define	TOKEN_H
#include <QString>
/*%}
D       [0-9.]
%%
[ \t]   { ; }
log      return LOG;
pi      return PIVAL;
sin     return SIN;
cos     return COS;
tan     return TAN;
and     return AND;
not     return NOT;
xor     return XOR;
or      return OR;
{D}+    { sscanf( yytext, "%lf", &yylval ); return NUMBER ; }
"<<"    return LEFTSHIFT;
">>"    return RIGHTSHIFT;
"++"    return INC;
"--"    return DEC;
"+"     return PLUS;
"-"     return MINUS;
"~"     return UNARYMINUS;
"/"     return DIV;
"*"     return MUL;
"^"     return POW;
"("     return OPENBRACKET;
")"     return CLOSEBRACKET;
"%"     return MOD;
"^^"     return XOR;
"!!"     return NOT;
"!"      return FACT;
"&&"    return LAND;
"||"    return OR;
"|"     return IOR;
"&"     return AND;
"~~"     return COMPLEMENT;*/
enum TOKEN_TYPE {OP=0,FUN=1,OPENBRACK=2,CLOSEBRACK=3,CONST=4,NUMBER=5,ERRO=6};

class Token {
    QString _Token;
    TOKEN_TYPE this_TT;
    int strInputStart;
    int strInputEnd;
    bool hasBackground;
public:
    static const char   Color[7][100];
    QString getToken();
    TOKEN_TYPE getTOKEN_TYPE();
    int getStrInputStart();
    int getStrInputEnd();
    void setToken(QString Token);
    void setTOKEN_TYPE(TOKEN_TYPE TT);
    void setStrInputStart(int start);
    void setStrInputEnd(int end);
    void setSeed(bool seed);
    bool isSeed();
    bool operator==(Token & Tk);
    QString getFormattedString();
    Token(TOKEN_TYPE TT, QString Tk, int start, int end);
    virtual ~Token();
private:

};

#endif	/* TOKEN_H */

