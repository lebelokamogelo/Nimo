#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./lexer.c"
#include "./parser.c"

int eval(ASTNode *node)
{
    if (node->type == TOKEN_NUMBER)
    {
        return atoi(node->value);
    }
    return eval(node->left) + eval(node->right);
}

int main(void)
{
    char *source = "let x = 1 + (2 + 3);";

    List *list = Tokens(source);

    Parser parser;
    parser.tokens = list->data;
    parser.size = list->size;
    parser.current = 0;

    ASTNode *node = parse_statement(&parser);

    int result = eval(node);

    printf("The result is %d\n", result);

    free(parser.tokens);
    printf("Completed\n");

    return 0;
}