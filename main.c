#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

// Initialise global variables
static void init() {
  Line = 1;
  Putback = '\n';
  for (int i=0; i<12; i++) {
    stack[i] = 0;
    freestack[i] = 1;
  } 
}

// Print out a usage if started incorrectly
static void usage(char *prog) {
  fprintf(stderr, "Usage: %s infile [options]\n", prog);
  fprintf(stderr, "Options:\n"
                  "  compile    Compile the file to matrix code, then interpret the code\n"
                  "  ast        Print the AST of the code. (For debugging)\n");
  exit(1);
}

// Main program: check arguments and print a usage
// if we don't have an argument. Open up the input
// file and call scanfile() to scan the tokens in it.
int main(int argc, char *argv[]) {
  struct ASTnode *n;

  if (argc != 3)
    usage(argv[0]);

  init();

  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  // Create the output file
  if ((Outfile = fopen("out.temc", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.temc: %s\n", strerror(errno));
    exit(1);
  }

  scan(&Token);			// Get the first token from the input
  n = binexpr(0);		// Parse the expression in the file
  if (strcmp(argv[2], "compile") == 0) {
    compileAST(n);	  // compile the AST to bytecode
    PrintAndPopOP();

    freeall_stacks();

    Line = 0;

    fclose(Outfile);	// Close the output file

    interpretAST("out.temc");

    freeall_stacks();
  } else if (strcmp(argv[2], "ast") == 0) {
    printAST(n, 0);
    freeall_stacks();
  } else {
    usage(argv[0]);
  }

  return 0;
}