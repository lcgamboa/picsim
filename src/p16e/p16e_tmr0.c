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

#include "../../include/periferic16e.h"
#include "../../include/picsim.h"
#include <stdio.h>

extern const int fpw2[];

void p16e_tmr0_rst(_pic *pic) { pic->cp0 = 0; }

void p16e_tmr0(_pic *pic) {
  if ((((*pic->P16Emap.OPTION_REG) & 0x20) == 0x00) || // TOCS=FOSC/4
      ((((*pic->P16Emap.OPTION_REG) & 0x30) == 0x20) &&
       ((pic->t0cki_ == 0) &&
        (pic->pins[pic->t0cki - 1].value == 1))) || // T0CS=t0cki  T0SE =0
      ((((*pic->P16Emap.OPTION_REG) & 0x30) == 0x30) &&
       ((pic->t0cki_ == 1) &&
        (pic->pins[pic->t0cki - 1].value == 0)))) // T0CS=t0cki  T0SE =1
  {
    pic->cp0++;

    if (pic->lram == sfr_addr(pic->P16Emap.TMR0))
      pic->cp0 = 0; // RESET prescaler

    if (((*pic->P16Emap.OPTION_REG) & 0x08) == 0x08) // PSA
    {
      // Without prescaler
      if ((((*pic->P16Emap.TMR0) + 1) == 0x100)) {
        unsigned short offset = (sfr_addr(pic->P16Emap.INTCON) & 0x007F);
        for (int bk = 0; bk < 32; bk++) {
          pic->ram[(0x0080 * bk) | (offset)] |= 0x04; // TMR0IF
        }
      }
      (*pic->P16Emap.TMR0)++;
      pic->cp0 = 0;
    } else {
      // With prescaler
      if (pic->cp0 >= 2 * (fpw2[(*pic->P16Emap.OPTION_REG) & 0x07])) {
        if ((((*pic->P16Emap.TMR0) + 1) == 0x100)) {
          unsigned short offset = (sfr_addr(pic->P16Emap.INTCON) & 0x007F);
          for (int bk = 0; bk < 32; bk++) {
            pic->ram[(0x0080 * bk) | (offset)] |= 0x04; // TMR0IF
          }
        }
        (*pic->P16Emap.TMR0)++;
        pic->cp0 = 0;
      }
    }
  }
  pic->t0cki_ = pic->pins[pic->t0cki - 1].value;
}

void p16e_tmr0_2(_pic *pic) {
  if ((*pic->P16Emap.T0CON0) & 0x80) // TMR0ON
  {
    if ((((*pic->P16Emap.T0CON1) & 0xE0) == 0x40) || // TOCS=FOSC/4
        ((((*pic->P16Emap.T0CON1) & 0xE0) == 0x20) &&
         ((pic->t0cki_ == 0) &&
          (pic->pins[pic->t0cki - 1].value == 1))) || // T0CS=t0cki  T0SE =0
        ((((*pic->P16Emap.T0CON1) & 0xE0) == 0x00) &&
         ((pic->t0cki_ == 1) &&
          (pic->pins[pic->t0cki - 1].value == 0)))) // T0CS=t0cki  T0SE =1
    {
      pic->cp0++;

      if (pic->lram == sfr_addr(pic->P16Emap.TMR0L))
        pic->cp0 = 0; // RESET prescaler

      if (pic->cp0 >= fpw2[(*pic->P16Emap.T0CON1) & 0x0F]) {
        // TODO implement TMR0 postscaler
        // 8 bit mode
        if (((*pic->P16Emap.T0CON0) & 0x10) &&
            (((*pic->P16Emap.TMR0L) + 1) == 0x100))
          (*pic->P16Emap.PIR0) |= 0x20; // T0IF

        (*pic->P16Emap.TMR0L)++;

        // 16 bit mode
        if ((!(*pic->P16Emap.TMR0L)) && (!((*pic->P16Emap.T0CON0) & 0x10))) {
          if (((*pic->P16Emap.TMR0H) + 1) == 0x100)
            (*pic->P16Emap.PIR0) |= 0x20; // T0IF
          (*pic->P16Emap.TMR0H)++;
        }
        pic->cp0 = 0;
      }
    }
  }
  pic->t0cki_ = pic->pins[pic->t0cki - 1].value;
}
