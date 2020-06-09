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
p18_int_pin_rst(void)
{
 pic->int0v = 0;
 pic->int1v = 0;
 pic->int2v = 0;
}

void
p18_int_pin(void)
{
 //INT0
 if ((pic->pins[pic->int0 - 1].dir == PD_IN)&&(pic->pins[pic->int0 - 1].value != pic->int0v))
  {
   if (((!pic->int0v) &&((*pic->P18map.INTCON2) & 0x40)) || ((pic->int0v) && (!((*pic->P18map.INTCON2) & 0x40))))
    {
     (*pic->P18map.INTCON) |= 0x02; //INTF
    }
  }
 pic->int0v = pic->pins[pic->int0 - 1].value;

 //INT1
 if ((pic->pins[pic->int1 - 1].dir == PD_IN)&&(pic->pins[pic->int1 - 1].value != pic->int1v))
  {
   if (((!pic->int1v) &&((*pic->P18map.INTCON2) & 0x20)) || ((pic->int1v) && (!((*pic->P18map.INTCON2) & 0x20))))
    {
     (*pic->P18map.INTCON3) |= 0x01; //INT1F
    }
  }
 pic->int1v = pic->pins[pic->int1 - 1].value;

 //INT2
 if ((pic->pins[pic->int2 - 1].dir == PD_IN)&&(pic->pins[pic->int2 - 1].value != pic->int2v))
  {
   if (((!pic->int2v) &&((*pic->P18map.INTCON2) & 0x10)) || ((pic->int2v) && (!((*pic->P18map.INTCON2) & 0x10))))
    {
     (*pic->P18map.INTCON3) |= 0x02; //INT2F
    }
  }
 pic->int2v = pic->pins[pic->int2 - 1].value;
}



void
p18_int_pin_2(void)
{
 //INT0
 if ((pic->pins[pic->int0 - 1].dir == PD_IN)&&(pic->pins[pic->int0 - 1].value != pic->int0v))
  {
   if (((!pic->int0v) &&((*pic->P18map.INTCON) & 0x01)) || ((pic->int0v) && (!((*pic->P18map.INTCON) & 0x01))))
    {
     (*pic->P18map.PIR0) |= 0x01; //INTF
    }
  }
 pic->int0v = pic->pins[pic->int0 - 1].value;

 //INT1
 if ((pic->pins[pic->int1 - 1].dir == PD_IN)&&(pic->pins[pic->int1 - 1].value != pic->int1v))
  {
   if (((!pic->int1v) &&((*pic->P18map.INTCON) & 0x02)) || ((pic->int1v) && (!((*pic->P18map.INTCON) & 0x02))))
    {
     (*pic->P18map.PIR0) |= 0x02; //INTF
    }
  }
 pic->int1v = pic->pins[pic->int1 - 1].value;

 //INT2
 if ((pic->pins[pic->int2 - 1].dir == PD_IN)&&(pic->pins[pic->int2 - 1].value != pic->int2v))
  {
   if (((!pic->int2v) &&((*pic->P18map.INTCON) & 0x04)) || ((pic->int2v) && (!((*pic->P18map.INTCON) & 0x04))))
    {
     (*pic->P18map.PIR0) |= 0x04; //INTF
    }
  }
 pic->int2v = pic->pins[pic->int2 - 1].value;
}