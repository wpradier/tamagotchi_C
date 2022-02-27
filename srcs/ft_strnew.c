#include "tamagotchi.h"

void ft_bzero(char *str, size_t n){
  size_t i;

  i = 0;

  while(i < n){
    str[i] = '\0';
    i++;
  }
}

char *ft_strnew(size_t n){
  char *str;

  str = (char*)malloc(sizeof(char) * n);
  ft_bzero(str, n);

  return str;
}
