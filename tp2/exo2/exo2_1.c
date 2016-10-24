#include <stdio.h>
#include <math.h>
#include "exo2_1.h"

struct rat simplifie(struct rat n){
  int lim = n.num;
  if(n.num > n.den){
    lim = n.den;
  }
  int cpt = 2;
  while(cpt <= lim){
    if(n.num%cpt==0 && n.den%cpt==0){
      n.num = n.num/cpt;
      n.den = n.den/cpt;
    }else{
      cpt++;
    }
  }
  return n;
}

struct rat rat_produit(struct rat n1, struct rat n2){
  struct rat res = {n1.num * n2.num, n1.den * n2.den};
  res = simplifie(res);
  return res;
};

struct rat rat_somme(struct rat n1, struct rat n2){
	struct rat op1 = {n1.num * n2.den, n1.den * n2.den};
  struct rat op2 = {n2.num * n1.den, n2.den * n1.den};
  struct rat res = {op1.num + op2.num, op1.den};
  res = simplifie(res);
  printf("num = %d, den = %d\n",res.num,res.den);
	return res;
};

struct rat rat_plus_petit(struct rat list[]){
  int cpt = 0;
  struct rat temp = list[cpt];
  double min;
  while(list[cpt].den!=0){
    if(cpt==0){
      min = ((double)temp.num)/temp.den;
    }
    double test = ((double)list[cpt].num)/list[cpt].den;
    if(min > test){
      temp = list[cpt];
      min = temp.num/temp.den;
    }
    cpt++;
  }
  printf("num = %d, den = %d\n",temp.num,temp.den);
  return temp;
}

