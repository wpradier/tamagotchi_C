#include "tamagotchi.h"

void gameGraphicReturn(GtkWidget *, gpointer);

void            gameGraphicReturn(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);
  parameters->data = NULL;

  gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->data));

  free(parameters);
}

void          shopPage(s_parameters *parameters){
  GtkBuilder  *gtkBuilder;
  GtkWidget   *window;
  GtkWidget   *return_button;
  GtkWidget   *tamacash_label;
  GtkWidget   *label_food;
  GtkWidget   *label_health;
  char        *display_money;
  char        *display_food;
  char        *display_health;

	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("windows/shopWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "shop_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  tamacash_label = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tamacash_label"));
  display_money = ft_strnew(10);
  sprintf(display_money, "%d", parameters->gamestate->money);
  gtk_label_set_text(GTK_LABEL(tamacash_label), (gchar *)display_money);

  free(display_money);

  label_food = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_food"));
  display_food = ft_strnew(10);
  sprintf(display_food, "%d", parameters->gamestate->food);
  gtk_label_set_text(GTK_LABEL(label_food), (gchar *)display_food);

  label_health = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_health"));
  display_health = ft_strnew(10);
  sprintf(display_health, "%d", parameters->gamestate->health_kits); 
  gtk_label_set_text(GTK_LABEL(label_health), (gchar *)display_health);

  return_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "return_button"));
  g_signal_connect(return_button, "clicked", G_CALLBACK(gameGraphicReturn), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)window));

  gtk_widget_show_all(window);
}
