/* multiwin_icons.cpp */

/* $Id$ */

/*
 * Copyright 2006 Ken Pettit
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
#include <FL/Fl_Pixmap.H>

/* XPM */
const char * gMultiWinDoc_xpm[] = {
"15 18 5 1",
" 	c None",
".	c #848484",
"+	c #FFFFFF",
"@	c #C6C6C6",
"#	c #000000",
"               ",
" ..........    ",
" .++++++++@.   ",
" .+@......@+.  ",
" .++++++++...# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .@@@@@@@@@@@# ",
"  ############ ",
"               "};

/* XPM */
const char * gCloseBox[] = {
"20 19 4 1",
" 	c None",
".	c #FF0000",
"+	c #FFFFFF",
"#	c #000000",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +................+ ",
" +...++......++...+ ",
" +...+++....+++...+ ",
" +....+++..+++....+ ",
" +.....++++++.....+ ",
" +......++++......+ ",
" +.....++++++.....+ ",
" +....+++..+++....+ ",
" +...+++....+++...+ ",
" +...++......++...+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gCloseBoxSelected[] = {
"20 19 5 1",
" 	c None",
".	c #A00000",
"+	c #FFFFFF",
"@  c #C0C0C0",
"#	c #000000",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +................+ ",
" +...@@......@@...+ ",
" +...@@@....@@@...+ ",
" +....@@@..@@@....+ ",
" +.....@@@@@@.....+ ",
" +......@@@@......+ ",
" +.....@@@@@@.....+ ",
" +....@@@..@@@....+ ",
" +...@@@....@@@...+ ",
" +...@@......@@...+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gCloseBoxInactive[] = {
"20 19 4 1",
" 	c None",
".	c #FF8080",
"+	c #FFFFFF",
"#	c #000000",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +................+ ",
" +...++......++...+ ",
" +...+++....+++...+ ",
" +....+++..+++....+ ",
" +.....++++++.....+ ",
" +......++++......+ ",
" +.....++++++.....+ ",
" +....+++..+++....+ ",
" +...+++....+++...+ ",
" +...++......++...+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gMinimizeBox[] = {
"20 19 4 1",
" 	c None",
".	c #0000FF",
"+	c #FFFFFF",
"#	c #FFFFFF",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +...#######......+ ",
" +...#######......+ ",
" +...#######......+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};
const char * gMinimizeBoxSelected[] = {
"20 19 4 1",
" 	c None",
".	c #0000A0",
"+	c #FFFFFF",
"#	c #C0C0C0",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +...#######......+ ",
" +...#######......+ ",
" +...#######......+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gMinimizeBoxInactive[] = {
"20 19 4 1",
" 	c None",
".	c #8080FF",
"+	c #FFFFFF",
"#	c #D0D0D0",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +................+ ",
" +...#######......+ ",
" +...#######......+ ",
" +...#######......+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gMaximizeBox[] = {
"20 19 4 1",
" 	c None",
".	c #0000FF",
"+	c #FFFFFF",
"#	c #FFFFFF",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...##########...+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gMaximizeBoxSelected[] = {
"20 19 4 1",
" 	c None",
".	c #0000A0",
"+	c #FFFFFF",
"#	c #C0C0C0",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...##########...+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gMaximizeBoxInactive[] = {
"20 19 4 1",
" 	c None",
".	c #8080FF",
"+	c #FFFFFF",
"#	c #D0D0D0",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...##########...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...#........#...+ ",
" +...##########...+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gRestoreBox[] = {
"20 19 4 1",
" 	c None",
".	c #0000FF",
"+	c #FFFFFF",
"#	c #FFFFFF",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +....#########...+ ",
" +....#########...+ ",
" +....#.......#...+ ",
" +..#########.#...+ ",
" +..#########.#...+ ",
" +..#.......#.#...+ ",
" +..#.......###...+ ",
" +..#.......#.....+ ",
" +..#.......#.....+ ",
" +..#########.....+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gRestoreBoxSelected[] = {
"20 19 4 1",
" 	c None",
".	c #0000A0",
"+	c #FFFFFF",
"#	c #C0C0C0",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +....#########...+ ",
" +....#########...+ ",
" +....#.......#...+ ",
" +..#########.#...+ ",
" +..#########.#...+ ",
" +..#.......#.#...+ ",
" +..#.......###...+ ",
" +..#.......#.....+ ",
" +..#.......#.....+ ",
" +..#########.....+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};

const char * gRestoreBoxInactive[] = {
"20 19 4 1",
" 	c None",
".	c #8080FF",
"+	c #FFFFFF",
"#	c #D0D0D0",
"                    ",
"  ++++++++++++++++  ",
" +................+ ",
" +................+ ",
" +....#########...+ ",
" +....#########...+ ",
" +....#.......#...+ ",
" +..#########.#...+ ",
" +..#########.#...+ ",
" +..#.......#.#...+ ",
" +..#.......###...+ ",
" +..#.......#.....+ ",
" +..#.......#.....+ ",
" +..#########.....+ ",
" +................+ ",
" +................+ ",
" +................+ ",
"  ++++++++++++++++  ",
"                    "};



Fl_Pixmap gMultiWinDocIcon(gMultiWinDoc_xpm);
Fl_Pixmap gCloseIcon(gCloseBox);
Fl_Pixmap gCloseIconSelected(gCloseBoxSelected);
Fl_Pixmap gCloseIconInactive(gCloseBoxInactive);
Fl_Pixmap gMinimizeIcon(gMinimizeBox);
Fl_Pixmap gMinimizeIconSelected(gMinimizeBoxSelected);
Fl_Pixmap gMinimizeIconInactive(gMinimizeBoxInactive);
Fl_Pixmap gMaximizeIcon(gMaximizeBox);
Fl_Pixmap gMaximizeIconSelected(gMaximizeBoxSelected);
Fl_Pixmap gMaximizeIconInactive(gMaximizeBoxInactive);
Fl_Pixmap gRestoreIcon(gRestoreBox);
Fl_Pixmap gRestoreIconSelected(gRestoreBoxSelected);
Fl_Pixmap gRestoreIconInactive(gRestoreBoxInactive);

