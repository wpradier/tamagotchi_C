#include "tamagotchi.h"

void          alertPage(gchar *text){
  GtkBuilder  *gtkBuilder;
	GtkWidget   *window;
  GtkWidget   *label_alert;

  gtkBuilder = gtk_builder_new();
  gtkBuilder = gtk_builder_new_from_file("windows/alertWindow.glade");
  window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "alert_window"));
  gtk_builder_connect_signals(gtkBuilder, NULL);

  label_alert = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "label_alert"));
  gtk_label_set_text(GTK_LABEL(label_alert), text);

  gtk_widget_show_all(window);
}
