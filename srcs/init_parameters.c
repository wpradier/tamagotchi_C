#include "tamagotchi.h"

s_parameters *init_parameters(s_tamagotchi *tamagotchi, s_gamestate *gamestate, s_config *config, gpointer data){
  s_parameters  *parameters;

  parameters = (s_parameters*)malloc(sizeof(s_parameters) * 1);
  parameters->tamagotchi = tamagotchi;
  parameters->gamestate = gamestate;
  parameters->config = config;
  parameters->data = data;

  return parameters;
}
