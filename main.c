#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int	main(int argc, char **argv) {
    //init variable
	GtkBuilder *gtkBuilder;
    GtkWidget *window;

    gtk_init(&argc, &argv);

    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "test-glade.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "main_window"));

    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show_all(window);
    gtk_main();

    return EXIT_SUCCESS;
}
