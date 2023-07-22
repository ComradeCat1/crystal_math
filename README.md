# Tau Epsilon Math Compiler & Interpreter

This is the first part of impractical engineering: 
a compiler and interpreter for mathematics!
This program compiles a file containing arithmetic operations 
to a custom bytecode that looks like a 4 column matrix. (Matrix code)
After the compilation, the Tau Epsilon interpreter interprets the 
matrix code and executes the corresponding arithmetic operations
while storing temporary numbers on a stack. (Not really a stack,
because the interpreter can read any number from the stack.)

# The matrix code

## Specifications

The Tau Epsilon matrix code is an intermediate representation of mathematical operations.
Each instruction is a 4D row vector, having the following structure:

[opcode] [argument1] [argument2] [argument3]

There are currently 8 opcodes, with more coming in the future. The current opcodes are:

| Opcode | Name          | Description                                                                                                                                                                                                                                                                                                                                                          | Argument 1                                                           | Argument 2                                                                                  | Argument 3                                                                                |
|--------|---------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------|---------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------|
| 0      | NOPE          | Nope, don't do anything.                                                                                                                                                                                                                                                                                                                                             | This argument is ignored                                             | This argument is ignored                                                                    | This argument is ignored                                                                  |
| 1      | STORE         | Store the first argument in the cell pointed to by the second  argument. The third argument is ignored.                                                                                                                                                                                                                                                              | Numeric value to be stored                                           | Index of the cell in which  to store the number                                             | This argument is ignored                                                                  |
| 2      | LOAD          | Load the content of the cell pointed  to by the first argument into the cell  pointed to by the second argument. Save and delete the content of the cell whose index  is the first argument, shift all cells from  the index argument 2 to the right, and  store the saved content into the cell  pointed to by the second argument. The third  argument is ignored. | Index of the cell with the content that should be loaded.            | Index of the cell in which to load the content.                                             | This argument is ignored                                                                  |
| 3      | ADD           | Add the contents of the cells pointed to by  the first and second arguments, then store  the result in the cell pointed to by the  third argument. The contents of the cells pointed to by the first and second  arguments are deleted.                                                                                                                              | Index of the cell with the left operand                              | Index of the cell with the right operand                                                    | Index of the cell in which  to store the sum.                                             |
| 4      | SUB           | Subtract the content of the second cell  from the content of the first cell and store the result in the cell pointed to by the  third argument. The contents of the cells  pointed to by the first and second arguments are deleted.                                                                                                                                 | Index of the cell with the left operand                              | Index of the cell with the right operand                                                    | Index of the cell in which  to store the difference.                                      |
| 5      | MUL           | Multiply the contents of the cells pointed to by the first and second arguments, then store the result in the cell pointed to by the third argument. The contents of the cells pointed to by the first and second arguments are deleted.                                                                                                                             | Index of the cell with the left  operand                             | Index of the cell with the right operand                                                    | Index of the cell in which to store the product.                                          |
| 6      | DIV           | Divide the content of the first cell by the content of the second cell and store the quotient in the cell pointed to by the third argument. The contents of the cells pointed to by the first and second  arguments are deleted.                                                                                                                                     | Index of the cell with the left  operand                             | Index of the cell with the right operand                                                    | Index of the cell in which  to store the quotient.                                        |
| 7      | PRINT_AND_POP | Print and pop the contents of up to three cells by  specifying their indices. Duplicate arguments are  ignored.                                                                                                                                                                                                                                                      | Index of the first cell whose  content should be printed and popped. | Index of the second cell whose content should be printed and  popped. Ignored if duplicate. | Index of the third cell whose content should be printed and popped. Ignored if duplicate. |

## VM features

- Number of stack cells: 10
- Supported operations: + - * /
- Operator precedence: <br>
    - 20: * / <br>
    - 10: + - <br>
    - 0: Integer literals

# Upcoming features

### Roadmap with features in the order in which they will be added

- [ ] Add the modulo operator
- [x] Support changing the precedence with parentheses
- [ ] Allow defining custom variables and using them in the math code. This would require me to write a custom data structure to hold the variables.
- [ ] Add Boolean algebra operators and functions.
- [ ] Allow defining custom functions and using them in the math code.
- [ ] Make a lower level language for writing matrix code more easily
- [ ] Make a data type called "EpsiLong" for holding long integers
- [ ] Add support for exponentiation, nth roots and logarithms
- [ ] Add optimizations for special cases, like dividing a variable by itself
- [ ] Make a high precision floating point data type called "EpsiFloat", because some math operations require higher precision.
- [ ] Add support for trigonometry functions like sin, cos, tan etc.
- [ ] Add the possibility to import other math functions from Tau Epsilon script files. Then create a large standard library.
- [ ] Add arrays and multidimensional arrays
- [ ] Add support for calculus functions (Once I have a deeper understanding of them)
- [ ] Add a function for multiplying matrices that uses shortcuts for special cases of matrices.
- [ ] Try to add more number theory functions.
- [ ] Try to cover as many sub-fields of mathematics as possible.

# Summary
This is a Math VM at a very early stage of development. (And it's currently faster than Python!) 
Please be patient as I add more functionality, or if you're not patient, try contributing to this repository by adding the functionality that is planned on the roadmap above.