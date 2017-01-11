#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


#define FILENAME_SIZE 256

typedef struct {
	char fichier[FILENAME_SIZE];
} job_t;

//Permet d'afficher les details d'un fichier passe en parametre.
int afficher_detail(const char* fichier)
{
	struct stat buf;
	char t;
	int size;
	int retour = stat(fichier, &buf);
	//Permet de tester si il y a eu un probleme lors de la commande stat
	if(retour != 0){
		printf("Erreur lors de l'affichage du fichier.\n");
		return -1;
	}
	if(S_ISDIR(buf.st_mode)){
		//Fichier repertoire
		t = 'd';
	}else if(S_ISREG(buf.st_mode)){
		//Fichier regulier
		t = '-';
	}else if(S_ISCHR(buf.st_mode)){
		//Fichier caractere
		t = 'c';
	}else if(S_ISBLK(buf.st_mode)){
		//Fichier bloc
		t = 'b';
	}else{
		//Type de fichier inconnu
		t = '?';
	}
	//La taille du fichier
	size = buf.st_size;
	printf("%c, %s, %d.\n",t,fichier,size);
	return 0;
}

//Permet d'envoyer un job passe en parametre dans un fichier.
int envoyer_job(int fd, const job_t *job)
{
	int retour = write(fd, job, sizeof(job_t));
	if(retour < 0){
		printf("Erreur lors de l'ecriture.\n");
		return -1;
	}
	return 0;
}

//Permet de recuperer un job d'un fichier passe en parametre
int recevoir_job(int fd, job_t *job)
{
	int retour = read(fd, job, sizeof(job_t));
	if(retour < 0){
		printf("Erreur lors de la lecture du fichier.\n");
		return -1;
	}
	return 0;
}

void traitement_fils(int fd)
{
	job_t job;
	while(recevoir_job(fd, &job) == 0){
		afficher_detail(job.fichier);
	}
	printf("Fils de pid %d: Fini.\n",(int) getpid());
	exit(0);
}

int creer_fils(int tube[2])
{
	int pid = fork();
	if(pid==0){
		close(tube[1]);
		traitement_fils(tube[0]);
		return pid;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	//Permet de verifier qu'il y a bien un fichier passe en parametre
	if(argc < 3){
		printf("Nombre d'arguments invalide.\n");
		return -1;
	}
	int fd[2];
	int nbFils = atoi(argv[1]);
	int i;
	//job_t job;

	pipe(fd);
	close(fd[0]);
	for(i = 2 ; i < argc ; i++){
		//Le write boucle, en le commentant on voit bien que les processus fils finissent
		//write(fd[1], argv[i],sizeof(char)*FILENAME_SIZE);
	}
	for(i = 0 ; i < nbFils ; i++){
		creer_fils(fd);
	}
	

	pid_t pid;
	int status;

	while( ( pid = waitpid( pid, &status, 0 ) ) > 0 )
	{
		printf("Pere: fils de pid %d termine correctement.\n",(int) pid);
	}

	printf("Pere de pid %d: fini.\n",(int) getpid());

	return 0;
}