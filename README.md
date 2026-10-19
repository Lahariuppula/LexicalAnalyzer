# LexicalAnalyzer
A lexical analyzer in C that identifies and classifies tokens from C source files.
# Project Overview
This project implements a Lexical Analyzer in C that reads a C source file and identifies and classifies its tokens. It scans the input character by character and categorizes tokens into keywords, identifiers, constants, operators, special characters, comments, string literals, and preprocessor directives.
# Features
Identifies C keywords such as int, char, if, while, and return.
Recognizes identifiers and numeric constants.
Detects arithmetic, relational, logical, and other operators.
Identifies special characters such as braces, parentheses, brackets, commas, and semicolons.
Recognizes single-line and multi-line comments.
Handles string literals and character constants.
Detects preprocessor directives such as #include.
Reports unknown tokens.
Reads the input C file through command-line arguments.
# Sample Input
```c
#include <stdio.h>
int main()
{
    int a = 10;
    float b = 3.14;
    if (a >= 10)
    {
        printf("Hello World\n");
    }
    return 0;
}
```
# Expected Output
The output lists each recognized token alongside its category.
```c
Preprocessor         :  #include
Relational Operator  :  <
Identifier           :  stdio
Special Character    :  .
Identifier           :  h
Relational Operator  :  >
Keyword              :  int
Identifier           :  main
L_Paren              :  (
R_Paren              :  )
L_Brace              :  {
Keyword              :  int
Identifier           :  a
Assignment Operator  :  =
Int Constant         :  10
Special Character    :  ;
Keyword              :  float
Identifier           :  b
Assignment Operator  :  =
Float Constant       :  3.14
Special Character    :  ;
Keyword              :  if
L_Paren              :  (
Identifier           :  a
Relational Operator  :  >=
Int Constant         :  10
R_Paren              :  )
L_Brace              :  {
Identifier           :  printf
L_Paren              :  (
Literal              :  "Hello World\n"
R_Paren              :  )
Special Character    :  ;
R_Brace              :  }
Keyword              :  return
Int Constant         :  0
Special Character    :  ;
R_Brace              :  }
Tokens generated.
```
# Author
Soundharya Lahari Uppula
