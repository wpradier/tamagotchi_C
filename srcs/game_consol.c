#include "tamagotchi.h"

void game_consol(){
  char tamagotchi_name[100];
  printf("Choisissez le nom de votre tamagotchi : ");
  scanf("%s", tamagotchi_name);

  printf("Votre tamagotchi s'appelle : %s\n", tamagotchi_name);
}
