#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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
        strtok(line,",");
        parameter_2 = strtok (NULL, ",");
        printf("%s\n", parameter_2);
    }

   	free(line);
    exit(EXIT_SUCCESS);
}

/*
    List all files inside a directory
*/
void list_all_files(char *directory){
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}