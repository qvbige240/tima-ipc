#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([test], 1.0)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])

# Checks for programs.
AC_PROG_CC
#AC_PROG_RANLIB
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lc':
AC_CHECK_LIB([c], [main])
# FIXME: Replace `main' with a function in `-lgcc':
AC_CHECK_LIB([gcc], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h string.h sys/time.h termios.h unistd.h])
project_dir=$PWD
echo "project dir: $project_dir"
AC_SUBST(project_dir)

if test x$enable_sqlite3 = xyes; then
	SQLITE3_LIB='libsqlite3.a'
    AC_DEFINE(USE_SQLITE3, 1, [if sqlite3 is enabled])
    DEFINE_CFLAGS="$DEFINE_CFLAGS -DUSE_SQLITE3"
else
    SQLITE3_LIB=''
fi

if test x$enable_zlog = xyes; then
	ZLOG_LIB='libzlog.a'
    AC_DEFINE(USE_ZLOG, 1, [if zlog is enabled])
    DEFINE_CFLAGS="$DEFINE_CFLAGS -DUSE_ZLOG"
else
    ZLOG_LIB=''
fi

DEFINE_CFLAGS="$DEFINE_CFLAGS -DUSE_TESTDEF"
echo "DEFINE_CFLAGS: $DEFINE_CFLAGS"
echo "sqlite lib: $SQLITE3_LIB"

if test x$enable_x86 = xyes; then
    PLATFORMS="_X86_"
    GBASE_INCLUDE="/usr/include"
    GBASE_LIB="/usr/lib"
    echo "use gcc to compile"
    #AM_CFLAGS="-Wall -Wextra -Wdeclaration-after-statement"
	GOLBAL_CFLAGS="-g -O0 -DDEBUG -D_X86_ $DEFINE_CFLAGS -I${GBASE_INCLUDE}"
	GOLBAL_CPPFLAGS="-g -O0 -DDEBUG -D_X86_ -I${GBASE_INCLUDE}"
	GOLBAL_LDFLAGS="-L${GBASE_LIB} -L/lib"
	AC_SUBST(GOLBAL_CFLAGS)

    LIB_PATH='$(project_dir)/../premake/x86/install/lib'
	NANOMSG_LIB='$(project_dir)/../premake/x86/install/lib/libnanomsg.a'
	
	JANSSON_LIB='$(project_dir)/x86/lib/libjansson.a'
	CURL_LIB='$(project_dir)/x86/lib/libcurl.a'
	#SQLITE3_LIB='$(project_dir)/x86/lib/libsqlite3.a'
    #AC_SUBST(CURL_LIB)
	#AC_SUBST(JANSSON_LIB)

    STATIC_LIBS="$STATIC_LIBS $NANOMSG_LIB"

    if test X"$SQLITE3_LIB" != X; then
        STATIC_LIBS="$STATIC_LIBS $LIB_PATH/$SQLITE3_LIB"
    fi

    if test X"$ZLOG_LIB" != X; then
        STATIC_LIBS="$STATIC_LIBS $LIB_PATH/$ZLOG_LIB"
    fi

    echo "STATIC_LIBS: $STATIC_LIBS"
	AC_SUBST(STATIC_LIBS)
	
	DYNAMIC_LIBS="-ldl -lpthread -lrt -lanl"
	#DYNAMIC_LIBS="-lnanomsg -lpthread"
	AC_SUBST(DYNAMIC_LIBS)
	CFLAGS='-Wall $(GOLBAL_CFLAGS) -I$(project_dir)/../premake/x86/install/include/ -I$(project_dir)/ti'
	EXTRA_LDFLAGS='$(GOLBAL_LDFLAGS)'
	#EXTRA_LDFLAGS='$(project_dir)/../premake/x86/install/lib/'
	AC_SUBST(EXTRA_LDFLAGS)
else
    PLATFORMS="_NT966X_"
	GBASE_INCLUDE="/opt/mipsel-24kec-linux-uclibc/usr/mipsel-24kec-linux-uclibc/sysroot/usr/include"
	GBASE_LIB="/opt/mipsel-24kec-linux-uclibc/usr/mipsel-24kec-linux-uclibc/sysroot/lib"
	GOLBAL_CFLAGS="-g -O0 -DDEBUG -D_NT966X_ $DEFINE_CFLAGS -I${GBASE_INCLUDE}"
	GOLBAL_CPPFLAGS="-g -O0 -DDEBUG -D_NT966X_ -I${GBASE_INCLUDE}"
	GOLBAL_LDFLAGS="-L${GBASE_LIB}"
	AC_SUBST(GOLBAL_CFLAGS)

    LIB_PATH='$(project_dir)/mips/lib'
	
	JANSSON_LIB='$(project_dir)/mips/lib/libjansson.a'
	#CURL_LIB='$(project_dir)/mips/lib/libcurl.a'
	CURL_LIB=''
	#SQLITE3_LIB='$(project_dir)/mips/lib/libsqlite3.a'
    #AC_SUBST(SQLITE3_LIB)
	#AC_SUBST(JANSSON_LIB)
    #AC_SUBST(CURL_LIB)
    
	STATIC_LIBS="$STATIC_LIBS $JANSSON_LIB $CURL_LIB"

    if test X"$SQLITE3_LIB" != X; then
        STATIC_LIBS="$STATIC_LIBS $LIB_PATH/$SQLITE3_LIB"
    fi

    if test X"$ZLOG_LIB" != X; then
        STATIC_LIBS="$STATIC_LIBS $LIB_PATH/$ZLOG_LIB"
    fi

    echo "STATIC_LIBS: $STATIC_LIBS"
	AC_SUBST(STATIC_LIBS)

	DYNAMIC_LIBS="-lcrypto -lcurl -lssl -lnvtuctrl -ldl -lpthread -lrt -lm"
	#DYNAMIC_LIBS="-lnvtuctrl -lpthread -lrt -lm"
	AC_SUBST(DYNAMIC_LIBS)
	EXTRA_LDFLAGS='-L$(project_dir)/mips/lib'
	AC_SUBST(EXTRA_LDFLAGS)
	CFLAGS='-Wall $(GOLBAL_CFLAGS) -I$(project_dir)/mips/include -I$(project_dir)/vpk/inc -I$(project_dir)/vpk/src'
fi
echo "platform: $PLATFORMS"
echo "platform11111: ${PLATFORMS}"
echo 'platform222222: $(PLATFORMS)'
AM_CONDITIONAL(X8666, test "${PLATFORMS}" = "_X86_")
AM_CONDITIONAL(NT966X, test "${PLATFORMS}" = "_NT966X_")

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([bzero memset select strstr])

AC_CONFIG_FILES([Makefile
                 sample/Makefile
                 ti/Makefile])

AC_OUTPUT
