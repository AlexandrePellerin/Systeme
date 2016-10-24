#include <stdio.h>

int mon_strlen(char s[])
{
  int cpt = 0;
  while(s[cpt]!=0){
    cpt++;
  }
  return cpt;
}

int mon_strlen2(char *s)
{
  int cpt = 0;
  while(*s != 0){
    s++;
    cpt++;
  }
  return cpt;
}

int mon_strlen3(const char *s)
{
  int cpt = 0;
  while(*s != 0){
    s++;
    cpt++;
  }
  return cpt;
}

int mon_strcmp(char *s1, char *s2)
{
  int res = 0;
  while(*s1 != 0 && *s2 != 0 && res == 0){
    if(*s1 > *s2){
      res = 1;
    }else if(*s1 < *s2){
      res = -1;
    }
    s1++;s2++;
  }
  if(*s1 == 0 && res == 0 && *s2 != 0){
    res = -1;
  }else if(*s1 != 0 && res == 0 && *s2 != 0){
    res = 1;
  }
  return res;
}

int mon_strcmp2(char *s1, char *s2, int n)
{
  int res = 0, cpt = 0;
  while(*s1 != 0 && *s2 != 0 && res == 0 && cpt < n){
    if(*s1 > *s2){
      res = 1;
    }else if(*s1 < *s2){
      res = -1;
    }
    s1++;s2++;cpt++;
  }
  if(*s1 == 0 && res == 0 && *s2 != 0 && cpt != n){
    res = -1;
  }else if(*s1 != 0 && res == 0 && *s2 == 0 && cpt != n){
    res = 1;
  }
  
  return res;
}

char *mon_strcat(char *s1, const char *s2)
{
  int cpt = 0;
  while(*s1 != 0){
    s1++;
    cpt++;
  }
  while(*s2 != 0){
    *s1 = *s2;
    s1++;
    s2++;
    cpt++;
  }
  return s1-cpt;
}

char *mon_strchr(char *s, int c)
{
  char *res = NULL;
  while(res == NULL && *s != 0){
    if(*s == c){
      res = s;
    }
    s++;
  }
  return res;
}

char *mon_strstr(char *haystack, char *needle)
{
  char *res = haystack;
  int i = 0, trouve = 0;
  while(i<mon_strlen2(haystack) && trouve == 0){
    if(0 == mon_strcmp2(res,needle,mon_strlen2(needle))){
      trouve = 1;
    }
    i++;
    res++;
  }
  if(trouve == 1){
    return res-1;
  }else{
    return res;
  }
}
