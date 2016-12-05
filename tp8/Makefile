SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o) ligne_commande.o
AOUT=prog

$(AOUT): $(OBJS)
	gcc -o $@ $^


%.o: %.c
	gcc -Wall -Werror -W -c -o $@ $<

clean:
	mv ligne_commande.o ligne_commande
	rm -f *.o $(AOUT)
	mv ligne_commande ligne_commande.o
