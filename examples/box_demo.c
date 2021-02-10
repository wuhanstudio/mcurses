/*---------------------------------------------------------------------------------------------------------------------------------------------------
   mcurses box demo

   Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de

   Revision History:
   V1.0 2015 xx xx Frank Meyer, original version
   V1.1 2017 01 14 ChrisMicro, converted to Arduino example

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  ---------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <rtthread.h>
#include <stdlib.h>
#include "mcurses.h"

#define         myitoa(x,buf)                   itoa ((x), buf, 10)

void drawbox (uint8_t y, uint8_t x, uint8_t h, uint8_t w)
{
  uint8_t line;
  uint8_t col;

  move (y, x);
  addch (ACS_ULCORNER);
  for (col = 0; col < w - 2; col++)
  {
    addch (ACS_HLINE);
  }
  addch (ACS_URCORNER);

  for (line = 0; line < h - 2; line++)
  {
    move (line + y + 1, x);
    addch (ACS_VLINE);
    move (line + y + 1, x + w - 1);
    addch (ACS_VLINE);
  }

  move (y + h - 1, x);
  addch (ACS_LLCORNER);
  for (col = 0; col < w - 2; col++)
  {
    addch (ACS_HLINE);
  }
  addch (ACS_LRCORNER);
}


int mcurses_box_demo(int argc, char const *argv[])
{
  setFunction_putchar(rtt_putchar); // tell the library which output channel shall be used

  initscr();                  // initialize mcurses

  char    buf[10];
  uint8_t idx;
  clear ();
  drawbox (6, 20, 10, 20);

  for (idx = 1; idx <= 6; idx++)
  {
    mvaddstr_P (idx + 7, 23, "This is line ");
    addstr (myitoa(idx, buf));
    rt_thread_mdelay(400);
  }
  rt_thread_mdelay(1000);
  move(0, 0);
  clear ();

  return 0;
}
MSH_CMD_EXPORT(mcurses_box_demo, screen demo)
