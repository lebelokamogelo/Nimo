#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType
{
    TOKEN_LET,
    TOKEN_IDENTIFIER,
    TOKEN_EQUALS,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

typedef struct
{
    int size;
    int capacity;
    Token *data;
} List;

List *Tokens(char *source);

#endif