/* Contrôle TP ASR4 : 25 mars 2014 */

/* Nom    :
 * Prénom :
 * Groupe :
 */

/* Votre fichier doit compiler sans erreur avec les options de compilation :
 *  -Wall -Werror -pedantic
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pizza.h"


/* IMPLEMENTATION DES FONCTIONS A FAIRE ICI */

/* Stoppe un producteur */
/* Cette fonction NE DOIT PAS être modifiée */
void stop_producer(int pid)
{
    kill(pid, SIGKILL);
}

int pizza_ready(struct stock *s)
{
	if(s->bread>=1){
		if(s->tomato>=3){
			if(s->cheese>=2){
				if(s->ham>=2){
					return 0;
				}
			}
		}
	}
	return -1;
}

int create_consumer(int fd[2])
{
	int pid = fork();
	if(pid == 0){
		char buf[sizeof(int)];
		int ingredient = -1;
		struct stock s;
		while(pizza_ready(&s) == -1){
			close(fd[1]);
			ingredient = read(fd[0], &buf, sizeof(int));
			if(ingredient == BREAD){
				s.bread += 1;
			}else if(ingredient == TOMATO){
				s.tomato += 1;
			}else if(ingredient == CHEESE){
				s.cheese += 1;
			}else if(ingredient == HAM){
				s.ham += 1;
			}
			sleep(1);
		}
		printf("Kowabunga\n");
		stop_producer(pid);
		exit(0);
	}else{
		return -1;
	}

}

int create_producer(int fd[2], int ingredient, int delay)
{
	int pid = fork();
	if(pid > 0){
		while(1){
			close(fd[0]);
			write(fd[1], (void *) &ingredient, sizeof(int));
			sleep(delay);
		}
		stop_producer(pid);
		exit(pid);
	}else{
		return -1;
	}
}

int init_producers(int fd[2], int pid_producers[4])
{
	pid_producers[0] = create_producer(fd, BREAD, 4);
	pid_producers[1] = create_producer(fd, TOMATO, 1);
	pid_producers[2] = create_producer(fd, CHEESE, 2);
	pid_producers[3] = create_producer(fd, HAM, 3);
	if(pid_producers[0]!=-1
		&& pid_producers[1]!=-1
		&& pid_producers[2]!=-1
		&& pid_producers[3]!=-1){
		return 0;
	}
	return -1;
}

int main(int argc, char *argv[])
{
    if(argc !=2){
    	perror("Le nombre d'arguments n'est pas valide.");
    	return -1;
    }
    int nombre = 0;
    int fd[2];
    int pid_producers[4];
    int i;
    nombre = argv[1][0] - '0';
    init_producers(fd, pid_producers);
    for(i = 0 ; i < nombre ; i++){
    	create_consumer(fd);
    }
    waitpid(0, NULL, 0);

    for(i = 0 ; i < 4 ; i++){
    	stop_producer(pid_producers[i]);
    }
    return 0;
}