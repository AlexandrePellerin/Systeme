#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
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

int main(int argc, char *argv[])
{
	entete_bmp entete;

	int fd = open(argv[1],O_RDONLY);
	int fd2 = -1;
	if(argc > 1){
		fd2 = open(argv[2],O_WRONLY);
	}

	int n = lire_entete(fd, &entete);

	printf("%d\n",entete.fichier.signature);
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
	printf("%d\n",entete.bitmap.nombre_de_couleurs_importantes);

	if(fd2 >= 0){
		n = ecrire_entete(fd2, &entete);
	}
	return n;
}