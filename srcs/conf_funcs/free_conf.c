#include "tamagotchi.h"

void		free_conf(s_config *config) {
	free(config->location);
	free(config);
}
