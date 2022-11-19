/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2022  Luis Claudio Gamboa Lopes

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

int pic_wr_pin16(_pic *pic, unsigned char pin, unsigned char value);

void p16_adc_rst(_pic *pic) {
  pic->adcstep = 0;
  pic->adcon1 = 0xFF;
}

void p16_adc(_pic *pic) {
  float val;
  int chn;
  short dval;

  if (((*pic->P16map.ADCON0) & 0x05) == 0x05) // ADON and GO/DONE
  {
    pic->adcstep++;
    if (pic->adcstep > 10) {

      if (pic->processor == P16F777) {
        chn = (((*pic->P16map.ADCON0) & 0x02) << 2) |
              (((*pic->P16map.ADCON0) & 0x38) >> 3);
      } else {
        chn = ((*pic->P16map.ADCON0) & 0x38) >> 3;
      }

      if (pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG) {
        val = pic->pins[pic->adc[chn] - 1].avalue;
      } else {
        val = 0;
      }

      if (pic->processor == P16F777) {
        dval = ((1023 * val) / pic->vcc);
      } else { // VREF selection
        switch ((*pic->P16map.ADCON1) & 0x0F) {
        case 1: // VREF+
        case 3:
        case 5:
        case 10:
          dval = ((1023 * val) / pic->pins[pic->adc[3] - 1].avalue);
          break;
        case 8: // VREF+ VREF-
        case 11:
        case 12:
        case 13:
        case 15:
          dval = ((1023 * (val - pic->pins[pic->adc[2] - 1].avalue)) /
                  (pic->pins[pic->adc[3] - 1].avalue -
                   pic->pins[pic->adc[2] - 1].avalue));
          break;
        default:
          dval = ((1023 * val) / pic->vcc);
          break;
        }
      }

      if (dval < 0)
        dval = 0;
      if (dval > 1023)
        dval = 1023;

      if (((*pic->P16map.ADCON1) & 0x80) == 0x80) {
        (*pic->P16map.ADRESH) = (dval & 0xFF00) >> 8;
        (*pic->P16map.ADRESL) = (dval & 0x00FF);
      } else {
        dval = dval << 6;
        (*pic->P16map.ADRESH) = (dval & 0xFF00) >> 8;
        (*pic->P16map.ADRESL) = (dval & 0x00FF);
      }

      (*pic->P16map.ADCON0) &= ~0x04;

      // ADIF
      (*pic->P16map.PIR1) |= 0x40;

      pic->adcstep = 0;

      // printf("AD0=%02X AD1=%02X\n",pic->ram[ADCON0],pic->ram[ADCON1]);
      // printf("ADC conversion channel (%i)=%#04X (%08.3f)\n",chn,dval,val);
    }
  } else {
    pic->adcstep = 0;
  }

  if (((*pic->P16map.ADCON1) & 0x0F) != pic->adcon1) {

    if (pic->processor == P16F777) {
      switch ((*pic->P16map.ADCON1) & 0x0F) {
      case 0:
      case 1:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[9] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[10] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[11] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[12] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[13] - 1].ptype = PT_ANALOG;
        break;
      case 2:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[9] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[10] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[11] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[12] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 3:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[9] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[10] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[11] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 4:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[9] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[10] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 5:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[9] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 6:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 7:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 8:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 9:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 10:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 11:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 12:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 13:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 14:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      case 15:
        pic->pins[pic->adc[0] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[1] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[8] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[9] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[10] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[11] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[12] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[13] - 1].ptype = PT_DIGITAL;
        break;
      }
    } else {
      switch ((*pic->P16map.ADCON1) & 0x0F) {
      case 0:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        break;
      case 1:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        break;
      case 2:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 3:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 4:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 5:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 6:
      case 7:
        pic->pins[pic->adc[0] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[1] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 8:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
        break;
      case 9:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 10:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 11:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 12:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 13:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 14:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[2] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[3] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      case 15:
        pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
        pic->pins[pic->adc[1] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
        pic->pins[pic->adc[4] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[5] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[6] - 1].ptype = PT_DIGITAL;
        pic->pins[pic->adc[7] - 1].ptype = PT_DIGITAL;
        break;
      }
    }

    pic->adcon1 = (*pic->P16map.ADCON1) & 0x0F;
  }
}

void p16_adc_2(_pic *pic) {
  float val;
  int chn;
  short dval;

  if (((*pic->P16map.ADCON0) & 0x03) == 0x03) // ADON and GO/DONE
  {
    pic->adcstep++;
    if (pic->adcstep > 10) {

      chn = ((*pic->P16map.ADCON0) & 0x3C) >> 2;

      if (chn < pic->ADCCOUNT) {
        if (pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG) {
          val = pic->pins[pic->adc[chn] - 1].avalue;
        } else {
          val = 0;
        }
      } else {
        if (chn == 14) {
          val = 0; // CVref - comparators not implemented
        } else {
          val = 0.6; // Fixed reference
        }
      }

      // VREF selection
      switch (((*pic->P16map.ADCON1) & 0x30) >> 4) {
      case 1: // VREF+
        dval = ((1023 * val) / pic->pins[pic->adc[3] - 1].avalue);
        break;
      case 2: // VREF-
        dval = ((1023 * (val - pic->pins[pic->adc[2] - 1].avalue)) /
                (pic->vcc - pic->pins[pic->adc[2] - 1].avalue));
        break;
      case 3: // VREF+ VREF-
        dval = ((1023 * (val - pic->pins[pic->adc[2] - 1].avalue)) /
                (pic->pins[pic->adc[3] - 1].avalue -
                 pic->pins[pic->adc[2] - 1].avalue));
        break;
      default: // disabled
        dval = ((1023 * val) / pic->vcc);
        break;
      }

      if (dval < 0)
        dval = 0;
      if (dval > 1023)
        dval = 1023;

      if (((*pic->P16map.ADCON1) & 0x80) == 0x80) {
        (*pic->P16map.ADRESH) = (dval & 0xFF00) >> 8;
        (*pic->P16map.ADRESL) = (dval & 0x00FF);
      } else {
        dval = dval << 6;
        (*pic->P16map.ADRESH) = (dval & 0xFF00) >> 8;
        (*pic->P16map.ADRESL) = (dval & 0x00FF);
      }

      (*pic->P16map.ADCON0) &= ~0x02;

      // ADIF
      (*pic->P16map.PIR1) |= 0x40;

      pic->adcstep = 0;

      // printf("AD0=%02X AD1=%02X\n",pic->ram[ADCON0],pic->ram[ADCON1]);
      // printf("ADC conversion channel (%i)=%#04X (%08.3f)\n",chn,dval,val);
    }
  } else {
    pic->adcstep = 0;
  }

  if (pic->lram == sfr_addr(pic->P16map.ADCON1)) {
    // VREF selection
    switch (((*pic->P16map.ADCON1) & 0x30) >> 4) {
    case 1: // VREF+
      pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
      break;
    case 2: // VREF-
      pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
      break;
    case 3: // VREF+ VREF-
      pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
      pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
      break;
    default: // disabled
      pic->pins[pic->adc[3] - 1].ptype =
          ((*pic->P16map.ANSEL) & 0x08) ? PT_ANALOG : PT_DIGITAL;
      pic->pins[pic->adc[2] - 1].ptype =
          ((*pic->P16map.ANSEL) & 0x04) ? PT_ANALOG : PT_DIGITAL;
      break;
    }
    pic->ioupdated = 1;
  }

  if (pic->lram == sfr_addr(pic->P16map.ANSEL)) {
    for (int i = 0; i < 8; i++) {
      if ((*pic->P16map.ANSEL) & (1 << i)) {
        pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
      } else {
        pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
        if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
          pic_wr_pin16(pic, pic->adc[i], pic->pins[pic->adc[i] - 1].ovalue);
      }
    }
  }

  if (pic->lram == sfr_addr(pic->P16map.ANSELH)) {
    for (int i = 8; i < 14; i++) {
      if ((*pic->P16map.ANSELH) & (1 << (i - 8))) {
        pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
      } else {
        pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
        if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
          pic_wr_pin16(pic, pic->adc[i], pic->pins[pic->adc[i] - 1].ovalue);
      }
    }
  }
}
