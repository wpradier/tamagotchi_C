#include "tamagotchi.h"

int			main(int argc, char **argv) {
	GtkBuilder	*gtkBuilder;
	GtkWidget 	*window;
	MYSQL		*conn;
	s_tamagotchi	*tamagotchi;

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
	free_tamagotchi(tamagotchi);

	gtk_main();
	mysql_close(conn);

	return EXIT_SUCCESS;
}
