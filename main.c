#include <stdio.h>
#include <stdlib.h>
 #include <gtk/gtk.h>
 
int     main(int argc, char **argv) {
//init variable
GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *label_test;

gtk_init(&argc, &argv);

gtkBuilder = gtk_builder_new();
     gtkBuilder = gtk_builder_new_from_file("test-glade.glade");
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));
    gtk_builder_connect_signals(gtkBuilder, NULL);

    char *lol = "test";
    label_test = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_test"));

gchar *recep = gtk_label_get_text(GTK_LABEL(label_test));
g_print("%s", recep);
  
  gtk_label_set_text(GTK_LABEL(label_test), lol);
 
   gtk_widget_show_all(window);

 gtk_main();

return EXIT_SUCCESS;
}
