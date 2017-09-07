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

	int rc;
	char recvbuf[256];
	while (1) {
		memset(recvbuf, 0, sizeof(recvbuf));
		sleep(3);

		sprintf(recvbuf, "%s", "[pub]hello client");
		rc = tima_pub_send(fd, recvbuf, sizeof(recvbuf), 0);
		if (rc < 0)
			printf(" tima_pub_send error");
		printf("send: %s\n\n", recvbuf);

		//memset(recvbuf, 0, sizeof(recvbuf));

		//rc = tima_pub_recv(fd, recvbuf, strlen(recvbuf), 0);
		//if (rc < 0) {
		//	printf("tima_pub_recv error");
		//	return -1;
		//}

		//printf("recv: %s\n\n", recvbuf);
	}

	tima_pub_close(fd);

	return 0;
}

#if 1
int client(void)
{
	int rc;
	int fd = tima_sub_open();

	char buffer[256] = {0};
	while (1) {
		memset(buffer, 0, sizeof(buffer));
	
		rc = tima_sub_recv(fd, buffer, sizeof(buffer), 0);
		printf("rc = %d, recv: %s\n", rc, buffer);


		//memset(buffer, 0, sizeof(buffer));
		//sprintf(buffer, "%s", "[pub] receive from client");
		//rc = tima_sub_send(fd, buffer, sizeof(buffer), 0);		
		//if (rc < 0)
		//	printf(" tima_sub_send error");
		//printf("rc = %d, send: %s\n", rc, buffer);
	}

	tima_sub_close(fd);
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
