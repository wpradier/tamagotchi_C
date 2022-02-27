#include "tamagotchi.h"

void        marketButton(GtkWidget *, gpointer);
void        updateFood(GtkWidget *, gpointer);
void        updateHealth(GtkWidget *, gpointer);
void        updateHygiene(GtkWidget *, gpointer);
void        gamePlay(GtkWidget *, gpointer);
void        goToWork(GtkWidget *, gpointer);
void        changeImageState(GtkWidget *, gpointer);

void            marketButton(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  parameters = (s_parameters *)data;

  if (widget) g_print("Magasin\n");
  gtk_widget_destroy(parameters->data);

  shopPage(parameters);

  free(parameters);
}

void              updateFood(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");

    if (parameters->gamestate->food > 0){
      double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
      value -= 0.25;
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(parameters->data), value);

      parameters->gamestate->food -= 1;

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

        parameters->tamagotchi->last_fed = s_now;
     }else{
       alertPage("Achetez de la nourriture !");
     }

      //free(parameters);

     // pour comparer deux dates : difftime()
}

void              updateHealth(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");

    if ( parameters->gamestate->health_kits > 0 ){
      double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
      value = 1;
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(parameters->data), value);

      parameters->gamestate->health_kits -= 1;

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

       parameters->tamagotchi->last_health_update = s_now;
     }else{
       alertPage("Achetez des kits de soin !");
     }

     //free(parameters);

     // pour comparer deux dates : difftime()
}

void              updateHygiene(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");
    double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
    value += 0.25;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(parameters->data), value);

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

     parameters->tamagotchi->last_washed = s_now;
     parameters->data = NULL;

     //free(parameters);

     // pour comparer deux dates : difftime()
}

void              goToWork(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Aller au travail\n");

    char *file = "imgs/calqueWork.png";
    gtk_image_set_from_file(GTK_IMAGE(parameters->data), file);

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

     parameters->tamagotchi->last_worked = s_now;
     parameters->data = NULL;

     free(parameters);

     // pour comparer deux dates : difftime()
}

void            gamePlay(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  parameters = (s_parameters *)data;

  if (widget) g_print("Jeu lancé\n");

  gtk_widget_destroy(parameters->data);

  gamePlayGraphic(parameters);

  free(parameters);
}

void            changeTamagotchi(GtkWidget *widget, gpointer data){
  static int    count = 1;
  s_parameters  *parameters;
  int           random;

  parameters = (s_parameters *)data;

  if (widget) g_print("NAISSANCE DU TAMAGO\n");

  if (count == 1){
    srand( time( NULL ) );
    random = rand() % 2 + 0;
    if (random == 1){
      parameters->tamagotchi->color = "red";
    }else{
      parameters->tamagotchi->color = "purple";
    }
  }else{
    count += 1;
  }

  free(parameters);
}

void            changeImageState(GtkWidget *widget, gpointer data){
  GtkWidget     *food_bar;
  GtkWidget     *image_tamagotchi;
  GtkWidget     *hygiene_bar;
  double        value_food;
  double        value_hygiene;
  s_parameters  *parameters;
  char          *red = "red";
  char          *purple = "purple";
  char          *image_file;

  if (widget) g_print("Change image food\n");

  parameters = (s_parameters *)data;

  image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(parameters->data, "tamagotchi_image"));
  food_bar = GTK_WIDGET(gtk_builder_get_object(parameters->data, "food_bar"));
  hygiene_bar = GTK_WIDGET(gtk_builder_get_object(parameters->data, "hygiene_bar"));
  value_food = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(food_bar));
  value_hygiene = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(hygiene_bar));

  if (parameters->tamagotchi->color != red && parameters->tamagotchi->color != purple){
    image_file = "imgs/oeuf(1).png";
  }else{
    if (value_food > 0.5){
      if ( parameters->tamagotchi->color == red ){
        image_file = "imgs/tamagotchiRedChild/tamagotchiRedHungerChild.png";
      }else{
        image_file = "imgs/tamagotchiPurpleChild/tamagotchiPurpleHungerChild.png";
      }
    }else{
      if (value_hygiene < 0.5){
        if ( parameters->tamagotchi->color == red ){
          image_file = "imgs/tamagotchiRedChild/tamagotchiRedDirtyChild.png";
        }else{
          image_file = "imgs/tamagotchiPurpleChild/tamagotchiPurpleDirtyChild.png";
        }
      }else{
        if ( parameters->tamagotchi->color == red ){
          image_file = "imgs/tamagotchiRedChild/tamagotchiRedChild.png";
        }else{
          image_file = "imgs/tamagotchiPurpleChild/tamagotchiPurpleChild.png";
        }
      }
    }
  }

  gtk_image_set_from_file(GTK_IMAGE(image_tamagotchi), image_file);

  //free(parameters);
}

void         gameGraphic(s_parameters *parameters)
{
	//init variable
	GtkBuilder *gtkBuilder;
	GtkWidget  *window;
	GtkWidget  *market_button;
  GtkWidget  *image_tamagotchi;
  GtkWidget  *food_bar;
  GtkWidget  *food_button;
  GtkWidget  *game_button;
  GtkWidget  *health_bar;
  GtkWidget  *health_button;
  GtkWidget  *hygiene_bar;
  GtkWidget  *hygiene_button;
  GtkWidget  *work_button;
  GtkWidget  *name_label;
  GtkWidget  *image_background;

  /* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("windows/principalWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  g_print("NOM : %s\n", parameters->tamagotchi->name);
  print_parameters(parameters);

  image_background = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "image_background"));
  get_weather((gpointer)image_background);

  name_label = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "name_label"));
  gtk_label_set_text(GTK_LABEL(name_label), (gchar *)parameters->tamagotchi->name);

	market_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "market_button"));
	g_signal_connect(market_button, "clicked", G_CALLBACK(marketButton), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)window));

	image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tamagotchi_image"));

  food_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "food_bar"));
  food_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_food"));
  changeImageState(food_button, (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)gtkBuilder));
  g_signal_connect(food_button, "clicked", G_CALLBACK(updateFood), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)food_bar));
  g_signal_connect(food_button, "clicked", G_CALLBACK(changeImageState), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)gtkBuilder));

	health_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "health_bar"));
  health_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "health_button"));
  g_signal_connect(health_button, "clicked", G_CALLBACK(updateHealth), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)health_bar));

	hygiene_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hygiene_bar"));
  hygiene_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hygiene_button"));
  g_signal_connect(hygiene_button, "clicked", G_CALLBACK(updateHygiene), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)hygiene_bar));
  g_signal_connect(hygiene_button, "clicked", G_CALLBACK(changeImageState), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)gtkBuilder));

  work_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_work"));
  g_signal_connect(work_button, "clicked", G_CALLBACK(goToWork), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)image_tamagotchi));

  game_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_button"));
  g_signal_connect(game_button, "clicked", G_CALLBACK(changeTamagotchi), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)image_tamagotchi));
  g_signal_connect(game_button, "clicked", G_CALLBACK(gamePlay), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)window));

  free(parameters);

	gtk_widget_show_all(window);
}
