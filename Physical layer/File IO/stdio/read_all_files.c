#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char **file_name_array;

int total_files = 0;
int file_index = 0;

int main()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //Doesn't count . and .. as files
            if (!strcmp(".", dir->d_name)) continue;
            if (!strcmp("..", dir->d_name)) continue;
            total_files += 1;
        }  
    }

    printf("total files %d\n", total_files);
    closedir(d);

    d = opendir("."); //Open dir again to read all files
    file_name_array = (char**) malloc(total_files * sizeof(char*));


    while ((dir = readdir(d)) != NULL)
    {
        if (file_index > total_files) break;

        //Doesn't count . and .. as files
        if (!strcmp(".", dir->d_name)) continue;
        if (!strcmp("..", dir->d_name)) continue;

        file_name_array[file_index] =  dir->d_name;
        file_index += 1;
    }

    for (int i=0; i < total_files; i++){
		printf("%s \n", file_name_array[i]);
	}
}