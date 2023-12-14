# TINY Language Compiler - Scanner Phase

## Overview
This program implements the scanning (tokenization) step of a custom compiler for the TINY programming language. The TINY language is a simple programming language with basic features, including statements, I/O operations, mathematical expressions, boolean conditions, and control structures like if and repeat.

## Input
The scanner takes a source code file written in the TINY programming language as input. An example input file, `input.txt`, is provided for testing.

## Output
The scanner produces a text file containing the tokens found in the input file. Each token is represented on a single line in the following format:

```
[number of line the token was found in starting from 1 in square brackets] [the actual string that represents the token in the input file] [a string that represents the token type in round brackets]
```

For example:
```
[1] if (If)
[1] x (ID)
[2] 200 (Num)
...
```

## TINY Language Rules
- Statements are separated by semicolons (;).
- Comments are enclosed in curly braces {}.
- I/O operations include read and write.
- Mathematical expressions involve integers only, and operators + - * / ^.
- Boolean conditions are used in if and repeat statements, using <, =, and two mathematical expressions.
- Repeat statement: repeat until (boolean).
- If statement: if (boolean) then [else] end.
- Variable names can include only alphabetic characters (a:z or A:Z) and underscores.
- Variables are declared by assigning values to them with :=.
- All variables are integers.
- No procedures or declarations are allowed.

## Build Instructions
To compile the program, use a C++ compiler. For example:

```bash
g++ tiny_scanner.cpp -o tiny_scanner
```

## Usage
Compile the program and run it from the command line. Provide the TINY source code file as an argument:

```bash
./tiny_scanner input.txt
```

The output will be written to a file named `output.txt`.

## Example Input (input.txt)
```TINY
{ TINY Language Example }
x := 10;
y := 5;
z := x + y;
if (z < 20) then
    write(z)
else
    write(100)
end;
```

## Example Output (output.txt)
```
[2] x (ID)
[3] := (Assign)
[3] 10 (Num)
[4] ; (Semicolon)
[5] y (ID)
[6] := (Assign)
[6] 5 (Num)
[7] ; (Semicolon)
[8] z (ID)
[9] := (Assign)
[9] x (ID)
[9] + (Plus)
[9] y (ID)
[9] ; (Semicolon)
[10] if (If)
[10] ( (LParen)
[10] z (ID)
[10] < (LessThan)
[10] 20 (Num)
[10] ) (RParen)
[10] then (Then)
[11] write (Write)
[11] ( (LParen)
[11] z (ID)
[11] ) (RParen)
[12] else (Else)
[13] write (Write)
[13] ( (LParen)
[13] 100 (Num)
[13] ) (RParen)
[14] end (End)
[15] ; (Semicolon)
```