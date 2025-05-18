#include "../include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Token make_token(TokenType type, const char *value)
{
    Token token;
    token.type = type;
    token.value = strdup(value);
    return token;
}

List *Tokens(char *source)
{
    List *list = malloc(sizeof(List));
    // char *source = "let x = (1 + 2);";

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

            list->data[list->size++] = make_token(Number, data);
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
                list->data[list->size++] = make_token(Keyword, data);
            else
                list->data[list->size++] = make_token(Identifier, data);

            free(data);
        }
        else if (*source == '+')
        {
            list->data[list->size++] = make_token(Plus, "+");
            source++;
        }
        else if (*source == '=')
        {
            list->data[list->size++] = make_token(Equals, "=");
            source++;
        }
        else if (*source == '(')
        {
            list->data[list->size++] = make_token(OPEN_PAREN, "(");
            source++;
        }
        else if (*source == ')')
        {
            list->data[list->size++] = make_token(CLOSE_PAREN, ")");
            source++;
        }
        else if (*source == ';')
        {
            list->data[list->size++] = make_token(SEMICOLON, ";");
            source++;
        }
        else
        {
            source++;
        }
    }

    return list;
}
