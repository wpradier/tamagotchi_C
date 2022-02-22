#ifndef TAMAGOTCHI_H
# define TAMAGOTCHI_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <gtk/gtk.h>
# include <mysql/mysql.h>


# define BUFF_SIZE 50
# define QUERY_SIZE 300


typedef unsigned char	mybool;

typedef struct	Config {
	mybool		display_healthbar;
	mybool		display_hungerbar;
	mybool		display_funbar;
	mybool		display_hygienebar;	
	int		hunger_frequency;
	int		work_duration;
	int		grow_time;
	int		hide_and_seek_duration;
	int		dictation_duration;
	char		*location;
} s_config;

typedef struct	Save {
	char		*name;
	int		food;
	int		money;
	int		health_kits;
} s_save;

typedef struct 	Tamagotchi {
	char		*name;
	char		*color;
	char		*birthdate;
	mybool		alive;
	char		*last_fed;
	char		*last_washed;
	char		*last_played;
	char		*last_worked;
	unsigned short	health_bar;
	char		*last_health_update;
	char		*outfit;
} s_tamagotchi;

typedef struct	GameState {
	int		health;
	int		hunger;
	int		fun;
	int		hygiene;
	int		health_kits;
	int		food;
	int		money;
} s_gamestate;


MYSQL		*db_connect();
void 		game_graphic(int*, char***); 
s_save		*fetch_save(MYSQL *conn, int save_id);
s_config	*load_conf(char *conf_path);
void		print_conf(s_config *config);
void		free_conf(s_config *config);
s_tamagotchi	*init_tamagotchi(MYSQL *conn, int id_tamagotchi);
void		print_tamagotchi(s_tamagotchi *tamagotchi);
void		free_tamagotchi(s_tamagotchi *tamagotchi);
s_gamestate	*init_gamestate(s_save *save, s_tamagotchi *tamagotchi);

#endif
