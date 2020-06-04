/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2020  Luis Claudio Gamboa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include<stdio.h>
#include"../../include/picsim.h"
#include"../../include/periferic18.h"

extern const int fpw2[];

void
p18_wdt_rst(void)
{
 pic->twdt = 0;
 pic->wdt = 0;
}

void
p18_wdt(void)
{
 if (pic->getconf (CFG_WDT) || ((*pic->P18map.WDTCON) & 0x01))
  {
   //     printf("WDT ON %f   %i  0x%02X\n",pic->twdt ,pic->wdt,(*pic->P18map.RCON));

   pic->twdt += 4.0 / pic->freq;

   if (pic->twdt > (1e-3 * fpw2[(pic->config[1] & 0x0E00) >> 9]))
    {
     pic->twdt = 0;
     pic->wdt++;

     if (pic->wdt == pic->WDT_MS)
      {
       //reset
       pic->wdt = 0;

       if (pic->P18map.RCON)(*pic->P18map.RCON) &= ~0x08; //clear TO


       if (pic->sleep == 1)
        {
         pic->sleep = 0;
        }
       else
        {
         pic_reset (0);
        }

      }
    }
  }
}
