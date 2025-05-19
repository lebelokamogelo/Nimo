#include "../include/parser.h"
#include <stdio.h>

Token current_token(Parser *parser)
{
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

void parse_term(Parser *parser)
{
    Token token = current_token(parser);
    if (token.type == TOKEN_NUMBER || token.type == TOKEN_IDENTIFIER)
    {
        advance(parser);
    }
    else if (token.type == TOKEN_LPAREN)
    {
        advance(parser);
        parse_expression(parser);
        expect(parser, TOKEN_RPAREN);
    }
    else
    {
        fprintf(stderr, "Error: Expected NUMBER, IDENTIFIER, or LPAREN, got %d\n", token.type);
        exit(1);
    }
}

void parse_expression(Parser *parser)
{
    parse_term(parser);
    Token token = current_token(parser);
    while (token.type == TOKEN_PLUS)
    {
        advance(parser);
        parse_term(parser);
        token = current_token(parser);
    }
}

void parse_statement(Parser *parser)
{
    expect(parser, TOKEN_LET);
    expect(parser, TOKEN_IDENTIFIER);
    expect(parser, TOKEN_EQUALS);
    parse_expression(parser);
    expect(parser, TOKEN_SEMICOLON);
}