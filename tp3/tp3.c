#include <stdio.h>
#include "exo.h"

int main(void)
{
  char tab[20] = "toto";
  printf("Longueur : %d\n",mon_strlen(tab));
  char *s = tab;
  printf("Longueur2: %d\n",mon_strlen2(s));
  char *s2 = "salut";
  printf("Compare  : %d\n",mon_strcmp(s,s2));
  printf("Compare2 : %d\n",mon_strcmp2(s,s2,2));
  printf("Compare2 : %d\n",mon_strcmp2(s,s2,4));

  //printf("concatene: %s\n",mon_strcat(tab,s2));

  printf("recherche: %s\n",mon_strchr(tab,'z'));
  
  printf("rechermot: %s\n",mon_strstr(s,s2));
  return 0;
}
