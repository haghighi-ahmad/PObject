AM_CPPFLAGS= $(PPARAM_CFLAGS) \
	-I../include

pobjectincludedir = $(includedir)/pvm/pobject
pobjectinclude_HEADERS = ../include/xobject.hpp 

lib_LTLIBRARIES= libpobject.la
libpobject_la_SOURCES= xobject.cpp
libpobject_la_LDFLAGS= -version-info $(LIBPOBJECT_SO_VERSION)
libpobject_la_LIBADD= $(PPARAM_LIBS)
