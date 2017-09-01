/**
 * History:
 * ================================================================
 * 2017-08-29 qing.zou created
 *
 */

#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "tima_proc_rpcd.h"

#define IPC_URL		"ipc:///tmp/reqrep.ipc"

int tima_rpcd_open(void)
{
    int fd; 

	fd = nn_socket(AF_SP, NN_REP);
	if (fd < 0) {
		fprintf(stderr, "rpc socket: %s\n", nn_strerror (nn_errno ()));
		return (-1);
	}

	if (nn_bind(fd, IPC_URL) < 0) {
		fprintf(stderr, "rpc bind: %s\n", nn_strerror (nn_errno ()));
		nn_close(fd);
		return (-1);        
	}

	return fd;
}

int tima_rpcd_recv(int fd, void *buf, size_t len, int flags)
{
	int rc;

	if (buf == NULL) {
		fprintf(stderr, "recv buf is null pointer\n");
		return -1;
	}

	if ((rc = nn_recv(fd, buf, len, flags)) < 0) {
		fprintf(stderr, "rpc recv: %s\n", nn_strerror (nn_errno ()));
		return -1;
	}

	return rc;
}

int tima_rpcd_send(int fd, const void *buf, size_t len, int flags)
{
	int rc;

	if (buf == NULL) {
		fprintf(stderr, "send buf is null pointer\n");
		return -1;
	}

	if ((rc = nn_send(fd, buf, len, flags)) < 0) {
		fprintf(stderr, "rpc send: %s\n", nn_strerror (nn_errno ()));
		return -1;
	}

	return rc;
}

int tima_rpcd_close(int fd)
{
	return nn_close(fd);
}
