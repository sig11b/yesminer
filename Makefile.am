AUTOMAKE_OPTIONS = subdir-objects

if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/compat/jansson
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json makefile.in

SUBDIRS		= compat

bin_PROGRAMS	= yesminer

dist_man_MANS	= yesminer.1

CLEANFILES 	= yesminer.1

yesminer_SOURCES	=	elist.h miner.h compat.h \
				cpu-miner.c util.c \
				sha2.c \
				yespower-1.0.1/sha256.c yespower-1.0.1/yespower-opt.c \
				yespower-1.0.1-power2b/sha256-p2b.c yespower-1.0.1-power2b/yespower-opt-p2b.c yespower-1.0.1-power2b/blake2b.c \
				YespowerMbc.c \
				yespower.c

yesminer_LDFLAGS	= $(PTHREAD_FLAGS)
yesminer_LDADD		= @LIBCURL@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@
yesminer_CPPFLAGS	= $(PTHREAD_FLAGS) @CPPFLAGS@ $(JANSSON_INCLUDES)

#
%.1: manpage.in miner.h
	-sed -e "s,\@VERSION\@,$(VERSION),g" \
	-e "s,\@PACKAGE_NAME\@,$(PACKAGE_NAME)," \
	-e "s,\@PACKAGE_NAME_UPPER\@,`echo $(PACKAGE_NAME) |tr [:lower:] [:upper:]`," \
	-e "s,\@DATE\@,`date -r $? +%F`," \
	-e '/.RS 11/q' manpage.in > $@
	-grep '\[ALGO' miner.h | sed '/NONE/q' | grep -v NONE | sed -e s/'.*= *"'// -e s/'".*'// | sort >> $@
	-echo '.RE' >> $@ ; echo '.RS' >> $@ ; echo 'Historic algorithms:' >> $@ ; echo '.RE' >> $@ ; echo '.RS 11' >> $@ ;
	-grep '\[ALGO' miner.h | sed -n '/NONE/,$$p' | grep -v NONE | sed -e s/'.*= *"'// -e s/'".*'// | sort >> $@
	-sed -n '/.RS 11/,$$p' manpage.in | grep -v '.RS 11' | sed "s,\@PACKAGE_NAME\@,$(PACKAGE_NAME)," >> $@
	-sed -e /'^ *$$'/d -e s/$$/,/ -e '$$s/,//' AUTHORS >> $@

