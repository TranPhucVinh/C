#include <stdio.h>
#include <dirent.h>

void listAllFile(char *directory);
void createFile(char *filename);
void readFile(char *filename);
void writeToFile(char *file, char *data);
void deleteFile(char *filename);

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