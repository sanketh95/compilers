#include "symbol.h"
#include "stdio.h"

extern FILE *f;

main ()
{	

	FILE *f1;
	char ch;
	int i=0;
	sym_tab.cur_size=0;
	statement_list ();
	fclose(f);
	

	f1 = fopen("final.s","w");
	

	fprintf(f1, ".data\n");
	
	for(i=0;i<sym_tab.cur_size;i++){
		fprintf(f1, "\t\t%s: .byte 0\n", sym_tab.ids[i]);
	}

	fprintf(f1,".text\n.globl main\n\nmain:\n\n");

	//printf(f,"main:\n\n main:\n\n");

	f = fopen("temp.txt","r+");
	if(!f)
		printf("error\n");
	while( (ch=fgetc(f)) != EOF ){
		//printf("s\n");
		fprintf(f1,"%c", ch);
	}

	/*Close the open files*/
	fclose(f);
	fclose(f1);
	
}
