#include "data.h"
#include "decl.h"
#include "defs.h"
#include "bytecode.h"
#include <stdio.h>
#include <stdlib.h>

int alloc_stack(void) {
    for (int i=0; i<12; i++) {
        if (freestack[i]) {
            freestack[i]= 0;
            return(i);
        }
    }
    fprintf(stderr, "Out of stacks!\n");
    exit(1);
}

void freeall_stacks(void)
{
    for (int i=0; i<12; i++) {
        freestack[i] = 1;
        stack[i] = 0;
    }
}

void free_stack(int space)
{
    if (freestack[space] != 0) {
        fprintf(stderr, "Error trying to free stack %d\n", space);
        exit(1);
    }
    freestack[space] = 1;
    stack[space] = 0;
}

int find_stack(int val) {
    for (int i=0; i<10; i++) {
        if (stack[i] == val) {
            return(i);
        }
    }
    fprintf(stderr, "Error trying to find stack with value %d\n", val);
    exit(1);
}

int StoreOP(int n) {
    int stack_space = alloc_stack();
    stack[stack_space] = n;
    fprintf(Outfile, "%d %d %d 0\n", STORE, n, stack_space);
    return stack_space;
}

int LoadOP(int space_in) {
    fprintf(Outfile, "%d %d 0 0\n", LOAD, space_in);
    return 0;
}

int AddOP(int space1, int space2) {
    fprintf(Outfile, "%d %d %d %d\n", ADD_OP, space1, space2, space1);
    return 0;
}

int SubOP(int space1, int space2) {
    fprintf(Outfile, "%d %d %d %d\n", SUB_OP, space1, space2, space1);
    return 0;
}

int MulOP(int space1, int space2) {
    fprintf(Outfile, "%d %d %d %d\n", MUL_OP, space1, space2, space1);
    return 0;
}

int DivOP(int space1, int space2) {
    fprintf(Outfile, "%d %d %d %d\n", DIV_OP, space1, space2, space1);
    return 0;
}

int ModOP(int space1, int space2) {
    fprintf(Outfile, "%d %d %d %d\n", MOD_OP, space1, space2, space1);
    return 0;
}

int PrintAndPopOP() {
    int remaining;
    for (int i = 0; i < 10; i++) {
        if (!freestack[i]) {
            remaining = i;
            break;
        }
    }
    fprintf(Outfile, "%d %d 0 0\n", PRINT_AND_POP, remaining);
    return 0;
}

int compileAST(struct ASTnode *n) {
    int op1, op2;
    int leftval, rightval;
    int result;

    // Get the left and right sub-tree values
    if (n->left)
        leftval = compileAST(n->left);
    if (n->right)
        rightval = compileAST(n->right);
    
    switch (n->op) {
        case A_INTLIT:
            StoreOP(n->intvalue);
            return n->intvalue;
        case A_ADD:
            op1 = find_stack(leftval);
            op2 = find_stack(rightval);
            AddOP(op1, op2);
            result = stack[op1] + stack[op2];
            stack[op1] = stack[op2] = 0;
            freestack[op1] = freestack[op2] = 1;
            stack[op1] = result;
            freestack[op1] = 0;
            return result;
        case A_SUBTRACT:
            op1 = find_stack(leftval);
            op2 = find_stack(rightval);
            SubOP(op1, op2);
            result = stack[op1] - stack[op2];
            stack[op1] = stack[op2] = 0;
            freestack[op1] = freestack[op2] = 1;
            stack[op1] = result;
            freestack[op1] = 0;
            return result;
        case A_MULTIPLY:
            op1 = find_stack(leftval);
            op2 = find_stack(rightval);
            MulOP(op1, op2);
            result = stack[op1] * stack[op2];
            stack[op1] = stack[op2] = 0;
            freestack[op1] = freestack[op2] = 1;
            stack[op1] = result;
            freestack[op1] = 0;
            return result;
        case A_DIVIDE:
            op1 = find_stack(leftval);
            op2 = find_stack(rightval);
            DivOP(op1, op2);
            result = stack[op1] / stack[op2];
            stack[op1] = stack[op2] = 0;
            freestack[op1] = freestack[op2] = 1;
            stack[op1] = result;
            freestack[op1] = 0;
            return result;
        case A_MODULO:
            op1 = find_stack(leftval);
            op2 = find_stack(rightval);
            ModOP(op1, op2);
            result = stack[op1] % stack[op2];
            stack[op1] = stack[op2] = 0;
            freestack[op1] = freestack[op2] = 1;
            stack[op1] = result;
            freestack[op1] = 0;
            return result;
        default:
            fprintf(stderr, "syntax error on line %d, token %d\n", Line, n->op);
            exit(1);
    }
    return 0;
}
