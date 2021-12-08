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
#include"../../include/periferic16.h"

void
p16_int_portb_rst(void)
{
 pic->portbm = 0;
}

void
p16_int_portb(void)
{
 unsigned char temp;

 temp = (*pic->P16map.TRISB)&0xF0;
 if (((*pic->P16map.PORTB) & temp) != (pic->portb & temp))
  {
   pic->portbm = 1;
  }

 if (pic->rram == sfr_addr (pic->P16map.PORTB))
  {
   pic->portbm = 0;
  }

 if (pic->portbm)
  {
   pic->ram[(0x0000) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] |= 0x01; //RBIF
   pic->ram[(0x0080) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] |= 0x01;
   if (pic->processor != P16F84A)
    {
     pic->ram[(0x0100) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] |= 0x01;
     pic->ram[(0x0180) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] |= 0x01;
    }
  }
}


void
p16_int_portb_2(void)
{
 unsigned char temp;

 temp = (*pic->P16map.TRISB);
 if (((*pic->P16map.PORTB) & temp) != (pic->portb & temp))
  {
   pic->portbm = 1;
  }

 if (pic->rram == sfr_addr (pic->P16map.PORTB))
  {
   pic->portbm = 0;
  }

 if (pic->portbm)
  {
   pic->ram[(0x0000) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] |= 0x01; //RBIF
   pic->ram[(0x0080) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] |= 0x01;
  }
}