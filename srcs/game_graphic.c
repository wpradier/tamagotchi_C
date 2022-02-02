#include "tamagotchi.h"

static void buttonClicked();
void updateFood();
void gamePlay();

static void buttonClicked(){
        g_print("Bouton pressé\n");
}

void updateFood(GtkWidget *widget, gpointer data){
    if (widget) g_print("Modification progresse barre\n");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), 0.9);

    /* time */
    /* read time */
     time_t now = time (NULL);

     /* convert in localtime */
     struct tm tm_now = *localtime (&now);

     /* create char JJ/MM/AAAA HH:MM:SS */
     char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];

     strftime (s_now, sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);

     /* print result : */
     g_print("'%s'\n", s_now);

     // pour comparer deux dates : difftime()
}

void gamePlay(GtkWidget *widget, gpointer data){
  if (widget) g_print("Jeu lancé\n");
  gtk_widget_destroy(data);

  GtkBuilder *gtkBuilder;
	GtkWidget *window;

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("gameWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  gtk_widget_show_all(window);
}

/*
void editName(GtkWidget *widget, gchar data){
    if (widget) g_print("Modification progresse barre\n");
    recep_entry_text = gtk_entry_get_text(GTK_ENTRY(name_input));
}*/

void editName(GtkWidget *widget, gpointer data){
    if (widget) g_print("Modification progresse barre\n");

    const gchar *recep_entry_text = gtk_entry_get_text(GTK_ENTRY(data));
    g_print("%s", recep_entry_text);
}

void game_graphic(int *argc, char***argv)
{
	//init variable
	GtkBuilder *gtkBuilder;
	GtkWidget *window;
	GtkWidget *market_button;
  GtkWidget *image_tamagotchi;
  GtkWidget *food_bar;
  GtkWidget *food_button;
  GtkWidget *edit_name_button;
  GtkWidget *name_input;
  GtkWidget *game_button;
  //GtkWidget *name_label;

	/* init gtk */
	gtk_init(argc, argv);

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("test-glade.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

	/* init button market*/
	market_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "market_button"));
	g_signal_connect(market_button, "clicked", G_CALLBACK(buttonClicked), (gpointer) NULL);

  /* init tamagotchi image */
	image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tamagotchi_image"));
  char *file = "image.jpg";
  /* change link image */
  gtk_image_set_from_file(GTK_IMAGE(image_tamagotchi), file);

  /* init container food_bar */
	food_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "food_bar"));

  /*init button food */
  food_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_food"));
  g_signal_connect(food_button, "clicked", G_CALLBACK(updateFood), (gpointer) food_bar);

  /* init button game */
  game_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_button"));
  g_signal_connect(game_button, "clicked", G_CALLBACK(gamePlay), (gpointer) window);

  /* init name input */
  name_input = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "name_input"));

  /* init edit name button */
  edit_name_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "edit_name_button"));

  //g_signal_connect(edit_name_button, "clicked", G_CALLBACK(editName), (gchar) recep_entry_text);
  g_signal_connect(edit_name_button, "clicked", G_CALLBACK(editName), (gpointer) name_input);

  // A LA PLACE DE recep_entry_text METTRE LE NOM STOCKE DANS LA BDD
  /* init label name */
  //name_label = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "name_label"));

  /* Change name label */
  //gtk_label_set_text(GTK_LABEL(name_label), recep_entry_text);

  /* Get name label */
  //const gchar *recep = gtk_label_get_text(GTK_LABEL(name_label));
  //g_print("%s", recep);


	/* Print and event loop */
	gtk_widget_show_all(window);

  /* hidden name_input */
  //gtk_widget_hide(name_input);
}
