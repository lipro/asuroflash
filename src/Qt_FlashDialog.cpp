/****************************************************************************
** Form implementation generated from reading ui file 'QT_FlashDialog.ui'
**
** Created: Don Mai 8 17:11:22 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Qt_FlashDialog.h"
#include <qvariant.h>

#include <qbuttongroup.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qtextview.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextstream.h>

#define TTYS   0
#define TTYUSB 1

/*
 *  Constructs a QT_FlashDialog which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
QT_FlashDialog::QT_FlashDialog( QWidget* parent,  const char* name, bool modal, WFlags fl ) : QDialog( parent, name, modal, fl), CAsuro()
{
	char portName[256];

	QPixmap image0( ( const char** ) logo_data );

	setName( "ASURO Flash Tool" );
	setFixedSize(392, 422);
	setCaption( "ASURO Flash Tool" );

	PixmapLabel1 = new QLabel( this, "PixmapLabel1" );
	PixmapLabel1->setGeometry( QRect( 150, 10, 82, 69 ) ); 
	PixmapLabel1->setPixmap( image0 );
	PixmapLabel1->setScaledContents( TRUE );

	ABOUT = new QLabel( this, "ABOUT" );
	ABOUT->setGeometry( QRect( 240, 0, 150, 90 ) );
	ABOUT->setText(ASUROAbout);

	FILE = new QLineEdit( this, "FILE" );
	FILE->setGeometry( QRect( 20, 97, 290, 25 ) );

	STATUS = new QLabel( this, "STATUS" );
	STATUS->setGeometry( QRect( 20, 180, 350, 20 ) );
	STATUS->setFrameShape( QLabel::StyledPanel );
	STATUS->setFrameShadow( QLabel::Sunken );
	STATUS->setAlignment( int( QLabel::AlignCenter ) );
	STATUS->setText( "" );

	PROGRESSBAR = new QProgressBar( 100, this, "PROGRESSBAR" );
	PROGRESSBAR->setGeometry( QRect( 20, 210, 350, 24 ) );
	PROGRESSBAR->setIndicatorFollowsStyle (FALSE);
	PROGRESSBAR->setProgress(0);

	TEXT = new QTextView( this, "TEXT" );
	TEXT->setGeometry( QRect( 20, 240, 350, 130 ) );
	TEXT->setText(LICENSE);

	EXIT = new QPushButton( this, "EXIT" );
	EXIT->setGeometry( QRect( 170, 380, 80, 31 ) ); 
	EXIT->setText( "Exit" );

	BROWSE = new QPushButton( this, "BROWSE" );
	BROWSE->setGeometry( QRect( 320, 95, 50, 29 ) ); 
	BROWSE->setText( ". . ." );

	PROGRAMM = new QPushButton( this, "PROGRAMM" );
	PROGRAMM->setGeometry( QRect( 150, 132, 101, 33 ) );
	PROGRAMM->setText( "Programm" );
	PROGRAMM->setEnabled(FALSE);

	PORT = new QComboBox( this, "PORT" );
	PORT->setGeometry( QRect( 20, 10, 140, 30 ) );

	PORT_TEXT = new QLineEdit( this, "PORT_TEXT" );
	PORT_TEXT->setGeometry( QRect( 20, 50, 130, 25 ) );

	// signals and slots connections
	connect( EXIT, SIGNAL( clicked() ),this, SLOT(slotCancel()));
	connect( BROWSE, SIGNAL( clicked() ), this, SLOT( slotBrowse()));
	connect( PROGRAMM, SIGNAL( clicked() ), this, SLOT( slotProgramm()));  
	connect( PORT, SIGNAL ( activated(int) ), this, SLOT( slotPort(int)));
	connect( PORT_TEXT, SIGNAL ( textChanged(const QString &) ), this, SLOT( slotNewPort(const QString &)));
	connect( FILE, SIGNAL ( textChanged(const QString &) ), this, SLOT( slotNewFileName(const QString &)));

	QFileInfo programPath;	
	QString tmp;

	tmp = programPath.absFilePath() + "/AsuroFl.ini";
	strcpy(m_ASUROIniPath,tmp.latin1());

	InitCAsuro();
	for (int i = 0; i < 255; i++)
		if (PortScan(portName,i,TTYS)) PORT->insertItem( trUtf8( portName ) );
	for (int i = 0; i < 255; i++)
		if (PortScan(portName,i,TTYUSB)) PORT->insertItem( trUtf8( portName ) );

	m_fileName = m_ASUROfileName;
	m_portName = m_ASUROCOMPort;

	// try to find port from *.ini file in ComboBox
	for(int i = 0; i < PORT->count(); i++) {
		PORT->setCurrentItem(i);
		if  (PORT->currentText() == m_portName) break;
	}

	FILE->setText(m_ASUROfileName);
	PORT_TEXT->setText(m_portName);
	if (m_fileName != "") PROGRAMM->setEnabled(TRUE); 
}

/*  
 *  Destroys the object and frees any allocated resources
 */
QT_FlashDialog::~QT_FlashDialog()
{
}

void QT_FlashDialog::slotBrowse()
{
	QFileDialog* fd = new QFileDialog( this, "file Dialog", TRUE);
	fd->setMode( QFileDialog::ExistingFile);
	fd->setFilter("ASURO Firmware (*.hex)");
	fd->setViewMode( QFileDialog::Detail);

	if( fd->exec() == QDialog::Accepted) {
		m_fileName = fd->selectedFile();
		strcpy(m_ASUROfileName,m_fileName.latin1());
		FILE->setText( m_fileName );
		if (m_fileName != "") PROGRAMM->setEnabled(TRUE); 
	}
}

void QT_FlashDialog::slotNewFileName (const QString &)
{
	m_fileName = FILE->text();
	strcpy(m_ASUROfileName,m_fileName.latin1());
}


void QT_FlashDialog::slotNewPort (const QString &)
{
	m_portName = PORT_TEXT->text();
	strcpy(m_ASUROCOMPort,m_portName.latin1());
}

void QT_FlashDialog::slotProgramm()
{
	m_msg = "";
	PROGRAMM->setEnabled(FALSE);
	EXIT->setText("Cancel");
	Programm();
	EXIT->setText("Exit");
	PROGRAMM->setEnabled(TRUE);
}

void QT_FlashDialog::slotPort(int)
{
	PORT_TEXT->setText(PORT->currentText());
}

void QT_FlashDialog::slotCancel()
{

	if (EXIT->text() == "Cancel") {
		m_ASUROCancel = TRUE;
		EXIT->setText("Exit");
	}
	else
		qApp->quit();
}

void QT_FlashDialog::Status(char* text)
{
	STATUS->setText(text);
}

void QT_FlashDialog::MessageText(char* text)
{
	QFont font = TEXT->font();
	QFontMetrics fm(font);

	m_msg = m_msg + "<br>" + text; 
	QRect rec = fm.boundingRect(m_msg);
	TEXT->setText(m_msg);
	TEXT->ensureVisible(0,rec.width());

}

void QT_FlashDialog::WarningText(char* text)
{
	QFont font = TEXT->font();
	QFontMetrics fm(font);

	m_msg = m_msg + "<b><font color=\"#FF8000\">" + text + "</font></b>";
	QRect rec = fm.boundingRect(m_msg);
	TEXT->setText(m_msg);
	TEXT->ensureVisible(0,rec.width());
}

void QT_FlashDialog::SuccessText (char* text)
{
	QFont font = TEXT->font();
	QFontMetrics fm(font);

	m_msg = m_msg + "<b><font color=\"#00FF00\">" + text + "</font></b>";	
	QRect rec = fm.boundingRect(m_msg);
	TEXT->setText(m_msg);
	TEXT->ensureVisible(0,rec.width());
}

void QT_FlashDialog::ErrorText(char* text)
{
	QFont font = TEXT->font();
	QFontMetrics fm(font);

	m_msg = m_msg + "<b><font color=\"#FF0000\">" + text + "</font></b>";	
	QRect rec = fm.boundingRect(m_msg);
	TEXT->setText(m_msg);
	TEXT->ensureVisible(0,rec.width());
}

void QT_FlashDialog::Progress(unsigned int progress)
{
	PROGRESSBAR->setProgress(progress);
}

void QT_FlashDialog::ViewUpdate(void)
{
	qApp->processEvents();
}


void QT_FlashDialog::TimeWait(unsigned int time) // msec
{
#ifdef WINDOWS
	Sleep(time);
#else
	usleep(time * 1000);
#endif

}

