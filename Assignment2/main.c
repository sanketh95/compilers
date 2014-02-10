#include <stdio.h>
#include "lex.h"
#include "symbol.h"

extern yyleng;
extern char * yytext;

void main(){

st sym_tab;
sym_tab.cur_size=0;

while(lex() != EOI){
	//printf("%0.*s\n", yyleng,yytext);
}
pprint();

}
