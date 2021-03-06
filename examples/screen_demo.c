/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses screen demo
 *
 * Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de
 *
 * Revision History:
 * V1.0 2015 xx xx Frank Meyer, original version
 * V1.1 2017 01 14 ChrisMicro, converted to Arduino example
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#include <rtthread.h>
#include <stdlib.h>
#include "mcurses.h"

#define         myitoa(x,buf)                   itoa ((x), buf, 10)

static uint8_t  fast;

void message_P (const char * msg)
{
    move (LINES - 2, 0);
    addstr_P (msg);
    clrtoeol ();
}

void shift_left (uint8_t y, uint8_t x, uint8_t ch)
{
    uint8_t col;

    move (y, COLS - 2);
    addch (ch);
    move (y, x);

    for (col = COLS - 2; col > x; col--)
    {
        rt_thread_mdelay(5);
        delch ();
    }
}

void shift_left_str (uint8_t y, uint8_t x, char * str)
{
    char *  s;
    uint8_t xx = x;

    attrset (F_RED);

    for (s = str; *s; s++)
    {
        if (*s != ' ')
        {
        shift_left (y, xx, *s);
        }
        xx++;
    }

    move (y, x);
    attrset (A_REVERSE);

    for (s = str; *s; s++)
    {
        addch (*s);
        rt_thread_mdelay(25);
    }

    move (y, x);
    attrset (F_BLUE);

    for (s = str; *s; s++)
    {
        addch (*s);
        rt_thread_mdelay(25);
    }
}

void screen_demo ()
{
    char    buf[10];
    uint8_t line;
    uint8_t col;

    clear ();

    show_top_line_P ("TOP LINE 2");
    show_bottom_line_P ("BOTTOM LINE 22");
    setscrreg (2, LINES - 4);

    if (fast)
    {
        mvaddstr_P (10, 20, "MCURSES LIB DEMO IN FAST MOTION");
    }
    else
    {
        shift_left_str (10, 20, "MCURSES LIB DEMO IN SLOW MOTION");
    }

    for (line = 0; line < 5; line++)
    {
        scroll ();
        rt_thread_mdelay(200);
    }

    move (5, 15);
    for (line = 0; line < 5; line++)
    {
        insertln ();
        rt_thread_mdelay(200);
    }

    move (10, 18);
    for (col = 0; col < 5; col ++)
    {
        insch (' ');
        rt_thread_mdelay(200);
    }

    move (10, 18);
    for (col = 0; col < 5; col ++)
    {
        delch ();
        rt_thread_mdelay(200);
    }

    clear ();

    show_top_line_P ("TOP LINE 2");
    show_bottom_line_P ("BOTTOM LINE 22");

    message_P ("line positioning test");

    for (line = 2; line <= LINES - 4; line++)
    {
        move (line, 0);
        addstr (myitoa (line + 1, buf));
    }

    rt_thread_mdelay(700);

    message_P ("BOLD attribute test");
    attrset (A_BOLD);
    mvaddstr_P (10, 10, "BOLD");
    attrset (A_NORMAL);
    rt_thread_mdelay(700);

    message_P ("REVERSE attribute test");
    attrset (A_REVERSE);
    mvaddstr_P (11, 10, "REVERSE");
    attrset (A_NORMAL);
    rt_thread_mdelay(700);

    message_P ("insert character test");
    for (col = 10; col <= 22; col += 2)
    {
        mvinsch (11, col, ' ');
    }
    move (11, col + 1);
    rt_thread_mdelay(700);

    message_P ("UNDERLINE attribute test");
    attrset (A_UNDERLINE);
    mvaddstr_P (12, 10, "UNDERLINE");
    attrset (A_NORMAL);
    rt_thread_mdelay(1000);

    message_P ("insert line test");
    move (11, 10);
    insertln ();
    rt_thread_mdelay(1000);

    addstr_P ("Inserted line, will be deleted soon...");
    rt_thread_mdelay(1000);

    message_P ("delete character test");
    for (col = 10; col <= 16; col += 1)
    {
        mvdelch (12, col);
    }
    move (12, 18);
    rt_thread_mdelay(1000);

    message_P ("delete line test");
    move (11, 10);
    deleteln ();
    rt_thread_mdelay(1000);

    message_P ("scroll up line test");
    for (line = 0; line < LINES - 4; line++)
    {
        scroll ();
        rt_thread_mdelay(50);
    }

    move ( 8, 20); attrset (A_BOLD | F_BLACK   | B_WHITE); addstr ("BLACK");
    move ( 9, 20); attrset (A_BOLD | F_RED     | B_WHITE); addstr ("RED");
    move (10, 20); attrset (A_BOLD | F_GREEN   | B_WHITE); addstr ("GREEN");
    move (11, 20); attrset (A_BOLD | F_YELLOW  | B_WHITE); addstr ("YELLOW");
    move (12, 20); attrset (A_BOLD | F_BLUE    | B_WHITE); addstr ("BLUE");
    move (13, 20); attrset (A_BOLD | F_MAGENTA | B_WHITE); addstr ("MAGENTA");
    move (14, 20); attrset (A_BOLD | F_CYAN    | B_WHITE); addstr ("CYAN");
    move (15, 20); attrset (A_BOLD | F_WHITE   | B_BLACK); addstr ("WHITE");
    move (16, 20); attrset (A_NORMAL); addstr ("normal");

    move ( 8, 50); attrset (A_BOLD | B_BLACK   | F_WHITE); addstr ("BLACK");
    move ( 9, 50); attrset (A_BOLD | B_RED     | F_WHITE); addstr ("RED");
    move (10, 50); attrset (A_BOLD | B_GREEN   | F_WHITE); addstr ("GREEN");
    move (11, 50); attrset (A_BOLD | B_YELLOW  | F_BLACK); addstr ("YELLOW");
    move (12, 50); attrset (A_BOLD | B_BLUE    | F_WHITE); addstr ("BLUE");
    move (13, 50); attrset (A_BOLD | B_MAGENTA | F_WHITE); addstr ("MAGENTA");
    move (14, 50); attrset (A_BOLD | B_CYAN    | F_WHITE); addstr ("CYAN");
    move (15, 50); attrset (A_BOLD | B_WHITE   | F_BLACK); addstr ("WHITE");
    move (16, 50); attrset (A_NORMAL); addstr ("normal");
    rt_thread_mdelay(2000);
}

int mcurses_screen_demo(int argc, char const *argv[])
{
    setFunction_putchar(rtt_putchar);   // tell the library which output channel shall be used

    initscr();                          // initialize mcurses
    char    buf[10];
    uint8_t idx;

    screen_demo ();
    clear ();
    mvaddstr_P (10, 10, "Now the same in full speed... ");

    for (idx = 3; idx > 0; idx--)
    {
        move (10, 40);
        myitoa(idx, buf);
        addstr (buf);
        rt_thread_mdelay(1000);
    }

    fast = 1;
    screen_demo ();
    clear ();
    fast = 0;

    rt_thread_mdelay(3000);

    move(0, 0);
    clear ();

    return 0;
}
MSH_CMD_EXPORT(mcurses_screen_demo, mcurses screen demo)
