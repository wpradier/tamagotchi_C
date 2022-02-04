#include "tamagotchi.h"

void		print_tamagotchi(s_tamagotchi *tamagotchi) {
	printf("Tamagotchi:\n");
	printf(" name: %s\n", tamagotchi->name);
	printf(" color: %s\n", tamagotchi->color);
	printf(" birthdate: %s\n", tamagotchi->birthdate);
	printf(" alive: %d\n", tamagotchi->alive);
	printf(" last_fed: %s\n", tamagotchi->last_fed);
	printf(" last_washed: %s\n", tamagotchi->last_washed);
	printf(" last_played: %s\n", tamagotchi->last_played);
	printf(" last_worked: %s\n", tamagotchi->last_worked);
	printf(" health_bar: %hu\n", tamagotchi->health_bar);
	printf(" last_health_update: %s\n", tamagotchi->last_health_update);
	printf(" outfit: %s\n", tamagotchi->outfit);
}
