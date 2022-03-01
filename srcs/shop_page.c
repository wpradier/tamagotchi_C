#include "tamagotchi.h"

void gameGraphicReturn(GtkWidget *, gpointer);
void buyFood(GtkWidget *, gpointer);
void buyHealth(GtkWidget *, gpointer);
void printBuy(GtkWidget *, gpointer);

void            printBuy(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;
  char          *display_money;

  if (widget) g_print("Achat de nourriture\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);

  printf("%s\n", gtk_label_get_text(GTK_LABEL(parameters->data)));

  display_money = ft_strnew(10);
  sprintf(display_money, "%d", parameters->gamestate->money);
  gtk_label_set_text(GTK_LABEL(parameters->data), (gchar *)display_money);

  free(display_money);
}

void            buyFood(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;
  char          *display_food;

  if (widget) g_print("Achat de nourriture\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);

  if (parameters->gamestate->money >= 20){
    parameters->gamestate->money -= 20;
    parameters->gamestate->food += 1;

    printf("%s\n", gtk_label_get_text(GTK_LABEL(parameters->data)));

    display_food = ft_strnew(10);
    sprintf(display_food, "%d", parameters->gamestate->food);
    gtk_label_set_text(GTK_LABEL(parameters->data), (gchar *)display_food);

    free(display_food);
  }else{
    alertPage("Vous n'avez pas assez d'argent !");
  }

  //free(parameters);
}

void            buyHealth(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;
  char          *display_health;

  if (widget) g_print("Achat de nourriture\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);


  if (parameters->gamestate->money >= 10){
    parameters->gamestate->money -= 10;
    parameters->gamestate->health_kits += 1;

    display_health = ft_strnew(10);
    sprintf(display_health, "%d", parameters->gamestate->health_kits);
    gtk_label_set_text(GTK_LABEL(parameters->data), (gchar *)display_health);
  }else{
    alertPage("Vous n'avez pas assez d'argent !");
  }

  free(display_health);

  //free(parameters);
}

void            gameGraphicReturn(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);
  parameters->data = NULL;

  gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->data));

  free(parameters);
}

void          shopPage(s_parameters *parameters){
  GtkBuilder  *gtkBuilder;
  GtkWidget   *window;
  GtkWidget   *return_button;
  GtkWidget   *tamacash_label;
  GtkWidget   *label_food;
  GtkWidget   *label_health;
  GtkWidget   *init_tamagotchi;
  GtkWidget   *basic_tamagotchi;
  GtkWidget   *girl_tamagotchi;
  GtkWidget   *hero_tamagotchi;
  GtkWidget   *button_buy_food;
  GtkWidget   *button_buy_health;
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

  free(display_food);

  label_health = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_health"));
  display_health = ft_strnew(10);
  sprintf(display_health, "%d", parameters->gamestate->health_kits);
  gtk_label_set_text(GTK_LABEL(label_health), (gchar *)display_health);

  free(display_health);

  init_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "init_tamagotchi"));
  basic_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "basic_tamagotchi"));
  girl_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "girl_tamagotchi"));
  hero_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hero_tamagotchi"));

  if (!strcmp(parameters->tamagotchi->color, "purple")){
    printf("ok");
    gtk_image_set_from_file(GTK_IMAGE(init_tamagotchi), "imgs/tamagotchiPurple/tamagotchiPurple0.png");
    gtk_image_set_from_file(GTK_IMAGE(basic_tamagotchi), "imgs/tamagotchiPurple/tamagotchiPurple1.png");
    gtk_image_set_from_file(GTK_IMAGE(girl_tamagotchi), "imgs/tamagotchiPurple/tamagotchiPurple2.png");
    gtk_image_set_from_file(GTK_IMAGE(hero_tamagotchi), "imgs/tamagotchiPurple/tamagotchiPurple3.png");
  }else{
    gtk_image_set_from_file(GTK_IMAGE(init_tamagotchi), "imgs/tamagotchiRed/tamagotchiRed0.png");
    gtk_image_set_from_file(GTK_IMAGE(basic_tamagotchi), "imgs/tamagotchiRed/tamagotchiRed1.png");
    gtk_image_set_from_file(GTK_IMAGE(girl_tamagotchi), "imgs/tamagotchiRed/tamagotchiRed2.png");
    gtk_image_set_from_file(GTK_IMAGE(hero_tamagotchi), "imgs/tamagotchiRed/tamagotchiRed3.png");
  }

  button_buy_food = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_buy_food"));
  g_signal_connect(button_buy_food, "clicked", G_CALLBACK(buyFood), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)label_food));
  g_signal_connect(button_buy_food, "clicked", G_CALLBACK(printBuy), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)tamacash_label));

  button_buy_health = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_buy_health"));
  g_signal_connect(button_buy_health, "clicked", G_CALLBACK(buyHealth), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)label_health));
  g_signal_connect(button_buy_health, "clicked", G_CALLBACK(printBuy), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)tamacash_label));

  return_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "return_button"));
  g_signal_connect(return_button, "clicked", G_CALLBACK(gameGraphicReturn), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)window));

  gtk_widget_show_all(window);
}
