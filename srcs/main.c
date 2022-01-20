#include "tamagotchi.h"

static void buttonClicked(){
	g_print("Bouton presser\n"); 
}
 
int     main(int argc, char **argv) {
	//init variable
	GtkBuilder *gtkBuilder;
	GtkWidget *window;
	GtkWidget *label_test;
	GtkWidget *button_test; 

	/* init gtk */
	gtk_init(&argc, &argv);

	/* Create window gtk */
	gtkBuilder = gtk_builder_new();
        gtkBuilder = gtk_builder_new_from_file("test-glade.glade");
        window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
        gtk_builder_connect_signals(gtkBuilder, NULL);

        /* init label test */
	char *test = "test";
        label_test = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_test"));

        /* Change test label */
	gtk_label_set_text(GTK_LABEL(label_test), test);

	/* Get test label */
	const gchar *recep = gtk_label_get_text(GTK_LABEL(label_test)); 
	g_print("%s", recep); 

	/* init button test*/
	button_test = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "buttonTest")); 
	g_signal_connect(button_test, "clicked", G_CALLBACK(buttonClicked), (gpointer) NULL);  
 
	/* Print and event loop */
        gtk_widget_show_all(window);
	gtk_main();

	/* Connect at the database */
	//db_connect();
	
	gchar *TEST = "TEST\n"; 
	g_print("%s", TEST );
	
	/* Close gtk */ 
	return EXIT_SUCCESS;
}
