#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countArg(int argc, char *argv[], char* chaine,int rep[])
{
	int i,j,k, optVal;
	int lonChaine = strlen(chaine);
	for(i = 1 ; i < argc ; i++){
		if(argv[i][0]=='-'){
			int lon = strlen(argv[i]);
			for( j = 1 ; j < lon ; j++){
				optVal = -1;
				for( k = 0 ; k < lonChaine ; k++){
					if(argv[i][j]==chaine[k]){
  			  			rep[k]++;
  			  			optVal = 0;
  		  			}
  		  		}
  		  		if(optVal == -1){
  		  			return -1;
  		  		}
			}
		}
	}
	return 0;
}