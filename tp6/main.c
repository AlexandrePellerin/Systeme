#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "modif_bmp.h"
#include "exo1.h"

int lire_deux_octets(int fd, uint16 *val)
{
	int n = read(fd, val, sizeof(uint16));
	return n;
}

int lire_quatre_octets(int fd, uint32 *val){
	int n = read(fd, val, sizeof(uint32));
	return n;
}

int lire_entete(int de, entete_bmp *entete)
{
	int erreur = 0;
	if((erreur=lire_deux_octets(de,&(entete->fichier.signature)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->fichier.taille_fichier)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->fichier.reserve)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->fichier.offset_donnees)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.taille_entete)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.largeur)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.hauteur)))>=0
		&& (erreur=lire_deux_octets(de,&(entete->bitmap.nombre_plans)))>=0
		&& (erreur=lire_deux_octets(de,&(entete->bitmap.profondeur)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.compression)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.taille_donnees_image)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.resolution_horizontale)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.resolution_verticale)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.taille_palette)))>=0
		&& (erreur=lire_quatre_octets(de,&(entete->bitmap.nombre_de_couleurs_importantes)))>=0
		){
		return erreur;
	}else{
		return -1;
	}
}

int ecrire_deux_octets(int fd, uint16 *val)
{
	int n = write(fd, val, sizeof(uint16));
	return n;
}

int ecrire_quatre_octets(int fd, uint32 *val)
{
	int n = write(fd, val, sizeof(uint32));
	return n;
}

int ecrire_entete(int vers, entete_bmp *entete)
{
	int erreur = 0;
	if((erreur=ecrire_deux_octets(vers,&(entete->fichier.signature)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->fichier.taille_fichier)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->fichier.reserve)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->fichier.offset_donnees)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.taille_entete)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.largeur)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.hauteur)))>=0
		&& (erreur=ecrire_deux_octets(vers,&(entete->bitmap.nombre_plans)))>=0
		&& (erreur=ecrire_deux_octets(vers,&(entete->bitmap.profondeur)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.compression)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.taille_donnees_image)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.resolution_horizontale)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.resolution_verticale)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.taille_palette)))>=0
		&& (erreur=ecrire_quatre_octets(vers,&(entete->bitmap.nombre_de_couleurs_importantes)))>=0
		){
		return erreur;
	}else{
		return -1;
	}
}

int verifier_entete(entete_bmp *entete)
{
	if(entete->bitmap.profondeur==24){
		return 1;
	}else{
		return 0;
	}
}

unsigned char* allouer_pixels(entete_bmp *entete){
	unsigned char* c; 
	c = malloc(sizeof(char)*entete->bitmap.taille_donnees_image); 
	return c;
}

int lire_pixels(int de, entete_bmp *entete, unsigned char *pixels)
{
	int rRead; 
	int rlseek; 
	rlseek = lseek(de, entete->fichier.offset_donnees, SEEK_SET); 
	if (rlseek == -1) 
	{ 
		perror("Lseek"); 
		return -1; 
	}
	rRead = read(de,pixels,entete->bitmap.taille_donnees_image); 
	if (rRead == -1) 
	{ 
		perror("lecture pixels"); 
		return -1; 
	} 
	
	return rRead; 
}

int ecrire_pixels(int vers, entete_bmp *entete, unsigned char *pixels){
    int rWrite; 
	int rlseek; 

	rlseek = lseek(vers, entete->fichier.offset_donnees, SEEK_SET); 

	rWrite = write(vers,pixels,entete->bitmap.taille_donnees_image); 
	if (rWrite == -1) 
	{ 
		perror("ecriture pixels"); 
		return -1; 
	} 
	if (rlseek == -1) 
	{ 
		perror("Lseek"); 
		return -1; 
	} 
	return rWrite; 
}

void rouge(entete_bmp *entete, unsigned char *pixels) 
{ 
	unsigned int i;
  	unsigned int j= entete->bitmap.largeur*3;
  	while (j%4!=0){
   		j++;
  	}	
  	for (i=0; i < entete->bitmap.taille_donnees_image; i+=3){ 
  		if(i%j!=0){
  	    	pixels[i+1]=0; 
        	pixels[i+2]=0; 
    	}else{
     		i+=2;
    	}
  	} 
} 

int copier_bmp(int de, int vers){
  entete_bmp entete;
  unsigned char *pixels;
  /* lecture du fichier source */
  lire_entete(de, &entete);
  pixels = allouer_pixels(&entete);
  lire_pixels(de, &entete, pixels);
  rouge(&entete, pixels);
  /* écriture du fichier destination */
  ecrire_entete(vers, &entete);
  ecrire_pixels(vers, &entete, pixels);
  /* on libère les pixels */
  free(pixels);
  return vers; /* on a réussi */
}

int main(int argc, char *argv[])
{
	//entete_bmp entete;

	int fd = open(argv[1],O_RDONLY);
	int fd2 = -1;
	if(argc > 1){
		fd2 = open(argv[2],O_WRONLY);
	}

	/*int n = lire_entete(fd, &entete);

	printf("%x\n",entete.fichier.signature);
	printf("%d\n",entete.fichier.taille_fichier);
	printf("%d\n",entete.fichier.reserve);
	printf("%d\n",entete.fichier.offset_donnees);
	printf("%d\n",entete.bitmap.taille_entete);
	printf("%d\n",entete.bitmap.largeur);
	printf("%d\n",entete.bitmap.hauteur);
	printf("%d\n",entete.bitmap.nombre_plans);
	printf("%d\n",entete.bitmap.profondeur);
	printf("%d\n",entete.bitmap.compression);
	printf("%d\n",entete.bitmap.taille_donnees_image); 
	printf("%d\n",entete.bitmap.resolution_horizontale);
	printf("%d\n",entete.bitmap.resolution_verticale);
	printf("%d\n",entete.bitmap.taille_palette);
	printf("%d\n",entete.bitmap.nombre_de_couleurs_importantes);*/

	/*if(fd2 >= 0){
		n = ecrire_entete(fd2, &entete);
	}*/

	if(fd2 >= 0){
		//entete_bmp entete2;
		//lire_entete(fd2, &entete2);
		//printf("verif: %d\n",verifier_entete(&entete));
		//printf("verif: %d\n",verifier_entete(&entete2));
		//if(verifier_entete(&entete)){
			copier_bmp(fd,fd2);
		//}
	}
	return 0;
}