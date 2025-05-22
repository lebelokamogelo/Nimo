#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct
{
    Token *tokens;
    int current;
    int size;
} Parser;

typedef struct ASTNode
{
    TokenType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

#include "../include/parser.h"
#include <stdio.h>

Token current_token(Parser *parser);
void advance(Parser *parser);
void expect(Parser *parser, TokenType type);

ASTNode *parse_term(Parser *parser);
ASTNode *parse_expression(Parser *parser);
void parse_statement(Parser *parser);

#endif