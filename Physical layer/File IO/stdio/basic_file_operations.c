#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#define ELEMENT_NUMBERS 1

void listAllFile(char *directory);
void createFile(char *filename);
char *readFile(char *filename);
void readFileToBuffer(char *filename, char *buffer, int readSize);
void writeToFile(char *file, char *data);
void deleteFile(char *filename);
void renameFile(char *oldFileName, char *newFileName);

int main(void)
{
   printf("%s\n", readFile("README.md"));
   return(0);
}

void createFile(char *filename){
    FILE *fptr;
	fptr = fopen(filename, "w+");
	if (fptr == NULL) {
		printf("Unable to create file");
	}
	else {
        printf("File create successfully");
        fclose(fptr);
	}	
}

char *readFile(char *filename){
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp != NULL) {
        fseek(fp, 0L, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        static char *buffer;
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

void readFileToBuffer(char *filename, char *buffer, int readSize){
    FILE *fp;

    fp = fopen(filename, "r");

    fread(buffer, readSize, 1, fp); //set element number to 1 to read readSize bytes
    printf("%s\n", buffer);
    fclose(fp);
}

void writeToFile(char *file, char *data){
    FILE *fptr;
	fptr = fopen(file, "w+");
	if (fptr == NULL) {
		printf("Unable to open file");
	}
	else {
		fputs(data, fptr);
		fclose(fptr);
	}	
}

void deleteFile(char *filename){
    if (!remove(filename)) printf("Delete file successfully");
    else printf("Unable to delete the file");
}

void renameFile(char *oldFileName, char *newFileName){
    if (!rename(oldFileName, newFileName)) printf("Rename file sucessfully\n");
    else printf("Unable to rename file\n");
}

/*
    List all files inside a directory
*/
void listAllFile(char *directory){
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