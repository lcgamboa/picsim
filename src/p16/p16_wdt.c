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

#include "../../include/periferic16.h"
#include "../../include/picsim.h"
#include <stdio.h>

extern const int fpw2[];

void p16_wdt_rst(_pic *pic) {
  pic->twdt = 0;
  pic->wdt = 0;
}

void p16_wdt(_pic *pic) {
  if (pic->getconf(pic, CFG_WDT)) {
    pic->twdt += 4.0 / pic->freq;

    if (((*pic->P16map.OPTION_REG) & 0x08)) // PSA
    {
      if (pic->twdt > (1e-3 * fpw2[(*pic->P16map.OPTION_REG) & 0x07])) {
        pic->twdt = 0;
        pic->wdt++;
        if (pic->wdt == pic->WDT_MS) {
          // reset
          pic->wdt = 0;

          pic->ram[((0x0000) << 2) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] &=
              ~0x10;
          pic->ram[((0x0020) << 2) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] &=
              ~0x10;
          pic->ram[((0x0040) << 2) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] &=
              ~0x10;
          pic->ram[((0x0060) << 2) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] &=
              ~0x10;

          if (pic->sleep == 1) {
            pic->sleep = 0;
          } else {
            pic_reset(pic, 0);
          }
        }
      }
    } else {
      if (pic->twdt > 1e-3) {
        pic->twdt = 0;
        pic->wdt++;
        if (pic->wdt == pic->WDT_MS) {
          // reset
          pic->wdt = 0;

          pic->ram[((0x0000) << 2) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] &=
              ~0x10;
          pic->ram[((0x0020) << 2) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] &=
              ~0x10;
          if (pic->processor != P16F84A) {
            pic->ram[((0x0040) << 2) |
                     (sfr_addr(pic->P16map.STATUS) & 0x007F)] &= ~0x10;
            pic->ram[((0x0060) << 2) |
                     (sfr_addr(pic->P16map.STATUS) & 0x007F)] &= ~0x10;
          }
          if (pic->sleep == 1) {
            pic->sleep = 0;
          } else {
            pic_reset(pic, 0);
          }
        }
        //        printf("WDT=%02X\n",pic->wdt);
      }
    }
  }
}
