/***************************************************************************
                 Con_FlashDialog.cpp  -  Interface ASURO Console Flash
                             -------------------
    begin                : Die Aug 12 10:16:57 CEST 2003
    copyright            : (C) 2003 DLR RM by Jan Grewe
    email                : jan.grewe@dlr.de
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
#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <unistd.h>
#endif

#include <iostream>

#include "Con_FlashDialog.h"

Con_FlashDialog::Con_FlashDialog()
{

}

Con_FlashDialog::~Con_FlashDialog()
{

}

void Con_FlashDialog::Progress(unsigned int progress)
{
	std::cout << "." << std::flush;
}

void Con_FlashDialog::TimeWait(unsigned int time) // msec
{
#ifdef WINDOWS
	Sleep(time);
#elif defined LINUX
	usleep(time * 1000);
#endif
}

void Con_FlashDialog::MessageText(char* text)
{
	std::cout << std::endl << text << std::flush;
}

void Con_FlashDialog::WarningText(char* text)
{
	std::cout << text << std::flush;
}

void Con_FlashDialog::SuccessText (char* text)
{
	std::cout << text << std::flush;
}

void Con_FlashDialog::ErrorText(char* text)
{
	std::cout << text << std::flush;
}
