#ifndef LEXER_H
#define LEXER_H

typedef enum TokenType
{
    Number,
    Identifier,
    Keyword,
    Equals,
    Plus,
    OPEN_PAREN,
    CLOSE_PAREN,
    SEMICOLON,
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

List *Tokens();

#endif