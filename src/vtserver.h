/* vtserver.h */

/* $Id: vtserver.h,v 1.3 2015/02/24 20:19:17 kpettit1 Exp $ */

/*
* Copyright 2016 Ken Pettit
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/

#ifndef VTSERVER_H
#define VTSERVER_H

/*
============================================================================
Define call routines to hook to serial port functionality.
============================================================================
*/
// If compiled in cpp file, make declarations extern "C"
#ifdef __cplusplus

#include <FL/filename.H>
#include "MString.h"
#include "MStringArray.h"

class VTTpddServerLog;

extern "C"
{
#endif /* __cplusplus */

// Close the extern "C" block if compiling a cpp file
#ifdef __cplusplus
}

// Logging defines
#define		SERVER_LOG_RX					0
#define		SERVER_LOG_TX					1

/*
=====================================================================
Define the TPDD Server class.  This will be passed around in C land
as a void* context.
=====================================================================
*/
class VTServer 
{
public: 
	VTServer()  { m_pServerLog = NULL; m_logEnabled = TRUE; }
	~VTServer() {}

	// Methods
	virtual void		RegisterServerLog(VTTpddServerLog* pServerLog) { m_pServerLog = pServerLog;
																	 m_logEnabled = TRUE; }
	virtual void		UnregisterServerLog(VTTpddServerLog* pServerLog) { m_logEnabled = FALSE;
																	   m_pServerLog = NULL; }
	virtual int			IsCmdlineState(void) = 0;

protected:
	virtual void		LogData(char data, int rxTx) = 0;

	VTTpddServerLog*	m_pServerLog;		// Server log object for logging data
	int					m_logEnabled;
};

#endif  /* __cplusplus */

#endif	/* VTSERVER_H */

