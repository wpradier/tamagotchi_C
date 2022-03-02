#include "tamagotchi.h"

void editName(GtkWidget *, gpointer);
void destroyWindow(GtkWidget *, gpointer);

void            destroyWindow(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);
  parameters->data = NULL;

  free(parameters);
}

void             editName(GtkWidget *widget, gpointer data){
    s_parameters *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");

    const gchar *recep_entry_text = gtk_entry_get_text(GTK_ENTRY(parameters->data));
    g_print("%s", recep_entry_text);

    free(parameters->tamagotchi->name);
    parameters->tamagotchi->name = ft_strnew(strlen((char *)recep_entry_text) + 1);
    create_tamagotchi(conn,   parameters->tamagotchi->name);
  	strcpy(parameters->tamagotchi->name, (char *)recep_entry_text);

    parameters->data = NULL;

    gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->data));

    free(parameters);
}

void         nameGraphic(s_parameters *parameters){
  GtkBuilder *gtkBuilderName;
	GtkWidget  *windowName;
  GtkWidget  *edit_name_button;
  GtkWidget  *name_input;

  gtkBuilderName = gtk_builder_new();
  gtkBuilderName = gtk_builder_new_from_file("windows/nameWindow.glade");
  windowName = GTK_WIDGET(gtk_builder_get_object(gtkBuilderName, "name_window"));
  gtk_builder_connect_signals(gtkBuilderName, NULL);

  edit_name_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilderName, "edit_name_button"));
  name_input = GTK_WIDGET(gtk_builder_get_object(gtkBuilderName, "name_input"));

  g_signal_connect(edit_name_button, "clicked", G_CALLBACK(editName), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)name_input));
  g_signal_connect(edit_name_button, "clicked", G_CALLBACK(destroyWindow), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)windowName));

  free(parameters);

  gtk_widget_show_all(windowName);
}
