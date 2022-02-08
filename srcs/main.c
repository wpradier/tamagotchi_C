#include "tamagotchi.h"

s_gamestate		*GAMESTATE;

int			main(int argc, char **argv) {
	GtkBuilder	*gtkBuilder;
	GtkWidget 	*window;
	MYSQL		*conn;
	s_tamagotchi	*tamagotchi;
	s_save		*save;

	conn = db_connect();

	gtk_init(&argc, &argv);

	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "test-glade.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));

	g_object_unref(G_OBJECT(gtkBuilder));
	gtk_widget_show_all(window);

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

	return EXIT_SUCCESS;
}
