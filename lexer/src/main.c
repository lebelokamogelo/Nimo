#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./lexer.c"
#include "./parser.c"

void print_ast(ASTNode *node)
{

    if (node == NULL)
    {
        return;
    }
    print_ast(node->left);
    printf("%s\n", node->value);
    print_ast(node->right);
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

    print_ast(node);

    free(parser.tokens);
    printf("Completed\n");

    return 0;
}