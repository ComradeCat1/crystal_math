#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Token types
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_PERCENT, T_INTLIT, T_LPAREN, T_RPAREN, T_SEMI, T_PRINT
};

// Token structure
struct token {
  int token;				// Token type, from the enum list above
  int intvalue;				// For T_INTLIT, the integer value
};

// AST node types
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_MODULO, A_INTLIT, A_LPAREN, A_RPAREN, A_PRINT
};

// Abstract Syntax Tree structure
struct ASTnode {
  int op;				// "Operation" to be performed on this tree
  struct ASTnode *left;			// Left and right child trees
  struct ASTnode *right;
  int intvalue;				// For A_INTLIT, the integer value
};