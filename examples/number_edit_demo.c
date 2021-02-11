/*-----------------------------------------------------------------------------------------------------------------

   Edit an integer number with the line editor 

   Revision History:
   V1.0 2017 01 18 ChrisMicro, initial version

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

  ---------------------------------------------------------------------------------------------------------------*/

#include <rtthread.h>
#include <editor.h>

int mcurses_number_edit_demo(int argc, char const *argv[])
{
    setFunction_putchar(rtt_putchar);   // tell the library which output channel shall be used
    setFunction_getchar(rtt_getchar);   // tell the library which input channel shall be used

    initscr();                          // initialize MCURSES

    clear();
    rt_kprintf("Line Editor Demo\n");
    rt_thread_mdelay(1000);
    clear();

    move(5,15);
    rt_kprintf("edit number\n");

    while(1) 
    {
        static int16_t number=1234;

        move(6, 15);              // set cursor position

        number = editInt16(number);

        move(10, 15);              // set cursor position    

        rt_kprintf("\n");
        rt_kprintf("the number is: %ld        \n", number);

        rt_thread_mdelay(1000);
    }
    return 0;
}
MSH_CMD_EXPORT(mcurses_number_edit_demo, edit demo)
