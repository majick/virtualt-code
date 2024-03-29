/* genwrap.h */

/* General cross-platform development wrappers */

/* $Id$ */

/****************************************************************************
 * @format.tab-size 4		(Plain Text/Source Code File Header)			*
 * @format.use-tabs true	(see http://www.synchro.net/ptsc_hdr.html)		*
 *																			*
 * Copyright 2003 Rob Swindell - http://www.synchro.net/copyright.html		*
 *																			*
 * This library is free software; you can redistribute it and/or			*
 * modify it under the terms of the GNU Lesser General Public License		*
 * as published by the Free Software Foundation; either version 2			*
 * of the License, or (at your option) any later version.					*
 * See the GNU Lesser General Public License for more details: lgpl.txt or	*
 * http://www.fsf.org/copyleft/lesser.html									*
 *																			*
 * Anonymous FTP access to the most recent released source is available at	*
 * ftp://vert.synchro.net, ftp://cvs.synchro.net and ftp://ftp.synchro.net	*
 *																			*
 * Anonymous CVS access to the development source and modification history	*
 * is available at cvs.synchro.net:/cvsroot/sbbs, example:					*
 * cvs -d :pserver:anonymous@cvs.synchro.net:/cvsroot/sbbs login			*
 *     (just hit return, no password is necessary)							*
 * cvs -d :pserver:anonymous@cvs.synchro.net:/cvsroot/sbbs checkout src		*
 *																			*
 * For Synchronet coding style and modification guidelines, see				*
 * http://www.synchro.net/source.html										*
 *																			*
 * You are encouraged to submit any modifications (preferably in Unix diff	*
 * format) via e-mail to mods@synchro.net									*
 *																			*
 * Note: If this box doesn't appear square, then you need to fix your tabs.	*
 ****************************************************************************/

#ifndef _GENWRAP_H
#define _GENWRAP_H

#include <stdio.h>		/* sprintf */
#include "gen_defs.h"	/* ulong */
#include "wrapdll.h"	/* DLLEXPORT and DLLCALL */

#if defined(__unix__)
	#include <sched.h>		/* sched_yield */
	#include <time.h>	/* clock_t */
	#include <sys/time.h>	/* struct timeval */
	#include <strings.h>	/* strcasecmp() */
	#include <unistd.h>		/* usleep */
	#ifdef _THREAD_SAFE
		#include <pthread.h>/* Check for GNU PTH libs */
		#ifdef _PTH_PTHREAD_H_
			#include <pth.h>
		#endif
	#endif
#elif defined(_WIN32)
	#include <process.h>	/* getpid() */
#endif

/* utime() support */
#if defined(_MSC_VER) || defined(__WATCOMC__)
	#include <sys/utime.h>
#else
	#include <utime.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/*********************/
/* Compiler-specific */
/*********************/

/* Compiler Description */
#if defined(__BORLANDC__)

	#define DESCRIBE_COMPILER(str) sprintf(str,"BCC %X.%02X",__BORLANDC__>>8,__BORLANDC__&0xff);	

#elif defined(_MSC_VER)

	#define DESCRIBE_COMPILER(str) sprintf(str,"MSC %u", _MSC_VER);

#elif defined(__GNUC__)

	#define DESCRIBE_COMPILER(str) sprintf(str,"GCC %u.%02u",__GNUC__,__GNUC_MINOR__);

#elif defined(__WATCOMC__)

	#define DESCRIBE_COMPILER(str) sprintf(str,"WATC %d",__WATCOMC__);

#elif defined(__DMC__)	/* Digital Mars C/C++ */

	#define DESCRIBE_COMPILER(str) sprintf(str,"DMC %X.%02X",__DMC__>>8,__DMC__&0xff);	

#else /* Unknown compiler */

	#define DESCRIBE_COMPILER(str) strcpy(str,"UNKNOWN COMPILER");

#endif

/**********/
/* Macros */
/**********/

/* Target Platform Description */
#if defined(_WIN64)
	#define PLATFORM_DESC	"Win64"
#elif defined(_WIN32)
	#define PLATFORM_DESC	"Win32"
#elif defined(__OS2__)
	#define PLATFORM_DESC	"OS/2"
#elif defined(__MSDOS__)
	#define PLATFORM_DESC	"DOS"
#elif defined(__linux__)
	#define PLATFORM_DESC	"Linux"
#elif defined(__FreeBSD__)
	#define PLATFORM_DESC	"FreeBSD"
#elif defined(__OpenBSD__)
	#define PLATFORM_DESC	"OpenBSD"
#elif defined(__NetBSD__)
	#define PLATFORM_DESC	"NetBSD"
#elif defined(__APPLE__) && defined(__MACH__) && defined(__POWERPC__)
	#define PLATFORM_DESC	"MacOSX"
#elif defined(__APPLE__)
	#define PLATFORM_DESC	"MacOSX"
#elif defined(BSD)
	#define PLATFORM_DESC	"BSD"
#elif defined(__solaris__)
	#define PLATFORM_DESC	"Solaris"
#elif defined(__sun__)
	#define PLATFORM_DESC	"SunOS"
#elif defined(__gnu__)
	#define PLATFORM_DESC	"GNU/Hurd"
#elif defined(__QNX__)
	#define PLATFORM_DESC	"QNX"
#elif defined(__unix__)
	#define PLATFORM_DESC	"Unix"
#else
	#error "Need to describe target platform"
#endif

/*********************/
/* String Functionss */
/*********************/

#ifndef __APPLE__
#define snprintf	safe_snprintf
#endif

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__DMC__)
	#define vsnprintf		_vsnprintf
#endif

#if defined(__WATCOMC__)
	#define vsnprintf(s,l,f,a)	vsprintf(s,f,a)
#endif

#if !defined(_MSC_VER) && !defined(__BORLANDC__) && !defined(__WATCOMC__)
	DLLEXPORT char* DLLCALL ultoa(ulong, char*, int radix);
#endif

#if defined(__unix__)
	DLLEXPORT char*	DLLCALL strupr(char* str);
	DLLEXPORT char*	DLLCALL strlwr(char* str);
	DLLEXPORT char* DLLCALL	strrev(char* str);
	#if !defined(stricmp)
		#define stricmp(x,y)		strcasecmp(x,y)
		#define strnicmp(x,y,z)		strncasecmp(x,y,z)
	#endif
#endif

#if defined(__unix__)
	#define STRERROR(x)		strerror(x)
#else
	#define STRERROR(x)		truncsp(strerror(x))
#endif

/**********************************/
/* Common Utility Macro Functions */
/**********************************/

#if defined(_WIN32)

	#define YIELD()			Sleep(1) /* Must sleep at least 1ms to avoid 100% CPU utilization */
	#define	MAYBE_YIELD()	Sleep(0)
	#define SLEEP(x)		Sleep(x)
	#define BEEP(freq,dur)	Beep((DWORD)(freq),(DWORD)(dur))
	#define	popen			_popen
	#define pclose			_pclose
//	#define tzname			_tzname

#elif defined(__OS2__)

	#define YIELD()			DosSleep(1)	/* Must sleep at least 1ms to avoid 100% CPU utilization */
	#define	MAYBE_YIELD()	DosSleep(0)
	#define SLEEP(x)		DosSleep(x)
	#define BEEP(freq,dur)	DosBeep(freq,dur)

#elif defined(__unix__) || defined(__APPLE__)

	#if defined(_PTH_PTHREAD_H_)
		#define SLEEP(x)		({ int y=x; struct timeval tv; tv.tv_sec=(y/1000); tv.tv_usec=((y%1000)*1000); pth_nap(tv); })
	#else
		#define SLEEP(x)		({	int y=x; struct timeval tv;	tv.tv_sec=(y/1000); tv.tv_usec=((y%1000)*1000);	select(0,NULL,NULL,NULL,&tv); })
	#endif

	#define YIELD()			SLEEP(1)

	#if defined(_THREAD_SAFE)
		#if defined(__FreeBSD__)
			#define MAYBE_YIELD()			pthread_yield()
		#elif defined(_PTH_PTHREAD_H_)
			#define MAYBE_YIELD()			pth_yield(NULL)
		#elif defined(_POSIX_PRIORITY_SCHEDULING)
			#define MAYBE_YIELD()			sched_yield()
		#else
			#define MAYBE_YIELD()			YIELD()
		#endif
	#else
		#if defined(_POSIX_PRIORITY_SCHEDULING)
			#define	MAYBE_YIELD()			sched_yield()
		#else
			#define MAYBE_YIELD()			YIELD()
		#endif
	#endif

	/*
	 * QNX doesn't support fork() in threaded apps (yet) using vfork() instead
	 * works, but relies on undefined behaviours not being nasty.  On most OSs
	 * vfork() will share the stack between the parent and child...
	 */
	#if defined(__QNX__)
		#define FORK()	vfork()
	#else
		#define FORK()	fork()
	#endif

	#define BEEP(freq,dur)	unix_beep(freq,dur)
	DLLEXPORT void	DLLCALL	unix_beep(int freq, int dur);

#else	/* Unsupported OS */

	#error "Unsupported Target: Need some macros and/or function prototypes here."

#endif

/* Win32 implementations of recursive (thread-safe) std C time functions on Unix */

#if !defined(__unix__)	

	#include <time.h>		/* time_t, etc. */

	DLLEXPORT struct tm*    DLLCALL		gmtime_r(const time_t* t, struct tm* tm);
	DLLEXPORT struct tm*    DLLCALL		localtime_r(const time_t* t, struct tm* tm);
	DLLEXPORT char*	        DLLCALL		ctime_r(const time_t *t, char *buf);
	DLLEXPORT char*	        DLLCALL		asctime_r(const struct tm *tm, char *buf);
#endif

#if defined(__solaris__)
	#define CTIME_R(x,y)	ctime_r(x,y)
	/* #define CTIME_R(x,y)	ctime_r(x,y,sizeof y) */
#else
	#define CTIME_R(x,y)	ctime_r(x,y)
#endif

DLLEXPORT int		DLLCALL	xp_random(int);
DLLEXPORT char*		DLLCALL os_version(char *str);
DLLEXPORT char*		DLLCALL	lastchar(const char* str);
DLLEXPORT int		DLLCALL safe_snprintf(char *dst, size_t size, const char *fmt, ...);

/* C string/char escape-sequence processing */
DLLEXPORT char*		DLLCALL unescape_cstr(char* str);
DLLEXPORT char		DLLCALL unescape_char_ptr(const char* str, char** endptr);
DLLEXPORT char		DLLCALL unescape_char(char ch);

#if !defined(__unix__)
	#define		msclock()			clock()
	#define		MSCLOCKS_PER_SEC	CLOCKS_PER_SEC
#else
	#define		MSCLOCKS_PER_SEC	1000
	clock_t		msclock(void);
#endif

#if defined(__cplusplus)
}
#endif

#endif	/* Don't add anything after this line */
