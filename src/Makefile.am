lib_LTLIBRARIES = libproxygenrouting.la

libproxygenrouting_ladir = $(includedir)/proxygen/httpserver/routing
libproxygenrouting_la_HEADERS = Router.h \
				Route.h \
				AbstractRoute.h \
				DefaultRouteHandler.h
libproxygenrouting_la_SOURCES = Router.cpp \
				Router.h \
				AbstractRoute.h\
				Route.h \
				DefaultRouteHandler.h \
				DefaultRouteHandler.cpp
libproxygenrouting_la_CXXFLAGS = $(r3_CFLAGS) $(proxygenhttpserver_CFLAGS) $(folly_CFLAGS)
libproxygenrouting_la_LDFLAGS = $(r3_LIBS) $(proxygenhttpserver_LIBS) $(folly_LIBS)

