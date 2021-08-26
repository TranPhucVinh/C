#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define READ_SIZE   50

void listAllFile(char *directory);
void createFile(char *filename);
void readFile(char *filename);
void readFileToBuffer(char *filename, char *buffer, int readSize);
void writeToFile(char *file, char *data);
void deleteFile(char *filename);
void renameFile(char *oldFileName, char *newFileName);

int main(void)
{
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

void readFile(char *filename){
    FILE *fptr; //file pointer
    char c;

    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL){
        printf("Cannot open file \n");
        return;
    }

    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF){
        printf("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
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