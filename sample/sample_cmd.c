/**
 * History:
 * ================================================================
 * 2017-08-30 qing.zou created
 *
 */
#include <unistd.h>
#include <pthread.h>

#include "tima_rpc.h"
#include "tima_command.h"


int server(void)
{
	int rc;
	char recvbuf[256];

	int fd = tima_command_open();
	if (fd < 0) {
		printf("error\n");
		return -1;
	}

	char *str = "{\"Latitude\":0.000000,\"Longitude\":0.000000,\"Speed\":0.000000,\"Timestamp\":0}";
	while (1) {
		memset(recvbuf, 0, sizeof(recvbuf));
		rc = tima_command_recv(fd, recvbuf, sizeof(recvbuf), 0);
		if (rc < 0)
			printf(" tima_rpcd_recv error");
		printf("rc = %d, recv: %s\n", rc, recvbuf);
		// recv from client: tima -gpsinfo

		rc = tima_command_send(fd, str, strlen(str), 0);
		printf("rc = %d, send: %s\n", rc, str);
	}

	tima_command_close(fd);

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

void *test_client1(void *name)
{
	int rc;
	int fd = tima_rpc_open();

	char recv[256] = {0};
	char buffer[256] = {0};
	//const char *str = "tima -gpsinfo";
	const char *str = "tima -getvideo 1234567 5 ";
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		printf("[%s]Enter message to send: \n", (char*)name);
		scanf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
		//strcpy(buffer, "hello world");
		strcpy(buffer, str);

		rc = tima_cmd_send(fd, buffer, recv, sizeof(recv));
		printf("rc = %d, recv: %s\n", rc, recv);
	}

	tima_rpc_close(fd);
	return NULL;
}

void *test_client2(void *name)
{
	int rc;
	int fd = tima_rpc_open();

	char recv[256] = {0};
	char buffer[256] = {0};
	const char *str2 = "tima -gpsinfo";
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		printf("[%s]Enter message to send: \n", (char*)name);
		scanf("%s", buffer);
		memset(buffer, 0, sizeof(buffer));
		strcpy(buffer, str2);

		rc = tima_cmd_send(fd, buffer, recv, sizeof(recv));
		printf("rc = %d, recv: %s\n", rc, recv);
	}

	tima_rpc_close(fd);
	return NULL;
}
#endif

int mult_client(int argc, char *argv[])
{
	int ret = 0;
	void* thread_result;
	pthread_t pth_test3, pth_test2;

	char *client1 = "client1";
	ret = pthread_create(&pth_test3, NULL, test_client1, (void*)client1);
	if (ret != 0)
		printf("create thread \'client1\' failed");

	sleep(1);

	char *client2 = "client2";
	ret = pthread_create(&pth_test2, NULL, test_client2, (void*)client2);
	if (ret != 0)
		printf("create thread \'client2\' failed");

	pthread_join(pth_test3, &thread_result);
	pthread_join(pth_test2, &thread_result);

	return 0;
}

int main(int argc, char **argv)
{
	int rc;
	if (argc < 2) {
		fprintf (stderr, "Usage: %s [-s|client name]\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	if (strcmp(argv[1], "-s") == 0) {
		rc = server();
	} else {
		rc = mult_client(argc, argv);
	}
	exit (rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
