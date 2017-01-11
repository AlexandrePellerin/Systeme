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

void nettoies(){
	pid_t pid;
	int status;

	while( ( pid = waitpid( pid, &status, WNOHANG ) ) > 0 ){printf("Processus mort\n");}
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

int lance_commande(int in, int out, char *com, char **argv)
{
	int pid = fork();
	if( pid == 0 ){
		if( in != 0 ){
			if(close(0)==-1||dup(in)==-1) return -1;
		}
		if( out != 1 ){
			if(close(1)==-1||dup(out)==-1) return -1;
		}
		if(strcmp(com, "cd") == 0){
			// TODO
			//chdir();
		}else{
			execvp(com, argv);
			perror("iutshell: commande introuvable.");
			printf("La ligne de commande %s n'existe pas.\n", argv[0]);
			exit(1);
		}
		return 0;
	}else{
		if(in != 0){
			close(in);
		}
		if(out != -1){
			close(out);
		}
	}
	return pid;
}

void execute_ligne_commande()
{
	int flag = -1, nb = -1;

	int in = 0, out = 0;
	int fds[2];

	int sout = dup(1);
	int sin = dup(0);

	char ***argv = ligne_commande( &flag, &nb );

	int i;

	nettoies();

	if(flag < 0){
		if(nb != 0){
			printf("Une erreur est survenue lors de la lecture de la commande.\n");
		}
	}else{
		for( i = 0 ; i < nb ; i++ ){
			in = sin;
			out = sout;

			if( i != 0 ){
				in = fds[0];
			}
			if( nb > 1 && i != nb-1 ){
				pipe(fds);
			}
			if( i != nb-1 ){
				out = fds[1];
			}

			lance_commande(in, out, argv[i][0], argv[i]);
		}

		if( flag == 0 ){
			for( i = 0 ; i < nb ; i++ ){
				wait(0);
			}
		}
		/*int pid = fork();
		if( pid == 0 ){
			execvp(argv[0][0], argv[0]);
			perror("iutshell: commande introuvable.");
			printf("La ligne de commande %s n'existe pas.\n", argv[0][0]);
			return;
		}else{
			if( flag == 0 ){
				waitpid(pid, NULL, 0);
			}
		}*/
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