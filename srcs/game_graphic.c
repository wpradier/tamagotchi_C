#include "tamagotchi.h"

void        marketButton(GtkWidget *, gpointer);
void        updateFood(GtkWidget *, gpointer);
void        updateHealth(GtkWidget *, gpointer);
void        updateHygiene(GtkWidget *, gpointer);
void        gamePlay(GtkWidget *, gpointer);
void        goToWork(GtkWidget *, gpointer);
void        changeImageState(GtkWidget *, gpointer);
void        updateBored(GtkWidget *, gpointer);
gboolean saveSeconds(gpointer);

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

     time_t now = time (NULL);

      parameters->tamagotchi->last_fed = now;
      save_tamagotchi(parameters->conn, parameters->tamagotchi);
   }else{
     alertPage("Achetez de la nourriture !");
   }
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

       time_t now = time (NULL);
       parameters->tamagotchi->last_health_update = now;
       save_tamagotchi(parameters->conn, parameters->tamagotchi);
     }else{
       alertPage("Achetez des kits de soin !");
     }
}

void              updateHygiene(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");
    double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
    value += 0.25;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(parameters->data), value);

   time_t now = time (NULL);

   parameters->tamagotchi->last_washed = now;
   save_tamagotchi(parameters->conn, parameters->tamagotchi);
   parameters->data = NULL;
}

void              updateBored(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");
    double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
    value += 0.25;
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(parameters->data), value);

   time_t now = time (NULL);

   parameters->tamagotchi->last_played = now;
   save_tamagotchi(parameters->conn, parameters->tamagotchi);
   parameters->data = NULL;
}

void              goToWork(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Aller au travail\n");

    char *file = "imgs/calqueWork.png";
    gtk_image_set_from_file(GTK_IMAGE(parameters->data), file);

   time_t now = time (NULL);

   parameters->tamagotchi->last_worked = now;
   save_tamagotchi(parameters->conn, parameters->tamagotchi);
   parameters->data = NULL;

   free(parameters);
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

  parameters = (s_parameters *)data;

  if (widget) g_print("NAISSANCE DU TAMAGO\n");

   if (count == 1 && parameters->tamagotchi->born == 0){
     time_t now = time (NULL);
     parameters->tamagotchi->birthdate = now;
     parameters->tamagotchi->born = 1;
     save_tamagotchi(parameters->conn, parameters->tamagotchi);
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
  char          *image_file;

  if (widget) g_print("Change image food\n");

  parameters = (s_parameters *)data;

  printf("TEST1\n");

  image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(parameters->data, "tamagotchi_image"));
  food_bar = GTK_WIDGET(gtk_builder_get_object(parameters->data, "food_bar"));
  hygiene_bar = GTK_WIDGET(gtk_builder_get_object(parameters->data, "hygiene_bar"));
  value_food = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(food_bar));
  value_hygiene = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(hygiene_bar));

  printf("TEST2\n");
  if (parameters->tamagotchi->born != 1){
    image_file = "imgs/egg.png";
  }else{
    if (value_food > 0.5){
      if ((parameters->tamagotchi->birthdate - time(NULL)) > parameters->config->grow_time){
        if ( !strcmp(parameters->tamagotchi->color, "red")){
          if (!strcmp(parameters->tamagotchi->outfit, "none")){
            image_file = "imgs/tamagotchiRed/tamagotchiRedHunger0.png";
          }else{
            if (!strcmp(parameters->tamagotchi->outfit, "tee-shirt")){
              image_file = "imgs/tamagotchiRed/tamagotchiRedHunger1.png";
            }else{
              if (!strcmp(parameters->tamagotchi->outfit, "accessories")){
                image_file = "imgs/tamagotchiRed/tamagotchiRedHunger2.png";
              }else{
                image_file = "imgs/tamagotchiRed/tamagotchiRedHunger3.png";
              }
            }
          }
        }else{
          if (!strcmp(parameters->tamagotchi->outfit, "none")){
            image_file = "imgs/tamagotchiPurple/tamagotchiPurpleHunger0.png";
          }else{
            if (!strcmp(parameters->tamagotchi->outfit, "tee-shirt")){
              image_file = "imgs/tamagotchiPurple/tamagotchiPurpleHunger1.png";
            }else{
              if (!strcmp(parameters->tamagotchi->outfit, "accessories")){
                image_file = "imgs/tamagotchiPurple/tamagotchiPurpleHunger2.png";
              }else{
                image_file = "imgs/tamagotchiPurple/tamagotchiPurpleHunger3.png";
              }
            }
          }
        }
      }else{
        if ( !strcmp(parameters->tamagotchi->color, "red")){
          image_file = "imgs/tamagotchiRedChild/tamagotchiRedHungerChild.png";
        }else{
          image_file = "imgs/tamagotchiPurpleChild/tamagotchiPurpleHungerChild.png";
        }
      }
    }else{
      if (value_hygiene < 0.5){
        if ((parameters->tamagotchi->birthdate - time(NULL)) > parameters->config->grow_time){
          if ( !strcmp(parameters->tamagotchi->color, "red")){
            if (!strcmp(parameters->tamagotchi->outfit, "none")){
              image_file = "imgs/tamagotchiRed/tamagotchiRedDirty0.png";
            }else{
              if (!strcmp(parameters->tamagotchi->outfit, "tee-shirt")){
                image_file = "imgs/tamagotchiRed/tamagotchiRedDirty1.png";
              }else{
                if (!strcmp(parameters->tamagotchi->outfit, "accessories")){
                  image_file = "imgs/tamagotchiRed/tamagotchiRedDirty2.png";
                }else{
                  image_file = "imgs/tamagotchiRed/tamagotchiRedDirty3.png";
                }
              }
            }
          }else{
            if (!strcmp(parameters->tamagotchi->outfit, "none")){
              image_file = "imgs/tamagotchiPurple/tamagotchiPurpleDirty0.png";
            }else{
              if (!strcmp(parameters->tamagotchi->outfit, "tee-shirt")){
                image_file = "imgs/tamagotchiPurple/tamagotchiPurpleDirty1.png";
              }else{
                if (!strcmp(parameters->tamagotchi->outfit, "accessories")){
                  image_file = "imgs/tamagotchiPurple/tamagotchiPurpleDirty2.png";
                }else{
                  image_file = "imgs/tamagotchiPurple/tamagotchiPurpleDirty3.png";
                }
              }
            }
          }
        }else{
          if ( !strcmp(parameters->tamagotchi->color, "red") ){
            image_file = "imgs/tamagotchiRedChild/tamagotchiRedDirtyChild.png";
          }else{
            image_file = "imgs/tamagotchiPurpleChild/tamagotchiPurpleDirtyChild.png";
          }
        }
      }else{
        if ((parameters->tamagotchi->birthdate - time(NULL)) > parameters->config->grow_time){
          if ( !strcmp(parameters->tamagotchi->color, "red") ){
            image_file = "imgs/tamagotchiRed/tamagotchiRed0.png";
          }else{
            image_file = "imgs/tamagotchiPurple/tamagotchiPurple0.png";
          }
        }else{
          if ( !strcmp(parameters->tamagotchi->color, "red") ){
            image_file = "imgs/tamagotchiRedChild/tamagotchiRedChild.png";
          }else{
            image_file = "imgs/tamagotchiPurpleChild/tamagotchiPurpleChild.png";
          }
        }
      }
    }
  }

  printf("TEST3\n");

  gtk_image_set_from_file(GTK_IMAGE(image_tamagotchi), image_file);

  //free(parameters);
}

gboolean      saveSeconds(gpointer data){
  s_parameters  *parameters;

  parameters = (s_parameters *)data;

  save_tamagotchi(parameters->conn, parameters->tamagotchi);
  update_gamestate(parameters->gamestate, parameters->tamagotchi, parameters->config);

  //free(parameters);

  return TRUE;
}

void         gameGraphic(s_parameters *parameters)
{
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
  GtkWidget  *bored_bar;
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
	g_signal_connect(market_button, "clicked", G_CALLBACK(marketButton), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)window));

	image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tamagotchi_image"));

  food_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "food_bar"));
  food_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_food"));
  changeImageState(food_button, (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)gtkBuilder));
  g_signal_connect(food_button, "clicked", G_CALLBACK(updateFood), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)food_bar));
  g_signal_connect(food_button, "clicked", G_CALLBACK(changeImageState), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)gtkBuilder));

	health_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "health_bar"));
  health_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "health_button"));
  g_signal_connect(health_button, "clicked", G_CALLBACK(updateHealth), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)health_bar));

	hygiene_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hygiene_bar"));
  hygiene_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hygiene_button"));
  g_signal_connect(hygiene_button, "clicked", G_CALLBACK(updateHygiene), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)hygiene_bar));
  g_signal_connect(hygiene_button, "clicked", G_CALLBACK(changeImageState), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)gtkBuilder));

  work_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_work"));
  g_signal_connect(work_button, "clicked", G_CALLBACK(goToWork), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)image_tamagotchi));
  //g_timeout_add_seconds(parameters->config->work_duration, finishWork, (gpointer)init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)image_tamagotchi));

  bored_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "bored_bar"));
  game_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_button"));
  g_signal_connect(game_button, "clicked", G_CALLBACK(changeTamagotchi), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)image_tamagotchi));
  g_signal_connect(game_button, "clicked", G_CALLBACK(gamePlay), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)window));
  g_signal_connect(game_button, "clicked", G_CALLBACK(updateBored), (gpointer) init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)bored_bar));

	gtk_widget_show_all(window);

  if (!(parameters->config->display_hungerbar)){
    gtk_widget_hide(food_bar);
  }

  if (!(parameters->config->display_healthbar)){
    gtk_widget_hide(health_bar);
  }

  if (!(parameters->config->display_healthbar)){
    gtk_widget_hide(health_bar);
  }

  if (!(parameters->config->display_funbar)){
    gtk_widget_hide(bored_bar);
  }

  if (!(parameters->config->display_hygienebar)){
    gtk_widget_hide(hygiene_bar);
  }

  g_timeout_add(2, saveSeconds, (gpointer)init_parameters(parameters->save, parameters->tamagotchi, parameters->gamestate, parameters->config, parameters->conn, (gpointer)image_tamagotchi));

  free(parameters);
}
