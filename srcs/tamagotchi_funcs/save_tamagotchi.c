#include "tamagotchi.h"

int			save_tamagotchi(MYSQL *conn, s_tamagotchi *tamagotchi) {
	// MYSQL_RES	*res;
	char		query[QUERY_SIZE];
	int		outfit;

	if (!strcmp(tamagotchi->outfit, "tee-shirt")) {
		outfit = 2;
	} else if (!strcmp(tamagotchi->outfit, "accessories")) {
		outfit = 3;
	} else if (!strcmp(tamagotchi->outfit, "cape")) {
		outfit = 4;
	} else {
		outfit = 1; // none
	}

	snprintf(query, QUERY_SIZE, "UPDATE TAMAGOTCHIS SET alive = %d, born = %d, birthdate = %ld, last_fed = %ld, last_washed = %ld, last_played = %ld, last_worked = %ld, health_bar = %d, last_health_update = %ld, id_outfit = %d WHERE id = %d", tamagotchi->alive, tamagotchi->born, tamagotchi->birthdate, tamagotchi->last_fed, tamagotchi->last_washed, tamagotchi->last_played, tamagotchi->last_worked, tamagotchi->health_bar, tamagotchi->last_health_update, outfit, tamagotchi->id);


	printf("QUERY: %s\n", query);

	mysql_query(conn, query);

	return (1);
}
