/***************************************************************************
                               qt_flashdialog.h
                             -------------------
    begin                : Die Aug 12 10:16:57 CEST 2003
    copyright            : (C) 2003 DLR RM by Jan Grewe
    email                : jan.grewe@gmx.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 +   any later version.                                                    *
 ***************************************************************************/

/***************************************************************************
	Ver      date       Author        comment
	--------------------------------------------------------------------------
	1.0   12.08.2003    Jan Grewe     build
  1.1   27.08.2004    Jan Grewe     find possible interfaces
 ***************************************************************************/
#ifndef QT_FLASHDIALOG_H
#define QT_FLASHDIALOG_H

#include <qapplication.h>
#include <qvariant.h>
#include <qdialog.h>
#include <qimage.h>
#include <qpixmap.h>

#include "Picture.h"
#include "Asuro.h"

#define START_PAGE 0x0000


#define END_PAGE   0x2000

#define MAX_PAGE  128    // AtmelMega8 8kByte Flash
#define PAGE_SIZE 64 + 3 // Bytes +1PageNo +2 CRC16
#define BOOT_SIZE 1024   // Bytes

#define TIMEOUT_CONNECT 10
#define TIMEOUT_FLASH   5
#define MAX_TRY 10


class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QLabel;
class QLineEdit;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QTextView;
class QComboBox;

class QT_FlashDialog : public QDialog, public CAsuro
{ 
	Q_OBJECT

	public:
		QT_FlashDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE,
				WFlags fl = WStyle_Customize | WStyle_DialogBorder | WStyle_Title | WStyle_SysMenu | WStyle_Minimize);
		~QT_FlashDialog();

		QLabel* PixmapLabel1;
		QLabel* ABOUT;
		QLineEdit* FILE;
		QLabel* STATUS;
		QProgressBar* PROGRESSBAR;
		QTextView* TEXT;
		QPushButton* EXIT;
		QComboBox* PORT;
		QLineEdit* PORT_TEXT;
		QPushButton* BROWSE;
		QPushButton* PROGRAMM;

		QString m_fileName,m_portName,m_msg;
		unsigned char m_Port;
		void Status(char* text);
		void MessageText(char* text);
		void WarningText(char* text);
		void SuccessText (char* text);
		void ErrorText(char* text);
		void Progress(unsigned int progress);
		void ViewUpdate(void);
		void TimeWait(unsigned int time); // msec

		public slots:
			void slotCancel(void);
		void slotBrowse(void);
		void slotPort(int);
		void slotProgramm(void);
		void slotNewPort (const QString &);
		void slotNewFileName (const QString &);
};

#endif /* QT_FLASHDIALOG_H */
