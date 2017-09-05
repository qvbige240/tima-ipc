/**
 * History:
 * ================================================================
 * 2017-08-30 qing.zou created
 *
 */
#include <unistd.h>

#include "tima_rpc.h"
#include "tima_rpcd.h"

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

#if 0
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

		printf("=== send rc = %d\n", rc);

		//rc = tima_rpc_recv(fd, &msg, 0);
		memset(buffer, 0, sizeof(buffer));
		rc = tima_rpc_recv(fd, buffer, sizeof(buffer), 0);
		printf("rc = %d, recv: %s\n", rc, buffer);
	}

    //nn_freemsg (msg);
	tima_rpc_close(fd);
	return 0;
}
#else


int tima_cmd_send(int fd, const void *buf, char *recvbuf, size_t recvlen)
{
	int rc = 0;
	char *msg;

	if (!recvbuf) {
		fprintf(stderr, "recv buf is null pointer\n");
		return -1;
	}

	rc = tima_rpc_send(fd, buf, strlen(buf), 0);
	if (rc < 0) {
		printf("tima_rpc_send error");
		return -1;
	}
	printf("=== send rc = %d\n", rc);

	rc = tima_rpc_recv_alloc(fd, &msg, 0);
	if (rc < 0) {
		printf("tima_rpc_recv_alloc error");
		return -1;
	} else {
		int len = rc > recvlen-1 ? recvlen-1 : rc;
		memcpy(recvbuf, msg, len);
		tima_rpc_freemsg(msg);
		if (rc != len) {
			printf("warn: recvbuf is less than recv msg\n");
		}
	}

	return rc;
}

int client(void)
{
	int rc;
	int fd = tima_rpc_open();

	char recv[256] = {0};
	char buffer[256] = {0};
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		printf("Enter message to send: \n");
		scanf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
		strcpy(buffer, "hello world");

		//rc = tima_rpc_send(fd, buffer, strlen(buffer), 0);
		//if (rc < 0)
		//	printf(" tima_rpc_send error");

		//char *msg;
		//rc = tima_rpc_recv(fd, &msg, 0);
		//printf("recv: %s\n", msg);
		rc = tima_cmd_send(fd, buffer, recv, sizeof(recv));
		printf("rc = %d, recv: %s\n", rc, recv);
	}

	//nn_freemsg (msg);
	tima_rpc_close(fd);
	return 0;
}

#endif

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
