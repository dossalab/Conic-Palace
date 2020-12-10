/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <views/header.h>
#include <src/connman.h>
#include <util/i18n.h>

static GtkWidget *header_view;

static gboolean on_connect_click_event(GtkWidget *widget, gpointer user)
{
	connman_connect();
	return TRUE;
}

static gboolean on_disconnect_click_event(GtkWidget *widget, gpointer user)
{
	connman_disconnect();
	return TRUE;
}

static GtkWidget *header_view_create(void)
{
	GtkWidget *header, *connect, *disconnect;

	header = gtk_header_bar_new();
	connect = gtk_button_new_with_label(_("Connect"));
	disconnect = gtk_button_new_with_label(_("Disconnect"));

	g_signal_connect(G_OBJECT(connect), "clicked", \
			G_CALLBACK(on_connect_click_event), NULL);

	g_signal_connect(G_OBJECT(disconnect), "clicked", \
			G_CALLBACK(on_disconnect_click_event), NULL);

	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), connect);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), disconnect);

	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);

	return header;
}

void header_set_title(const char *title)
{
	gtk_header_bar_set_title(GTK_HEADER_BAR(header_view_instance()), title);
}

GtkWidget *header_view_instance(void)
{
	if (!header_view) {
		header_view = header_view_create();
	}

	return header_view;
}

