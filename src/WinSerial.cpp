/***************************************************************************
             WinSerial.cpp - Serial Communictaion in Posix standard
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
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "WinSerial.h"

#ifndef WINDOWS
#error Wrong OS only Windows implemented
#endif

CWinSerial::CWinSerial()
{

}

CWinSerial::~CWinSerial()
{

}

bool CWinSerial::Open(char* port)
{
	// TODO: adapot function to Windows
#if 0
	char text[256];

	strcpy(m_portName,port);
	m_portHandle = open ((const char*)m_portName, O_RDWR | O_NOCTTY);
	if (m_portHandle == -1) {
		sprintf(text,"Could not open %s\nAlready in use ?!?!\n",m_portName);
		MyMessageBox(text);
		return false;
	}
	// configure port settings
	tcgetattr(m_portHandle, &CommConfig);

	// 2400 Baud / Data Size 8-Bit / 1 Stop Bit / No Parity / No Flow Control / Zero TimeOut
	CommConfig.c_cflag = CREAD|CLOCAL|B2400|CS8;
	CommConfig.c_lflag = 0;
	CommConfig.c_oflag = 0;
	CommConfig.c_iflag = 0;
	CommConfig.c_cc[VMIN] = 0;
	CommConfig.c_cc[VTIME]= 0;


	// Set DTR & RTS
	ioctl(m_portHandle, TIOCMSET, TIOCM_DTR | TIOCM_RTS);

	if (tcsetattr(m_portHandle, TCSAFLUSH, &CommConfig)) {
		sprintf(text,"Can't write port settings on %s\n",m_portName);
		MyMessageBox(text);
		return false;
	} 	
	return true;
#else
	return false;
#endif
}

void CWinSerial::Close(void)
{
	// TODO: adapot function to Windows
#if 0
	close(m_portHandle);
#endif
}

bool CWinSerial::Scan(char* port,unsigned short number,unsigned short mode)
{
	int ret = false;
	if (mode == SERIAL) sprintf(m_portName,"COM%d",number);
	if (mode == USB) sprintf(m_portName,"COM%d",number);
	// TODO: adapot function to Windows
#if 0
	m_portHandle = open ((const char*)m_portName, O_RDWR | O_NOCTTY);
	if (m_portHandle != -1) {
		if(!(tcgetattr(m_portHandle, &CommConfig))) {
			strcpy(port,m_portName);
			ret = true;
		}
	}
	Close();
	return ret;
#else
	ret = true;
	return ret;
#endif
}

void CWinSerial::ClearBuffer(void)
{
	//  tcflush(m_portHandle,TCIFLUSH);
	//  tcflush(m_portHandle,TCOFLUSH);
	//  tcflush(m_portHandle,TCIOFLUSH);

}

int CWinSerial::Read(char* data, unsigned int length)
{
	// TODO: adapot function to Windows
#if 0
	int ret;
	char text[256];
	ret = read(m_portHandle,data,length);
	if (ret == -1) {
		sprintf(text,"Can't read from %s",m_portName);
		MyMessageBox(text); 
	} 
	return ret;	
#else
	char text[256];
	sprintf(text,"Can't read from %s",m_portName);
	MyMessageBox(text); 
	return -1;	
#endif
}

int CWinSerial::Write(char* data, unsigned int length)
{
	// TODO: adapot function to Windows
#if 0
	int ret;
	char text[256];
	ret = write(m_portHandle,data,length);
	if (ret == -1) {
		sprintf(text,"Can't write to %s",m_portName);
		MyMessageBox(text);
	}
	return ret; 
#else
	char text[256];
	sprintf(text,"Can't write to %s",m_portName);
	MyMessageBox(text); 
	return -1;	
#endif
}

void CWinSerial::Timeout(unsigned int timeout) //msec
{
	// TODO: adapot function to Windows
#if 0
	CommConfig.c_cc[VTIME]=timeout/100;
	tcsetattr(m_portHandle, TCSAFLUSH, &CommConfig);
#endif
}

void CWinSerial::MyMessageBox(char* Text)
{
#if defined _CONSOLE
	std::cout << Text << std::endl;
#else
#error Must be CONSOLE Applikation
#endif
}

