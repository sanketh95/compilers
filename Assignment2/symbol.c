#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

st sym_tab;

int search(char *s){
	int i=0;
	for(i=0;i<sym_tab.cur_size;i++){
		if(!strcmp(s,sym_tab.row[i].lexeme)){
			return 1;
		}
	}
	return 0;
}

void add_to_table(char *s, int token_class){
	if(sym_tab.cur_size == MAX_SIZE)
		return;
	if(!search(s)){
		
		sym_tab.row[sym_tab.cur_size].lexeme = (char *)malloc(sizeof(char) * (strlen(s) + 1) );
		strcpy(sym_tab.row[sym_tab.cur_size].lexeme,s);
		sym_tab.row[sym_tab.cur_size].token_class = token_class;
		sym_tab.cur_size++;	
		
	}

}

void pprint(){
	int i;
	for(i=0;i<sym_tab.cur_size;i++){
		printf("%s\t%d\n", sym_tab.row[i].lexeme,sym_tab.row[i].token_class);
	}
}