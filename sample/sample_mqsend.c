/**
 * History:
 * ================================================================
 * 2017-09-01 qing.zou created
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "tima_eventq.h"
#include "tima_command.h"

#define BUFFER_SIZE			EVENT_QUEUE_MSG_LEN_MAX

const char *str1 = "{\"event\":\"3001\",\"msg\":null}";
const char *str2 = "{\"event\":\"2001\",\"msg\":{\"id\":0,\"key\":\"2001\",\"rcode\":0,\"value\":\"[{\\\"camera\\\":0,\\\"type\\\":1,\\\"file\\\":\\\"/xxx/01.mp4\\\"},{\\\"camera\\\":1,\\\"type\\\":1,\\\"file\\\":\\\"/xxx/02.mp4\\\"}]\"}}";
//const char *str2 = "{\"event\":\"5001\",\"msg\":{\"value\":\"{\\\"type\\\":0}\"}}";
//const char *str = "{\"event\":\"5001\",\"msg\":{\"id\":0,\"key\":\"5001\",\"rcode\":0,\"value\":\"[{\\\"camera\\\":0,\\\"type\\\":1,\\\"file\\\":\\\"/xxx/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/01.mp4\\\"},{\\\"camera\\\":1,\\\"type\\\":1,\\\"file\\\":\\\"/xxx/02.mp4\\\"}]\"}}";

static void *event_post(void *name)
{
	int ret = 0;
	//char buffer[BUFFER_SIZE] = {0};

	//int key = tima_mqueue_open(EVENT_MQ_PATH, 'a');
	int key = tima_mqueue_open();
	
	//printf("str len = %d", (int)strlen(str));
	//strncpy(buffer, str, BUFFER_SIZE);

	char ch = '0';
	while (1) {
		printf("Enter message to reply: \n");
		scanf("%c", &ch);
		ret = tima_mqueue_post(key, (void*)str2);
		printf("[%s]post: %s, ret = %d\n", (char*)name, str2, ret);
		sleep(1);
	}

	return name;
}


static int tima_command_mock(int fd, char *recv_buff)
{
	int rc = 0;
	char *buf = recv_buff;
	//int rc = tima_command_recv(fd, recv_buff, nbytes, 0);
	//if (rc < 0) {
	//	printf(" tima_command_recv error");
	//	return -1;
	//}

	//printf("recv: %s\n", recv_buff);

	if (buf)
	{
		char *p = NULL;
		//GPS
		//p = strstr(buf, "-gpsinfo");
		// SNAP
		p = strstr(buf, "-snapshot");
		if (p != NULL)
		{
			const char *str = "{\"event\":\"5002\",\"msg\":{\"id\":0,\"key\":\"5002\",\"rcode\":0,\"value\":\"[{\\\"camera\\\":0,\\\"type\\\":0,\\\"file\\\":\\\"P70625-161747.jpg\\\"},{\\\"camera\\\":1,\\\"type\\\":0,\\\"file\\\":\\\"02.JPG\\\"}]\"}}";
			rc = tima_command_send(fd, str, strlen(str), 0);
			printf("rc = %d, send: %s\n", rc, str);
			return 0;
		}
		// VIDEO
		p = strstr(buf, "-movierec");
		if (p != NULL)
		{
			const char *str = "{\"event\":\"5001\",\"msg\":{\"id\":0,\"key\":\"5001\",\"rcode\":0,\"value\":\"[{\\\"camera\\\":0,\\\"type\\\":1,\\\"file\\\":\\\"2017_a.TS\\\"},{\\\"camera\\\":1,\\\"type\\\":1,\\\"file\\\":\\\"2017_b.TS\\\"}]\"}}";
			rc = tima_command_send(fd, str, strlen(str), 0);
			printf("rc = %d, send: %s\n", rc, str);
			return 0;
		}

	}
	return 0;
}

static void *command_mock(void *name)
{
	int rc;
	char recvbuf[256];

	int fd = tima_command_open();
	if (fd < 0) {
		printf("error\n");
		return NULL;
	}
	printf("server fd = %d\n", fd);

	while (1) {
		memset(recvbuf, 0, sizeof(recvbuf));
		rc = tima_command_recv(fd, recvbuf, sizeof(recvbuf), 0);
		if (rc < 0) {
			printf(" tima_rpcd_recv error");
		}
		printf("rc = %d, recv: %s\n", rc, recvbuf);
		tima_command_mock(fd, recvbuf);
	}

	tima_command_close(fd);

	return name;
}

static int test_mock(int argc, char *argv[])
{
	int ret = 0;
	void* thread_result;
	pthread_t pth_test3, pth_test2;

	char *client1 = "cmd";
	ret = pthread_create(&pth_test3, NULL, command_mock, (void*)client1);
	if (ret != 0)
		printf("create thread \'client1\' failed");

	sleep(1);

	char *client2 = "event";
	ret = pthread_create(&pth_test2, NULL, event_post, (void*)client2);
	if (ret != 0)
		printf("create thread \'client2\' failed");

	pthread_join(pth_test3, &thread_result);
	pthread_join(pth_test2, &thread_result);

	return 0;
}


int main(int argc, char **argv)
{
	int rc = 0;
	if (argc < 2) {
		fprintf (stderr, "Usage: %s [-p]\n", argv[0]);
		exit (EXIT_FAILURE);
	}

	if (strcmp(argv[1], "-p") == 0) {
		//event_post("POST", (char*)str2);
	} else {
		test_mock(argc, argv);
	}

	exit (rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
