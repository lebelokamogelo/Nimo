#include "../include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Token create_token(TokenType type, const char *value)
{
    Token token;
    token.type = type;
    token.value = value ? strdup(value) : NULL;
    ;
    return token;
}

List *Tokens(char *source)
{
    List *list = malloc(sizeof(List));

    list->capacity = 4;
    list->size = 0;
    list->data = malloc(list->capacity * sizeof(Token));

    while (*source != '\0')
    {
        if (*source == ' ')
        {
            source++;
            continue;
        }

        if (list->size >= list->capacity)
        {
            list->capacity *= 2;
            list->data = realloc(list->data, list->capacity * sizeof(Token));
        }

        if (isdigit(*source))
        {
            int capacity = 4;
            char *data = malloc(capacity * sizeof(char));
            int index = 0;
            while (isdigit(*source))
            {
                if (index >= capacity)
                {
                    capacity *= 2;
                    data = realloc(data, capacity * sizeof(char));
                }
                data[index++] = *source;
                source++;
            }
            data[index] = '\0';

            list->data[list->size++] = create_token(TOKEN_NUMBER, data);
            free(data);
        }
        else if (isalpha(*source))
        {
            int capacity = 4;
            char *data = malloc(capacity * sizeof(char));
            int index = 0;

            while (isalpha(*source) || isdigit(*source) || *source == '_')
            {
                if (index >= capacity)
                {
                    capacity *= 2;
                    data = realloc(data, capacity * sizeof(char));
                }
                data[index++] = *source;
                source++;
            }

            data[index] = '\0';

            if (strcmp(data, "let") == 0)
                list->data[list->size++] = create_token(TOKEN_LET, data);
            else
                list->data[list->size++] = create_token(TOKEN_IDENTIFIER, data);

            free(data);
        }
        else if (*source == '+')
        {
            list->data[list->size++] = create_token(TOKEN_PLUS, "+");
            source++;
        }
        else if (*source == '=')
        {
            list->data[list->size++] = create_token(TOKEN_EQUALS, "=");
            source++;
        }
        else if (*source == '(')
        {
            list->data[list->size++] = create_token(TOKEN_LPAREN, "(");
            source++;
        }
        else if (*source == ')')
        {
            list->data[list->size++] = create_token(TOKEN_RPAREN, ")");
            source++;
        }
        else if (*source == ';')
        {
            list->data[list->size++] = create_token(TOKEN_SEMICOLON, ";");
            source++;
        }
        else
        {
            source++;
        }
    }

    list->data[list->size] = create_token(TOKEN_EOF, NULL);
    return list;
}
