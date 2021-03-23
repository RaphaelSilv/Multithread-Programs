#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*                          984       1       149       55           0       */
char keywords[5][50] = {"jesus", "Lucifer", "Maria", "hell", "inquisitiveness"};
char occurrences[5];

int count_occurrences(char *linha, char *palavra)
{
    char temp[100] = "";
    int occurrences = 0;

    for (int i = 0; linha[i] != '\0'; i++)
    {

        if (linha[i] == ' ')
        {
            temp[0] = '\0';
        }
        else
        {
            size_t len = strlen(temp);
            temp[len] = linha[i];
            temp[len + 1] = '\0';

            if (strcmp(temp, palavra) == 0)
            {
                occurrences++;
            }
        }
    }
    return occurrences;
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "please, enter the file name and the num of lines. %s", argv[0]);
        return 1;
    }

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    const char *fileName = argv[1];
    int numLines = atoi(argv[2]);

    fp = fopen(fileName, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while (read = getline(&line, &len, fp) != -1 && numLines > 0)
    {

        for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        {
            int count = 0;
            count += count_occurrences(line, keywords[i]);
            occurrences[i] += count;
        }

        numLines--;
    }

    return 0;
}
