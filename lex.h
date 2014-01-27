#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM	6	// Decimal number
#define MINUS	7
#define DIV 8
#define EQUALS 9
#define LT 10
#define GT 11
#define ID 12
#define ASSIGN 13
#define IF 14
#define THEN 15
#define WHILE 17
#define DO 18
#define BEGIN 19
#define END 20

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;
