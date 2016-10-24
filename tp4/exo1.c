#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


char * miroir (const char *s)
{
	char *rep;
	int len = strlen(s);
	int i;
	rep = malloc(sizeof(char)*len);
	for(i = len ; i > 0 ; i--){
		rep[len-i] = s[i-1];
	}
	return rep;
}

char * saisie()
{
	char sa;
	char *rep = malloc(0);
	int cpt = 0;
  	do{
    	sa= getchar();
		rep[cpt] = sa;
    	cpt++;
		rep = realloc(rep,cpt*sizeof(char));
  	} while(isspace(sa) == 0);
  	return rep;
}