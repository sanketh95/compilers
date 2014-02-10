#include <stdio.h>
#include "lex.h"
#include "symbol.h"


extern yyleng;
extern char * yytext;

void main(){

st sym_tab;
sym_tab.cur_size=0;
int tok;

while( (tok=lex()) != EOI){
	if(tok == ERR)	{
		//printf("Invalid Lexeme %0.*s at line: %d\n",yyleng, yytext, yylineno);
	}
}
pprint();

}
