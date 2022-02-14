#include "tamagotchi.h"

void			set_save_fields(s_save *save, MYSQL_ROW row) {
	save->name = row[0];
	save->food = atoi(row[1]);
	save->money = atoi(row[2]);
	save->health_kits = atoi(row[3]);
}

s_save			*fetch_save(MYSQL *conn, int save_id) {
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char		query[QUERY_SIZE];
	s_save		*save;

	snprintf(query, QUERY_SIZE, "SELECT name, food, money, health_kits FROM SAVES WHERE id = %d", save_id);

	mysql_query(conn, query);
	res = mysql_store_result(conn);

	if (!res) {
		printf("Save not found");
		return (NULL);
	}

	row = mysql_fetch_row(res);
	mysql_free_result(res);

	save = (s_save*)malloc(sizeof(s_save) * 1);
	set_save_fields(save, row);

	return save;
}
