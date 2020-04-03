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
#include"../../include/periferic18.h"

void
p18_int_portb_rst(void)
{
 pic->portbm = 0;
}

void
p18_int_portb(void)
{
 unsigned char temp;

 temp = (*pic->P18map.TRISB)&0xF0;
 if (((*pic->P18map.PORTB) & temp) != (pic->portb & temp))
  {
   pic->portbm = 1;
  }

 if (pic->rram == sfr_addr (pic->P18map.PORTB))
  {
   pic->portbm = 0;
   //Only disable mismatch
   //(*pic->P18map.INTCON)&=~0x01;//RBIF
  }

 if (pic->portbm)
  {
   (*pic->P18map.INTCON) |= 0x01; //RBIF
  }

}