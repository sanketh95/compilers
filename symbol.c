#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

st sym_tab;

int search(char *s){
	int i=0;
	for(i=0;i<sym_tab.cur_size;i++){
		if(!strcmp(s,sym_tab.ids[i])){
			return 1;
		}
	}
	return 0;
}

void add_to_table(char *s){
	if(sym_tab.cur_size == MAX_SIZE)
		return;
	if(!search(s)){
		
		sym_tab.ids[sym_tab.cur_size] = (char *)malloc(sizeof(char) * (strlen(s) + 1) );
		strcpy(sym_tab.ids[sym_tab.cur_size],s);
		sym_tab.cur_size++;	
		
	}

}

void print(void){
	int i=0;
	for(i=0;i<sym_tab.cur_size;i++){
		printf("%s\n",sym_tab.ids[i] );
	}
}