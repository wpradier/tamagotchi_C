#include "tamagotchi.h"

void			set_tamagotchi_fields(s_tamagotchi *tamagotchi, MYSQL_ROW row) {
	printf("ROW 0\n");
	tamagotchi->name = row[0];
	printf("ROW 1\n");
	tamagotchi->color = row[1];
	printf("ROW 2\n");
	tamagotchi->birthdate = atoi(row[2]);
	printf("ROW 3\n");
	tamagotchi->alive = atoi(row[3]);
	printf("ROW 4\n");
	tamagotchi->born = atoi(row[4]);
	printf("ROW 5\n");
	tamagotchi->last_fed = atoi(row[5]);
	printf("ROW 6\n");
	tamagotchi->last_washed = atoi(row[6]);
	printf("ROW 7\n");
	tamagotchi->last_played = atoi(row[7]);
	printf("ROW 8: '%s'\n", row[8]);

	if (!row[8]) {
		tamagotchi->last_worked = 0;
	} else {
		tamagotchi->last_worked = atoi(row[8]);
	}

	printf("ROW 9\n");
	tamagotchi->health_bar = atoi(row[9]);
	printf("ROW 10\n");
	tamagotchi->last_health_update = atoi(row[10]);
	printf("ROW 11\n");
	tamagotchi->outfit = row[11];
	printf("END ROW\n");
}

s_tamagotchi		*init_tamagotchi(MYSQL *conn, int tamagotchi_id) {
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char		query[QUERY_SIZE];
	s_tamagotchi	*tamagotchi;

	snprintf(query, QUERY_SIZE, "SELECT TAMAGOTCHIS.name, color, birthdate, alive, born, last_fed, last_washed, last_played, last_worked, health_bar, last_health_update, OUTFITS.name as outfit FROM TAMAGOTCHIS LEFT JOIN OUTFITS ON TAMAGOTCHIS.id_outfit = OUTFITS.id WHERE TAMAGOTCHIS.id = %d;", tamagotchi_id);


	printf("QUERY: %s\n", query);
	mysql_query(conn, query);
	res = mysql_store_result(conn);

	printf("TEST1\n");
	if (!res) {
		printf("Tamagotchi not found");
		return (NULL);
	}

	printf("TEST2\n");
	row = mysql_fetch_row(res);
	printf("TEST3\n");
	mysql_free_result(res);
	printf("TEST4\n");

	tamagotchi = (s_tamagotchi*)malloc(sizeof(s_tamagotchi) * 1);
	printf("TEST5\n");
	set_tamagotchi_fields(tamagotchi, row);
	printf("TEST6\n");

	return (tamagotchi);
}
