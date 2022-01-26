#include "tamagotchi.h"

static void buttonClicked();

static void buttonClicked(){
        g_print("Bouton presser\n");
}

void game_graphic(int *argc, char***argv)
{
	//init variable
	GtkBuilder *gtkBuilder;
	GtkWidget *window;
	GtkWidget *label_test;
	GtkWidget *button_test;
  GtkWidget *image_tamagotchi;
  GtkWidget *food_barre;

	/* init gtk */
	gtk_init(argc, argv);

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("test-glade.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

	/* init label test */
	label_test = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_test"));

	/* Change test label */
  char *test = "test";
	gtk_label_set_text(GTK_LABEL(label_test), test);

	/* Get test label */
	const gchar *recep = gtk_label_get_text(GTK_LABEL(label_test));
	g_print("%s", recep);

	/* init button test*/
	button_test = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "buttonTest"));
	g_signal_connect(button_test, "clicked", G_CALLBACK(buttonClicked), (gpointer) NULL);

  /* init tamagotchi image */
	image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tamagotchi_image"));
  char *file = "image.jpg";
  gtk_image_set_from_file(GTK_IMAGE(image_tamagotchi), file);

  /* init container food_barre */
	food_barre = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "food_barre"));
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(food_barre), 0.5);

	/* Print and event loop */
	gtk_widget_show_all(window);
}
