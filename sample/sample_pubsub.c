/**
 * History:
 * ================================================================
 * 2017-08-30 qing.zou created
 *
 */
#include <unistd.h>

#include "tima_pub.h"
#include "tima_sub.h"

int server(void)
{
	int fd = tima_pub_open();

	int rc, i = 0;
	char recvbuf[256];
	while (1) {
		memset(recvbuf, 0, sizeof(recvbuf));

		sprintf(recvbuf, "%s%d", "[pub]hello client", ++i);
		rc = tima_pub_send(fd, recvbuf, sizeof(recvbuf), 0);
		if (rc < 0)
			printf(" tima_pub_send error");
		printf("send: %s\n\n", recvbuf);

		sleep(3);
	}

	tima_pub_close(fd);

	return 0;
}


int client(void)
{
	int rc;
	int fd = tima_sub_open();

	char buffer[256] = {0};
	while (1) {
		memset(buffer, 0, sizeof(buffer));

		rc = tima_sub_recv(fd, buffer, sizeof(buffer), 0);
		printf("rc = %d, recv: %s\n", rc, buffer);

		sleep(2);
	}

	tima_sub_close(fd);
	return 0;
}

int main(int argc, char **argv)
{
	int rc;
	if (argc < 2) {
		fprintf (stderr, "Usage: %s [-s|name]\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	if (strcmp(argv[1], "-s") == 0) {
		rc = server();
	} else {
		rc = client();
	}
	exit (rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
