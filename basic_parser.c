/* Basic parser, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.h"

statements()
{
    /*  statements -> expression SEMI
     *             |  expression SEMI statements
     */

    expression();

    if( match( SEMI ) )
	advance();
    else
        fprintf( stderr, "%d: Inserting missing semicolon\n", yylineno );

    if( !match(EOI) )   
        statements();			/* Do another statement. */
}


expression()
{
    /* expression -> term expression' */
/*
    sum();
    expr_prime();

 */
 
    great();
    expr_prime();
}

expr_prime()
{
    /* expression' -> MINUS sum expression'
     *              | epsilon
     */

/*
    if( match( MINUS ) )
    {
        advance();
        sum();
        expr_prime();
    }
*/
    if(match(EQUALS)){
        advance();
        great();
        expr_prime();
    }
}

great(){

    /*
        great -> less great_prime
    */

    less();
    great_prime();
}

great_prime(){

    /*
        great_prime -> > less great_prime | epsilon
    */
    if(match(GT)){
        advance();
        less();
        great_prime();
    }
}

less(){
    /*
        less -> sub less_prime
    */
    sub();
    less_prime();
}

less_prime(){
    /*
        less_prime -> < sub less_prime | epsilon
    */
    if(match(LT)){
        advance();
        sub();
        less_prime();
    }
}

sub(){
    /*
        sub -> sum sub_prime
    */
    sum();
    sub_prime();
}

sub_prime(){
    /*
        sub_prime -> add sub_prime | epsilon
    */
    if(match(MINUS)){
        advance();
        sum();
        sub_prime();
    }
}

sum()
{
    /* term -> factor term' */

    product();
    sum_prime();
}

sum_prime()
{
    /* term' -> TIMES factor term'
     *       |   epsilon
     */

    if( match( PLUS) )
    {
        advance();
        product();
        sum_prime();
    }
}


product(){
    /*
    product -> fraction product_prime


    */

    fraction();
    product_prime();
}

product_prime(){
    if(match(TIMES)){
        advance();
        fraction();
        product_prime();
    }
}

fraction(){
    /*
        fraction -> factor fraction_prime
    */
      factor();
      fraction_prime() ;
}

fraction_prime(){
    /*
    fraction_prime -> /factor fraction_prime | epsilon
    */
    if(match(DIV)){
        advance();
        factor();
        fraction_prime();
    }
}

factor()
{
    /* factor   ->    NUM_OR_ID
     *          |     LP expression RP
     */

    if( match(NUM) || match(ID)){
   //     printf("I'm advancing after matching a number or id\n");
        advance();
    }

    else if( match(LP) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else{
	   fprintf( stderr, "%d Number or identifier expected\n", yylineno );
        //advance();
    }
}
