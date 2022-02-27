#include "tamagotchi.h"

void print_parameters(s_parameters *parameters){
  printf("PARAMETERS : \n");
  printf("health_kits : %d\n", parameters->gamestate->health_kits); 
  print_tamagotchi(parameters->tamagotchi);
}
