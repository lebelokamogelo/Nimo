#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *source = "let x = (1 + 2);";

    while (*source != '\0')

    {
        if (*source == ' ')
        {
            source++;
            continue;
        }
        else if (isdigit(*source))
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

            printf("Number: %s\n", data);
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
            {
                printf("Keyword: %s\n", data);
            }
            else
            {
                printf("Identifier: %s\n", data);
            }

            free(data);
        }
        else if (*source == '+')
        {
            printf("Plus: +\n");
            source++;
        }
        else if (*source == '=')
        {
            printf("Equals: =\n");
            source++;
        }
        else if (*source == '(')
        {
            printf("Open Paren: (\n");
            source++;
        }
        else if (*source == ')')
        {
            printf("Close Paren: )\n");
            source++;
        }
        else if (*source == ';')
        {
            printf("Semicolon: ;\n");
            source++;
        }

        else
        {
            printf("Unknown token: %c\n", *source);
            source++;
        }
    }

    return 0;
}
