/***************************************************************************
                               WinSerial.h
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
 *                                                                         *
 ***************************************************************************/

/***************************************************************************
	Ver      date       Author        comment
	--------------------------------------------------------------------------
	0.0   04.02.2011    Stephan Linz  create (copied from PosixSerial)
 ***************************************************************************/ 
#ifndef WINSERIAL_H
#define WINSERIAL_H

#include <stdio.h>
#include <errno.h>

// TODO: adapot function to Windows
#if 0
#include <termios.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#endif

#if defined WIN32 || defined _WIN32 || defined _WIN32_
#define WINDOWS
#endif

#include "Serial.h"

class CWinSerial : public CSerial
{
public:
	CWinSerial();
	virtual ~CWinSerial();
	bool Open(unsigned int port);
	void Close(void);
	void ClearBuffer(void);
	int Read(char* data, unsigned int length);
	int Write(char* data, unsigned int length);
	void Timeout(unsigned int timeout); //msec

protected :
  int m_portHandle;
// TODO: adapot function to Windows
#if 0
  struct termios CommConfig;
#endif
	
private :
	void MyMessageBox(char* Text);
	char m_portName[256];

};
#endif

