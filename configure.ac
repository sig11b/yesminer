AC_INIT([yesminer],[2.6.1])

AC_PREREQ([2.69])
AC_CANONICAL_TARGET
AC_CONFIG_SRCDIR([cpu-miner.c])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS([cpuminer-config.h])

dnl Make sure anyone changing configure.ac/Makefile.am has a clue
AM_MAINTAINER_MODE

EXTERNAL_CFLAGS="$CFLAGS"

dnl Checks for programs
AC_PROG_CC
dnl - obsolote? AC_PROG_CC_C99
dnl - obsolote? AC_PROG_GCC_TRADITIONAL
AM_PROG_CC_C_O
AM_PROG_AS
AC_PROG_RANLIB

if test -n "$EXTERNAL_CFLAGS"; then
	CFLAGS="$EXTERNAL_CFLAGS"
else
	CFLAGS='-Wall -O3 -fomit-frame-pointer'
	AX_APPEND_COMPILE_FLAGS([-march=armv8-a+simd+crypto -march=native])
fi

dnl Checks for header files
dnl - obsolote? AC_HEADER_STDC
AC_CHECK_HEADERS([sys/endian.h sys/param.h syslog.h])
AC_CHECK_LIB([log],[syslog])
# sys/sysctl.h requires sys/types.h on FreeBSD
# sys/sysctl.h requires sys/param.h on OpenBSD
AC_CHECK_HEADERS([sys/sysctl.h], [], [],
[#include <sys/types.h>
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
])

AC_CHECK_DECLS([be32dec, le32dec, be32enc, le32enc], [], [],
[AC_INCLUDES_DEFAULT
#ifdef HAVE_SYS_ENDIAN_H
#include <sys/endian.h>
#endif
])

AC_FUNC_ALLOCA
AC_CHECK_FUNCS([getopt_long])

PTHREAD_FLAGS="-pthread"
WS2_LIBS=""

# conditional builds for all platforms
case $target in
*-*-mingw*)
	have_win32=true
	PTHREAD_FLAGS=""
	WS2_LIBS="-lws2_32"
	;;

*linux*)
	if test -z "$LIBCURL"; then
	LIBCURL="-lcurl"
	fi

	# libcurl install path (for mingw : --with-curl=/usr/local)
	AC_ARG_WITH([curl],
		[  --with-curl=PATH         prefix where curl is installed [default=/usr]])

	if test -n "$with_curl"; then
	LIBCURL_CFLAGS="$LIBCURL_CFLAGS -I$with_curl/include"
	LIBCURL_CPPFLAGS="$LIBCURL_CPPFLAGS -I$with_curl/include"
	LIBCURL_LDFLAGS="$LIBCURL_LDFLAGS -L$with_curl/lib"
	fi

	# SSL install path (for mingw : --with-crypto=/usr/local/ssl)
	AC_ARG_WITH([crypto],
		[  --with-crypto=PATH       prefix where openssl crypto is installed [default=/usr]])

	if test -n "$with_crypto" ; then
	LIBCURL_CFLAGS="$LIBCURL_CFLAGS -I$with_crypto/include"
	LIBCURL_CPPFLAGS="$LIBCURL_CPPFLAGS -I$with_crypto/include"
	LIBCURL_LDFLAGS="-L$with_crypto/lib $LIBCURL_LDFLAGS"
	LIBCURL="$LIBCURL -lssl -lcrypto"
	fi

	CFLAGS="$CFLAGS $LIBCURL_CFLAGS"
	CPPFLAGS="$CPPFLAGS $LIBCURL_CPPFLAGS"
	LDFLAGS="$LDFLAGS $LIBCURL_LDFLAGS"

	AC_SUBST(LIBCURL)
	# AC_SUBST(LIBCURL_CFLAGS)
	# AC_SUBST(LIBCURL_CPPFLAGS)
	# AC_SUBST(LIBCURL_LDFLAGS)
	;;

*-apple-*)
	if test -z "$LIBCURL"; then
		LIBCURL="-lcurl"
	fi

	# libcurl install path (for mingw : --with-curl=/usr/local)
	AC_ARG_WITH([curl],
	  [  --with-curl=PATH         prefix where curl is installed [default=/usr]])

	if test -n "$with_curl"; then
		LIBCURL_CFLAGS="$LIBCURL_CFLAGS -I$with_curl/include"
		LIBCURL_CPPFLAGS="$LIBCURL_CPPFLAGS -I$with_curl/include"
		LIBCURL_LDFLAGS="$LIBCURL_LDFLAGS -L$with_curl/lib"
	fi

	# SSL install path (for mingw : --with-crypto=/usr/local/ssl)
	AC_ARG_WITH([crypto],
	   [  --with-crypto=PATH       prefix where openssl crypto is installed [default=/usr]])

	if test -n "$with_crypto" ; then
	   LIBCURL_CFLAGS="$LIBCURL_CFLAGS -I$with_crypto/include"
	   LIBCURL_CPPFLAGS="$LIBCURL_CPPFLAGS -I$with_crypto/include"
	   LIBCURL_LDFLAGS="-L$with_crypto/lib $LIBCURL_LDFLAGS"
	   LIBCURL="$LIBCURL -lssl -lcrypto"
	fi

	CFLAGS="$CFLAGS $LIBCURL_CFLAGS"
	CPPFLAGS="$CPPFLAGS $LIBCURL_CPPFLAGS"
	LDFLAGS="$LDFLAGS $LIBCURL_LDFLAGS"

	AC_SUBST(LIBCURL)
	# AC_SUBST(LIBCURL_CFLAGS)
	# AC_SUBST(LIBCURL_CPPFLAGS)
	# AC_SUBST(LIBCURL_LDFLAGS)
	;;
esac

case $target in
  *-*-mingw*)
		LIBCURL_CHECK_CONFIG(, 7.15.2, ,
		  [AC_MSG_ERROR([Missing required libcurl >= 7.15.2])])
		;;
esac

AC_CHECK_LIB(jansson, json_loads, request_jansson=false, request_jansson=true)
AC_CHECK_LIB([pthread], [pthread_create], PTHREAD_LIBS="-lpthread",
  AC_CHECK_LIB([pthreadGC2], [pthread_create], PTHREAD_LIBS="-lpthreadGC2",
    AC_CHECK_LIB([pthreadGC1], [pthread_create], PTHREAD_LIBS="-lpthreadGC1",
      AC_CHECK_LIB([pthreadGC], [pthread_create], PTHREAD_LIBS="-lpthreadGC"
))))

AM_CONDITIONAL([WANT_JANSSON], [test x$request_jansson = xtrue])
AM_CONDITIONAL([HAVE_WINDOWS], [test x$have_win32 = xtrue])

if test x$request_jansson = xtrue
then
	JANSSON_LIBS="compat/jansson/libjansson.a"
else
	JANSSON_LIBS=-ljansson
fi

AC_SUBST(JANSSON_LIBS)
AC_SUBST(PTHREAD_FLAGS)
AC_SUBST(PTHREAD_LIBS)
AC_SUBST(WS2_LIBS)

AC_CONFIG_FILES([
	Makefile
	compat/Makefile
	compat/jansson/Makefile
	])
AC_OUTPUT
