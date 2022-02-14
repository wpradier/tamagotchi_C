#include "tamagotchi.h"

s_gamestate		*GAMESTATE;

int			main(int argc, char **argv) {
	MYSQL		*conn;
	s_tamagotchi	*tamagotchi;
	s_save		*save;
	int choice;

	conn = db_connect();

	printf("INIT\n");
	tamagotchi = init_tamagotchi(conn, 1);
	printf("INITIALIZED\n");
	print_tamagotchi(tamagotchi);
	printf("FETCH SAVE\n");
	save = fetch_save(conn, 1);
	printf("SAVE:\n");
	printf("name: %s, food: %d, money: %d\n", save->name, save->food, save->money);
	printf("GAMESTATE:\n");
	GAMESTATE = init_gamestate(save, tamagotchi);
	printf("Health: %d, health kits: %d, food: %d, money: %d", GAMESTATE->health, GAMESTATE->health_kits, GAMESTATE->money, GAMESTATE->food);

	free_tamagotchi(tamagotchi);

	//gtk_main();
	mysql_close(conn);

	do{
		printf("Tapez 0 pour jouer en console ou 1 pour jouer en graphique : ");
		scanf("%d", &choice);
	}while(choice != 0 && choice != 1);

	if (choice == 0){
		printf("Vous êtes en version console\n");
	}else{
		printf("Vous êtes en version graphique\n");

		homePage(&argc, &argv);
    gtk_main();
	}


	return EXIT_SUCCESS;
}
