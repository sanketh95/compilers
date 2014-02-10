
#define MAX_SIZE 1000

struct table_row{
	int token_class;
	char *lexeme;
};

typedef struct symbol_table{

	int cur_size;
	struct table_row row[MAX_SIZE];

}st;

extern void add_to_table(char *, int);
extern int search(char *);
extern void print(void);

extern st sym_tab;
