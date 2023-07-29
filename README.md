# Tau Epsilon Math Compiler & Interpreter

This is the first part of impractical engineering: 
a compiler and interpreter for mathematics!
This program compiles a file containing arithmetic operations 
to a custom bytecode that looks like a 4 column matrix. (Matrix code)
After the compilation, the Tau Epsilon interpreter interprets the 
matrix code and executes the corresponding arithmetic operations
while storing temporary numbers on a stack. (Not really a stack,
because the interpreter can read any number from the stack.)

# The Tau Epsilon VM

## Build instructions

In order to build this VM from source, you need GCC and optionally GNU Make.
If you are on a Linux machine, you can proceed to building from source, and if you're 
on Windows, you need to install MinGW w64 to get GCC and perhaps you can get a Make 
binary for Windows by googling it.

### Building from source

1. Clone this repository
2. Type `cd te_math_vm` in a terminal
3. Type `make comp` to compile the main executable
4. (Optional) Type `make interp` to compile the interpreter. The main executable compiles the code and interprets it, whereas the interpreter only interprets a compiled Matrix code.

```
git clone https://github.com/ComradeCat1/te_math_vm.git
cd te_math_vm
make comp
make interp
```

## Usage instructions

After you have the main executable (which is called "te"), you can use it to evaluate your math operations doing the following steps:
1. Create a text file (preferably with the .te extension) and write your math operations in it.
2. Save the text file.
3. Run the following command to execute the file:
```
./te infile compile
```
If you want to view the generated AST (for debugging purposes), run the following command:
```
./te infile ast
```
If you're on Windows, you can use the same commands, but remove the ./ from the beginning of the commands.
<br>4. You will see a number printed to the console. That's the result of the math operations in your text file.

## VM features

- Number of stack cells: 12
- Supported operations: + - * / %
- Operator precedence: <br>
    - 30: ( ) <br>
    - 20: * / % <br>
    - 10: + - <br>
    - 0: Integer literals

# Upcoming features

### Roadmap with features ordered by priority in descending order.

- [x] Add the modulo operator
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