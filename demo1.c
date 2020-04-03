
#include <gtk/gtk.h>

static void
activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget *title ;

  title = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (title), "Mango Dictionary");
  gtk_window_set_default_size (GTK_WINDOW (title), 500, 500);
  gtk_widget_show_all (title);
}

int
main (int argc , char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}