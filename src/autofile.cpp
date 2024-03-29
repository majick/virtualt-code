/* autofile.cpp */

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

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Preferences.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_ask.H>

#include "FLU/Flu_File_Chooser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "m100emu.h"
#include "autofile.h"

extern "C" struct tm* mytime;

/*
================================================================================
VTAutoFile:	This is the class constructor for the AutoFile file generator
================================================================================
*/
VTAutoFile::VTAutoFile(void)
{
	m_ActiveSeqNum = -1;
	m_PageNum = 1;
}

/*
=======================================================
Generates an autoformat filename based on preferences.
=======================================================
*/
MString VTAutoFile::GenFilename()
{
	MString		filename;
	MString		beforeSeq;
	MString		afterSeq;
	int			len, c;
	int			seq = 0;
	int			seqFound = FALSE;
	char		page[11];
	FILE*		fd;
	const char*		formatCode;

	// Build the filename by parsing the format & looking for % modifiers
	len = m_Format.GetLength();
	formatCode = m_Format;
	for (c = 0; c < len; c++)
	{
		if (formatCode[c] == '%')
		{
			if (formatCode[c+1] == 'd')
			{
				// Add date code
				page[0] = (mytime->tm_year % 100) / 10 + '0';
				page[1] = (mytime->tm_year % 10) + '0';
				page[2] = (mytime->tm_mon+1) / 10 + '0';
				page[3] = (mytime->tm_mon+1) % 10 + '0';
				page[4] = (mytime->tm_mday / 10) + '0';
				page[5] = (mytime->tm_mday % 10) + '0';
				page[6] = 0;
	
				// Add date to filename
				if (seqFound)
					afterSeq += page;
				else
					beforeSeq += page;
			}
			else if (formatCode[c+1] == 's')
			{
				seqFound = TRUE;
			}
			else if (formatCode[c+1] == 'p')
			{
				// Add page number
				sprintf(page, "%d", m_PageNum);
				if (seqFound)
					afterSeq += page;
				else
					filename += page;
			}

			// Skip the format code
			c++;
		}
		else
		{
			if (seqFound)
				afterSeq += formatCode[c];
			else
				beforeSeq += formatCode[c];
		}
	}

	// Okay, the format string is parsed.  If it contains a seq number,
	// then find a seq that doesn't exist yet, if not already found.
	if (seqFound)
	{
		// Test if we already have a seq number for this session
		if (m_ActiveSeqNum == -1)
		{
			// Find a seq number that represents a file that doens't exist
			for (seq = 0; ;seq++)
			{
				// Build filename for testing
				sprintf(page, "%d", seq);
				filename = m_DirName;
				filename += beforeSeq + page + afterSeq;

				fd = fopen((const char *) filename, "r");
				if (fd == NULL)
				{
					break;
				}
				// Close the file
				fclose(fd);
			}

			// Okay, now save the sequence number
			m_ActiveSeqNum = seq;
		}

		// Build the filename
		sprintf(page, "%d", m_ActiveSeqNum);
		filename = m_DirName + beforeSeq + page + afterSeq;
	}
	else
	{
		filename = beforeSeq;
	}

	m_Filename = filename;
	return filename;
}

/*
=======================================================
Prompts the user for a filename using the a default 
name or autogenerated name.
=======================================================
*/
int VTAutoFile::PromptFilename()
{
	Flu_File_Chooser*	fc;
	char				text[80];

	while (1)
	{
		if (m_PageNum == 1)
			strcpy(text, (const char *) m_ChooserTitle);
		else
			sprintf(text, "Select File for Page %d", m_PageNum);

		if (m_Filename == "")
			m_Filename = ".";
		// Prompt the user with the filename & give a chance to change
		fl_cursor(FL_CURSOR_WAIT);
		fc = new Flu_File_Chooser((const char *) m_Filename, "*.*", 
			Fl_File_Chooser::CREATE, text);
		fl_cursor(FL_CURSOR_DEFAULT);

		fc->show();
		fc->value((const char *) m_Filename);
		while (fc->visible())
			Fl::wait();

		if (fc->value() == NULL)
			return 1;
			
		// Check if filename was selected
		if (strlen(fc->value()) == 0)
			return 1;

		// Check if file already exists and ask to overwrite or not
	    // Try to open the ouput file
	    FILE* fd = fopen(fc->value(), "rb+");
	    if (fd != NULL)
	    {
	        // File already exists! Check for overwrite!
	        fclose(fd);

			int c = fl_choice("Overwrite existing file?", "Cancel", "Yes", "No");
			if (c == 2)
				continue;
			if (c == 0)
			{
				delete fc;
				return 1;
			}
		}
		break;
	}

	m_Filename = fc->value();
	delete fc;
	
	return 0;
}

