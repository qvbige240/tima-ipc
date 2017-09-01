AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS = test
test_LDADD =\
$(project_dir)/ti/librpc.a \
$(STATIC_LIBS)
LIBS=$(DYNAMIC_LIBS)
test_LDFLAGS=$(EXTRA_LDFLAGS)
test_SOURCES =\
sample_rpc.c
