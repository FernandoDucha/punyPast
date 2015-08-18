%{
#include <alloca.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#define YYSTYPE double
double calcfact(double);
void yyerror(char *s );
void warning( char *  s , char * t );
double reg[99];
int count=0;
double ans;
char format[200];
extern int fflex (void);
%}

%token DOUBLE INTEGER LONG FLOAT
%token SEP EOLN
%%
list:   |list SEP LONG  {reg[count++]=yylval;}
        |list SEP FLOAT {reg[count++]=yylval;}
        |list SEP DOUBLE {reg[count++]=yylval;}
        |list SEP INTEGER {reg[count++]=yylval;}
        |list LONG  {reg[count++]=yylval;}
        |list FLOAT {reg[count++]=yylval;}
        |list DOUBLE {reg[count++]=yylval;}
        |list INTEGER {reg[count++]=yylval;}
        |list EOLN
        ;
%%

#include <stdio.h>
#include <ctype.h>
char *progname="MeuPrograma";
void yyerror( char * s )
{
  warning( s , ( char * )0 );
  yyparse();
}

void warning( char *  s , char * t )
{
  fprintf( stderr ,"%s: %s\n" , progname , s );
  if ( t )
    fprintf( stderr , " %s\n" , t );
}
typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
int formatString(char * string) {
 YY_BUFFER_STATE buffer = ff_scan_string(string);
/*   strcpy(format,"%g\n"); */
    if (yyparse()){
        printf("errado!\n");
        return 0;
    }
    else{
        return 1;
    }
} 