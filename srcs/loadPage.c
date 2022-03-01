#include "tamagotchi.h"

void  deleteLoadPage(GtkWidget *, gpointer);

void            deleteLoadPage(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

    parameters = (s_parameters *)data;

    print_parameters(parameters);

    gtk_widget_destroy(parameters->data);

    parameters->data = NULL;
    gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->data));

    free(parameters);

}

void load_part(s_parameters *parameters){
  GtkBuilder *gtkBuilder;
  GtkWidget  *window;
  GtkWidget  *button_part1;

  gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("windows/chargeWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "load_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  button_part1 = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_part1"));
  gtk_button_set_label(GTK_BUTTON(button_part1), "test");
  g_signal_connect(button_part1, "clicked", G_CALLBACK(deleteLoadPage), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)window));

  gtk_widget_show_all(window);
}
