#ifndef TAMAGOTCHI_H
# define TAMAGOTCHI_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <gtk/gtk.h>
# include <mysql/mysql.h>


typedef struct 	Tamagotchi {
	char		*name;
	char		*color;
	char		*birthdate;
	unsigned char	alive;
	char		*last_fed;
	char		*last_washed;
	char		*last_played;
	char		*last_worked;
	unsigned short	health_bar;
	char		*last_health_update;
	char		*outfit;
} s_tamagotchi;


MYSQL		*db_connect();
void 		game_graphic(int*, char***); 
s_tamagotchi	*init_tamagotchi(MYSQL *conn, int id_tamagotchi);
void		print_tamagotchi(s_tamagotchi *tamagotchi);
void		free_tamagotchi(s_tamagotchi *tamagotchi);

#endif
