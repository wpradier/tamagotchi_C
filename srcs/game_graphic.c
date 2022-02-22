#include "tamagotchi.h"

void        deleteHomePage(GtkWidget *, gpointer);
void        gameGraphic(s_parameters *);
static void buttonClicked();
void        updateFood(GtkWidget *, gpointer);
void        updateHealth(GtkWidget *, gpointer);
void        updateHygiene(GtkWidget *, gpointer);
void        gamePlay();
void        editName(GtkWidget *, gpointer);
void        destroyWindow(GtkWidget *, gpointer );

void            deleteHomePage(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);

  gameGraphic(init_parameters(parameters->tamagotchi, parameters->gamestate, NULL));
  free(parameters);
}


void            destroyWindow(GtkWidget *widget, gpointer data){
  s_parameters  *parameters;

  if (widget) g_print("Jeu lancé\n");

  parameters = (s_parameters *)data;
  gtk_widget_destroy(parameters->data);
  parameters->data = NULL;

  free(parameters);
}

static void buttonClicked(){
      g_print("Bouton pressé\n");
}

void updateFood(GtkWidget *widget, gpointer data){
    s_parameters *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");
    double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
    value -= 0.25;
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

      parameters->tamagotchi->last_fed = s_now;

     // pour comparer deux dates : difftime()
}

void updateHealth(GtkWidget *widget, gpointer data){
    s_parameters *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");
    double value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(parameters->data));
    value = 1;
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

     parameters->tamagotchi->last_health_update = s_now;

     // pour comparer deux dates : difftime()
}

void updateHygiene(GtkWidget *widget, gpointer data){
    s_parameters *parameters;

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

     // pour comparer deux dates : difftime()
}

void gamePlay(GtkWidget *widget, gpointer data){
  if (widget) g_print("Jeu lancé\n");
  gtk_widget_destroy(data);

  gamePlayGraphic();
}

void             editName(GtkWidget *widget, gpointer data){
    s_parameters *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");

    const gchar *recep_entry_text = gtk_entry_get_text(GTK_ENTRY(parameters->data));
    g_print("%s", recep_entry_text);

    parameters->tamagotchi->name = (char *)recep_entry_text;
    parameters->data = NULL;
    free(parameters);
}

void              setName(GtkWidget *widget, gpointer data){
    s_parameters  *parameters;

    parameters = (s_parameters *)data;

    if (widget) g_print("Modification progresse barre\n");

    gtk_label_set_text(GTK_LABEL(parameters->data), (gchar *)parameters->tamagotchi->name);
    parameters->data = NULL;
    free(parameters);
}

void         gameGraphic(s_parameters *parameters)
{
	//init variable
	GtkBuilder *gtkBuilder;
	GtkWidget  *window;
	GtkWidget  *market_button;
  //GtkWidget *image_tamagotchi;
  GtkWidget  *food_bar;
  GtkWidget  *food_button;
  GtkWidget  *game_button;
  GtkWidget  *health_bar;
  GtkWidget  *health_button;
  GtkWidget  *hygiene_bar;
  GtkWidget  *hygiene_button;
  GtkBuilder *gtkBuilderName;
	GtkWidget  *windowName;
  GtkWidget  *edit_name_button;
  GtkWidget  *name_label;
  GtkWidget  *name_input;

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("windows/principalWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

	/* init button market*/
	market_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "market_button"));
	g_signal_connect(market_button, "clicked", G_CALLBACK(buttonClicked), (gpointer) NULL);

  /* init tamagotchi image */
	// image_tamagotchi = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "tamagotchi_image"));
  // char *file = "image.jpg";
  // /* change link image */
  // gtk_image_set_from_file(GTK_IMAGE(image_tamagotchi), file);

  /* init container food_bar */
	food_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "food_bar"));

  /*init button food */
  food_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "button_food"));
  g_signal_connect(food_button, "clicked", G_CALLBACK(updateFood), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)food_bar));

  /* init container health_bar */
	health_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "health_bar"));

  /*init button health */
  health_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "health_button"));
  g_signal_connect(health_button, "clicked", G_CALLBACK(updateHealth), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)health_bar));

  /* init container hygiene_bar */
	hygiene_bar = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hygiene_bar"));

  /*init button hygiene */
  hygiene_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "hygiene_button"));
  g_signal_connect(hygiene_button, "clicked", G_CALLBACK(updateHygiene), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)hygiene_bar));

  /* init button game */
  game_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "game_button"));
  g_signal_connect(game_button, "clicked", G_CALLBACK(gamePlay), (gpointer) window);

  //////////////////////////////////////////////////////////////////////////////////
  /* WindowNme */
  gtkBuilderName = gtk_builder_new();
	gtkBuilderName = gtk_builder_new_from_file("windows/nameWindow.glade");
	windowName = GTK_WIDGET(gtk_builder_get_object(gtkBuilderName, "name_window"));
	gtk_builder_connect_signals(gtkBuilderName, NULL);

  edit_name_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilderName, "edit_name_button"));
  name_label = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "name_label"));
  name_input = GTK_WIDGET(gtk_builder_get_object(gtkBuilderName, "name_input"));

  g_signal_connect(edit_name_button, "clicked", G_CALLBACK(editName), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)name_input));
  g_signal_connect(edit_name_button, "clicked", G_CALLBACK(setName), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)name_label));
  g_signal_connect(edit_name_button, "clicked", G_CALLBACK(destroyWindow), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)windowName));

	/* Print and event loop */
  gtk_widget_show_all(windowName);
	gtk_widget_show_all(window);
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

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
	gtkBuilder = gtk_builder_new_from_file("./windows/homeWindow.glade");
	window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
	gtk_builder_connect_signals(gtkBuilder, NULL);

  continue_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "continue_button"));
  gtk_widget_set_opacity(continue_button, 0.5);

  load_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "load_button"));
  gtk_widget_set_opacity(load_button, 0.5);

  new_button = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "new_button"));
  g_signal_connect(new_button, "clicked", G_CALLBACK(deleteHomePage), (gpointer) init_parameters(parameters->tamagotchi, parameters->gamestate, (gpointer)window));

  gtk_widget_show_all(window);
}
