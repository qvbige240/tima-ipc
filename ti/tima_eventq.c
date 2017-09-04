/**
 * History:
 * ================================================================
 * 2017-09-01 qing.zou created
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>

#include "tima_eventq.h"

typedef struct ipc_msg
{
	long msg_type;
	char msg_value[EVENT_QUEUE_MSG_LEN_MAX];
} ipc_msg_t;

int tima_mqueue_open(char* fname, int id)
{
	int qid;
	key_t key;

	//if ((key = ftok(".", 'a')) == -1)
	if ((key = ftok(fname, id)) == -1)
	{
		//LOG_E("ftok error!\n");
		fprintf(stderr, "ftok error: %s!\n", strerror(errno));
		return -1;
	}

	if ((qid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		//LOG_E("msgget error!\n");
		fprintf(stderr, "msgget error: %s!\n", strerror(errno));
		return -1;
	}

	printf("queue %d opened\n", qid);

	return qid;
}

int tima_mqueue_is_empty(int qid)
{
	//int ret = 0;
	struct msqid_ds buf;

	if ((msgctl(qid, IPC_STAT, &buf)) != 0)
	{
		fprintf(stderr, "msgctl error: %s!\n", strerror(errno));
	}

	//if (buf.msg_qnum != 0)
	//{
	//	ret = 0;
	//}
	//else
	//{
	//	ret = 1;
	//}

	//return ret;
	return (buf.msg_qnum != 0 ? 0 : 1);
}

int tima_mqueue_post(int qid, void* msg_value)
{
	ipc_msg_t message = {0};

	message.msg_type = getpid();
	memcpy(message.msg_value, msg_value, sizeof(message.msg_value));

	if (msgsnd(qid, &message, EVENT_QUEUE_MSG_LEN_MAX, 0) < 0)
	{
		//LOG_E("msgsnd ERROR!\n");
		fprintf(stderr, "msgsnd error: %s!\n", strerror(errno));
		return -1;
	}

	return 0;
}

int tima_mqueue_recv(int qid, void* msg_value)
{
	ipc_msg_t message = {0};

	if (msgrcv(qid, (void*)&message, EVENT_QUEUE_MSG_LEN_MAX, 0, 0) < 0)
	{
		//LOG_E("msgrcv ERROR!\n");
		fprintf(stderr, "msgrcv error: %s!\n", strerror(errno));
		return -1;
	}
	memcpy(msg_value, (void*)&message.msg_value, EVENT_QUEUE_MSG_LEN_MAX);

	return 0;
}
