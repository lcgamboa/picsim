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

#include "../../include/periferic18.h"
#include "../../include/picsim.h"
#include <stdio.h>

extern const int fpw2[];

void p18_wdt_rst(_pic *pic) {
  pic->twdt = 0;
  pic->wdt = 0;
}

void p18_wdt(_pic *pic) {
  if (pic->getconf(pic, CFG_WDT) || ((*pic->P18map.WDTCON) & 0x01)) {
    //     printf("WDT ON %f   %i  0x%02X\n",pic->twdt
    //     ,pic->wdt,(*pic->P18map.RCON));

    pic->twdt += 4.0 / pic->freq;

    if (pic->twdt > (1e-3 * fpw2[pic->getconf(pic, CFG_WDT_DIV)])) {
      pic->twdt = 0;
      pic->wdt++;

      if (pic->wdt == pic->WDT_MS) {
        // reset
        pic->wdt = 0;

        if (pic->P18map.RCON)
          (*pic->P18map.RCON) &= ~0x08; // clear TO

        if (pic->sleep == 1) {
          pic->sleep = 0;
        } else {
          pic_reset(pic, 0);
        }
      }
    }
  }
}

void p18_wdt_2(_pic *pic) {
  // TODO WDT support window and clock select
  /*
  pic->config[2] &  0x0700  WDTCWS WDT Configuration Clock Select bits
  pic->config[2] &  0x3800  WDTCCS WDT Configuration Window Select bits
  pic->config[2] &  0x001F  WDTCPS WDT Configuration Period Select bits
   */

  if ((pic->getconf(pic, CFG_WDT) == 0x60) || // Enabled
      ((pic->getconf(pic, CFG_WDT) == 0x40) &&
       pic->sleep) || // Enabled and disabled in sleep
      ((pic->getconf(pic, CFG_WDT) == 0x20) &&
       ((*pic->P18map.WDTCON0) & 0x01))) // Software Enable
  {
    // printf("WDT ON %f   %i  0x%02X\n",pic->twdt
    // ,pic->wdt,(*pic->P18map.STATUS));

    pic->twdt += 4.0 / pic->freq;

    int div = pic->getconf(pic, CFG_WDT_DIV);

    if (div > 18)
      div = 0;

    if (pic->twdt > (1e-3 * fpw2[div])) {
      pic->twdt = 0;
      pic->wdt++;

      if (pic->wdt == pic->WDT_MS) {
        // reset
        pic->wdt = 0;

        (*pic->P18map.STATUS) &= ~0x40; // TO

        if (pic->sleep == 1) {
          pic->sleep = 0;
        } else {
          pic_reset(pic, 0);
        }
      }
    }
  }
}
