#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct
{
    Token *tokens;
    int current;
} Parser;

typedef enum
{
    AST_LET,
    AST_BINARY,
    AST_NUMBER,
    AST_IDENTIFIER
} ASTNodeType;

typedef struct ASTNode
{
    ASTNodeType type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

#include "../include/parser.h"
#include <stdio.h>

Token current_token(Parser *parser);
void advance(Parser *parser);
void expect(Parser *parser, TokenType type);

void parse_term(Parser *parser);
void parse_expression(Parser *parser);
void parse_statement(Parser *parser);

#endif