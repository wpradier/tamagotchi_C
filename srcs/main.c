#include "tamagotchi.h"

int			main(int argc, char **argv) {
  MYSQL					*conn;
	s_tamagotchi	*tamagotchi;

	s_save		    *save;
	s_config	    *config;
  int 					choice;
	s_gamestate		*gamestate;
	s_parameters	*parameters;

	conn = db_connect();

	gtk_init(&argc, &argv);

	printf("LOAD CONF\n");
	if (!(config = load_conf("tamago.conf"))) {
		mysql_close(conn);
		return (EXIT_FAILURE);
	}
	print_conf(config);

	printf("INIT\n");
	tamagotchi = create_tamagotchi(conn, "Jean-Charles");
	printf("INITIALIZED\n");
	print_tamagotchi(tamagotchi);
	printf("FETCH SAVE\n");
	save = fetch_save(conn, 1);
	printf("SAVE:\n");
	printf("name: %s, food: %d, money: %d\n", save->name, save->food, save->money);
	printf("GAMESTATE:\n");
	gamestate = init_gamestate(save, tamagotchi, config);
	printf("Health: %d, health kits: %d, food: %d, money: %d\n", gamestate->health, gamestate->health_kits, gamestate->money, gamestate->food);
	parameters = init_parameters(tamagotchi, gamestate, config, NULL);
  print_parameters(parameters);

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
    print_parameters(parameters);
		homePage(&argc, &argv, parameters);
    gtk_main();
	}

	return (EXIT_SUCCESS);
}
