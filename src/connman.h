/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef SRC_CONNMAN_H
#define SRC_CONNMAN_H

#include <stdbool.h>

bool connman_connect(void);
void connman_disconnect(void);

#endif

