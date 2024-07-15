#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>

#define ELEMENT_NUMBERS 1

void list_all_files(char *directory);
void create_file(char *filename);
char *read_file(char *filename);
void read_file_to_buffer(char *filename, char *buffer, int readSize);
void write_to_file(char *file, char *data);
void delete_file(char *filename);
void rename_file(char *oldFileName, char *newFileName);

int main(void)
{
    list_all_files("."); //List all files in current folder
    printf("%s\n", read_file("README.md"));
    return(0);
}

void create_file(char *filename){
    FILE *fp;
	fp = fopen(filename, "w+");
	if (fp == NULL) {
		printf("Unable to create file");
	}
	else {
        printf("File create successfully");
        fclose(fp);
	}	
}

char *read_file(char *filename){
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp != NULL) {
        fseek(fp, 0L, SEEK_END);//Set file position from index 0 to the end of file
        long file_size = ftell(fp);//Then get the file size
        fseek(fp, 0L, SEEK_SET);//Return file position back to the beginning

        char *buffer;
        buffer = (char *) malloc(file_size);
        bzero(buffer, file_size);//delete garbage value

        fread(buffer, file_size, ELEMENT_NUMBERS, fp);//Will read ELEMENT_NUMBERS*file_size from fp
        fclose(fp);
        return buffer;
   } else {
       printf("Unable to open file %s", filename);
       return "NULL";
    }
}

void read_file_to_buffer(char *filename, char *buffer, int readSize){
    FILE *fp;

    fp = fopen(filename, "r");

    fread(buffer, readSize, 1, fp); //set element number to 1 to read readSize bytes
    printf("%s\n", buffer);
    fclose(fp);
}

void write_to_file(char *file, char *data){
    FILE *fp;
	fp = fopen(file, "w+");
	if (fp == NULL) {
		printf("Unable to open file");
	}
	else {
		fputs(data, fp);
		fclose(fp);
	}	
}

void delete_file(char *filename){
    if (!remove(filename)) printf("Delete file successfully");
    else printf("Unable to delete the file");
}

void rename_file(char *oldFileName, char *newFileName){
    if (!rename(oldFileName, newFileName)) printf("Rename file sucessfully\n");
    else printf("Unable to rename file\n");
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
