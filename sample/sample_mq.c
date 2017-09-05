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

#define BUFFER_SIZE		EVENT_QUEUE_MSG_LEN_MAX

void *test_event_post(void *name)
{
	int ret = 0;
	char buffer[BUFFER_SIZE] = {0};
	//eventq = vpk_eventq_open("/test", "a+");
	//return_val_if_fail(eventq != NULL, -1);

	int key = tima_mqueue_open("/tmp/test", 'a');

	//snprintf(buffer, sizeof(buffer), "1001");
	snprintf(buffer, sizeof(buffer), "%s %s", (char*)name, "1001");

	while (1) {
		ret = tima_mqueue_post(key, buffer);
		printf("[%s]post: %s, ret = %d\n", (char*)name, buffer, ret);
		sleep(2);
	}
}

int test_event_recv(void)
{
	int ret = 0;
	char buffer[BUFFER_SIZE] = {0};

	int key = tima_mqueue_open("/tmp/test", 'a');

	while (1) {
		ret = tima_mqueue_recv(key, buffer);
		printf("recv: %s, ret = %d\n", buffer, ret);
	}

	return 0;
}

int mult_post(int argc, char *argv[])
{
	int ret = 0;
	void* thread_result;
	pthread_t pth_test3, pth_test2;

	//vpk_system_init(argc, argv);
	//vpk_logging_level_set("DEBUG");

	//eventq = vpk_eventq_open();

	char *test3 = "test3";
	ret = pthread_create(&pth_test3, NULL, test_event_post, (void*)test3);
	if (ret != 0)
		printf("create thread \'vpk_test3\' failed");
		//LOG_E("create thread \'vpk_test3\' failed");

	sleep(1);

	char *test2 = "test2";
	ret = pthread_create(&pth_test2, NULL, test_event_post, (void*)test2);
	if (ret != 0)
		printf("create thread \'vpk_test2\' failed");

	pthread_join(pth_test3, &thread_result);
	pthread_join(pth_test2, &thread_result);

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
		rc = mult_post(argc, argv);
	} else {
		rc = test_event_recv();
	}
	exit (rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
