#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>
#include <stdio.h>

// Initialise global variables
static void init() {
  Line = 1;
  Putback = '\n';
  for (int i=0; i<10; i++) {
    stack[i] = 0;
    freestack[i] = 1;
  } 
}

// Print out a usage if started incorrectly
static void usage(char *prog) {
  fprintf(stderr, "Usage: %s infile\n", prog);
  exit(1);
}

// Main program: check arguments and print a usage
// if we don't have an argument. Open up the input
// file and call scanfile() to scan the tokens in it.
int main(int argc, char *argv[]) {
  struct ASTnode *n;

  if (argc != 2)
    usage(argv[0]);

  init();

  interpretAST(argv[1]);

  freeall_stacks();

  return 0;
}