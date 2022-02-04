#include "tamagotchi.h"

void			set_tamagotchi_fields(s_tamagotchi *tamagotchi, MYSQL_ROW row) {
	tamagotchi->name = row[0];
	tamagotchi->color = row[1];
	tamagotchi->birthdate = row[2];
	tamagotchi->alive = atoi(row[3]);
	tamagotchi->last_fed = row[4];
	tamagotchi->last_washed = row[5];
	tamagotchi->last_played = row[6];
	tamagotchi->last_worked = row[7];
	tamagotchi->health_bar = atoi(row[8]);
	tamagotchi->last_health_update = row[9];
	tamagotchi->outfit = row[10];
}

s_tamagotchi		*init_tamagotchi(MYSQL *conn, int id_tamagotchi) {
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char		query[300];
	s_tamagotchi	*tamagotchi;

	snprintf(query, 300, "SELECT TAMAGOTCHIS.name, color, birthdate, alive, last_fed, last_washed, last_played, last_worked, health_bar, last_health_update, OUTFITS.name as outfit FROM TAMAGOTCHIS LEFT JOIN OUTFITS ON TAMAGOTCHIS.id_outfit = OUTFITS.id WHERE TAMAGOTCHIS.id = %d", id_tamagotchi);

	mysql_query(conn, query);
	res = mysql_store_result(conn);

	if (!res) {
		printf("Tamagotchi not found");
		return (NULL);
	}

	row = mysql_fetch_row(res);
	mysql_free_result(res);

	tamagotchi = (s_tamagotchi*)malloc(sizeof(s_tamagotchi) * 1);
	set_tamagotchi_fields(tamagotchi, row);

	return (tamagotchi);
}
