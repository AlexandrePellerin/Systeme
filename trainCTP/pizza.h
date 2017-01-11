#ifndef PIZZA_FACTORY
#define PIZZA_FACTORY

#define BREAD  0
#define TOMATO 1
#define CHEESE 2
#define HAM    3

struct stock {
    int bread;
    int tomato;
    int cheese;
    int ham;
};

int pizza_ready(struct stock * s);
int create_producer(int fd[2], int ingredient, int delay);
int init_producers(int fd[2], int pid_producers[4]);
int create_consumer(int fd[2]);

/* Fonction fournie pour stopper les processus producteurs
 * NE PAS MODIFIER */
void stop_producer(int pid);

#endif