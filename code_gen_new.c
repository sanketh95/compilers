#include <stdio.h>
#include "lex.h"

char *expression(void);
char *great(void);
char *less(void);
char *sub(void);
char *sum(void);
char *product(void);
char *fraction(void);
char *factor(void);

extern char *newname( void       );
extern void freename( char *name );

/*Function definitions begin here*/

statement()
{
    /*  statement -> expression SEMI
     *             |  expression SEMI statement
     */

/*
    expression();

    if( match( SEMI ) )
	advance();
    else
        fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );

    if( !match(EOI) )   
        statements();			// Do another statement.

*/
    if(match(ID)){
        advance();
        if(match(ASSIGN)){              
            advance();
            expression();
        }
        else
            fprintf(stderr, "Not a valid assignment\n");
        
    }
    else if(match(IF)){
        advance();
        expression();
        if(match(THEN)){
            advance();
            statement();
        }
        else
            fprintf(stderr, "%d: Then missing\n", yylineno);
    }
    else if(match(WHILE)){
        advance();
        expression();
        if(match(DO)){
            advance();
            statement();
        }
        else
            fprintf(stderr, "%d: Do missing after while\n", yylineno);
    }

    else if(match(BEGIN)){
        advance();
        opt_statements();
        if(match(END)){
            printf("match end\n");
            advance();
        }
        else 
            fprintf(stderr, "%d End expected\n", yylineno);
    }

}

opt_statements(){

    /*
        opt_statements -> statement_list | epsilon
    */

    statement_list();
}

statement_list(){
    /*
        statement_list -> statement statement_list_prime
    */
    statement();
    statement_list_prime();
}

statement_list_prime(){
    if(match(SEMI)){
        advance();
        statement();
        statement_list_prime();
    }
}

char *expression(void){
	char *var1, *var2;
	var1 = great();
	while(match(EQUALS)){
		advance();
		var2 = great();
		printf("%s = %s\n", var1, var2);
		freename(var2);
	}

	return var1;
}

char *great(void){
	char *var1, *var2;
	var1 = less();
	while(match(GT)){
		advance();
		var2 = less();
		printf("%s:%s > %s \n", var1,var1,var2 );
		freename(var2);
	}

	return var1;
}

char *less(void){
	char *var1, *var2;
	var1 = sub();
	while(match(LT)){
		advance();
		var2 = sub();
		printf("%s:%s < %s\n", var1,var1,var2);
		freename(var2);
	}

	return var1;
}

char *sub(void){
	char *var1, *var2;
	var1 = sum();
	while(match(MINUS)){
		advance();
		var2 = sum();
		printf("%s: %s - %s\n", var1,var1,var2);
		freename(var2);
	}

	return var1;
}

char *sum(void){
	char *var1, *var2;
	var1 = product();
	while(match(PLUS)){
		advance();
		var2 = product();
		printf("%s: %s + %s\n", var1,var1,var2);
		freename(var2);
	}

	return var1;
}

char *product(void){
	char *var1, *var2;
	var1 = fraction();
	while(match(TIMES)){
		advance();
		var2 = fraction();
		printf("%s: %s * %s\n", var1,var1,var2);
		freename(var2);
	}

	return var1;
}

char *fraction(void){
	char *var1, *var2;
	var1 = factor();
	while(match(DIV)){
		advance();
		var2 = factor();
		printf("%s: %s / %s\n", var1,var1,var2);
		freename(var2);
	}

	return var1;
}

char    *factor(void)
{
    char *tempvar;

    if( match(NUM) || match(ID) )
    {
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */

        printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext );
        advance();
    }
    else if( match(LP) )
    {
        advance();
        tempvar = expression();
        if( match(RP) )
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    }
    else
	fprintf( stderr, "%d: Number or identifier expected\n", yylineno );

    return tempvar;
}