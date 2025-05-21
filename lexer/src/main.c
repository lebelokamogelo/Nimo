#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./lexer.c"
#include "./parser.c"

ASTNode *parse_1_plus_2(Token *tokens);
int ast_current_index = 0;

// print the AST in prefix notation
void print_ast(ASTNode *node)
{
    if (node == NULL)
        return;
    printf("%s\n", node->value);
    print_ast(node->left);
    print_ast(node->right);
}

int main(void)
{
    char *source = "let x = 1 + 2;";

    List *list = Tokens(source);

    Token tokens[5];

    Parser parser;
    parser.tokens = list->data;
    parser.current = 0;

    parse_statement(&parser);

    free(parser.tokens);
    printf("Completed\n");

    tokens[0] = (Token){.type=TOKEN_NUMBER, .value="1"};
    tokens[1] = (Token){.type=TOKEN_PLUS, .value="+"};
    tokens[2] = (Token){.type=TOKEN_NUMBER, .value="2"};
    tokens[3] = (Token){.type=TOKEN_PLUS, .value="+"};
    tokens[4] = (Token){.type=TOKEN_NUMBER, .value="3"};
    
    // Writing a simple parser
    ASTNode *ast = parse_1_plus_2(tokens);

    print_ast(ast);
    

    return 0;
}

ASTNode *create_ast_op(char *operator, ASTNode *left, ASTNode *right)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_BINARY;
    node->value = operator;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *parse_1_plus_2(Token *tokens)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->value = tokens[ast_current_index].value;
    node->left = NULL;
    node->right = NULL;
    ast_current_index++;

    while (ast_current_index < 5 && tokens[ast_current_index].type == TOKEN_PLUS)
    {
        char *operator = tokens[ast_current_index].value;
        ast_current_index++;
        ASTNode *right = parse_1_plus_2(tokens);
        
        node = create_ast_op(operator, node, right);
    }
    return node;
}

