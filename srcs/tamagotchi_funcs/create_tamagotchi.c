#include "tamagotchi.h"

int			get_id(MYSQL *conn) {
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char		query[QUERY_SIZE];

	snprintf(query, QUERY_SIZE,"SELECT id FROM TAMAGOTCHIS ORDER BY id DESC LIMIT 1");

	mysql_query(conn, query);
	res = mysql_store_result(conn);

	if (!mysql_num_rows(res)) {
		return (1); // if no tamagotchi in db, we create tamagotchi with id #1
	}


	row = mysql_fetch_row(res);
	mysql_free_result(res);

	return (atoi(row[0]) + 1);
}

char			*get_color() {
	char		*color_list[2] = {"red", "purple"};
	char		*color;
	int		i;

	srand(time(NULL));

	i = rand() % 2;

	color = ft_strnew(strlen(color_list[i]));

	strcpy(color, color_list[i]);

	return (color);
}


s_tamagotchi		*create_tamagotchi(MYSQL *conn, char *name) {
	time_t		curr;
	char		query[QUERY_SIZE];
	int		id;
	char		*color;

	curr = time(NULL);
	id = get_id(conn);

	color = get_color();

	printf("COLOR: %s\n", color);
	printf("ID: %d\n", id);


	snprintf(query, QUERY_SIZE, "INSERT INTO TAMAGOTCHIS VALUES (%d, \"%s\", \"%s\", %ld, %d, %d, %ld, %ld, %ld, NULL, 100, %ld, 1, 1);", id, name, color, curr, 1, 0, curr, curr, curr, curr);


	free(color);

	mysql_query(conn, query);
	printf("QUERY: %s\n", query);

	return init_tamagotchi(conn, id);
}
