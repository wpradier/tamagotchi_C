#include "tamagotchi.h"


s_gamestate		*init_gamestate(s_save *save, s_tamagotchi *tamagotchi, s_config *config) {
	s_gamestate	*gamestate;

	gamestate = (s_gamestate*)malloc(sizeof(s_gamestate) * 1);

	gamestate->health_kits = save->health_kits;
	gamestate->money = save->money;
	gamestate->food = save->food;
 

	if (!update_gamestate(gamestate, tamagotchi, config)) {
		return (NULL);
	}

	return (gamestate);
}
