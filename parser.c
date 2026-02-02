#include <stdio.h>
#include <ctype.h>
#include <string.h>

void tokenize(FILE *fp)
{
    char ch;
    char buffer[50];
    int i;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch))
            continue;

        if (isalpha(ch))
        {
            i = 0;
            buffer[i++] = ch;

            while (isalnum(ch = fgetc(fp)))
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            ungetc(ch, fp);

            if (strcmp(buffer, "int") == 0 || strcmp(buffer, "print") == 0)
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
        }

        else if (isdigit(ch))
        {
            i = 0;
            buffer[i++] = ch;

            while (isdigit(ch = fgetc(fp)))
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            ungetc(ch, fp);

            printf("Number: %s\n", buffer);
        }

        else if (ch == '=' || ch == '+')
        {
            printf("Operator : %c\n", ch);
        }

        else if (ch == ';' || ch == '(' || ch == ')')
        {
            printf("SYMBOL: %c\n", ch);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc != 2)
    {
        printf("Usage: ./parser inputfile\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("Error opening file\n");
        return 1;
    }

    tokenize(fp);
    fclose(fp);
    return 0;
}
