# support by:
#    https://gnunet.org/svn/gnunet-qt/configure.ac
#    http://git.savannah.gnu.org/cgit/gnokii.git/tree/
#    http://git.0pointer.de/?p=avahi.git;a=blob_plain;f=configure.ac;hb=HEAD

# use: autoreconf -i

AC_PREREQ([2.63])
AC_INIT([asuroflash], [1.2], [asuro-bug@li-pro.net])
AM_INIT_AUTOMAKE([1.10 dist-bzip2 dist-zip])
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/Con_Flash.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

BUILDDATE=`date +%Y-%m-%d`
AC_SUBST(BUILDDATE)

AC_CANONICAL_HOST

# Setup defaults.
CPPFLAGS="-D_CONSOLE $CPPFLAGS"

# Check system type.
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
#REQUIRES_LIBANY="anylib >= 0.0-0"
#AC_SUBST(REQUIRES_LIBANY)
#PKG_CHECK_MODULES(anylib, $REQUIRES_LIBANY)

#
# Check for Qt 3
#
AC_ARG_ENABLE(qt3,
	AS_HELP_STRING([--disable-qt3],[Disable building of Qt3 frontend]),
	[case "${enableval}" in
		yes) HAVE_QT3=yes ;;
		no)  HAVE_QT3=no ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-qt3) ;;
	esac],
	[HAVE_QT3=yes])

if test "x$HAVE_QT3" = "xyes" ; then
	PKG_CHECK_MODULES( QT3, [ qt-mt >= 3.0.0 ])
	AC_SUBST(QT3_CFLAGS)
	AC_SUBST(QT3_LIBS)
	QT3_PREFIX="`$PKG_CONFIG --variable=prefix qt-mt`/bin"
	AC_PATH_PROGS(MOC_QT3, [moc-qt3 moc], no, [$QT3_PREFIX])
	if test "$MOC_QT3" = no; then
		AC_MSG_ERROR([Could not find QT3 moc])
	fi
	AC_SUBST(MOC_QT3)
	AC_PATH_PROGS(UIC_QT3, [uic-qt3 uic], no, [$QT3_PREFIX])
	if test "$UIC_QT3" = no; then
		AC_MSG_ERROR([Could not find QT3 uic])
	fi
	AC_SUBST(UIC_QT3)
fi
AM_CONDITIONAL(HAVE_QT3, test "x$HAVE_QT3" = "xyes")

#
# Check for Qt 4
#
AC_ARG_ENABLE(qt4,
	AS_HELP_STRING([--enable-qt4],[Disable building of Qt4Core frontend]),
	[case "${enableval}" in
		yes) HAVE_QT4=yes ;;
		no)  HAVE_QT4=no ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-qt4) ;;
	esac],
	[HAVE_QT4=no])

if test "x$HAVE_QT4" = "xyes" ; then
	PKG_CHECK_MODULES( QT4, [ QtCore >= 4.0.0 ])
	AC_SUBST(QT4_CFLAGS)
	AC_SUBST(QT4_LIBS)
	QT4_PREFIX="`$PKG_CONFIG --variable=prefix QtCore`/bin"
	AC_PATH_PROGS(MOC_QT4, [moc-qt4 moc], no, [$QT4_PREFIX])
	if test "$MOC_QT4" = no; then
		AC_MSG_ERROR([Could not find QT4 moc])
	fi
	AC_SUBST(MOC_QT4)
	AC_PATH_PROGS(UIC_QT4, [uic-qt4 uic], no, [$QT4_PREFIX])
	if test "$UIC_QT4" = no; then
		AC_MSG_ERROR([Could not find QT4 uic])
	fi
	AC_SUBST(UIC_QT4)
fi
AM_CONDITIONAL(HAVE_QT4, test "x$HAVE_QT4" = "xyes")

#
# Check for GTK+ 2.0
#
AC_ARG_ENABLE(gtk,
	AS_HELP_STRING([--enable-gtk],[Disable use of GTK+ 2]),
	[case "${enableval}" in
		yes) HAVE_GTK=yes ;;
		no)  HAVE_GTK=no ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-gtk) ;;
	esac],
	[HAVE_GTK=no])

if test "x$HAVE_GTK" = "xyes" ; then
	# Check for GTK 2.0
	PKG_CHECK_MODULES(GTK20, [ gtk+-2.0 >= 2.14.0 ])
	AC_SUBST(GTK20_CFLAGS)
	AC_SUBST(GTK20_LIBS)
fi
AM_CONDITIONAL(HAVE_GTK, test "x$HAVE_GTK" = "xyes")

#
# Check for GTK+ 3.0
#
AC_ARG_ENABLE(gtk3,
	AS_HELP_STRING([--enable-gtk3],[Disable use of GTK+ 3]),
	[case "${enableval}" in
		yes) HAVE_GTK3=yes ;;
		no)  HAVE_GTK3=no ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-gtk3) ;;
	esac],
	[HAVE_GTK3=no])

if test "x$HAVE_GTK3" = "xyes" ; then
	# Check for GTK 3.0
	PKG_CHECK_MODULES(GTK30, [ gtk+-3.0 ])
	AC_SUBST(GTK30_CFLAGS)
	AC_SUBST(GTK30_LIBS)
fi
AM_CONDITIONAL(HAVE_GTK3, test "x$HAVE_GTK3" = "xyes")

AM_CONDITIONAL(HAVE_GTK2OR3, test "x$HAVE_GTK3" = "xyes" -o "x$HAVE_GTK" = "xyes" )

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

# ==========================================================================
AS_AC_EXPAND(EXPANDED_BINDIR, "$bindir")

echo "
 ---{ $PACKAGE_NAME $VERSION }---

    prefix:                     ${prefix}
    bindir:                     ${EXPANDED_BINDIR}
    C Compiler:                 ${CC}
    CFLAGS:                     ${CFLAGS}
    Enable GTK 2.0:             ${HAVE_GTK}
    Enable GTK 3.0:             ${HAVE_GTK3}
    Enable QT3:                 ${HAVE_QT3}
    Enable QT4:                 ${HAVE_QT4}
"

echo "\
    Building asuroflash         yes
    Building qasuroflash        ${HAVE_QT3}
    Building gasuroflash        ${HAVE_GTK}
"
