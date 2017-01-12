AM_CPPFLAGS= $(PPARAM_CFLAGS) -I../include

noinst_PROGRAMS= udobject
udobject_SOURCES= udobject.cpp

examples_ldadd= $(PPARAM_LIBS) -L$(top_srcdir)/src/.libs -lpobject -lpthread
examples_ldflags= -Wl,--rpath -Wl,$(top_srcdir)/src/.libs

udobject_LDADD= $(examples_ldadd)
udobject_LDFLAGS= $(examples_ldflags)
