#include "lexer.h"
static const char *keywords[MAX_KEYWORDS] = {"int", "float", "return", "if", "else", "while", "for", 
    "do", "break", "continue", "union", "enum", "goto","char", "double", "void", "switch", "case", 
    "default", "const", "static", "sizeof", "struct", "typedef","auto", "extern", "volatile", 
    "signed", "unsigned", "short", "long", "register"};

static const char *operators = "+-*/%=!<>|&^~?:";
static const char *specialCharacters = ".,;{}()[]";
static FILE *fptr = NULL;

int initializeLexer(int argc, char *argv[])
{
    // If file is not passed error
    if(argc!=2)
    {
        printf("Invalid Arguments\n");
        return FAILURE;
    }
    // Check the file is .c file or not
    int flag=1;
    char *ptr=strstr(argv[1], ".c");
    if(ptr!=NULL)
    {
        if(strcmp(ptr,".c")==0)
        {
            if(argv[1][0]!='.')
            {
                flag=0;
            }
        }
    }
    // If file is not .c return error
    if(flag)
    {
        printf("Invalid Filename\n");
        return FAILURE;
    }
    // open the file in read mode
    fptr=fopen(argv[1], "r");
    if(fptr==NULL)
    {
        printf("File is Not present\n");
        return FAILURE;
    }
    // Check if the file is empty or not
    char ch=fgetc(fptr);
    if(ch==EOF)
    {
        fclose(fptr);
        printf("File is empty\n");
        return FAILURE;
    }
    // If not empty rewind offset 
    rewind(fptr);
    return SUCCESS;
}
// Function to return separate token
Token getNextToken()
{
    // Declare variable
    Token token;
    char str[MAX_TOKEN_SIZE];
    char ch=fgetc(fptr);
    int i=0;
    // Run a loop untill EOF
    while(ch!=EOF)
    {
        // Check ch is alphabet or underscore
        if(isalpha(ch) || ch=='_')
        {
            // Run a loop to store character
            while(isalnum(ch) || ch=='_')
            {
                str[i++]=ch;
                ch=fgetc(fptr);
            }
            // Move 1byte back
            if(ch!=EOF)
            {
                fseek(fptr, -1, SEEK_CUR);
            }
        }
        // Check it is digit
        else if(isdigit(ch))
        {
            int dot = 0;
            // Run a loop to store all digit
            while(isdigit(ch) || (ch=='.' && dot==0))
            {
                if (ch=='.')
                {
                    dot=1;
                }
                str[i++]=ch;
                ch=fgetc(fptr);
            }
            // Move 1byte back
            if (ch!=EOF)
            {
                fseek(fptr, -1, SEEK_CUR);
            }
        }
        // not a digit or alphabet
        else
        {
            // If i>0 a string is stored
            if (i>0)
            {
                // Set null character at last
                str[i] = '\0';
                // If ch is not space move 1byte back
                if(!isspace(ch))
                {
                    fseek(fptr, -1, SEEK_CUR);
                }
                // Check str is a keyword
                if(isKeyword(str)==SUCCESS)
                {
                    // Update the structure
                    strcpy(token.lexeme, str);
                    token.type=KEYWORD;
                }
                // Check str is a constant
                else if (isConstant(str) == SUCCESS)
                {
                    // Update the structure
                    strcpy(token.lexeme, str);
                    token.type = CONSTANT;
                }
                // Check str is a identifier
                else if (isIdentifier(str) == SUCCESS)
                {
                    // Update the structure
                    strcpy(token.lexeme, str);
                    token.type = IDENTIFIER;
                }
                // else update unknown
                else
                {
                    strcpy(token.lexeme, str);
                    token.type = UNKNOWN;
                }
                return token;
            }
            // check it is space
            if (isspace(ch))
            {
                ch=fgetc(fptr);
                continue;
            }
            // if ch is # update the str
            if(ch=='#')
            {
                i = 0;
                str[i++] = ch;
                ch = fgetc(fptr);
                while (isalpha(ch))
                {
                    str[i++] = ch;
                    ch = fgetc(fptr);
                }
                str[i] = '\0';
                strcpy(token.lexeme, str);
                token.type = PREPROCESSOR;
                if (ch != EOF)
                {
                    fseek(fptr, -1, SEEK_CUR);
                }
                return token;
            }
            /* Check for character literal */
            if (ch == '\'')
            {
                i = 0;
                str[i++] = ch;
                ch = fgetc(fptr);
                /* Read character literal */
                if (ch == '\\')
                {
                    str[i++] = ch;
                    ch = fgetc(fptr);
                    if (ch != EOF && ch != '\n')
                    {
                        str[i++] = ch;
                        ch = fgetc(fptr);
                    }
                }
            else if (ch != EOF && ch != '\'' && ch != '\n')
            {
                str[i++] = ch;
                ch = fgetc(fptr);
            }
            /* Check closing single quote */
            if (ch == '\'')
            {
                str[i++] = ch;
                str[i] = '\0';
                strcpy(token.lexeme, str);
                token.type = CONSTANT;
                return token;
            }
            /* Invalid character literal */
            str[i] = '\0';
            strcpy(token.lexeme, str);
            token.type = UNKNOWN;
            return token;
            }
            // check for string
            if(ch=='"')
            {
                i=0;
                str[i++]=ch;
                ch=fgetc(fptr);
                // Run a loop to store string
                while (ch != '"' && ch != EOF && ch != '\n')
                {
                    str[i++]=ch;
                    ch=fgetc(fptr);
                }
                if (ch != '"')
                {
                    str[i] = '\0';
                    strcpy(token.lexeme, str);
                    token.type = UNKNOWN;
                    return token;
                }
                str[i++] = '"';
                str[i] = '\0';
                // Update structure 
                strcpy(token.lexeme, str);
                token.type = STRING_LITERAL;
                return token;
            }
            // Check it is operator
            if (isOperator(ch) == SUCCESS)
            {
                char next=fgetc(fptr);
                // Check for single line comment
                if (ch=='/' && next == '/')
                {
                    i=0;
                    str[i++]=ch;
                    str[i++]=next;
                    ch=fgetc(fptr);
                    while (ch!='\n' && ch!=EOF)
                    {
                        str[i]=ch;
                        i++;
                        ch=fgetc(fptr);
                    }
                    // Update the structure
                    str[i]='\0';
                    strcpy(token.lexeme, str);
                    token.type = SCOMMENT;
                    return token;
                }
                // Check for multi comment
                if (ch == '/' && next == '*')
                {
                    i=0;
                    str[i++]=ch;
                    str[i++]=next;
                    char prev=0;
                    ch=fgetc(fptr);
                    while (ch!=EOF)
                    {
                        if(ch!='\n' && ch!='\r')
                        {
                            str[i]=ch;
                            i++;
                        }
                        if (prev=='*' && ch=='/')
                        {
                            break;
                        }
                        prev=ch;
                        ch=fgetc(fptr);
                    }
                    // Update the structure
                    str[i] = '\0';
                    strcpy(token.lexeme, str);
                    token.type = MCOMMENT;
                    return token;
                }
                // Check for postfix,prefix, logical operator
                if ((ch == '+' && next == '+') || (ch == '-' && next == '-') || 
                    (ch == '=' && next == '=') || (ch == '!' && next == '=') ||
                    (ch == '>' && next == '=') || (ch == '<' && next == '=') || 
                    (ch == '&' && next == '&') || (ch == '|' && next == '|'))
                {
                    // Update the token as operator
                    token.lexeme[0] = ch;
                    token.lexeme[1] = next;
                    token.lexeme[2] = '\0';
                    token.type = OPERATOR;
                    return token;
                }
                // Move 1 byte back and update the operator
                fseek(fptr, -1, SEEK_CUR);
                token.lexeme[0] = ch;
                token.lexeme[1] = '\0';
                token.type = OPERATOR;
                return token;
            }
            // If it is a specialcharacter update structure
            if (isSpecialCharacter(ch) == SUCCESS)
            {
                token.lexeme[0] = ch;
                token.lexeme[1] = '\0';
                token.type = SPECIAL_CHARACTER;
                return token;
            }
            // Else return unknown
            else
            {
                token.lexeme[0] = ch;
                token.lexeme[1] = '\0';
                token.type = UNKNOWN;
                return token;
            }
        }
        ch=fgetc(fptr);
    }
    // If str is filled
    if(i>0)
    {
        // Add null at last
        str[i]='\0';
        // check the function and update the structure
        if(isKeyword(str) == SUCCESS)
        {
            token.type = KEYWORD;
        }
        else if(isConstant(str) == SUCCESS)
        {
            token.type = CONSTANT;
        }
        else if(isIdentifier(str) == SUCCESS)
        {
            token.type = IDENTIFIER;
        }
        else
        {
            token.type = UNKNOWN;
        }
        strcpy(token.lexeme, str);
        return token;
    }
    // If EOF return structure as ENDFILE
    if (ch == EOF)
    {
        fclose(fptr);
        token.type = ENDFILE;
        token.lexeme[0] = '\0';
        return token;
    }
}
// Function to check constant
int isConstant(char *str)
{
    int i=0,dot=0;
    // Run a loop to check for digit
    while(str[i])
    {
        if(isdigit(str[i]))
        {
            i++;
        }
        else if(str[i]=='.')
        {
            if(dot)
            {
                return FAILURE;
            }
            dot=1;
            i++;
        }
        else
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}
// Check it is identifier
int isIdentifier(char *str)
{
    int i=0;
    if(str[i]=='_' || isalpha(str[i]))
    {
        i++;
    }
    else
    {
        return FAILURE;
    }
    // Run a loop to check identifier 
    while(str[i])
    {
        if (!(isalnum(str[i]) || str[i] == '_'))
        {
            return FAILURE;
        }
        i++;
    }
    return SUCCESS;
}
// Function to check keyword
int isKeyword(char *str)
{
    // Run a loop an check in keyword array
    for (int i=0;i<MAX_KEYWORDS;i++)
    {
        if(strcmp(str,keywords[i])==0)
        {
            return SUCCESS;
        }
    }
    return FAILURE;
}
// Function to check Specialcharacter
int isSpecialCharacter(char ch)
{
    // Check in the specialcharacter string
    if(strchr(specialCharacters,ch))
    {
        return SUCCESS;
    }
    return FAILURE;
}
// Function to check operator
int isOperator(char ch)
{
    // Check in the operator string
    if(strchr(operators,ch))
    {
        return SUCCESS;
    }
    return FAILURE;
}