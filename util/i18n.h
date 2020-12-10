/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef UTIL_I18N_H
#define UTIL_I18N_H

#include <libintl.h>

#define _(text) gettext(text)

void i18n_init(void);

#endif

