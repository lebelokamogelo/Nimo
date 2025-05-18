#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./lexer.c"

int main(void)
{
    // char source[] = "let x = (1 + 2);";

    List *list = Tokens();

    for (int i = 0; i < list->size; i++)
    {
        printf("Token[%d] -> %s\n", i, list->data[i].value);
    }

    return 0;
}
