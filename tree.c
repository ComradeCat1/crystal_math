#include "defs.h"
#include "data.h"
#include "decl.h"
#include <string.h>

// Build and return a generic AST node
struct ASTnode *mkastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue) {
  struct ASTnode *n;

  // Malloc a new ASTnode
  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (n == NULL) {
    fprintf(stderr, "Unable to malloc in mkastnode()\n");
    exit(1);
  }
  // Copy in the field values and return it
  n->op = op;
  n->left = left;
  n->right = right;
  n->intvalue = intvalue;
  return (n);
}


// Make an AST leaf node
struct ASTnode *mkastleaf(int op, int intvalue) {
  return (mkastnode(op, NULL, NULL, intvalue));
}

// Make a unary AST node: only one child
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue) {
  return (mkastnode(op, left, NULL, intvalue));
}

// Function to print the AST recursively with indentation
void printAST(struct ASTnode* node, int level) {
  if (node == NULL) {
    return;
  }

  // Indent based on the level
  for (int i = 0; i < level; i++) {
    printf("  ");
  }

  switch (node->op) {
    case A_ADD:
      printf("op: +, intvalue: %d\n", node->intvalue);
      break;
    case A_SUBTRACT:
      printf("op: -, intvalue: %d\n", node->intvalue);
      break;
    case A_MULTIPLY:
      printf("op: *, intvalue: %d\n", node->intvalue);
      break;
    case A_DIVIDE:
      printf("op: /, intvalue: %d\n", node->intvalue);
      break;
    case A_MODULO:
      printf("op: %%, intvalue: %d\n", node->intvalue);
      break;
    case A_INTLIT:
      printf("intvalue: %d\n", node->intvalue);
      break;
    case A_PRINT:
      printf("op: print, intvalue: %d\n", node->intvalue);
      break;
    default:
      fprintf(stderr, "Invalid AST node operator: %d\n", node->op);
      exit(1);
  }

  // Recursively print the left and right child nodes with increased level
  printAST(node->left, level + 1);
  printAST(node->right, level + 1);
}