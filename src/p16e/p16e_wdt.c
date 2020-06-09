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
#include"../../include/periferic16e.h"

extern const int fpw2[];

void
p16e_wdt_rst(void)
{
 pic->twdt = 0;
 pic->wdt = 0;
}

void
p16e_wdt(void)
{

 //TODO WDT support window and clock select  
 /*
 pic->config[2] &  0x0700  WDTCWS WDT Configuration Clock Select bits
 pic->config[2] &  0x3800  WDTCCS WDT Configuration Window Select bits
 pic->config[2] &  0x001F  WDTCPS WDT Configuration Period Select bits
  */

 if ((pic->getconf (CFG_WDT) == 0x60) || //Enabled
     (pic->getconf (CFG_WDT) && pic->sleep) || //Enabled and disabled in sleep    
     ((pic->getconf (CFG_WDT) == 0x20)&&((*pic->P16Emap.WDTCON0) & 0x01))) //Software Enable
  {
   pic->twdt += 4.0 / pic->freq;

   int div;

   if ((pic->config[2] & 0x001F) == 0x1F)//software controlled
    {
     div = ((*pic->P16Emap.WDTCON0) & 0x3E) >> 1;
    }
   else //configuration controlled
    {
     div = pic->config[2] & 0x001F;
    }

   if (div > 18)div = 0;

   if (pic->twdt > (1e-3 * fpw2[div]))
    {
     pic->twdt = 0;
     pic->wdt++;
     if (pic->wdt == pic->WDT_MS)
      {
       //reset
       pic->wdt = 0;

       unsigned char temp;
       int bk;
       int offset = 0x007F & sfr_addr (pic->P16Emap.STATUS);
       temp = (*pic->P16Emap.STATUS);
       temp &= ~0x10;

       for (bk = 0; bk < 32; bk++)
        pic->ram[(0x0080 * bk) | offset] = temp;

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


void
p16e_wdt_2(void)
{
 
 if ((pic->getconf (CFG_WDT) == 0x18) || //Enabled
    ((pic->getconf (CFG_WDT) == 0x10)&& pic->sleep) || //Enabled and disabled in sleep    
    ((pic->getconf (CFG_WDT) == 0x08)&&((*pic->P16Emap.WDTCON) & 0x01))) //Software Enable
  {
   pic->twdt += 4.0 / pic->freq;

   int div= ((*pic->P16Emap.WDTCON) & 0x3E) >> 1;
   
   if (div > 18)div = 0;

   if (pic->twdt > (1e-3 * fpw2[div]))
    {   
     pic->twdt = 0;
     pic->wdt++;
     if (pic->wdt == pic->WDT_MS)
      {
       //reset
       pic->wdt = 0;

       unsigned char temp;
       int bk;
       int offset = 0x007F & sfr_addr (pic->P16Emap.STATUS);
       temp = (*pic->P16Emap.STATUS);
       temp &= ~0x10;

       for (bk = 0; bk < 32; bk++)
        pic->ram[(0x0080 * bk) | offset] = temp;

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
