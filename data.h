#include <stdio.h>

#ifndef extern_
 #define extern_ extern
#endif

extern_ int     	Line;
extern_ int		Putback;
extern_ FILE		*Infile;
extern_ FILE		*Outfile;
extern_ struct token	Token;

extern_ int stack[10];
extern_ int freestack[10];