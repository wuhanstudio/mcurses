/************************************************************************

  The Matrix Rain Screen Saver

  This code is converted from QBASIC to C.

  QBasic Code from
  http://codegolf.stackexchange.com/questions/17285/make-the-matrix-digital-rain-using-the-shortest-amount-of-code

************************************************************************/

#include <rtthread.h>
#include <stdlib.h>
#include "mcurses.h"

#define setLocation(x,y) move(y,x)

int t[80];

void sub_d(int p, int s, int x, int y)
{
  uint8_t r;
  uint8_t g;

  r = (p % 16) * 16;
  g = 180 - p;
  if (r < 10) attrset (F_BLACK); // forground color black
  else
  {
    if (g > 170) attrset(F_WHITE);
    else if (g > 169) attrset(F_GREEN );
  }

  if ((y >= 0) && (y < 24) && (x < 80))
  {
    int xx, yy;
    xx = x;
    yy = y;
    setLocation(xx, yy);
    char c;
    c = 33 + (x * y) % 200;
    addch(c);
  }
}

int mcurses_matrix_rain(int argc, char const *argv[])
{
  setFunction_putchar(rtt_putchar); // tell the library which output channel shall be used

  initscr();    // initialize mcurses
  curs_set (0); // set cursor invisible
  clear();
  
  int i;
  int x;
  int y;
  int k;

  for (i = 0; i < 80; i++)
  {
    t[i] = - random() % 50;
  }

  //sub_d(1,1,10,10);
  while (1)
  {
    for (k = 1; k < 80; k++)
    {
      i = rand() % 79;
      if (t[i] > 28)t[i] = 0;
      t[i] = t[i] + 1;
      y = t[i];
      sub_d( 0     , 0, i, y - 6);
      sub_d( 2  + x, 0, i, y - 5  );
      sub_d( 2  + x, 0, i, y - 4  );
      sub_d( 10 + x, 0, i, y - 3 );
      sub_d( 10 + x, 0, i, y - 2 );
      sub_d( 11 + x, 0, i, y - 1 );
      sub_d( 0     , 2 + x, i, y );
    }
  }

  return 0;
}
MSH_CMD_EXPORT(mcurses_matrix_rain, screen demo)


/*
QBASIC orginal code from:
http://codegolf.stackexchange.com/questions/17285/make-the-matrix-digital-rain-using-the-shortest-amount-of-code

DECLARE SUB d (p!, s!, x!, y!)
DIM t(80)
FOR i = 1 TO 80
  t(i) = INT(-50 * RND)
NEXT
s = TIMER
f = 0
w$ = "bullet"
o = 1
 * o = 1
CLS
WHILE 1
    FOR i = 1 TO 80
        IF t(i) > 28 THEN t(i) = 0: IF f THEN SOUND 100 * i, 1
        t(i) = t(i) + 1
        y = t(i)
        d 0, 0, i, y - 6
        d 2 + x, 0, i, y - 5
        d 2 + x, 0, i, y - 4
        d 10 + x, 0, i, y - 3
        d 10 + x, 0, i, y - 2
        d 11 + x, 0, i, y - 1
        d 0, 2 + x, i, y
    NEXT
    k$ = INKEY$
    IF k$ <> "" THEN
        IF MID$(w$, o, 1) = k$ THEN
            o = o + 1
            IF o = LEN(w$) + 1 THEN z = 1: f = 100
        ELSE
            o = 1
        END IF

    END IF
    x = x + z
    l = TIMER
    WHILE l = TIMER
    WEND

WEND

SUB d (p, s, x, y)
COLOR p MOD 16, s MOD 16
IF y > 0 AND y < 24 THEN LOCATE y, x: PRINT CHR$(33 + (x * y) MOD 200);
END SUB
*/
 
 
