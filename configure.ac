AC_INIT([dtexconvert], [], [dtexconvert@yudin.org])
AC_PREREQ(2.61)
AC_CONFIG_SRCDIR(src/main.cpp)

AM_INIT_AUTOMAKE(dtexconvert, 0.1)
AM_CONFIG_HEADER(config.h)
AC_PROG_CXX
AC_HEADER_STDC

if test "$DELIGHT" == ""; then
	AC_MSG_ERROR( [Test for 3delight failed. helloworld required 3delight.])
else
	AC_CHECK_HEADER([${DELIGHT}]/include/dtex.h, break,
		AC_MSG_ERROR([Test for 3delight failed. helloworld required 3delight.]))
fi

CPPFLAGS="$CPPFLAGS -I\${DELIGHT}/include"

AC_CONFIG_FILES([
Makefile 
src/Makefile
])

AC_OUTPUT

echo "
Configuration:

  Source code location:       ${srcdir}
  Compiler:                   ${CC}
  Compiler flags:             ${CPPFLAGS}
"
