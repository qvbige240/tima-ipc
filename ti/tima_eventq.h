/**
 * History:
 * ================================================================
 * 2017-09-01 qing.zou created
 *
 */
#include "tima_typedef.h"

#ifndef TIMA_EVENTQ_H
#define TIMA_EVENTQ_H

TIMA_EXTERN_BEGIN

#define EVENT_QUEUE_MSG_LEN_MAX		16

/**
 * Initialize the system.
 * 
 */
//TIMAPI int vpk_system_init(int argc, char* argv[]);


TIMAPI int tima_mqueue_open(char* fname, int id);

TIMAPI int tima_mqueue_is_empty(int qid);

TIMAPI int tima_mqueue_post(int qid, void* msg_value);

TIMAPI int tima_mqueue_recv(int qid, void* msg_value);

TIMA_EXTERN_END

#endif // TIMA_EVENTQ_H
