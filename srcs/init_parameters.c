#include "tamagotchi.h"

s_parameters *init_parameters(s_tamagotchi *tamagotchi, s_gamestate *gamestate, gpointer data){
  s_parameters  *parameters;

  parameters = (s_parameters*)malloc(sizeof(s_parameters) * 1);
  parameters->tamagotchi = tamagotchi;
  parameters->gamestate = gamestate;
  parameters->data = data;

  return parameters;
}
