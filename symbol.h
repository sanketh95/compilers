
#define MAX_SIZE 50
typedef struct symbol_table{

	int cur_size;
	char *ids[50];
}st;

extern void add_to_table(char *);
extern int search(char *);
extern void print(void);

extern st sym_tab;
