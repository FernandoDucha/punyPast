%{
#define YYSTYPE double
#include "y.tab.h"
#include <math.h>
extern double yylval;
%}
S   [ ;\.\-,:\t]
%%
{S}+  {printf("found sep\n"); return SEP;}
"%d"    {yylval=0; printf("found integer\n"); return INTEGER;}
"%g"    {yylval=1; printf("found double\n");return DOUBLE;}
"%f"    {yylval=2; printf("found float\n");return FLOAT;}
"%l"    {yylval=3; printf("found long\n");return LONG;}
"\n"    {return EOLN;}
