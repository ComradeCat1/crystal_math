#include "defs.h"
#include "data.h"
#include "decl.h"
#include <stdio.h>
#include <stdlib.h>

// List of AST operators
static char *ASTop[] = { "+", "-", "*", "/" };

// Return the position of character c
// in string s, or -1 if c not found
static int chrpos(char *s, int c) {
  char *p;

  p = strchr(s, c);
  return (p ? p - s : -1);
}

// Get the next character from the input file.
static int nextOut() {
  int c;

  if (Putback) {		// Use the character put
    c = Putback;		// back if there is one
    Putback = 0;
    return c;
  }

  c = fgetc(Outfile);		// Read from output file
  if ('\n' == c)
    Line++;			// Increment line count

  return c;
}

// Put back an unwanted character
static void putback(int c) {
  Putback = c;
}

// Skip past input that we don't need to deal with, 
// i.e. whitespace, newlines. Return the first
// character we do need to deal with.
static int skipOut() {
  int c;

  c = nextOut();
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = nextOut();
  }

  return (c);
}

// Scan and return an integer literal
// value from the input file. Store
// the value as a string in Text.
static int scanBytecode(int c) {
  int k, val = 0;

  int is_neg = 0;
  if ('-' == c) {
    is_neg = 1;
    c = nextOut();
  }

  // Convert each character into an int value
  while ((k = chrpos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = nextOut();
  }

  if (is_neg) {
    val = -val;
  }

  // We hit a non-integer character, put it back.
  putback(c);
  return val;
}

// Given an AST, interpret the
// operators in it and return
// a final value.
int interpretAST(char *out) {
    Outfile = fopen(out, "r");
    int c;

    int arg1, arg2, arg3, throw_away, result;

    // Determine the opcode based on
    // the input character
    while (!feof(Outfile)) {
        c = scanBytecode(skipOut());
        switch(c) {
            case 0:
                break;
            case 1:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                throw_away = scanBytecode(skipOut());
                stack[arg2] = arg1;
                freestack[arg2] = 0;
                break;
            case 2:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                throw_away = scanBytecode(skipOut());
                for (int i = arg2; i < 9; i++) {
                    stack[i+1] = stack[i];
                    freestack[i+1] = freestack[i];
                }
                stack[arg2] = stack[arg1+1];
                stack[arg1+1] = 0;
                freestack[arg2] = freestack[arg1+1];
                freestack[arg1+1] = 1;
                break;
            case 3:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                arg3 = scanBytecode(skipOut());
                result = stack[arg1] + stack[arg2];
                stack[arg1] = stack[arg2] = 0;
                freestack[arg1] = freestack[arg2] = 1;
                stack[arg3] = result;
                freestack[arg3] = 0;
                break;
            case 4:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                arg3 = scanBytecode(skipOut());
                result = stack[arg1] - stack[arg2];
                stack[arg1] = stack[arg2] = 0;
                freestack[arg1] = freestack[arg2] = 1;
                stack[arg3] = result;
                freestack[arg3] = 0;
                break;
            case 5:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                arg3 = scanBytecode(skipOut());
                result = stack[arg1] * stack[arg2];
                stack[arg1] = stack[arg2] = 0;
                freestack[arg1] = freestack[arg2] = 1;
                stack[arg3] = result;
                freestack[arg3] = 0;
                break;
            case 6:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                arg3 = scanBytecode(skipOut());
                result = stack[arg1] / stack[arg2];
                stack[arg1] = stack[arg2] = 0;
                freestack[arg1] = freestack[arg2] = 1;
                stack[arg3] = result;
                freestack[arg3] = 0;
                break;
            case 7:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                arg3 = scanBytecode(skipOut());
                printf("%d\n", stack[arg1]);
                stack[arg1] = 0;
                freestack[arg1] = 1;
                break;
            case 8:
                arg1 = scanBytecode(skipOut());
                arg2 = scanBytecode(skipOut());
                arg3 = scanBytecode(skipOut());
                result = stack[arg1] % stack[arg2];
                stack[arg1] = stack[arg2] = 0;
                freestack[arg1] = freestack[arg2] = 1;
                stack[arg3] = result;
                freestack[arg3] = 0;
                break;
            default:
                printf("Unknown opcode %d at line %d\n", c, Line);
                exit(1);
        }
    }
    // printf("Final stack: [ %d , %d , %d , %d , %d , %d , %d , %d , %d , %d , %d, %d]\n", stack[0], stack[1], stack[2], stack[3], stack[4], stack[5], stack[6], stack[7], stack[8], stack[9], stack[10], stack[11]);
    fclose(Outfile);
    return 0;
}