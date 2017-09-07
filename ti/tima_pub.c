/**
 * History:
 * ================================================================
 * 2017-09-07 qing.zou created
 *
 */

#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

#include "tima_pub.h"

#define IPC_URL		"ipc:///tmp/pubsub.ipc"

int tima_pub_open(void)
{
	int fd; 

	fd = nn_socket(AF_SP, NN_PUB);
	if (fd < 0) {
		fprintf(stderr, "pub socket: %s\n", nn_strerror (nn_errno ()));
		return (-1);
	}

	if (nn_bind(fd, IPC_URL) < 0) {
		fprintf(stderr, "rpc bind: %s\n", nn_strerror (nn_errno ()));
		nn_close(fd);
		return (-1);        
	}

	return fd;
}

//int tima_pub_recv(int fd, void *buf, size_t len, int flags)
//{
//	int rc;
//
//	if (buf == NULL) {
//		fprintf(stderr, "recv buf is null pointer\n");
//		return -1;
//	}
//
//	if ((rc = nn_recv(fd, buf, len, flags)) < 0) {
//		fprintf(stderr, "pub recv: %s\n", nn_strerror (nn_errno ()));
//		return -1;
//	}
//
//	return rc;
//}

int tima_pub_send(int fd, const void *buf, size_t len, int flags)
{
	int rc;

	if (buf == NULL) {
		fprintf(stderr, "send buf is null pointer\n");
		return -1;
	}

	if ((rc = nn_send(fd, buf, len, flags)) < 0) {
		fprintf(stderr, "pub send: %s\n", nn_strerror (nn_errno ()));
		return -1;
	}

	return rc;
}

int tima_pub_close(int fd)
{
	return nn_close(fd);
}

