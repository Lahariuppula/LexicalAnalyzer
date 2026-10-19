#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) 
{
    
    // Validate the file from command line argument
    if(initializeLexer(argc,argv)==FAILURE)
    {
        printf("Usage: <lexer.out> <filename>\n");
        return FAILURE;
    }

    Token token;

    // call function getnexttoken and get a token
    while ((token = getNextToken()).type != ENDFILE) 
    {
        if (token.type == UNKNOWN)
        {
            printf(" Error: '%s'\n", token.lexeme);
            printf("Tokens cannot be generated.\n");
            return FAILURE;
        }
        switch(token.type)
        {
            // If token is keyword
            case KEYWORD:
                        printf("%-20s :  ","Keyword");
                        break;

            // If token is Operator
            case OPERATOR:
                        if (strcmp(token.lexeme, "=") == 0)
                        {
                            printf("%-20s :  ", "Assignment Operator");
                        }
                        else if (strcmp(token.lexeme, "<") == 0 ||strcmp(token.lexeme, ">") == 0 ||
                                 strcmp(token.lexeme, "<=") == 0||strcmp(token.lexeme, ">=") == 0 ||
                                 strcmp(token.lexeme, "==") == 0||strcmp(token.lexeme, "!=") == 0)
                        {
                            printf("%-20s :  ", "Relational Operator");
                        }
                        else if (strcmp(token.lexeme, "&&") == 0 || strcmp(token.lexeme, "||") == 0 ||
                                  strcmp(token.lexeme, "!") == 0)
                        {
                            printf("%-20s :  ", "Logical Operator");
                        }
                        else if (strcmp(token.lexeme, "+") == 0 || strcmp(token.lexeme, "-") == 0 ||
                                strcmp(token.lexeme, "*") == 0 || strcmp(token.lexeme, "/") == 0 ||
                                strcmp(token.lexeme, "%") == 0)
                        {
                            printf("%-20s :  ", "Arithmetic Operator");
                        }
                        else if (strcmp(token.lexeme, "++") == 0)
                        {
                            printf("%-20s :  ", "Inc Operator");
                        }
                        else if(strcmp(token.lexeme, "--") == 0)
                        {
                        printf("%-20s :  ", "Dec Operator");
                        }
                        else
                        {
                            printf("%-20s :  ", "Operator");
                        }
                        break;

            // If token is Special Character
            case SPECIAL_CHARACTER:
                        if (strcmp(token.lexeme, "{") == 0)
                        {
                            printf("%-20s :  ", "L_Brace");
                        }
                        else if (strcmp(token.lexeme, "}") == 0)
                        {
                            printf("%-20s :  ", "R_Brace");
                        }
                        else if (strcmp(token.lexeme, "(") == 0)
                        {
                            printf("%-20s :  ", "L_Paren");
                        }
                        else if (strcmp(token.lexeme, ")") == 0)
                        {
                            printf("%-20s :  ", "R_Paren");
                        }
                        else if (strcmp(token.lexeme, "[") == 0)
                        {
                            printf("%-20s :  ", "L_Bracket");
                        }
                        else if (strcmp(token.lexeme, "]") == 0)
                        {
                            printf("%-20s :  ", "R_Bracket");
                        }
                        else
                        {
                            printf("%-20s :  ", "Special Character");
                        }
                        break;

            // If token is Constant
            case CONSTANT:
                        if (strchr(token.lexeme, '\'') != NULL)
                        {
                            printf("%-20s :  ", "Char Constant");
                        }
                        else if (strchr(token.lexeme, '.') != NULL)
                        {
                            printf("%-20s :  ", "Float Constant");
                        }
                        else
                        {
                            printf("%-20s :  ", "Int Constant");
                        } 
                        break;

            // If token is Identifier
            case IDENTIFIER:
                        printf("%-20s :  ","Identifier");
                        break;

            // If token is Single comment
            case SCOMMENT:
                        printf("%-20s :  ","scomment");
                        break;

            // If token is Multi Comment
            case MCOMMENT:
                        printf("%-20s :  ","mcomment");
                        break;

            // If token is Preprocessor
            case PREPROCESSOR:
                        printf("%-20s :  ","Preprocessor");
                        break;

            // If token is String 
            case STRING_LITERAL:
                        printf("%-20s :  ","Literal");
                        break;

            // Print Invalid token
            default:
                        printf("%-20s :  ","INVALID_TOKEN");
        }

        // Print the token
        printf("%s\n",token.lexeme);
    }

    printf("Tokens generated.\n");
    return 0;
}