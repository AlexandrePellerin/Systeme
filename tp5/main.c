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
	
	int cpt = argc - 1;
	int car, mot, lig;
	int totalCar = 0, totalMot = 0, totalLig = 0;
	while(argv[cpt][0] != '-' && cpt>0){
		//Lecture
		int f = open(argv[cpt], O_RDONLY);
		//Si la lecture c'est mal passe.
		if(f == -1){
			printf("Mauvaise Utilisation.");
		}else{

			car = 0, mot = 0, lig = 0;
			//Effectue le traitement du fichier
			codeRetour = traiter(f, &car, &mot, &lig);
			//Si le traitement s'est mal passe
			if(codeRetour != 0){
				printf("Mauvaise Utilisation.");
			}else{
				//Ferme le fichier
				close(f);
				int aff = 0;
				//Affiche le nb de caracteres
				if(nbArg[0] != 0){
					printf("carac: %d ",car);
					totalCar += car;
					aff = 1;
				}
				//Affiche le nb de mots
				if(nbArg[1] != 0){
					printf("words: %d ",mot);
					totalMot += mot;
					aff = 1;
				}
				//Affiche le nb de lignes
				if(nbArg[2] != 0){
					printf("ligne: %d ",lig);
					totalLig += lig;
					aff = 1;
				}
				//Affiche le nb de caracteres, mots et lignes
				if(aff == 0){
					printf("carac: %d words: %d ligne: %d",car,mot,lig);
				}
			}
		}
		printf(" --> %s\n",argv[cpt]);
		cpt--;
	}

	if(cpt == argc-1){
		//Saisie
		car = 0, mot = 0, lig = 0;
		codeRetour = traiter(0, &car, &mot, &lig);
		int aff = 0;
		//Affiche le nb de caracteres
		printf("\n");
		if(nbArg[0] != 0){
			printf("carac: %d ",car);
			totalCar += car;
			aff = 1;
		}
		//Affiche le nb de mots
		if(nbArg[1] != 0){
			printf("words: %d ",mot);
			totalMot += mot;
			aff = 1;
		}
		//Affiche le nb de lignes
		if(nbArg[2] != 0){
			printf("ligne: %d ",lig);
			totalLig += lig;
			aff = 1;
		}
		//Affiche le nb de caracteres, mots et lignes
		if(aff == 0){
			printf("carac: %d words: %d ligne: %d",car,mot,lig);
		}
		printf(" --> stdin\n");
	}else{
		//Total
		if(totalCar != 0 && totalCar != car){
			printf("%d ",totalCar);
		}
		if(totalMot != 0 && totalMot != mot){
			printf("%d ",totalMot);
		}
		if(totalLig != 0 && totalLig != lig){
			printf("%d ",totalLig);
		}
		printf("Total\n");
	}
	
	return 0;
}