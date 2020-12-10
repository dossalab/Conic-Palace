/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <stdio.h>

#define log_e(format, ...) \
	printf("[err]\t" format "\n\r", ##__VA_ARGS__)

#define log_i(format, ...) \
	printf("[info]\t" format "\n\r", ##__VA_ARGS__)

#endif

