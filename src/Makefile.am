bin_PROGRAMS = asuroflash

EXTRA_DIST = \
	WinSerial.cpp \
	WinSerial.h

asuroflash_SOURCES = \
	Con_Flash.cpp \
	Con_FlashDialog.cpp \
	Con_FlashDialog.h \
	Asuro.cpp \
	Asuro.h \
	PosixSerial.cpp \
	PosixSerial.h \
	Serial.cpp \
	Serial.h

if HAVE_GTK
bin_PROGRAMS += gasuroflash

gasuroflash_CPPFLAGS = \
	$(GTK20_CFLAGS) \
	$(GTKMM24_CFLAGS) \
	$(GTHREAD_CFLAGS)

gasuroflash_LDADD = \
	$(GTK20_LIBS) \
	$(GTKMM24_LIBS) \
	$(GTHREAD_LIBS)

gasuroflash_SOURCES = \
	Gtk_Flash.cpp \
	Gtk_FlashDialog.cpp \
	Gtk_FlashDialog.h \
	Asuro.cpp \
	Asuro.h \
	PosixSerial.cpp \
	PosixSerial.h \
	Serial.cpp \
	Serial.h

endif # HAVE_GTK

if HAVE_QT3
bin_PROGRAMS += qasuroflash

qasuroflash_CPPFLAGS = \
	$(QT3_CFLAGS)

qasuroflash_LDADD = \
	$(QT3_LIBS)

qasuroflash_SOURCES = \
	Qt_Flash.cpp \
	Qt_FlashDialog.cpp \
	Qt_FlashDialog.h \
	Picture.h \
	Asuro.cpp \
	Asuro.h \
	PosixSerial.cpp \
	PosixSerial.h \
	Serial.cpp \
	Serial.h

nodist_qasuroflash_SOURCES = \
	Qt_FlashDialog.moc.cpp

CLEANFILES = $(nodist_qasuroflash_SOURCES)

# Define special suffices for moc/uic
SUFFIXES = .ui.h .moc.cpp

# Convert %.ui files into %.ui.h
.ui.ui.h:
	$(UIC_QT3) $< -o $@

# Create %.moc.cpp from %.h
.h.moc.cpp:
	$(MOC_QT3) $< -o $@

endif # HAVE_QT3

