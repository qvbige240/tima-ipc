/**
 * History:
 * ================================================================
 * 2017-08-30 qing.zou created
 *
 */
#include <unistd.h>

#include "tima_proc_rpc.h"
#include "tima_proc_rpcd.h"

int server(void)
{
	int fd = tima_rpcd_open();

	int rc;
	char recvbuf[256];
	while (1) {
		memset(recvbuf, 0, sizeof(recvbuf));
		rc = tima_rpcd_recv(fd, recvbuf, sizeof(recvbuf), 0);
		if (rc < 0)
			printf(" tima_rpcd_recv error");
		printf("recv: %s\n", recvbuf);

		sleep(3);

		sprintf(recvbuf, "%s %s", recvbuf, " back from server");
		//printf("Enter message to send: \n");
		//scanf("%s", recvbuf);
		rc = tima_rpcd_send(fd, recvbuf, strlen(recvbuf), 0);
	}

	tima_rpcd_close(fd);

	return 0;
}

int client(void) 
{
	int rc;
	char *msg;
	int fd = tima_rpc_open();

	char buffer[256] = {0};
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		printf("Enter message to send: \n");
		scanf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
		strcpy(buffer, "hello world");

		rc = tima_rpc_send(fd, buffer, strlen(buffer), 0);
		if (rc < 0)
			printf(" tima_rpc_send error");

		rc = tima_rpc_recv(fd, &msg, 0);
		printf("recv: %s\n", msg);
	}

    //nn_freemsg (msg);
	tima_rpc_close(fd);
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
