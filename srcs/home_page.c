#include "tamagotchi.h"

void  deleteHomePageNew(GtkWidget *, gpointer);
void  deleteHomePage(GtkWidget *, gpointer);

void            deleteHomePageNew(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  if (gtk_widget_get_opacity(widget) <= 0.4 || gtk_widget_get_opacity(widget) >= 0.6){

    parameters = (s_parameters *)data;
    printf("DELETE HOME PAGE : \n");

    gtk_widget_destroy(parameters->data);

    parameters->data = NULL;

    if (!strcmp(gtk_button_get_label(GTK_BUTTON(widget)), "Nouveau")){
      nameGraphic(init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, parameters->data));
    }else{
      gameGraphic(init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, parameters->data));
    }

    free(parameters);
  }
}

void            deleteHomePage(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  if (gtk_widget_get_opacity(widget) <= 0.4 || gtk_widget_get_opacity(widget) >= 0.6){

    parameters = (s_parameters *)data;
    printf("DELETE HOME PAGE : \n");

    gtk_widget_destroy(parameters->data);

    parameters->data = NULL;
    load_part(init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, parameters->data));

    free(parameters);
  }
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

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("./windows/homeWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  continue_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "continue_button"));
  gtk_widget_set_opacity(continue_button, 0.5);
  g_signal_connect(continue_button, "clicked", G_CALLBACK(deleteHomePageNew), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)window));

  load_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "load_button"));
  gtk_widget_set_opacity(load_button, 0.5);
  g_signal_connect(load_button, "clicked", G_CALLBACK(deleteHomePage), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)window));

  new_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "new_button"));
  g_signal_connect(new_button, "clicked", G_CALLBACK(deleteHomePageNew), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)window));

  gtk_widget_show_all(window);
}
