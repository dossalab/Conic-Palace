/*
 * Part of the Conic project - robot arm controller
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <src/connman.h>
#include <libconic.h>
#include <util/logger.h>

static int conic_fd = -1;

bool connman_connect(void)
{
	bool connected;

	if (conic_fd < 0) {
		log_i("connecting...");
		conic_fd = conic_device_open();
	}

	connected = (conic_fd != -1);

	if (connected) {
		log_i("ok");
	}

	return connected;

}

void connman_disconnect(void)
{
	if (conic_fd >= 0) {
		log_i("disconnecting from %d", conic_fd);
		conic_device_close(conic_fd);
		conic_fd = -1;
	}
}

