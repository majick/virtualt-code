/* lpt.h */

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


#ifndef _LPT_H_
#define _LPT_H_

#ifdef __cplusplus
#include "vtobj.h"
extern "C" {
#endif

void init_lpt(void);
void deinit_lpt(void);
void send_to_lpt(unsigned char byte);
void handle_lpt_timeout(unsigned long time);

#ifdef __cplusplus
}
#endif

#define LPT_MODE_NONE	0
#define	LPT_MODE_EMUL	1

void build_lpt_setup_tab(void);

#define LPT_STATUS_IDLE			0
#define LPT_STATUS_READY		1
#define	LPT_STATUS_ABORTED		2

#ifdef __cplusplus

void load_lpt_preferences(Fl_Preferences* pPref);
void save_lpt_preferences(Fl_Preferences* pPref);
void get_lpt_options(void);
void cb_printer_properties(Fl_Widget* w, void*);

class VTPrinter;

typedef struct
{
	int		lpt_mode;			// Printer emulation mode
	char	lpt_emul_name[64];	// Name of emulated printer
	int		lpt_cr2lf;			// Convert CR to LF?
	int		lpt_auto_ff;		// Send auto FF after timeout?
	int		lpt_aff_timeout;	// Timeout in seconds
	int		lpt_auto_close;		// Auto close session after tiemout?
	int		lpt_close_timeout;	// Timeout in seconds
} lpt_prefs_t;

/*
=======================================================
Define the VTLpt class.  This class is where all
the action happens.
=======================================================
*/
class VTLpt
{
public:
	VTLpt();

	void			SendToLpt(unsigned char byte);		// Deals with bytes printed
	void			DeinitLpt(void);
	void			HandleTimeouts(unsigned long time);	// Handles all timeouts
	void			PrinterProperties(int useActivePrinter);			// Creates preferences dialog
	void 			UpdatePreferences(Fl_Preferences* pPref);
	void			PrinterPropOk(VTPrinter* pPrint);
	void			PrinterPropCancel(void);
	void			EndPrintSession(void);
	void			CancelPrintSession(void);
	void			ResetPrinter(void);					// Reset printer
	void			CancelPrintJob(void);				// Cancel the current print job

	int				GetPrinterCount(void);				// Returns # printers registered
	VTPrinter*		GetPrinter(int index);				// Returns pointer to a specific printer

protected:
	int					m_EmulationMode;				// Current emulation mode
	int					m_ConvertCRtoLF;

	Fl_Window*			m_pProp;						// Printer Properties window
	Fl_Button*			m_pCancel;
	Fl_Return_Button*	m_pOk;
	Fl_Preferences*		m_pPref;

	VTObArray			m_Printers;						// Array of registered printers
	VTPrinter*			m_pActivePrinter;				// Pointer to emulated printer

	int					m_PortStatus;
	time_t				m_PortActivity;
	time_t				m_PortTimeout;
	int					m_AFFSent;						// True if an Auto FormFeed sent
	unsigned char		m_PrevChar;						// Previous byte sent

	char				m_TimeStr[10];

};

#endif

 
#endif
