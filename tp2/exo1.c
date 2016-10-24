#include <stdio.h>
#include "tp1_1.h"

int main(void){
  int src[4] = {1,2,3,4};
  afficher(src,4);
  printf("somme : %d\n", somme(src,4));
  int dst[8];
  copie_dans(dst,src,sizeof(dst)/sizeof(dst[0]));
  afficher(dst,4);
  ajoute_apres(dst,4,src,4);
  afficher(dst,8);
  return 0;
}


