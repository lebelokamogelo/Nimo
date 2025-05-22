#include "../include/parser.h"
#include <stdio.h>

Token current_token(Parser *parser)
{
    if (parser->current >= parser->size)
    {
        return (Token){.type = TOKEN_EOF, .value = NULL};
    }
    return parser->tokens[parser->current];
}

void advance(Parser *parser)
{
    parser->current++;
}

void expect(Parser *parser, TokenType type)
{
    Token token = current_token(parser);
    if (token.type == type)
    {
        advance(parser);
    }
    else
    {
        printf("Error: Expected token type %d, got %d\n", type, token.type);
        exit(1);
    }
}

ASTNode *create_ast_op(char *operator, ASTNode * left, ASTNode *right)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = TOKEN_PLUS;
    node->value = operator;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *create_number_node(Parser *parser)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = TOKEN_NUMBER;
    node->value = current_token(parser).value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

ASTNode *parse_term(Parser *parser)
{

    ASTNode *node = create_number_node(parser);
    printf("%s\n", node->value);

    if (node->type == TOKEN_NUMBER || node->type == TOKEN_IDENTIFIER)
    {
        advance(parser);
        Token node_bin = current_token(parser);
        if (node_bin.value == NULL)
            return node;

        else if (node_bin.type == TOKEN_SEMICOLON)
            return node;

        printf("%s\n", node_bin.value);
    }
    else if (node->type == TOKEN_LPAREN)
    {
        advance(parser);
        parse_expression(parser);
        expect(parser, TOKEN_RPAREN);
    }
    else
    {
        fprintf(stderr, "Error: Expected NUMBER, IDENTIFIER, or LPAREN, got %d\n", node->type);
        exit(1);
    }

    return node;
}

ASTNode *parse_expression(Parser *parser)
{
    ASTNode *node = parse_term(parser);
    Token token = current_token(parser);
    while (token.type == TOKEN_PLUS)
    {
        advance(parser);
        parse_term(parser);
        token = current_token(parser);
    }
    return node;
}

void parse_statement(Parser *parser)
{
    expect(parser, TOKEN_LET);
    expect(parser, TOKEN_IDENTIFIER);
    expect(parser, TOKEN_EQUALS);
    parse_expression(parser);
    // expect(parser, TOKEN_SEMICOLON);
}