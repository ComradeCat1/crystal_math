#include <stdio.h>

#ifndef extern_
 #define extern_ extern
#endif

extern_ int     	Line;
extern_ int		Putback;
extern_ FILE		*Infile;
extern_ FILE		*Outfile;
extern_ struct token	Token;

extern_ int stack[12];
extern_ int freestack[12];

#define TEXTLEN         512             // Length of symbols in input
extern_ char Text[TEXTLEN + 1];         // Last identifier scanned