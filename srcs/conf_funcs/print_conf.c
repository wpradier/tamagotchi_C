#include "tamagotchi.h"

void		print_conf(s_config *config) {
	printf("Configuration:\n");
	printf(" display_healthbar: %d\n", config->display_healthbar);
	printf(" display_hungerbar: %d\n", config->display_hungerbar);
	printf(" display_funbar: %d\n", config->display_funbar);
	printf(" display_hygienebar: %d\n", config->display_hygienebar);
	printf(" hunger_frequency: %d\n", config->hunger_frequency);
	printf(" work_duration: %d\n", config->work_duration);
	printf(" grow_time: %d\n", config->grow_time);
	printf(" hide_and_seek_duration: %d\n", config->hide_and_seek_duration);
	printf(" dictation_duration: %d\n", config->dictation_duration);
	printf(" location: %s\n", config->location);
}
