#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "exo1.h"

int motMillieu(int argc, char *argv[])
{
	int moins = 1, i;
	for(i = 1 ; i < argc ; i++){
		if(argv[i][0] == '-' && moins ==0){
			return 1;
		}
		if(argv[i][0] != '-'){
			moins = 0;
		}
	}
	return 0;
}

int traiter (int f, int *car, int *mot, int *lig)
{
	char buf[80];
	int temp, i;
	int booleen = 0;
	while( ( temp = read( f,buf,80*sizeof(char) ) ) > 0 ) {
		for(i = 0 ; i < temp ; i++){
			if(isspace(buf[i])){
				booleen = 0;
				if(buf[i] == '\n'){
					(*lig)++;
				}
			}else if(booleen == 0){
				booleen = 1;
				(*mot)++;
			}
			(*car)++;
		}
	}
	return 0;
}

int main(int argc, char * argv[])
{
	if(motMillieu(argc,argv)==1){
		printf("Mauvaise Utilisation.\n");
		return 10;
	}

	int nbArg[] = {0,0,0};
	int codeRetour = countArg(argc,argv,"cwl",nbArg);
	if( codeRetour == -1 ){
		printf("Mauvaise Utilisation.\n");
		return 20;
	}

	int f = open(argv[2], O_RDONLY);
	if(f == -1){
		printf("Mauvaise Utilisation.\n");
		return 30;
	}

	int car = 0, mot = 0, lig = 0;
	codeRetour = traiter(f, &car, &mot, &lig);
	if(codeRetour != 0){
		printf("Mauvaise Utilisation.\n");
		return 40;
	}

	close(f);
	int aff = 0;
	if(nbArg[0] != 0){
		printf("carac: %d ",car);
		aff = 1;
	}
	if(nbArg[1] != 0){
		printf("words: %d ",mot);
		aff = 1;
	}
	if(nbArg[2] != 0){
		printf("ligne: %d ",lig);
		aff = 1;
	}
	if(aff == 0){
		printf("carac: %d words: %d ligne: %d --> %s",car,mot,lig,argv[2]);
	}
	printf("\n");


	return 0;
}