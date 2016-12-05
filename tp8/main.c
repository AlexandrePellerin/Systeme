#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "ligne_commande.h"

void ajouteApres(char *chaine, int n, char *directory, int len)
{
	int i;
	for(i = 0 ; i < len ; i++){
		chaine[i+n] = directory[i];
	}
}

void affiche_prompt()
{
	char *directory = NULL;
	char *user = NULL;
	char *home = NULL;
	char hostname[20];
	gethostname(hostname, 20);
	user = getenv("USER");
	home = getenv("HOME");

	directory = getcwd(NULL, 128);
	char *repertoire = malloc(sizeof(char)*130);
	if(strstr(directory,home)==NULL){
		printf("%s@%s:%s$ ", user, hostname, directory);
	}else{
	repertoire[0]='~';
	int temp = strlen(home);

	ajouteApres(repertoire, 1, directory+temp, 128-temp);

	printf("%s@%s:%s$ ", user, hostname, repertoire);
	}
	fflush(stdout);

	free(repertoire);
	free(directory);
	return;
}

void execute_ligne_commande()
{
	int flag = -1, nb = -1;

	char ***argv = ligne_commande( &flag, &nb );

	if(flag < 0){
		printf("Une erreur est survenue lors de la lecture de la commande.\n");
	}else{
		int pid = fork();
		if( pid == 0 ){
			execvp(argv[0][0], argv[0]);
			perror("iutshell: commande introuvable.");
			printf("La ligne de commande %s n'existe pas.\n", argv[0][0]);
			return;
		}else{
			if( flag == 0 ){
				waitpid(pid, NULL, 0);
			}
		}
	}
	free(argv);
}

int main(void)
{
	while(1){
	affiche_prompt();
	execute_ligne_commande();
	}
	return 0;
}