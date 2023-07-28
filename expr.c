#include "defs.h"
#include "data.h"
#include "decl.h"

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode *primary(void) {
  struct ASTnode *n;

  switch (Token.token) {
    case T_INTLIT:
      n = mkastleaf(A_INTLIT, Token.intvalue);
      scan(&Token);
      return n;
    case T_LPAREN:
      scan(&Token);
      n = binexpr(0);
      if (Token.token != T_RPAREN) {
        fprintf(stderr, "syntax error on line %d, expected ')'\n", Line);
        exit(1);
      }
      scan(&Token);
      return n;
    default:
      fprintf(stderr, "syntax error on line %d, token %d\n", Line, Token.token);
      exit(1);
  }
}


// Convert a binary operator token into an AST operation.
int arithop(int tokentype) {
  switch (tokentype) {
  case T_PLUS:
    return (A_ADD);
  case T_MINUS:
    return (A_SUBTRACT);
  case T_STAR:
    return (A_MULTIPLY);
  case T_SLASH:
    return (A_DIVIDE);
  case T_LPAREN:
    return (A_LPAREN);
  case T_RPAREN:
    return (A_RPAREN);
  case T_PERCENT:
    return (A_MODULO);
  default:
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    exit(1);
  }
}

// Operator precedence for each token
static int OpPrec[] = { 0, 10, 10, 20, 20, 20, 0 };

// Check that we have a binary operator and
// return its precedence.
static int op_precedence(int tokentype) {
  switch (tokentype) {
    case T_LPAREN:
      return 30;
    case T_RPAREN:
      return 30;
    default:
      int prec = OpPrec[tokentype];
      if (prec == 0) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
        exit(1);
      }
      return prec;
  }
}

struct ASTnode *binexpr(int ptp) {
  struct ASTnode *left, *right;
  int tokentype;

  // Get the primary expression on the left.
  left = primary();

  // If no tokens left, return just the left node
  tokentype = Token.token;
  if (tokentype == T_EOF)
    return left;

  // While the precedence of this token is
  // more than that of the previous token precedence
  while (op_precedence(tokentype) > ptp && tokentype != T_RPAREN) {
    // Fetch the next token
    scan(&Token);

    // Check for opening parenthesis
    if (tokentype == T_LPAREN) {
      // Parse the expression inside the parentheses
      right = binexpr(0);

      // Check for closing parenthesis
      if (Token.token != T_RPAREN) {
        fprintf(stderr, "syntax error on line %d, expected ')'\n", Line);
        exit(1);
      }
      scan(&Token);
    } else {
      // Parse the next primary expression
      right = binexpr(op_precedence(tokentype));
    }

    // Join the left and right expressions with the operator
    left = mkastnode(arithop(tokentype), left, right, 0);

    // Update the details of the current token
    tokentype = Token.token;
    if (tokentype == T_EOF)
      return left;
  }

  // Return the tree we have when the precedence
  // is the same or lower
  return left;
}