# TINY Language Compiler - Code Generation Phase

## Overview
This program implements the code generation step of a custom compiler for the TINY programming language. The input can be either the path to the source code file written in the TINY programming language or hardcoded within the code. The program outputs three things: the symbol table, the syntax tree with data types, and a simulation of the compilation.

## Input
The program takes the path of a source code file written in the TINY programming language as input, or you can hardcode the TINY source code within the code. An example input file, `input.txt`, is provided for testing.

## Output
The program outputs three things:

1. **Symbol Table:**
   The symbol table contains information about all named variables in the following format for each variable:
   `[Var=variable name][Mem=initial value of the variable][Line=the first line number the variable appears in][Line=the second line number the variable appears in]` and so on for all the other lines the variable is referenced in.

   Example of a symbol table:
   ```
   [Var=x][Mem=0][Line=6][Line=7][Line=20]
   [Var=y][Mem=0][Line=1]
   ```

2. **Syntax Tree:**
   The syntax tree is the same as the output of the previous assignment, but each non-void (Integer or Boolean) node is followed by its data type in square brackets. Type checking is performed, and errors are printed to the terminal if a type mismatch occurs.

   Example of an Integer node: `[ID][x][Integer]`
   Example of a Boolean node: `[Oper][LessThan][Boolean]`
   Example of a void node: `[Read][x]`

3. **Simulation of Compilation:**
   A simulation of the compilation process is run, assuming the program is actually running. The only parts that interact with the terminal are `Read` and `Write` statements. Other statements are handled internally.

   Example of a `Read x` statement:
   ```
   Enter x: [user input]
   ```

   Example of a `Write 5` statement:
   ```
   val: 5
   ```

## Build Instructions
To compile the program, use a C++ compiler. For example:

```bash
g++ tiny_compiler.cpp -o tiny_compiler
```

## Usage
Compile the program and run it from the command line. Provide the path to the TINY source code file as an argument:

```bash
./tiny_compiler input.txt
```

## Example Input (input.txt)
```TINY
x := 10;
y := 5;
z := x + y;
if z < 20 then
    write(z)
else
    write(100)
end;
```

## Example Output
```
Symbol Table:
[Var=x][Mem=0][Line=2][Line=3][Line=4]
[Var=y][Mem=0][Line=5][Line=6][Line=7]
[Var=z][Mem=0][Line=8][Line=9][Line=10][Line=11]

Syntax Tree:
[Assign][x][Integer]
   [Num][10][Integer]
[Assign][y][Integer]
   [Num][5][Integer]
[Assign][z][Integer]
   [ID][x][Integer]
   [Oper][Plus][Integer]
      [ID][y][Integer]
if [Oper][LessThan][Boolean]
      [ID][z][Integer]
      [Num][20][Integer]
then [Write][z][Void]
else [Write][100][Void]

Simulation:
Enter x: [user input]
val: 15
```