/*
 * Part of the Conic Palace - robot control center
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

#define APPLICATION_ID	"org.conic.palace"

static void main_layout_populate(GtkWidget *window)
{
	gtk_container_set_border_width(GTK_CONTAINER(window), 8);
}

static void app_activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;

	window = gtk_application_window_new(app);
	main_layout_populate(window);
	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
	int retval;
	GtkApplication *app;

	app = gtk_application_new(APPLICATION_ID, G_APPLICATION_FLAGS_NONE);

	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
	retval = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return retval;
}

