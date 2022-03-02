#include "tamagotchi.h"

int 		update_hunger(s_gamestate *gamestate, time_t time_diff, int hunger_frequency) {

	if (time_diff < 0) {
		return (0);
	}

	gamestate->hunger = hunger_frequency * time_diff;

	return (1);
}

int		update_fun(s_gamestate *gamestate, time_t time_diff) {
	
	if (time_diff < 0) {
		return (0);
	}

	gamestate->fun = 100 - (FUN_FREQUENCY * time_diff); // Decreasing with time

	return (1);
}

int		update_hygiene(s_gamestate *gamestate, time_t time_diff) {

	if (time_diff < 0) {
		return (0);
	}

	gamestate->hygiene = 100 - (WASH_FREQUENCY * time_diff);

	return (1);
}

int		update_health(s_gamestate *gamestate, s_tamagotchi *tamagotchi, s_config *config, time_t curr) {
	int	health;
	int	hunger;
	int	hygiene;
	int	fun;

	health = gamestate->health;
	hunger = gamestate->hunger;
	hygiene = gamestate->hygiene;
	fun = gamestate->fun;

	if (hunger >= 100) {
		while (hunger >= 100) {
			health -= 10;
			hunger -= 100;
		}
		tamagotchi->last_fed = curr - (hunger * config->hunger_frequency);
	}
	

	if (hygiene <= 0) {
		while (hygiene <= 0) {
			health -= 10;
			hygiene += 100;
		}
		tamagotchi->last_washed = curr - ((100 - hygiene) * WASH_FREQUENCY);
	}

	if (fun <= 0) {
		while (fun <= 0) {
			health -= 10;
			fun += 100;
		}
		tamagotchi->last_played = curr - ((100 - fun) * FUN_FREQUENCY);
	}

	gamestate->hunger = hunger;
	gamestate->hygiene = hygiene;
	gamestate->fun = fun;
	gamestate->health = health;
	tamagotchi->health_bar = health;

	return (1);
}

int		update_gamestate(s_gamestate *gamestate, s_tamagotchi *tamagotchi, s_config *config) {
	time_t	curr;

	curr = time(NULL);

	if (!update_hunger(gamestate, curr - tamagotchi->last_fed, config->hunger_frequency)) {
		return (0);
	}
	
	if (!update_fun(gamestate, curr - tamagotchi->last_played)) {
		return (0);
	}

	if (!update_hygiene(gamestate, curr - tamagotchi->last_washed)) {
		return (0);
	}

	if (!update_health(gamestate, tamagotchi, config, curr)) {
		return (0);
	}

	return (1);
}
