/***************************************************************************
                               Serial.h
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
	1.0   12.08.2003    Jan Grewe     build
 ***************************************************************************/ 
#ifndef _SERIAL_H_
#define _SERIAL_H_

class CSerial  
{
public:
	CSerial();
	virtual ~CSerial();
	virtual bool Open(unsigned int port) = 0;
	virtual void Close(void) = 0;
	virtual void ClearBuffer(void) = 0;
	virtual int Read(char* data, unsigned int length) = 0;
	virtual int Write(char* data, unsigned int length) = 0;
	virtual void Timeout(unsigned int timeout) = 0; //msec 
	unsigned char m_Port;
};

#endif
