#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

	int total_line = 0;

    char *parameter_2;

   	fp = fopen("database.txt", "r");
    if (!fp)
        exit(EXIT_FAILURE);

	while (getline(&line, &len, fp) != -1) {
        parameter_2 = strtok(line,",");
        parameter_2 = strtok (NULL, ",");
        printf("%s", parameter_2);
    }

   	free(line);
    exit(EXIT_SUCCESS);
}