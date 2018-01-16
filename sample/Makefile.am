AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS = cmd 
#cmd_LDADD =\
#$(project_dir)/tima-api/.libs/libtimapi.a
LIBS="-ltimapi $(DYNAMIC_LIBS)"
cmd_LDFLAGS=$(EXTRA_LDFLAGS)
cmd_SOURCES =\
sample_cmd.c

#bin_PROGRAMS += mqueue
#mqueue_LDADD =\
#$(project_dir)/ti/.libs/libtimapi.a \
#$(STATIC_LIBS)
#LIBS=$(DYNAMIC_LIBS)
#mqueue_LDFLAGS=$(EXTRA_LDFLAGS)
#mqueue_SOURCES =\
#sample_mq.c

bin_PROGRAMS += mqueue
LIBS="-ltimapi $(DYNAMIC_LIBS)"
mqueue_LDFLAGS=$(EXTRA_LDFLAGS)
mqueue_SOURCES =\
sample_mq.c

bin_PROGRAMS += pubsub
LIBS="-ltimapi $(DYNAMIC_LIBS)"
pubsub_LDFLAGS=$(EXTRA_LDFLAGS)
pubsub_SOURCES =\
sample_pubsub.c

bin_PROGRAMS += reply
LIBS="-ltimapi $(DYNAMIC_LIBS)"
reply_LDFLAGS=$(EXTRA_LDFLAGS)
reply_SOURCES =\
sample_reply.c

bin_PROGRAMS += mqsend
LIBS="-ltimapi $(DYNAMIC_LIBS)"
mqsend_LDFLAGS=$(EXTRA_LDFLAGS)
mqsend_SOURCES =\
sample_mqsend.c
