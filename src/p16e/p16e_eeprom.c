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

void p16e_eeprom_rst(_pic *pic) { pic->ee_wr = 0; }

void p16e_eeprom(_pic *pic) {
  // EEPROM

  if (pic->P16Emap.EECON1) {
    if (((*pic->P16Emap.EECON1) & 0x04) == 0x04) {
      if ((*pic->P16Emap.EECON2) != 0) {
        if ((*pic->P16Emap.EECON2) == 0x55) {
          (*pic->P16Emap.EECON2) = 0;
          pic->ee_wr = -1;
        } else {
          if (((*pic->P16Emap.EECON2) == 0xAA) && (pic->ee_wr == -1)) {
            (*pic->P16Emap.EECON2) = 0;
            pic->ee_wr = 1;
          } else {
            (*pic->P16Emap.EECON2) = 0;
            pic->ee_wr = 0;
          }
        }
      }
    }

    if (((*pic->P16Emap.EECON1) & 0x03) != 0x00) {
      if (((*pic->P16Emap.EECON1) & 0x01) == 0x01) // RD
      {
        if (((*pic->P16Emap.EECON1) & 0x80) == 0) {
          (*pic->P16Emap.EEDATL) = pic->eeprom[(*pic->P16Emap.EEADRL)];
        } else {
          (*pic->P16Emap.EEDATL) = (pic->prog[((*pic->P16Emap.EEADRH) << 8) |
                                              (*pic->P16Emap.EEADRL)]) &
                                   0x00FF;
          (*pic->P16Emap.EEDATH) = ((pic->prog[((*pic->P16Emap.EEADRH) << 8) |
                                               (*pic->P16Emap.EEADRL)]) &
                                    0xFF00) >>
                                   8;
          //       printf("Reading
          //       %04X=%04X\n",(pic->ram[P877_EEADRH]<<8)|pic->ram[P877_EEADR],(pic->ram[P877_EEDATAH]<<8)
          //       | pic->ram[P877_EEDATA]);
        }
        (*pic->P16Emap.EECON1) &= ~0x01;
      } else {
        if (pic->ee_wr == 1) {
          if (((*pic->P16Emap.EECON1) & 0x80) == 0) {
            pic->eeprom[(*pic->P16Emap.EEADRL)] = (*pic->P16Emap.EEDATL);
          } else {
            pic->prog[((*pic->P16Emap.EEADRH) << 8) | (*pic->P16Emap.EEADRL)] =
                ((*pic->P16Emap.EEDATH) << 8) | (*pic->P16Emap.EEDATL);

            //      printf("Writing
            //      %04X=%04X\n",(pic->ram[P877_EEADRH]<<8)|pic->ram[P877_EEADR],(pic->ram[P877_EEDATAH]<<8)
            //      | pic->ram[P877_EEDATA]);
          }
          (*pic->P16Emap.EECON1) &= ~0x02;
          pic->ee_wr = 0;
        }
      }
    }
  }
}

void p16e_eeprom_2(_pic *pic) {
  // EEPROM

  if (pic->P16Emap.NVMCON1) {
    if (((*pic->P16Emap.NVMCON1) & 0x04) == 0x04) {
      if ((*pic->P16Emap.NVMCON2) != 0) {
        if ((*pic->P16Emap.NVMCON2) == 0x55) {
          (*pic->P16Emap.NVMCON2) = 0;
          pic->ee_wr = -1;
        } else {
          if (((*pic->P16Emap.NVMCON2) == 0xAA) && (pic->ee_wr == -1)) {
            (*pic->P16Emap.NVMCON2) = 0;
            pic->ee_wr = 1;
          } else {
            (*pic->P16Emap.NVMCON2) = 0;
            pic->ee_wr = 0;
          }
        }
      }
    }

    if (((*pic->P16Emap.NVMCON1) & 0x03) != 0x00) {
      if (((*pic->P16Emap.NVMCON1) & 0x01) == 0x01) // RD
      {
        if (((*pic->P16Emap.NVMCON1) & 0x80) == 0) {
          (*pic->P16Emap.NVMDATL) = pic->eeprom[(*pic->P16Emap.NVMADRL)];
        } else {
          (*pic->P16Emap.NVMDATL) = (pic->prog[((*pic->P16Emap.NVMADRH) << 8) |
                                               (*pic->P16Emap.NVMADRL)]) &
                                    0x00FF;
          (*pic->P16Emap.NVMDATH) = ((pic->prog[((*pic->P16Emap.NVMADRH) << 8) |
                                                (*pic->P16Emap.NVMADRL)]) &
                                     0xFF00) >>
                                    8;
        }
        (*pic->P16Emap.NVMCON1) &= ~0x01;
      } else {
        if (pic->ee_wr == 1) {
          if (((*pic->P16Emap.NVMCON1) & 0x80) == 0) {
            pic->eeprom[(*pic->P16Emap.NVMADRL)] = (*pic->P16Emap.NVMDATL);
          } else {
            pic->prog[((*pic->P16Emap.NVMADRH) << 8) |
                      (*pic->P16Emap.NVMADRL)] =
                ((*pic->P16Emap.NVMDATH) << 8) | (*pic->P16Emap.NVMDATL);
          }
          (*pic->P16Emap.NVMCON1) &= ~0x02;
          pic->ee_wr = 0;
        }
      }
    }
  }
}