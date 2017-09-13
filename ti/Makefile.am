AUTOMAKE_OPTIONS=foreign
#noinst_LIBRARIES = librpc.a
#librpc_a_LIBADD =\
#$(STATIC_LIBS)
#librpc_a_SOURCES=\
#tima_proc_rpc.c \
#tima_proc_rpcd.h \
#tima_typedef.h \
#tima_proc_rpcd.c \
#tima_proc_rpc.h
lib_LTLIBRARIES = libtmipc.la
LIBS=$(DYNAMIC_LIBS)
libtmipc_la_LDFLAGS = -fPIC $(EXTRA_LDFLAGS)
#libtmipc_la_LDFLAGS = $(EXTRA_LDFLAGS)
libtmipc_la_LIBADD =\
$(STATIC_LIBS)
#$(project_dir)/premake/x86/install/lib/libnanomsg.so
#$(project_dir)/premake/x86/install/lib/libnanomsg.a
#$(project_dir)/premake/x86/install/lib/libnanomsg.so
#$(STATIC_LIBS)
libtmipc_la_SOURCES=\
tima_eventq.c \
tima_eventq.h \
tima_pub.c \
tima_pub.h \
tima_rpc.c \
tima_rpcd.c \
tima_rpcd.h \
tima_rpc.h \
tima_sub.c \
tima_sub.h \
tima_typedef.h
include_HEADERS =\
tima_typedef.h \
tima_rpc.h \
tima_rpcd.h \
tima_pub.h \
tima_sub.h \
tima_eventq.h
