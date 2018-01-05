/**
 * History:
 * ================================================================
 * 2017-09-07 qing.zou created
 *
 */

#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

#include "tima_sub.h"

#define IPC_URL		"ipc:///tmp/pubsub.ipc"

int tima_sub_open(void)
{
    int fd; 

	fd = nn_socket(AF_SP, NN_SUB);
	if (fd < 0) {
		fprintf(stderr, "sub socket: %s\n", nn_strerror (nn_errno ()));
		return (-1);
	}

	if (nn_connect(fd, IPC_URL) < 0) {
		fprintf(stderr, "sub connect: %s\n", nn_strerror (nn_errno ()));
		nn_close(fd);
		return (-1);        
	}

	/*  We want all messages, so just subscribe to the empty value. */
	if (nn_setsockopt (fd, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) < 0) {
		fprintf (stderr, "sub nn_setsockopt: %s\n", nn_strerror (nn_errno ()));
		nn_close (fd);
		return (-1);        
	}

	return fd;
}

int tima_sub_recv(int fd, void *buf, size_t len, int flags)
{
	int rc;

	if (buf == NULL) {
		fprintf(stderr, "recv buf is null pointer\n");
		return -1;
	}

	if ((rc = nn_recv(fd, buf, len, flags)) < 0) {
		fprintf(stderr, "sub recv: %s\n", nn_strerror (nn_errno ()));
		return -1;
	}

	return rc;
}

//int tima_sub_send(int fd, const void *buf, size_t len, int flags)
//{
//	int rc;
//
//	if (buf == NULL) {
//		fprintf(stderr, "send buf is null pointer\n");
//		return -1;
//	}
//
//	if ((rc = nn_send(fd, buf, len, flags)) < 0) {
//		fprintf(stderr, "sub send: %s\n", nn_strerror (nn_errno ()));
//		return -1;
//	}
//
//	return rc;
//}

int tima_sub_close(int fd)
{
	return nn_close(fd);
}
