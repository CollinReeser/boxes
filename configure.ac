AC_INIT([main],[0.1])

dnl Switch to a C++ compiler, and check if it works.
AC_LANG(C++)
AC_PROG_CXX

dnl Require certain headers to exist (which also imples >=C++23 support).
AC_CHECK_HEADERS([print], [], [AC_MSG_ERROR([<print> header required])])
AC_CHECK_HEADERS([format], [], [AC_MSG_ERROR([<format> header required])])
AC_CHECK_HEADERS([generator], [], [AC_MSG_ERROR([<generator> header required])])

AC_ARG_VAR(SDL_DIR, "Root of built SDL git clone, with `include` and `build`")

AC_ARG_VAR(MDSPAN_DIR, "Directory containing an `mdspan.hpp` <mdspan> implementation")

dnl Process Makefile.in to create Makefile
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
