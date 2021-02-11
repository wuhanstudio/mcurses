#include <rtthread.h>
#include "mcurses.h"

int mcurses_simple_test(int argc, char const *argv[])
{
    setFunction_putchar(rtt_putchar);   // tell the library which output channel shall be used

    initscr();                          // initialize mcurses

    clear ();

    move (11, 15);                      // set cursor position
    addstr ("Hello, World");            // show text

    rt_thread_mdelay(3000);

    move(0, 0);
    clear ();

    return 0;
}
MSH_CMD_EXPORT(mcurses_simple_test, mcurses simple test demo)
