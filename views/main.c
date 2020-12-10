/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <views/main.h>
#include <util/i18n.h>
#include <widgets/viewport.h>

static GtkWidget *main_view;

static GtkWidget *main_view_create(void)
{
	GtkWidget *demo;

	demo = viewport_create();

	return demo;
}

GtkWidget *main_view_instance(void)
{
	if (!main_view) {
		main_view = main_view_create();
	}

	return main_view;
}

