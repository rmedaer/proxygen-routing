# Initialize autotools
AC_PREREQ([2.69])
AC_INIT([proxygenrouting], [1], [rme@escaux.com])
AM_INIT_AUTOMAKE([foreign])
LT_INIT

# We are developing in C++11
AC_PROG_CC
AC_PROG_CXX
AX_CHECK_COMPILE_FLAG([-std=c++1y], [CXXFLAGS="$CXXFLAGS -std=c++1y"])

AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Check libraries and headers
PKG_CHECK_MODULES(r3, r3)

AC_CHECK_LIB([folly], [getenv], [], [AC_MSG_ERROR(
    [Please install folly library])])

AC_CHECK_LIB([proxygenhttpserver], [getenv], [], [AC_MSG_ERROR(
    [Please install proxygen library])])

AC_OUTPUT([Makefile src/Makefile])
