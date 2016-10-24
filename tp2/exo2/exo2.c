#include <stdio.h>
#include "exo2_1.h"

int main(void)
{
	struct rat n1 = {1,2}; 
  	struct rat n2 = {.num = 3, .den = 8};
  	rat_produit(n1,n2);
  	rat_somme(n1,n2);
    struct rat n3 = {0,0};
    struct rat list[4] = {n1,n2,n3};
    rat_plus_petit(list);
	return 0;
}