#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exo1.h"

int main(int argc, char * argv[])
{

  if(argc == 1){
  	printf("Mauvaise utilisation.\n");	
  	return 1;
  }

  int i,j,lon=0;
  int m = 0 , s = 0 ;
  for(i = 1 ; i < argc ; i++){
    lon = strlen(argv[i]);
    if(argv[i][0]=='-'){
  	  for(j = 1 ; j < lon ; j++){
  		  if(argv[i][j]!='s' && argv[i][j]!='m'){
  			  printf("Mauvaise utilisation.\n");
  			  return 1;
  		  }
  		  if(argv[i][j]=='m'){
  			  m ++;
  		  }
  		  if(argv[i][j]=='s'){
  			  s ++;
  		  }
  	  }
    }
  }

  for(i = 1 ; i < argc ; i++){
    if(argv[i][0]!='-' && s!=0){
      printf("Mauvaise utilisation.\n");
      return 1;
    }
  }

  if(s == 0 && m == 0){ 
    printf("Mauvaise Utilisation.\n");
    return -1;
  }
  if(s == 0 && m != 1){
   printf("Mauvaise Utilisation.\n");
   return -1;
  }else if(s==0){
    if((argv[argc-1][0])=='-' || argc>3){
      printf("Mauvaise Utilisation.\n");
      return 1;
    }
    printf("%s\n",miroir(argv[argc-1]));
    return 0;
  }
  if(s != 1 && m == 0){
    printf("Mauvaise Utilisation.\n");
    return -1;
  }else if(m==0){
    printf("%s\n",saisie());
    return 0;
  }
  if(s != 0 && m != 0){
    printf("%s\n",miroir(saisie()));
    return 0;
  }

  return 0;
}