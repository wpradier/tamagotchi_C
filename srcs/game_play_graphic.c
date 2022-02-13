#include "tamagotchi.h"

#define COUNT 5

void setImage(GtkWidget *widget, gpointer data);
void changeImage(GtkWidget *widget, gpointer data);
// void getTime(char *ptr);

int count = 0;
char *start_game;
char *last_action;

// void getTime(char *ptr){
//   /* time */
//   /* read time */
//    time_t now = time (NULL);
//
//    /* convert in localtime */
//    struct tm tm_now = *localtime (&now);
//
//    /* create char HH:MM:SS */
//    char s_now[sizeof "HH:MM:SS"];
//    strftime (s_now, sizeof s_now, "%H:%M:%S", &tm_now);
//
//     if (count == 1){
//       start_game = s_now;
//     }else{
//       last_action = s_now;
//     }
//
//    // pour comparer deux dates : difftime()
// }

void setImage(GtkWidget *widget, gpointer data){
  if (widget) g_print("\n");

  char *file = "imgs/calque.png";

  gtk_image_set_from_file(GTK_IMAGE(data), file);

}

void changeImage(GtkWidget *widget, gpointer data){
  if (widget) g_print("\n");

  if (count < COUNT){
    count += 1;
    int random;
    GtkWidget *image_case;
    GtkWidget *button;

    //getTime();
    start_game = start_game;
    g_print("\nstart_game : %s", start_game);
    g_print("\nlast_action : %s", last_action);

    srand( time( NULL ) );
    random = rand() % 25 + 0;

    char id2[200];
    sprintf(id2, "%d", random);

    char idtest2[200];
    sprintf(idtest2, "%d %d", random, random);

    /* init tamagotchi image */
    image_case = GTK_WIDGET(gtk_builder_get_object(data, id2));
    button = GTK_WIDGET(gtk_builder_get_object(data, idtest2));
    char *file2 = "imgs/game.png";
    // /* change link image */
    gtk_image_set_from_file(GTK_IMAGE(image_case), file2);

    g_signal_connect(button, "clicked", G_CALLBACK(setImage), (gpointer) image_case);
    g_signal_connect(button, "clicked", G_CALLBACK(changeImage), (gpointer) data);
  } else if (count == COUNT){
    g_print("\njeu fini !!!!");
    g_print("\nstart_game : %s", start_game);
    g_print("\nlast_action : %s", last_action);
    // double result_time = difftime(last_action, start_game);
    // g_print("\n%lf", result_time);
  }
}

void gamePlayGraphic(){
  GtkBuilder *gtkBuilder;
  GtkWidget *window;
  //GtkWidget *image_case;
  GtkWidget *button;
  int random;
  //int* lastId = 0;

  /* Create window gtk */
  gtkBuilder = gtk_builder_new();
  gtkBuilder = gtk_builder_new_from_file("windows/gameWindow.glade");
  window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_window"));
  gtk_builder_connect_signals(gtkBuilder, NULL);

  //for (int i = 0; i < COUNT; ++i){
    srand( time( NULL ) );
    random = rand() % 25 + 0;

    char id[200];
    sprintf(id, "%d", random);

    char idtest[200];
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
      changeImage(button, gtkBuilder);

  //}


  gtk_widget_show_all(window);
}
