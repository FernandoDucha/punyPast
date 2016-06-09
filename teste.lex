%{
#define YYSTYPE double
#include "teste.tab.h"
#include <math.h>
// [a-zA-Z_]+ return IDENT;

extern double yylval;
%}
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
"="     return ASSIGN;
"&&"    return LAND;
"||"    return OR;
"|"     return IOR;
"&"     return AND;
"~~"     return COMPLEMENT;
"\n"    return EOLN;
