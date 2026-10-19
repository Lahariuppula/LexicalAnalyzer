#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE 1

#define MAX_KEYWORDS 32
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    STRING_LITERAL,
    SCOMMENT,
    MCOMMENT,
    ENDFILE,
    PREPROCESSOR,
    UNKNOWN
} TokenType;

typedef struct 
{
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

// Function Prototype
int initializeLexer(int ,char **);
Token getNextToken();
int isKeyword(char* str);
int isOperator(char );
int isSpecialCharacter(char );
int isConstant(char* );
int isIdentifier(char* str);

#endif