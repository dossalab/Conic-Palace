/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <math.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <libconic.h>
#include <src/connman.h>
#include <util/i18n.h>
#include <views/main.h>
#include <views/header.h>

static void app_activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget *window, *main_view, *header;

	window = gtk_application_window_new(app);
	header = header_view_instance();
	main_view = main_view_instance();

	gtk_window_set_titlebar(GTK_WINDOW(window), header);
	gtk_container_add(GTK_CONTAINER(window), main_view);

	gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
	int retval;
	GtkApplication *app;

	i18n_init();
	app = gtk_application_new("org.conic.palace", G_APPLICATION_FLAGS_NONE);

	g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
	retval = g_application_run(G_APPLICATION(app), argc, argv);

	connman_disconnect();
	g_object_unref(app);

	return retval;
}

