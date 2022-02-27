#include "tamagotchi.h"

void			set_tamagotchi_fields(s_tamagotchi *tamagotchi, MYSQL_ROW row) {
	tamagotchi->name = ft_strnew(strlen(row[0]) + 1);
	strcpy(tamagotchi->name, row[0]);
	tamagotchi->color = ft_strnew(strlen(row[1]) + 1);
	strcpy(tamagotchi->color, row[1]);
	tamagotchi->birthdate = ft_strnew(strlen(row[2]) + 1);
	strcpy(tamagotchi->birthdate, row[2]);
	tamagotchi->alive = atoi(row[3]);
	tamagotchi->last_fed = ft_strnew(strlen(row[4]) + 1);
	strcpy(tamagotchi->last_fed, row[4]);
	tamagotchi->last_washed = ft_strnew(strlen(row[5]) + 1);
	strcpy(tamagotchi->last_washed, row[5]);
	tamagotchi->last_played = ft_strnew(strlen(row[6]) + 1);
	strcpy(tamagotchi->last_played, row[6]);
	tamagotchi->last_worked = ft_strnew(strlen(row[7]) + 1);
	strcpy(tamagotchi->last_worked, row[7]);
	tamagotchi->health_bar = atoi(row[8]);
	tamagotchi->last_health_update = ft_strnew(strlen(row[9]) + 1);
	strcpy(tamagotchi->last_health_update, row[9]);
	tamagotchi->outfit = ft_strnew(strlen(row[10]) + 1);
	strcpy(tamagotchi->outfit, row[10]);
}

s_tamagotchi		*init_tamagotchi(MYSQL *conn, int tamagotchi_id) {
	MYSQL_RES			*res;
	MYSQL_ROW			row;
	char					query[QUERY_SIZE];
	s_tamagotchi	*tamagotchi;

	snprintf(query, QUERY_SIZE, "SELECT TAMAGOTCHIS.name, color, birthdate, alive, last_fed, last_washed, last_played, last_worked, health_bar, last_health_update, OUTFITS.name as outfit FROM TAMAGOTCHIS LEFT JOIN OUTFITS ON TAMAGOTCHIS.id_outfit = OUTFITS.id WHERE TAMAGOTCHIS.id = %d", tamagotchi_id);

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
