#include "tamagotchi.h"

void setImage(GtkWidget *, gpointer);
void changeImage(GtkWidget *, gpointer);
void returnGameGraphic(GtkWidget *, gpointer);

void returnGameGraphic(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);
  parameters->data = NULL;

  gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->data));

  free(parameters);
}

void    setImage(GtkWidget *widget, gpointer data){
  char  *file = "imgs/calque.png";

  if (widget) g_print("\n");

  gtk_image_set_from_file(GTK_IMAGE(data), file);
}

void              changeImage(GtkWidget *widget, gpointer data){
   g_print("---access FUNCTION---\n");
   s_parameters   *parameters;
   int            random;
   gpointer       test;
   GtkWidget      *image_case;
   GtkWidget      *button;
   GtkWidget      *container_end;
   GtkWidget      *button_return;
   GtkWidget      *window;
   static int     count = 0;
   char           *id2;
   char           *idtest2;
   char           *file2 = "imgs/game.png";
   int            count_game;

   parameters = (s_parameters *)data;

   if (widget) g_print("\n");

   count_game = parameters->config->hide_and_seek_duration;
   printf("---COUNT---: %d\n", count);

   if (count < count_game){
    g_print("---access IF---\n");
    id2 = ft_strnew(3);
    idtest2 = ft_strnew(6);
    count += 1;

    srand( time( NULL ) );
    random = rand() % 25 + 1;

    sprintf(id2, "%d", random);
    sprintf(idtest2, "%d %d", random, random);
    g_print("---access parameters---\n");
    test = parameters->data;
    parameters->data = test;
    g_print("---end access parameters---\n");
    image_case = GTK_WIDGET(gtk_builder_get_object(parameters->data, id2));
    button = GTK_WIDGET(gtk_builder_get_object(parameters->data, idtest2));

    free(id2);
    free(idtest2);

    gtk_image_set_from_file(GTK_IMAGE(image_case), file2);

    g_signal_connect(button, "clicked", G_CALLBACK(setImage), (gpointer) image_case);
    g_signal_connect(button, "clicked", G_CALLBACK(changeImage), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->data));
  } else if (count == count_game){
    g_print("\njeu fini !!!!");
    count = 0;
    parameters->gamestate->money += 25;
    container_end = GTK_WIDGET(gtk_builder_get_object(parameters->data, "container_end"));
    gtk_widget_show(container_end);

    window = GTK_WIDGET(gtk_builder_get_object(parameters->data, "game_window"));

    button_return = GTK_WIDGET(gtk_builder_get_object(parameters->data, "button_return"));
    g_signal_connect(button_return, "clicked", G_CALLBACK(returnGameGraphic), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)window));
  }
  //free(parameters);
}

void          gamePlayGraphic(s_parameters *parameters){
  GtkBuilder  *gtkBuilder;
  GtkWidget   *window;
  GtkWidget   *button;
  GtkWidget   *container_end;
  int         random;
  char        *id;
  char        *idtest;

  /* Create window gtk */
  gtkBuilder = gtk_builder_new();
  gtkBuilder = gtk_builder_new_from_file("windows/gameWindow.glade");
  window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_window"));
  gtk_builder_connect_signals(gtkBuilder, NULL);

  id = ft_strnew(3);
  idtest = ft_strnew(6);

  srand( time( NULL ) );
  random = rand() % 25 + 1;

  sprintf(id, "%d", random);

  sprintf(idtest, "%d %d", random, random);

  button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, idtest));

  free(id);
  free(idtest);

  changeImage(button, (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->config, (gpointer)gtkBuilder));

  gtk_widget_show_all(window);

  container_end = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "container_end"));
  gtk_widget_hide(container_end);
}
