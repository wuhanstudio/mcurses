/*---------------------------------------------------------------------------------------------------------------------------------------------------
   mcurses key test

   Copyright (c) 2011-2015 Frank Meyer - frank(at)fli4l.de

   Revision History:
   V1.0 2015 xx xx Frank Meyer, original version
   V1.1 2017 01 14 ChrisMicro, addapted as Arduino example
   V1,2,2017 01 15 ChrisMicro, now showing escape characters sequentialy

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
  ---------------------------------------------------------------------------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <mcurses.h>
#include <editor.h>
#include <hexedit.h>

#define         myitoa(x,buf)                   itoa ((x), buf, 10)

int mcurses_key_test(int argc, char const *argv[])
{
    rt_kprintf("key test demo\n");
    rt_thread_mdelay(1000);

    setFunction_putchar(rtt_putchar);   // tell the library which output channel shall be used

    initscr();                          // initialize mcurses
    clear ();

    while (1)
    {
        char    buf[10];
        uint8_t idx;
        static uint8_t cnt;
        uint8_t ch;

        move (10, 10);
        addstr_P (("Press a key : "));

        rt_thread_mdelay(50);
        ch = rtt_getchar();

        switch (ch)
        {
            case '\t':          addstr_P ("TAB");               break;
            case '\r':          addstr_P ("CR");                break;
            case KEY_ESCAPE:    addstr_P ("KEY_ESCAPE");        break;
            case KEY_DOWN:      addstr_P ("KEY_DOWN");          break;
            case KEY_UP:        addstr_P ("KEY_UP");            break;
            case KEY_LEFT:      addstr_P ("KEY_LEFT");          break;
            case KEY_RIGHT:     addstr_P ("KEY_RIGHT");         break;
            case KEY_HOME:      addstr_P ("KEY_HOME");          break;
            case KEY_DC:        addstr_P ("KEY_DC");            break;
            case KEY_IC:        addstr_P ("KEY_IC");            break;
            case KEY_NPAGE:     addstr_P ("KEY_NPAGE");         break;
            case KEY_PPAGE:     addstr_P ("KEY_PPAGE");         break;
            case KEY_END:       addstr_P ("KEY_END");           break;
            case KEY_BTAB:      addstr_P ("KEY_BTAB");          break;
            case KEY_F(1):      addstr_P ("KEY_F(1)");          break;
            case KEY_F(2):      addstr_P ("KEY_F(2)");          break;
            case KEY_F(3):      addstr_P ("KEY_F(3)");          break;
            case KEY_F(4):      addstr_P ("KEY_F(4)");          break;
            case KEY_F(5):      addstr_P ("KEY_F(5)");          break;
            case KEY_F(6):      addstr_P ("KEY_F(6)");          break;
            case KEY_F(7):      addstr_P ("KEY_F(7)");          break;
            case KEY_F(8):      addstr_P ("KEY_F(8)");          break;
            case KEY_F(9):      addstr_P ("KEY_F(9)");          break;
            case KEY_F(10):     addstr_P ("KEY_F(10)");         break;
            case KEY_F(11):     addstr_P ("KEY_F(11)");         break;
            case KEY_F(12):     addstr_P ("KEY_F(12)");         break;
            case ERR:           rt_thread_mdelay(100); cnt++;   break;
            default:            addch (ch);                     break;
        }

        addstr_P (("                "));
        clrtoeol ();

        move (12, 10);
        addstr_P ("key value is ");
        addstr (myitoa(ch, buf));
        addstr_P (" ( 0x");
        itoxx(ch);
        addstr_P (" )");
        clrtoeol ();

        if (ch == ERR)
        {
            addstr_P ("ERROR");
            clrtoeol ();
        }
    }

    return 0;
}
MSH_CMD_EXPORT(mcurses_key_test, mcurses key test demo)
