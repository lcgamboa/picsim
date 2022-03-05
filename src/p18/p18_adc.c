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

int pic_wr_pin18(_pic *pic, unsigned char pin, unsigned char value);

void p18_adc_rst(_pic *pic) {
  pic->adcstep = 0;
  pic->adcon1 = 0xFF;
}

void p18_adc(_pic *pic) {
  float val;
  int chn;
  short dval;

  if (pic->ADCCOUNT > 0) {

    if (((*pic->P18map.ADCON0) & 0x03) == 0x03) // ADON and GO/DONE
    {
      pic->adcstep++;
      if (pic->adcstep > 10) {
        chn = ((*pic->P18map.ADCON0) & 0x3C) >> 2;

        if ((pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG) &&
            (chn < pic->ADCCOUNT)) {
          val = pic->pins[pic->adc[chn] - 1].avalue;
        } else {
          val = 0;
        }

        // VREF selection
        switch ((*pic->P18map.ADCON1) & 0x30) {
        case 0x10: // VREF+
          dval = ((1023 * val) / pic->pins[pic->adc[3] - 1].avalue);
          break;
        case 0x20: // VREF-
          dval = ((1023 * (val - pic->pins[pic->adc[2] - 1].avalue)) /
                  (pic->vcc - pic->pins[pic->adc[2] - 1].avalue));
          break;
        case 0x30: // VREF+ VREF-
          dval = ((1023 * (val - pic->pins[pic->adc[2] - 1].avalue)) /
                  (pic->pins[pic->adc[3] - 1].avalue -
                   pic->pins[pic->adc[2] - 1].avalue));
          break;
        default:
          dval = ((1023 * val) / pic->vcc);
          break;
        }

        if (dval < 0)
          dval = 0;
        if (dval > 1023)
          dval = 1023;

        if ((*pic->P18map.ADCON2) & 0x80) // ADFM
        {                                 // Rigth
          (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
          (*pic->P18map.ADRESL) = (dval & 0x00FF);
        } else { // left
          dval = dval << 6;
          (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
          (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }

        (*pic->P18map.ADCON0) &= ~0x02;

        // ADIF
        (*pic->P18map.PIR1) |= 0x40;

        pic->adcstep = 0;
      }
    } else {
      pic->adcstep = 0;
    }

    if (!pic->P18map.ANSELA) {
      if (((*pic->P18map.ADCON1) & 0x0F) != pic->adcon1) {
        int i;
        for (i = 0; i < pic->ADCCOUNT; i++) {
          if (((*pic->P18map.ADCON1) & 0x0F) < (0x0F - i))
            pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
          else
            pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
        }

        if ((*pic->P18map.ADCON1) & 0x20) // VCFG1
          pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        if ((*pic->P18map.ADCON1) & 0x10) // VCFG0
          pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;

        pic->adcon1 = (*pic->P18map.ADCON1) & 0x0F;
      }
    } else {

      if (pic->lram == sfr_addr(pic->P18map.ANSELA)) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTA)) {
            if ((*pic->P18map.ANSELA) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if (pic->lram == sfr_addr(pic->P18map.ANSELB)) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTB)) {
            if ((*pic->P18map.ANSELB) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if (pic->lram == sfr_addr(pic->P18map.ANSELC)) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTC)) {
            if ((*pic->P18map.ANSELC) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if ((pic->P18map.ANSELD) && (pic->lram == sfr_addr(pic->P18map.ANSELD))) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTD)) {
            if ((*pic->P18map.ANSELD) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if ((pic->P18map.ANSELE) && (pic->lram == sfr_addr(pic->P18map.ANSELE))) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTE)) {
            if ((*pic->P18map.ANSELE) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }
    }
  }
}

void p18_adc_2(_pic *pic) {
  float val;
  int chn;
  short dval;

  if (pic->ADCCOUNT > 0) {

    if (((*pic->P18map.ADCON0) & 0x05) == 0x05) // ADON and GO/DONE
    {
      pic->adcstep++;
      if (pic->adcstep > 10) {
        chn = ((*pic->P18map.ADCON0) & 0x38) >> 3;

        if (pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG) {
          val = pic->pins[pic->adc[chn] - 1].avalue;
        } else {
          val = 0;
        }

        // VREF selection
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

        if (dval < 0)
          dval = 0;
        if (dval > 1023)
          dval = 1023;

        if (((*pic->P18map.ADCON1) & 0x80) == 0x80) // ADFM
        {
          (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
          (*pic->P18map.ADRESL) = (dval & 0x00FF);
        } else {
          dval = dval << 6;
          (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
          (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }

        (*pic->P18map.ADCON0) &= ~0x04;

        // ADIF
        (*pic->P18map.PIR1) |= 0x40;

        pic->adcstep = 0;
      }
    } else {
      pic->adcstep = 0;
    }

    if (((*pic->P18map.ADCON1) & 0x0F) != pic->adcon1) {
      switch ((*pic->P18map.ADCON1) & 0x0F) {
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

      pic->adcon1 = (*pic->P18map.ADCON1) & 0x0F;
    }
  }
}

void p18_adc_3(_pic *pic) {
  // FIXME only basic mode implemented
  float val;
  int chn;
  short dval;

  if (pic->ADCCOUNT > 0) {
    if (((*pic->P18map.ADCON0) & 0x81) == 0x81) // ADON and GO/DONE
    {
      pic->adcstep++;
      if (pic->adcstep > 10) {
        chn = (*pic->P18map.ADPCH) & 0x3F;

        if ((pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG) &&
            (chn < pic->ADCCOUNT)) {
          val = pic->pins[pic->adc[chn] - 1].avalue;
        } else {
          val = 0;
        }
        // TODO add VREF selection support
        dval = ((1023 * val) / pic->vcc);

        if ((*pic->P18map.ADCON0) & 0x04) // ADFM
        {                                 // Rigth
          (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
          (*pic->P18map.ADRESL) = (dval & 0x00FF);
        } else { // left
          dval = dval << 6;
          (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
          (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }

        (*pic->P18map.ADCON0) &= ~0x01;

        // ADIF
        (*pic->P18map.PIR1) |= 0x01;

        pic->adcstep = 0;
      }
    } else {
      pic->adcstep = 0;
    }

    if (!pic->P18map.ANSELA) {
      if (((*pic->P18map.ADCON1) & 0x0F) != pic->adcon1) {
        int i;
        for (i = 0; i < pic->ADCCOUNT; i++) {
          if (((*pic->P18map.ADCON1) & 0x0F) < (0x0F - i))
            pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
          else
            pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
        }

        if ((*pic->P18map.ADCON1) & 0x20) // VCFG1
          pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
        if ((*pic->P18map.ADCON1) & 0x10) // VCFG0
          pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;

        pic->adcon1 = (*pic->P18map.ADCON1) & 0x0F;
      }
    } else {

      if (pic->lram == sfr_addr(pic->P18map.ANSELA)) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTA)) {
            if ((*pic->P18map.ANSELA) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if (pic->lram == sfr_addr(pic->P18map.ANSELB)) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTB)) {
            if ((*pic->P18map.ANSELB) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if (pic->lram == sfr_addr(pic->P18map.ANSELC)) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTC)) {
            if ((*pic->P18map.ANSELC) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if ((pic->P18map.ANSELD) && (pic->lram == sfr_addr(pic->P18map.ANSELD))) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTD)) {
            if ((*pic->P18map.ANSELD) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }

      if ((pic->P18map.ANSELE) && (pic->lram == sfr_addr(pic->P18map.ANSELE))) {
        for (int i = 0; i < pic->ADCCOUNT; i++) {
          if ((pic->adc[i]) &&
              (pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTE)) {
            if ((*pic->P18map.ANSELE) &
                (1 << pic->pins[pic->adc[i] - 1].pord)) {
              pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            } else {
              pic->pins[pic->adc[i] - 1].ptype = PT_DIGITAL;
              if (pic->pins[pic->adc[i] - 1].dir == PD_IN)
                pic_wr_pin18(pic, pic->adc[i],
                             pic->pins[pic->adc[i] - 1].ovalue);
            }
          }
        }
      }
    }
  }
}
