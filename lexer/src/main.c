#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./lexer.c"
#include "./parser.c"

int main(void)
{
    char *source = "let x = 1 + 2;";

    List *list = Tokens(source);

    Parser parser;
    parser.tokens = list->data;
    parser.current = 0;

    parse_statement(&parser);

    free(parser.tokens);
    printf("Completed\n");

    return 0;
}
