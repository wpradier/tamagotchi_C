#include "tamagotchi.h"


s_gamestate		*init_gamestate(s_save *save, s_tamagotchi *tamagotchi) {
	s_gamestate	*gamestate;
	
	gamestate = (s_gamestate*)malloc(sizeof(s_gamestate) * 1);

	gamestate->health = tamagotchi->health_bar; // TEMPORAIRE
	gamestate->health_kits = save->health_kits;
	gamestate->money = save->money;
	gamestate->food = save->food;

	return (gamestate);
}
