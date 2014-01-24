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

    sum();
    expr_prime();
}

expr_prime()
{
    /* expression' -> MINUS sum expression'
     *              | epsilon
     */

    if( match( MINUS ) )
    {
        advance();
        sum();
        expr_prime();
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

    if( match(NUM_OR_ID) )
        advance();

    else if( match(LP) )
    {
        advance();
        expression();
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
	fprintf( stderr, "%d Number or identifier expected\n", yylineno );
}
