#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define FALSE 0
#define TRUE 1

//author Tomás Alves 68681 e Luis Martins 68473

long long getFileSize( char *fileName );
void getEcrypted(char *argv[], int fileSize,int seed);
int compareFiles(char *file1, char *file2);


int main( int argc, char *argv[ ] ){
	FILE *fin, *fout;
	long long fileSize;

	if( argc != 4 ){
		printf("Usage: %s <fileName>\n", argv[0]);
		return 1;
	}

	fin = fopen( argv[ 1 ],  "rb");
	if( fin == NULL ){
		printf("File %s does not exist\n", argv[1]);
		return 2;
	}
	else
        //Guardar o tamanho do ficheiro
		fileSize = getFileSize( argv[1]);


    fout = fopen( argv[ 2 ],  "wb");
	if( fout == NULL ){
		printf("File %s does not exist\n", argv[2]);
		return 2;
	} 
	

	getEcrypted(argv,fileSize,atoi(argv[3]));
	

	if (getFileSize(argv[2]) != 0)
		printf("Encryption of %s succeeded.\n", argv[2]);
	else
		printf("Encryption of %s failed.\n", argv[2]);

	fclose(fin);
	fclose(fout);
	
	return 0;
}


long long getFileSize(char *filename) {
    struct stat file_status;
    if (stat(filename, &file_status) < 0) {
        return -1;
    }
    return (int)file_status.st_size;
}

void getEcrypted(char *argv[], int fileSize,int seed){
int resultEncrypt[fileSize];
FILE *fin, *fout;
fin = fopen( argv[ 1 ],  "rb");
fout = fopen( argv[ 2 ],  "wb");

	srand(seed);
	int cont, c;

	cont = TRUE;

	for (int i = 0; i < fileSize ; i++)
	{
		//Byte
		c = fgetc(fin);
		resultEncrypt[i] = rand() ^ c;
		//Escreve no ficheiro
		fputc(resultEncrypt[i], fout);
	}

	fclose(fin);
	fclose(fout);
	
}







    
	