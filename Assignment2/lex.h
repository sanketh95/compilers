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
#define ELSE 15
#define WHILE 17
#define DO 18
#define AUTO 19
#define CONST 20
#define BREAK 21
#define CASE 22
#define CHAR 23
#define CONTINUE 24
#define DEFAULT 25
#define ENUM 26
#define EXTERN 27
#define FLOAT 28
#define FOR 29
#define GOTO 30
#define INT 31
#define LONG 32
#define REGISTER 33
#define RETURN 34
#define SHORT 35
#define SIGNED 36
#define SIZEOF 37
#define STATIC 38
#define STRUCT 39
#define SWITCH 40
#define TYPEDEF 41
#define UNION 42
#define UNSIGNED 43
#define VOID 44
#define VOLATILE 45
#define GTE 46
#define LTE 47
#define PP 48
#define PE 49
#define ME 50
#define TE 51
#define MODEQ 52
#define MOD 53
#define MM 54
#define DE 55
#define AND 56
#define OR 57
#define NOT 58
#define COMMA 59
#define LF 60
#define RF 61
#define DOT 62
#define REF 63
#define LS 64
#define RS 65
#define DQ 66
#define SQ 67
#define BS 68
#define CONSTANT 69
#define CHARACTER 70
#define STRING 71
#define ERR 72
#define DEFINE 73
#define INCLUDE 74
#define DECIMAL 75

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;
