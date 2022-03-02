#include "tamagotchi.h"

int			main(int argc, char **argv) {
  MYSQL					*conn;
	s_save		    *save;
	s_config	    *config;
  int 					choice;
	s_parameters	*parameters;

	conn = db_connect();

	gtk_init(&argc, &argv);

	printf("LOAD CONF\n");
	if (!(config = load_conf("tamago.conf"))) {
		mysql_close(conn);
		return (EXIT_FAILURE);
	}
	print_conf(config);

	printf("FETCH SAVE\n");
	save = fetch_save(conn, 1);
	printf("SAVE:\n");
	printf("name: %s, food: %d, money: %d\n", save->name, save->food, save->money);
	parameters = init_parameters(save, NULL, NULL, config, conn, NULL);

	do{
		printf("Tapez 0 pour jouer en console ou 1 pour jouer en graphique : ");
		scanf("%d", &choice);
	}while(choice != 0 && choice != 1);

	if (choice == 0){
		printf("Vous êtes en version console\n");

		game_consol(parameters);
	}else{
		printf("Vous êtes en version graphique\n");


    printf("CALL HOME PAGE\n");
		homePage(&argc, &argv, parameters);
    gtk_main();
	}

	return (EXIT_SUCCESS);
}
