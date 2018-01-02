AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS = rpc
LIBS="-ltimapi $(DYNAMIC_LIBS)"
rpc_LDFLAGS=$(EXTRA_LDFLAGS)
rpc_SOURCES =\
sample_rpc.c

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
