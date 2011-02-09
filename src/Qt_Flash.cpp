/***************************************************************************
                                Qt_Flash.cpp
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
 ***************************************************************************/ 
#include <qapplication.h>

#include "Qt_FlashDialog.h"


int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	QPixmap icon( ( const char** ) icon_data );

	QT_FlashDialog dialog( 0, 0, TRUE );
	app.setMainWidget(&dialog);

	dialog.setIcon(icon);
	dialog.exec();

	return 0;
}

