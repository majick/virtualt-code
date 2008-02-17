/* printer.h */

/* $Id$ */

/*
 * Copyright 2008 Ken Pettit
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


#ifndef _PRINTER_H_
#define _PRINTER_H_

#include "vtobj.h"
#include "MString.h"

class Fl_Preferences;

#define	PRINT_ERROR_NONE		0
#define PRINT_ERROR_ABORTED		1
#define	PRINT_ERROR_IO_ERROR	2

/*
==========================================================================
Define the VTPrinter class.  This is a virtual class that other printers
will derive from to add specific functionality.
==========================================================================
*/
class VTPrinter : public VTObject
{
public:
	VTPrinter();

	// Pure virtual functions specific to the printer
	virtual MString		GetName() = 0;					// Get name of the printer
	virtual void		BuildPropertyDialog() = 0;		// Builds property dialog
	virtual int			GetProperties(void) = 0;		// Get printer properties from Dialog & save
	virtual int			GetBusyStatus() = 0;			// Read BUSY from printer
	virtual void		SendAutoFF(void) = 0;			// Send a FormFeed if needed
	virtual void		Deinit(void) = 0;				// Deiniatalizes the printer

	// Common printer setup functions
	virtual void		Init(Fl_Preferences* pPref);	// Initialization routine
	virtual int			Print(unsigned char byte);		// This is the main "Print" routine
	virtual void		EndPrintSession(void);			// Called by LPT device to end printing

protected:
	virtual void		PrintByte(unsigned char byte) = 0;	// Print a byte
	virtual void		Init(void) = 0;					// Virtual init for actual printers
	virtual int			OpenSession(void) = 0;			// Opens a new print session
	virtual int			CloseSession(void) = 0;			// Closes the current print session

	Fl_Preferences*		m_pPref;
	int					m_SessionActive;				// Indicates if a print session active

};

#endif
