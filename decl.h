#include <stdio.h>

int scan(struct token *t);

struct ASTnode *mkastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(int rbp);

int interpretAST(char *out);
int compileAST(struct ASTnode *n);

int alloc_stack();
void free_stack(int space);
void freeall_stacks();
int PrintAndPopOP();