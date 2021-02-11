/*-----------------------------------------------------------------------------------------------------------------

   How to use the hexadecimal editor of MCURSES
   
   What:
    With this example you can edit the RAM-Memory contents of the ARDUINO.
   
   Why:
    This may be useful for debugging purposes

   Hint: 
    to exit the editor, press two times ESC

   Revision History:
   V1.0 2017 01 18 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

---------------------------------------------------------------------------------------------------------------*/

#include <rtthread.h>
#include <editor.h>
#include <hexedit.h>

int mcurses_hex_editor(int argc, char const *argv[])
{
    setFunction_putchar(rtt_putchar); // tell the library which output channel shall be used
    setFunction_getchar(rtt_getchar); // tell the library which input channel shall be used

    initscr();                            // initialize mcurses
    clear();

    while(1)
    {
        static uint16_t    memmoryStartAddress = 0x100;    // ATMEGA RAM start

        hexedit (memmoryStartAddress);

        clear();
        char str[]="hexadecimal editor stopped";
        rt_kprintf(str + '\n');

        rt_thread_mdelay(3000);
    }

    return 0;
}
MSH_CMD_EXPORT(mcurses_hex_editor, mcurses hex editor demo)
