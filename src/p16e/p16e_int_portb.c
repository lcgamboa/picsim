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

void
p16e_int_portb_rst(void) { }

void
p16e_int_portb(void)
{

 unsigned char temp;
 unsigned char val;
 //POSITIVE
 temp = (*pic->P16Emap.TRISB)&(*pic->P16Emap.IOCBP);
 val = ((*pic->P16Emap.PORTB) & temp) & ~(pic->portb & temp);
 if (val)
  {
   (*pic->P16Emap.IOCBF) |= val;
   unsigned short offset = (sfr_addr (pic->P16Emap.INTCON) & 0x007F);
   for (int bk = 0; bk < 32; bk++)
    {
     pic->ram[(0x0080 * bk) | (offset)] |= 0x01; //IOCIF
    }
  }

 //NEGATIVE
 temp = (*pic->P16Emap.TRISB)&(*pic->P16Emap.IOCBN);
 val=~((*pic->P16Emap.PORTB) & temp) & (pic->portb & temp);
 if (val)
  {
   (*pic->P16Emap.IOCBF) |= val;
   unsigned short offset = (sfr_addr (pic->P16Emap.INTCON) & 0x007F);
   for (int bk = 0; bk < 32; bk++)
    {
     pic->ram[(0x0080 * bk) | (offset)] |= 0x01; //IOCIF
    }
  }

 if (pic->lram == sfr_addr (pic->P16Emap.IOCBF))
  {
   if ((*pic->P16Emap.IOCBF) == 0)
    {
     unsigned short offset = (sfr_addr (pic->P16Emap.INTCON) & 0x007F);
     for (int bk = 0; bk < 32; bk++)
      {
       pic->ram[(0x0080 * bk) | (offset)] &= 0xFE; //IOCIF
      }
    }

  }

}