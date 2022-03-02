#include "tamagotchi.h"

void			set_tamagotchi_fields(s_tamagotchi *tamagotchi, MYSQL_ROW row) {
	tamagotchi->name = row[0];
	tamagotchi->color = row[1];
	tamagotchi->birthdate = atoi(row[2]);
	tamagotchi->alive = atoi(row[3]);
	tamagotchi->born = atoi(row[4]);
	tamagotchi->last_fed = atoi(row[5]);
	tamagotchi->last_washed = atoi(row[6]);
	tamagotchi->last_played = atoi(row[7]);

	if (!row[8]) {
		tamagotchi->last_worked = 0;
	} else {
		tamagotchi->last_worked = atoi(row[8]);
	}

	tamagotchi->health_bar = atoi(row[9]);
	tamagotchi->last_health_update = atoi(row[10]);
	tamagotchi->outfit = row[11];
}

s_tamagotchi		*init_tamagotchi(MYSQL *conn, int tamagotchi_id) {
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char		query[QUERY_SIZE];
	s_tamagotchi	*tamagotchi;

	snprintf(query, QUERY_SIZE, "SELECT TAMAGOTCHIS.name, color, birthdate, alive, born, last_fed, last_washed, last_played, last_worked, health_bar, last_health_update, OUTFITS.name as outfit FROM TAMAGOTCHIS LEFT JOIN OUTFITS ON TAMAGOTCHIS.id_outfit = OUTFITS.id WHERE TAMAGOTCHIS.id = %d;", tamagotchi_id);


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
