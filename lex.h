#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM	6	/* Decimal Number or Identifier */
#define MINUS	7
#define DIV 8
#define EQUALS 9
#define LT 10
#define GT 11
#define ID 12

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;
