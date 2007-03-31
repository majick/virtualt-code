/* m100emu.h */

/* $Id$ */

/*
 * Copyright 2004 Stephen Hurd and Ken Pettit
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


#ifndef _M100EMU_H_
#define _M100EMU_H_

#include "gen_defs.h"
#include "roms.h"


#ifdef __cplusplus
extern "C" {
#endif

extern char  op[26];
extern int trace;
extern int fullspeed;
extern int gExitApp;
extern int gExitLoop;
extern float cpu_speed;
extern uchar *gMemory[64];
extern RomDescription_t	 *gStdRomDesc;
extern int   gModel;
extern char gsOptRomFile[256];
__inline double hirestimer(void);
typedef void (*mem_monitor_cb)(void);
typedef void (*debug_monitor_callback)();
void	mem_set_monitor_callback(mem_monitor_cb cb);
int		debug_set_monitor_callback(debug_monitor_callback pCallback);
void	debug_clear_monitor_callback(debug_monitor_callback pCallback);
extern	char	gDebugActive;
extern	char	gStopped;
extern	char	gSingleStep;
extern	int		gDebugMonitorFreq;

	
int		check_model_support(int model);
void	get_emulation_path(char* emu, int model);
void	get_model_string(char* str, int model);
void	get_rom_path(char* file, int model);
void	init_cpu(void);
//void	cpu_delay(int cy);
void	resetcpu(void);
void	cb_int65(void);

#ifdef __cplusplus
}
#endif


#endif
