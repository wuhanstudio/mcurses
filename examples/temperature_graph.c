/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * mcurses temperature demo
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

void temperature ()
{
    uint8_t idx;
    uint8_t t;
    uint8_t x;
    uint8_t counter;
    char    buf[10];
    unsigned char temp[15] = { 0, 8, 15, 21, 26, 30, 32, 35, 32, 30, 26, 21, 15, 8, 0 };

    curs_set (0);                                                       // set cursor invisible
    clear ();
    show_top_line_P ("Temperatures in a disk storage");
    show_bottom_line_P ("");


    for (counter = 0; counter < 30; counter++)
    {
        for (idx = 0; idx < 15; idx++)
        {

            if (temp[idx] > 30)
            {
                attrset (B_RED);
            }
            else if (temp[idx] > 20)
            {
                attrset (B_BROWN);
            }
            else
            {
                attrset (B_GREEN);
            }

            mvaddstr (idx + 4, 5, "Disk ");
            myitoa (idx + 1, buf);

            if (idx + 1 < 10)
            {
                addch (' ');
            }

            addstr (buf);
            addstr (": ");
            myitoa (temp[idx] + 20, buf);
            addstr (buf);
            addch ('C');
            attrset (A_NORMAL);
           attrset (B_BLACK);

            move (idx + 4, 20);

            addch ('|');

            for (t = 0; t < temp[idx]; t++)
            {
                addch ('#');
            }

            clrtoeol ();

            x = rand() & 0x1F;

            if (x == 0x01)
            {
                if (temp[idx] < 55)
                {
                    temp[idx]++;
                }
            }
            else if (x == 0x02)
            {
                if (temp[idx] > 0)
                {
                    temp[idx]--;
                }
            }
        }
        rt_thread_mdelay (100);
    }

    curs_set (1);                                                       // set cursor visible (normal)
}

int mcurses_temperature_demo(int argc, char const *argv[])
{
  setFunction_putchar(rtt_putchar); // tell the library which output channel shall be used

  initscr();                  // initialize mcurses

  clear ();
  temperature();
  rt_thread_mdelay (3000);

  move(0, 0);
  clear ();

  return 0;
}
MSH_CMD_EXPORT(mcurses_temperature_demo, screen demo)
