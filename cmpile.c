
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void"};

int isKeyword(char word[])
{
    for (int i = 0; i < 9; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main()
{
    FILE *file;
    char ch, word[20];
    int i;

    file = fopen("input.c", "r");
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        return 1;
    }

    printf("Lexical Analysis Output:\n");

    while ((ch = fgetc(file)) != EOF)
    {
        // For identifiers and keywords
        if (isalpha(ch))
        {
            i = 0;
            while (isalnum(ch))
            {
                word[i++] = ch;
                ch = fgetc(file);
            }
            word[i] = '\0';
            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
            ungetc(ch, file); // put back last character
        }

        // For operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>')
        {
            printf("Operator: %c\n", ch);
        }
    }

    fclose(file);
    return 0;
}
