#include <stdio.h>
#include <stdlib.h>

// Abstract Syntax Tree structure
struct ASTnode {
  int op;                     // "Operation" to be performed on this tree
  struct ASTnode *left;       // Left and right child trees
  struct ASTnode *right;
  int intvalue;               // For A_INTLIT, the integer value
};

// Function to print the AST recursively with indentation
void printAST(struct ASTnode* node, int level) {
  if (node == NULL) {
    return;
  }

  // Indent based on the level
  for (int i = 0; i < level; i++) {
    printf("  ");
  }

  // Print the current node
  printf("op: %d, intvalue: %d\n", node->op, node->intvalue);

  // Recursively print the left and right child nodes with increased level
  printAST(node->left, level + 1);
  printAST(node->right, level + 1);
}

int main() {
  // Create an example AST
  struct ASTnode* root = malloc(sizeof(struct ASTnode));
  root->op = 1;
  root->intvalue = 10;

  struct ASTnode* leftChild = malloc(sizeof(struct ASTnode));
  leftChild->op = 2;
  leftChild->intvalue = 5;

  struct ASTnode* rightChild = malloc(sizeof(struct ASTnode));
  rightChild->op = 3;
  rightChild->intvalue = 7;

  root->left = leftChild;
  root->right = rightChild;

  // Print the AST with tree-like structure
  printAST(root, 0);

  // Free the allocated memory
  free(leftChild);
  free(rightChild);
  free(root);

  return 0;
}