AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS = rpc
LIBS="-ltmipc $(DYNAMIC_LIBS)"
rpc_LDFLAGS=$(EXTRA_LDFLAGS)
rpc_SOURCES =\
sample_rpc.c

#bin_PROGRAMS += mqueue
#mqueue_LDADD =\
#$(project_dir)/ti/.libs/libtmipc.a \
#$(STATIC_LIBS)
#LIBS=$(DYNAMIC_LIBS)
#mqueue_LDFLAGS=$(EXTRA_LDFLAGS)
#mqueue_SOURCES =\
#sample_mq.c

bin_PROGRAMS += mqueue
LIBS="-ltmipc $(DYNAMIC_LIBS)"
mqueue_LDFLAGS=$(EXTRA_LDFLAGS)
mqueue_SOURCES =\
sample_mq.c
