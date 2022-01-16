#include "tamagotchi.h"

void		db_connect() 
{
	char		*host = "127.0.0.1";
	char		*user = "root";
	char		*password = "root";
	char		*dbname = "tamagotchi_c";
	unsigned short	port = 12345;
	char		*unix_socket = NULL;
	unsigned int	flag = 0;
	MYSQL 		*conn;

	conn = mysql_init(NULL);

	if (!(mysql_real_connect(conn, host, user, password, dbname,
		       	port, unix_socket, flag))) {
		fprintf(stderr, "Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(EXIT_FAILURE);
	}
	printf("CONNECTED");
}
