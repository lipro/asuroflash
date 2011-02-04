AC_PREREQ([2.63])
AC_INIT([asuroflash], [1.2-devel], [asuro-bug@li-pro.net])
AM_INIT_AUTOMAKE([1.10 dist-bzip2 dist-zip])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/Con_Flash.cpp])
AC_CONFIG_HEADERS([config.h])

BUILDDATE=`date +%Y-%m-%d`
AC_SUBST(BUILDDATE)

AC_CANONICAL_HOST

# Setup defaults.
CPPFLAGS="-D_CONSOLE $CPPFLAGS"

# Check system type.
# TODO support more OS, see:
#    https://gnunet.org/svn/gnunet-qt/configure.ac
#    http://git.savannah.gnu.org/cgit/gnokii.git/tree/
AC_MSG_CHECKING([checking system type])
case "$host_os" in
linux*)
	AC_MSG_RESULT([Linux])
	AC_DEFINE_UNQUOTED(LINUX,1,[This is a Linux system])
	CPPFLAGS="-D_LINUX_ $CPPFLAGS"
	;;
*)
	AC_MSG_RESULT(Unrecognised OS $host_os)
	AC_DEFINE_UNQUOTED(OTHEROS,1,[Some strange OS])
	;;
esac

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h sys/ioctl.h sys/time.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_HEADER_STDC

# Checks for library functions.
AC_CHECK_FUNCS([memset strrchr strstr])

# Output configuration files.
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
