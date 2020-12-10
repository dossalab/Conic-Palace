/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef VIEWS_HEADER_H
#define VIEWS_HEADER_H

#include <gtk/gtk.h>

void header_set_title(const char *title);
GtkWidget *header_view_instance(void);

#endif

