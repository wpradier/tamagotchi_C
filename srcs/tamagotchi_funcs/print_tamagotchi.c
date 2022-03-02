#include "tamagotchi.h"

void		print_tamagotchi(s_tamagotchi *tamagotchi) {
	printf("Tamagotchi:\n");
	printf(" name: %s\n", tamagotchi->name);
	printf(" color: %s\n", tamagotchi->color);
	printf(" birthdate: %ld\n", tamagotchi->birthdate);
	printf(" alive: %d\n", tamagotchi->alive);
	printf(" last_fed: %ld\n", tamagotchi->last_fed);
	printf(" last_washed: %ld\n", tamagotchi->last_washed);
	printf(" last_played: %ld\n", tamagotchi->last_played);
	printf(" last_worked: %ld\n", tamagotchi->last_worked);
	printf(" health_bar: %hu\n", tamagotchi->health_bar);
	printf(" last_health_update: %ld\n", tamagotchi->last_health_update);
	printf(" outfit: %s\n", tamagotchi->outfit);
}
