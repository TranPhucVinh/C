#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char **file_name_array;

int get_total_files(char *folder_name);
char **form_file_name_array(char *folder_name, int total_files);

int main()
{
    int total_files = get_total_files(".");
    file_name_array = form_file_name_array(".", total_files);
    for (int i=0; i < total_files; i++){
		printf("%s \n", file_name_array[i]);
	}
}

int get_total_files(char *folder_name){
    int total_files = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(folder_name);
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

    closedir(d);
    return total_files;
}

char **form_file_name_array(char *folder_name, int total_files){
    char **file_name_array;
    DIR *d;
    struct dirent *dir;
    
    int file_index = 0;

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

    return file_name_array;
}