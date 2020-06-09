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
p18_int_ports_rst(void) { }

void
p18_int_ports(void)
{

 unsigned char temp;
 unsigned char val;
 //POSITIVE
 temp = (*pic->P18map.TRISB)&(*pic->P18map.IOCBP);
 val = ((*pic->P18map.PORTB) & temp) & ~(pic->portb & temp);
 if (val)
  {
   (*pic->P18map.IOCBF)  |= val;
   (*pic->P18map.PIR0)   |= 0x10; //IOCIF
  }

 //NEGATIVE
 temp = (*pic->P18map.TRISB)&(*pic->P18map.IOCBN);
 val=~((*pic->P18map.PORTB) & temp) & (pic->portb & temp);
 if (val)
  {
   (*pic->P18map.IOCBF) |= val;
   (*pic->P18map.PIR0)  |= 0x10; //IOCIF
  }

 if (pic->lram == sfr_addr (pic->P18map.IOCBF))
  {
   if ((*pic->P18map.IOCBF) == 0)
    {
     (*pic->P18map.PIR0) &= 0xEF; //IOCIF
    }
  }

}