#include "tamagotchi.h"

#define COUNT 5

void setImage(GtkWidget *, gpointer);
void changeImage(GtkWidget *, gpointer);
void returnGameGraphic(GtkWidget *, gpointer);
// time_t getTime();
//
// time_t getTime(){
//   /* time */
//   /* read time */
//    time_t now = time (NULL);
//
//    /* convert in localtime */
//    // struct tm tm_now = *localtime (&now);
//    //
//    // /* create char HH:MM:SS */
//    // char s_now[sizeof "HH:MM:SS"];
//    // strftime (s_now, sizeof s_now, "%H:%M:%S", &tm_now);
//
//    return now;
//
//    // pour comparer deux dates : difftime()
// }

void returnGameGraphic(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);
  parameters->data = NULL;

  gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->data));

  free(parameters);
}

void    setImage(GtkWidget *widget, gpointer data){
  char  *file = "imgs/calque.png";

  if (widget) g_print("\n");

  gtk_image_set_from_file(GTK_IMAGE(data), file);
}

void              changeImage(GtkWidget *widget, gpointer data){
   s_parameters   *parameters;
   //static time_t start_game;
   //char         last_action;
   int            random;
   GtkWidget      *image_case;
   GtkWidget      *button;
   GtkWidget      *container_end;
   GtkWidget      *button_return;
   GtkWidget      *window;
   //GtkWidget    *start_time;
   static int     count = 0;
   char           id2[200];
   char           idtest2[200];
   char           *file2 = "imgs/game.png";

   parameters = (s_parameters *)data;

   if (widget) g_print("\n");

   /*init start_time*/
   //start_time = GTK_WIDGET(gtk_builder_get_object(data, "start_time"));

   if (count < COUNT){
    count += 1;

    // if (count == 1){
    //   start_game = time (NULL);
    //   gtk_label_set_text(GTK_LABEL(start_time), (gchar *)start_game);
    // }//else{
    //  last_action = (char)getTime();
    //}

    // g_print("\nstart_game : %s", start_game);
    // g_print("\nlast_action : %s", last_action);

    srand( time( NULL ) );
    random = rand() % 25 + 0;

    sprintf(id2, "%d", random);
    sprintf(idtest2, "%d %d", random, random);

    image_case = GTK_WIDGET(gtk_builder_get_object(parameters->data, id2));
    button = GTK_WIDGET(gtk_builder_get_object(parameters->data, idtest2));

    gtk_image_set_from_file(GTK_IMAGE(image_case), file2);

    g_signal_connect(button, "clicked", G_CALLBACK(setImage), (gpointer) image_case);
    g_signal_connect(button, "clicked", G_CALLBACK(changeImage), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, parameters->data));
  } else if (count == COUNT){
    g_print("\njeu fini !!!!");
    count = 0;
    parameters->gamestate->money += 25;
    container_end = GTK_WIDGET(gtk_builder_get_object(parameters->data, "container_end"));
    gtk_widget_show(container_end);

    window = GTK_WIDGET(gtk_builder_get_object(parameters->data, "game_window"));

    button_return = GTK_WIDGET(gtk_builder_get_object(parameters->data, "button_return"));
    g_signal_connect(button_return, "clicked", G_CALLBACK(returnGameGraphic), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)window));


    // g_print("\nstart_game : %s", start_game);
    // g_print("\nlast_action : %s", last_action);
    // double result_time = difftime(last_action, start_game);
    // g_print("\n%lf", result_time);
  }
  free(parameters);
}

void          gamePlayGraphic(s_parameters *parameters){
  GtkBuilder  *gtkBuilder;
  GtkWidget   *window;
  //GtkWidget *image_case;
  GtkWidget   *button;
  GtkWidget   *container_end;
  int         random;
  char        id[200];
  char        idtest[200];
  //int* lastId = 0;

  /* Create window gtk */
  gtkBuilder = gtk_builder_new();
  gtkBuilder = gtk_builder_new_from_file("windows/gameWindow.glade");
  window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_window"));
  gtk_builder_connect_signals(gtkBuilder, NULL);

  //for (int i = 0; i < COUNT; ++i){
    srand( time( NULL ) );
    random = rand() % 25 + 0;

    sprintf(id, "%d", random);

    sprintf(idtest, "%d %d", random, random);
    g_print("%s", id);

    /* init tamagotchi image */
    //image_case = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, id));
    button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, idtest));
    //char *file = "tamagotchi.png";
    // /* change link image */
    //gtk_image_set_from_file(GTK_IMAGE(image_case), file);
    //*lastId = atoi(id);

    // ATTENTION : il faut que ce code ne s'exécute qu'une seule et unique fois
      // g_signal_connect(button, "clicked", G_CALLBACK(test), (gpointer) image_case);
      // g_signal_connect(button, "clicked", G_CALLBACK(changeImage), (gpointer) gtkBuilder);

      changeImage(button, (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)gtkBuilder));

  //}
      gtk_widget_show_all(window);

      container_end = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "container_end"));
      gtk_widget_hide(container_end);
}
