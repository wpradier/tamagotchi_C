#include "tamagotchi.h"

void  deleteHomePage(GtkWidget *, gpointer);

void            deleteHomePage(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  printf("DELETE HOME PAGE : \n");
  print_parameters(parameters);

  gtk_widget_destroy(parameters->data);

  parameters->data = NULL;
  nameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->data));
  free(parameters);
}

void          homePage(int *argc, char***argv, s_parameters *parameters){
  //init variable
	GtkBuilder  *gtkBuilder;
	GtkWidget   *window;
  GtkWidget   *continue_button;
  GtkWidget   *load_button;
  GtkWidget   *new_button;

	/* init gtk */
	gtk_init(argc, argv);
  
  printf("HOME PAGE : \n");
  print_parameters(parameters);

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("./windows/homeWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  continue_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "continue_button"));
  gtk_widget_set_opacity(continue_button, 0.5);

  load_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "load_button"));
  gtk_widget_set_opacity(load_button, 0.5);

  new_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "new_button"));
  g_signal_connect(new_button, "clicked", G_CALLBACK(deleteHomePage), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)window));

  gtk_widget_show_all(window);
}
