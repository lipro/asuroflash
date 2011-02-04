bin_PROGRAMS = asuroflash qasuroflash

EXTRA_DIST = \
	WinSerial.cpp \
	WinSerial.h

asuroflash_SOURCES = \
	Con_Flash.cpp \
	ANSIAsuro.cpp \
	ANSIAsuro.h \
	Asuro.cpp \
	Asuro.h \
	PosixSerial.cpp \
	PosixSerial.h \
	Serial.cpp \
	Serial.h

qasuroflash_CPPFLAGS = \
	$(QT_CXXFLAGS)

qasuroflash_LDADD = \
	$(QT_LIBS)

qasuroflash_SOURCES = \
	Main.cpp \
	Picture.h \
	Qt_FlashDialog.cpp \
	Qt_FlashDialog.h \
	Asuro.cpp \
	Asuro.h \
	PosixSerial.cpp \
	PosixSerial.h \
	Serial.cpp \
	Serial.h

nodist_qasuroflash_SOURCES = \
	Qt_FlashDialog.moc.cpp

# Define special suffices for moc/uic
SUFFIXES = .ui.h .moc.cpp

# Convert %.ui files into %.ui.h
.ui.ui.h:
	$(QT_UIC) $< -o $@

# Create %.moc.cpp from %.h
.h.moc.cpp:
	$(QT_MOC) $< -o $@

CLEANFILES = $(nodist_qasuroflash_SOURCES)
