#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */
int define_found=0;  

void add(int);

int lex(void){

   static char input_buffer[1024];
   char        *current;
   int first_char_is_digit = 0;
   int invalid_num= 0;
   int tc;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         current = input_buffer;
         ++yylineno;
         while(isspace(*current))
            ++current;
      }
  //    printf("%s\n", current);
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
           case ',':
            add(COMMA);
            return COMMA;
           case '=':
        //    printf("ASSIGN\n");
            if(*(current+1) == '='){
                yyleng=2;
                add(EQUALS);
                return EQUALS;
            }
            add(ASSIGN);
            return ASSIGN;
           case '<':
         //   printf("LT\n");
            if(*(current+1) == '='){
                yyleng=2;
                add(LTE);
                return LTE;
            }
            add(LT);
            return LT;
           case '>':
         //   printf("GT\n");
            if(*(current+1) == '='){
                yyleng=2;
                add(GTE);
                return GTE;
            }
            add(GT);
            return GT;
           case ';':
         //   printf("semi colon\n");
           add(SEMI);
            return SEMI;
           case '+':
         //  printf("plus\n");
            if(*(current+1) == '+'){
              yyleng=2;
              add(PP);
              return PP;
            }
            else if(*(current+1) == '='){
              yyleng=2;
              add(PE);
              return PE;
            }
            add(PLUS);
            return PLUS;
           case '-':
              if(*(current+1) == '-'){
                yyleng=2;
                add(MM);
                return MM;
              }
            else if(*(current+1) == '='){
              yyleng=2;
              add(ME);
              return ME;
            }
            else if(*(current+1) == '>'){
              yyleng=2;
              add(RF);
              return RF;
            }
         //  printf("minus\n");
            add(MINUS);
            return MINUS;
           case '*':
            if(*(current+1) == '='){
              yyleng=2;
              add(TE);
              return TE;
            }
         //  printf("mul\n");
            add(TIMES);
            return TIMES;
           case '/':
         //  printf("div\n");
            if(*(current+1) == '='){
              yyleng=2;
              add(DE);
              return DE;
            }
            add(DIV);
            return DIV;
           case '(':
         //   printf("lp\n");
            add(LP);
            return LP;
           case ')':
         //   printf("rp\n");
            add(RP);
            return RP;
           case '{':
           add(LF);
            return LF;
           case '}':
            add(RF);
            return RF;
           case '[':
            add(LS);
            return LS;
           case ']':
            add(RS);
            return RS;
           case '\"':
            add(DQ); 
            return DQ;
           case '\'':
           add(SQ);
            return SQ;
           case '%':
            if(*(current+1) == '='){
              yyleng=2;
              add(MODEQ);
              return MODEQ;
            }
            add(MOD);
            return MOD;
           case '&':
            if(*(current+1) == '&'){
              yyleng=2;
              add(AND);
              return AND;
            }
           case '|':
            if(*(current+1) == '|'){
              yyleng=2;
              add(OR);
              return OR;
            }
           case '!':
            add(NOT);
            return NOT;
           case '.':
            add(DOT);
            return DOT;
           case '\\':
            add(BS);
            return BS;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current) && *current!='#')
               fprintf(stderr, "Invalid char %c\n", *current);
            else{               

              if(*current == '#')
                current++;

               if(isdigit(*current)) 
                  first_char_is_digit = 1;
               
                current++;
               while(isalnum(*current) || *current=='_' ){
                  if(isalpha(*current) || *current == '_' ){

                    if(first_char_is_digit && !invalid_num)
                        invalid_num = 1;
                  }
                  
                  ++current;
               }

               yyleng = current - yytext;
               if(invalid_num)
                  fprintf(stderr, "Neither number nor id\n");
               else
                  if(first_char_is_digit){
                      add(NUM);
                      return NUM;
                    }
                  else{
                      //printf("%0.*s\n",yyleng, yytext );
                      tc = find_keyword();
                      add(tc);
                      return tc;
                  }
            }
            break;
         }
      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
//    printf("%d\n", Lookahead);
}

int find_keyword(){
  char *temp;
  int i;
  temp = (char *) malloc(sizeof(char) * (yyleng+1));
  temp[yyleng]='\0';
  for(i=0;i<yyleng;i++){
    temp[i]=yytext[i];
  }
  
  /*Compare for keywords*/
  if(!strcmp(temp,"if")){
    return IF;
  }
  else if(!strcmp(temp,"while")){
    return WHILE;
  }
  else if(!strcmp(temp,"do")){
    return DO;
  }
  else if(!strcmp(temp,"else"))
    return ELSE;
  else if(!strcmp(temp,"auto"))
    return AUTO;
  else if(!strcmp(temp,"const"))
    return CONST;
  else if(!strcmp(temp,"break"))
    return BREAK;
  else if(!strcmp(temp,"case"))
    return CASE;
  else if(!strcmp(temp,"char"))
    return CHAR;
  else if(!strcmp(temp,"continue"))
    return CONTINUE;
  else if(!strcmp(temp,"default"))
    return DEFAULT;
  else if(!strcmp(temp,"enum"))
    return ENUM;
  else if(!strcmp(temp,"extern"))
    return EXTERN;
  else if(!strcmp(temp,"float"))
    return FLOAT;
  else if(!strcmp(temp,"for"))
    return FOR;
  else if(!strcmp(temp,"goto"))
    return GOTO;
  else if(!strcmp(temp,"int"))
    return INT;
  else if(!strcmp(temp,"long"))
    return LONG;
  else if(!strcmp(temp,"register"))
    return REGISTER;
  else if(!strcmp(temp,"return"))
    return RETURN;
  else if(!strcmp(temp,"short"))
    return SHORT;
  else if(!strcmp(temp,"signed"))
    return SIGNED;
  else if(!strcmp(temp,"sizeof"))
    return SIZEOF;
  else if(!strcmp(temp,"static"))
    return STATIC;
  else if(!strcmp(temp,"struct"))
    return STRUCT;
  else if(!strcmp(temp,"switch"))
    return SWITCH;
  else if(!strcmp(temp,"typedef"))
    return TYPEDEF;
  else if(!strcmp(temp,"union"))
    return UNION;
  else if(!strcmp(temp,"void"))
    return VOID;
  else if(!strcmp(temp,"volatile"))
    return VOLATILE;
  else if(!strcmp(temp,"#define")){
    define_found=1;
    lex();
  }
  else{
    if(define_found){
        define_found=0;
        return CONSTANT;
    }
    return ID;
  }
}


void add(int tc){
  char *temp;
  int i;
  temp = (char *) malloc(sizeof(char) * (yyleng+1));
  temp[yyleng]='\0';
  for(i=0;i<yyleng;i++){
    temp[i]=yytext[i];
  }
    add_to_table_no_check(temp, tc);
}