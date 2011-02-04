ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

EXTRA_DIST = \
	Windows/MSVS2008/asuroflash.sln \
	Windows/MSVS2008/asuroflash.vcproj

.PHONY : ChangeLog
ChangeLog:
	git log --no-merges master | \
		unexpand -a | sed -e 's/\s\s*$$//' > $@

