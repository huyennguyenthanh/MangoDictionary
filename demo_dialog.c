#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

void quick_message (GtkWindow *parent, gchar *message)
{
 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;

 message = (char*)malloc(sizeof(char));
 strcpy(message,"Welcome to Mango Dictionary");
 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Message",
                                       parent,
                                       flags,
                                       ("Quit"),
                                       GTK_RESPONSE_NONE,
                                       NULL);
 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (message);

 // Ensure that the dialog box is destroyed when the user responds

 g_signal_connect_swapped (dialog,
                           "response",
                           G_CALLBACK (gtk_widget_destroy),
                           dialog);

 // Add the label, and show everything we’ve added

 gtk_container_add (GTK_CONTAINER (content_area), label);
 gtk_widget_show_all (dialog);
}
static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;

  /* create a new window, and set its title */
  
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Mango Dictionary");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);
  //gtk_container_set_border_width (GTK_CONTAINER (window), 100);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  button = gtk_button_new_with_label ("Button 1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);


  ////// ---  quick_message(GTK_WINDOW(window),"Hello abc")
  // (0,0) = column 0, row 0
  /* Place the first button in the grid cell (0, 0)
  (1 ,1) is the button include 1 row 1 column
  */
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Button 2");
  g_signal_connect (button, "clicked", G_CALLBACK (quick_message), NULL);
  //Place the second button in the grid cell (1, 0)
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);


  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

  gtk_widget_show_all (window);

}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}