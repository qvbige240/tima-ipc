AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS = rpc
rpc_LDADD =\
$(project_dir)/ti/.libs/librpc.a \
$(STATIC_LIBS)
LIBS=$(DYNAMIC_LIBS)
rpc_LDFLAGS=$(EXTRA_LDFLAGS)
rpc_SOURCES =\
sample_rpc.c

bin_PROGRAMS += mqueue
mqueue_LDADD =\
$(project_dir)/ti/.libs/librpc.a \
$(STATIC_LIBS)
LIBS=$(DYNAMIC_LIBS)
mqueue_LDFLAGS=$(EXTRA_LDFLAGS)
mqueue_SOURCES =\
sample_mq.c
