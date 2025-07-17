AUTOMAKE_OPTIONS = subdir-objects

if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/compat/jansson
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json manpage.in

SUBDIRS		= compat

bin_PROGRAMS	= yesminer

dist_man_MANS	= yesminer.1

CLEANFILES 	= yesminer.1 yespower-1.0.1/yespower-sse2neon.c

yesminer_SOURCES	=	elist.h miner.h compat.h \
				cpu-miner.c util.c \
				sha2.c \
				yespower-1.0.1/sha256.c yespower-1.0.1/blake2b.c yespower-1.0.1/blake256.c \
				yespower-1.0.1/yespower-pow.c \
				yespower.c

yespower-1.0.1/yespower-pow.c: yespower-1.0.1/yespower-sse2neon.c

yespower-1.0.1/yespower-sse2neon.c: yespower-1.0.1/yespower-opt.c
	sed \
	-e 's/#include <[e,x,s]mmintrin.h>/#include "sse2neon.h"/' \
	-e 's/#include "yespower-opt.c"/#include "yespower-sse2neon.c"/' \
	$? > $@
#all	-e 's/#include <[e,x,p,t,s,n,w]mmintrin.h>/#include "sse2neon.h"/'

#yespower-1.0.1/yespower-pow.o : CFLAGS += -D__SSE__ -D__SSE2__ -D__AVX__


AM_LDFLAGS	= $(PTHREAD_FLAGS)
yesminer_LDADD	= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@
AM_CPPFLAGS	= $(PTHREAD_FLAGS) @CPPFLAGS@ $(JANSSON_INCLUDES)

#
%.1: manpage.in miner.h AUTHORS
	-sed -e "s,\@VERSION\@,$(VERSION),g" \
	-e "s,\@PACKAGE_NAME\@,$(PACKAGE_NAME)," \
	-e "s,\@PACKAGE_NAME_UPPER\@,`echo $(PACKAGE_NAME) |tr [:lower:] [:upper:]`," \
	-e "s,\@DATE\@,`date -r manpage.in +%F`," \
	-e '/.RS 11/q' manpage.in > $@
	-grep '\[ALGO' miner.h | sed '/NONE/q' | grep -v NONE | sed -e s/'.*= *"'// -e s/'".*'// | sort  | sed s/'\\n             '/'`'/ | tr '`' '\n' >> $@
	-echo '.RE' >> $@ ; echo '.RS' >> $@ ; echo 'Historic algorithms:' >> $@ ; echo '.RE' >> $@ ; echo '.RS 11' >> $@ ;
	-grep '\[ALGO' miner.h | sed -n '/NONE/,$$p' | grep -v NONE | sed -e s/'.*= *"'// -e s/'".*'// | sed s/'\\n             '/'`'/ | tr '`' '\n' >> $@
	-sed -n '/.RS 11/,$$p' manpage.in | grep -v '.RS 11' | sed "s,\@PACKAGE_NAME\@,$(PACKAGE_NAME)," >> $@
	-sed -e /'^ *$$'/d -e s/$$/,/ -e '$$s/,//' AUTHORS >> $@

