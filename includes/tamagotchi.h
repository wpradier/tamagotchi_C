#ifndef TAMAGOTCHI_H
# define TAMAGOTCHI_H

# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>
# include <mysql/mysql.h>
# include <time.h>

void	db_connect();
void 	homePage(int*, char***);
void  gamePlayGraphic(); 

#endif
