#include "tamagotchi.h"

int main(int argc, char **argv){
	int choice;

	do{
		printf("Tapez 0 pour jouer en console ou 1 pour jouer en graphique : ");
		scanf("%d", &choice);
		fflush(stdin); 
	}while(choice != 0 && choice != 1);


	/* Connect at the database */
	db_connect();

	if (choice == 0){
		printf("Vous êtes en version console\n");

		game_consol();
	}else{
		printf("Vous êtes en version graphique\n");

		game_graphic(&argc, &argv);
   	gtk_main();

   	gchar *TEST = "TEST\n";
   	g_print("%s", TEST );
	}

	return EXIT_SUCCESS;
}
