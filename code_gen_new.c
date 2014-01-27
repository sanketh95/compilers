#include <stdio.h>
#include "lex.h"
#include <stdlib.h>

char *expression(void);
char *great(void);
char *less(void);
char *sub(void);
char *sum(void);
char *product(void);
char *fraction(void);
char *factor(void);

char *current_lexeme(void);

extern char *newname( void       );
extern void freename( char *name );

#define ACCUMULATOR "t0"

int if_count = 0;
int while_count = 0;

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
    	char *var1 = current_lexeme(), *var2;
        advance();
        if(match(ASSIGN)){  
            advance();
            var2 = expression();

            //printf("%s = %s \n", var1,var2);
            printf("MOV %s,%s\n", var2,var1);


            freename(var2);
            free(var1);	
        }
        else
            fprintf(stderr, "%d: Not a valid assignment\n",yylineno);
        
    }
    else if(match(IF)){
    	char *var1;
    	if_count++;
        advance();
        var1 = expression();
        if(!var1){
        	fprintf(stderr, "%d: Invalid Expression\n",yylineno);
        	return;
        }
        printf("CMP %s, $0\n",var1 );
        printf("JLE Else%d\n",if_count);
        if(match(THEN)){
        	//printf("if(%s){\n", var1);

        	freename(var1);

            advance();
            statement();
            printf("Else%d:\n",if_count);
            //printf("}\n");
        }
        else
            fprintf(stderr, "%d: Then expected after if\n", yylineno);
        
    }
    else if(match(WHILE)){
    	char *var;
    	while_count++;
        advance();
        var = expression();
        if(!var){
        	fprintf(stderr, "%d: Invalid Expression\n",yylineno);
        	return;
        }
        printf("While%d:\n",while_count);
        printf("CMP %s, $0\n", var);
        printf("JLE Exit%d\n", while_count);
        if(match(DO)){
        	//printf("while\t(%s)\n", var);
        	//printf("do{\n");

            advance();
            statement();
            //printf("}\n");
            freename(var);
            printf("JMP While%d\n",while_count);
            printf("Exit%d:\n",while_count);
        }
        else
            fprintf(stderr, "%d: Do expected after while\n", yylineno);
    }

    else if(match(BEGIN)){
    	printf("begin\n");
        advance();
        opt_statements();
        if(match(END)){
            printf("end\n");
            advance();
        }
        else 
            fprintf(stderr, "%d End expected begin\n", yylineno);
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
    while(match(SEMI)){
    	advance();
    	statement();
    }
}
/*
statement_list_prime(){
    if(match(SEMI)){
        advance();
        statement();
        statement_list_prime();
    }
    else{
    	if(!match(EOI)){
    		statement_list();
    	}
    }
}

*/

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
		printf("%s=%s > %s \n", var1,var1,var2 );
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
		printf("%s=%s < %s\n", var1,var1,var2);
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
		//printf("%s = %s - %s\n", var1,var1,var2);
		printf("SUB %s, %s\n",var2,var1 );
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
		//printf("%s = %s + %s\n", var1,var1,var2);
		printf("ADD %s, %s\n", var2,var1);
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
		//printf("%s = %s * %s\n", var1,var1,var2);
		printf("IMUL %s, %s\n", var2, var1);
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
		//printf("%s = %s / %s\n", var1,var1,var2);
		printf("MOV %s,%s\n", var1, ACCUMULATOR );
		printf("DIV %s\n", var2);
		printf("MOV %s, %s\n", ACCUMULATOR,var1);
		freename(var2);
	}

	return var1;
}

char    *factor(void)
{
    char *tempvar=NULL;

    if( match(ID) )
    {
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */
        printf("MOV %0.*s, %s\n",  yyleng, yytext ,tempvar=newname());
        advance();
    }
    else if (match(NUM)){
    	printf("MOV $%0.*s, %s\n",  yyleng, yytext ,tempvar=newname());
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

char *current_lexeme(){
  char *temp;
  int i;
  temp = (char *) malloc(sizeof(char) * (yyleng+1));
  temp[yyleng]='\0';
  for(i=0;i<yyleng;i++){
    temp[i]=yytext[i];
  }

  return temp;
}