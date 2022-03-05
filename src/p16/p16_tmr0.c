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

void p16_tmr0_rst(_pic *pic) { pic->cp0 = 0; }

void p16_tmr0(_pic *pic) {
  if ((((*pic->P16map.OPTION_REG) & 0x20) == 0x00) || // TOCS=FOSC/4
      ((((*pic->P16map.OPTION_REG) & 0x30) == 0x20) &&
       ((pic->t0cki_ == 0) &&
        (pic->pins[pic->t0cki - 1].value == 1))) || // T0CS=t0cki  T0SE =0
      ((((*pic->P16map.OPTION_REG) & 0x30) == 0x30) &&
       ((pic->t0cki_ == 1) &&
        (pic->pins[pic->t0cki - 1].value == 0)))) // T0CS=t0cki  T0SE =1
  {
    pic->cp0++;

    if (pic->lram == sfr_addr(pic->P16map.TMR0))
      pic->cp0 = 0; // RESET prescaler

    if (((*pic->P16map.OPTION_REG) & 0x08) == 0x08) // PSA
    {
      if ((((*pic->P16map.TMR0) + 1) == 0x100)) {
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |=
            0x04; // T0IF
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |= 0x04;
        if (pic->processor != P16F84A) {
          pic->ram[(0x0100) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |= 0x04;
          pic->ram[(0x0180) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |= 0x04;
        };
      }
      (*pic->P16map.TMR0)++;
      pic->cp0 = 0;
    } else {
      if (pic->cp0 >= 2 * (fpw2[(*pic->P16map.OPTION_REG) & 0x07])) {
        if ((((*pic->P16map.TMR0) + 1) == 0x100)) {
          pic->ram[(0x0000) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |=
              0x04; // T0IF
          pic->ram[(0x0080) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |= 0x04;
          if (pic->processor != P16F84A) {
            pic->ram[(0x0100) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |=
                0x04;
            pic->ram[(0x0180) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] |=
                0x04;
          }
        }
        (*pic->P16map.TMR0)++;
        pic->cp0 = 0;
      }
    }
  }
  pic->t0cki_ = pic->pins[pic->t0cki - 1].value;
}
