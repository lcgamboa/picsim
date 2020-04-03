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
p16e_int_pin_rst(void) 
{ 
  pic->int0v = 0;
    //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

void
p16e_int_pin(void) 
{ 
  //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
 /*
 //INT
 
    if((pic->pins[pic->int0-1].dir == PD_IN)&&(pic->pins[pic->int0-1].value  != pic->int0v))
    {
      if(((!pic->int0v) &&(pic->ram[P16E_OPTION] & 0x40))||((pic->int0v) && (!(pic->ram[P16E_OPTION] & 0x40))))
      {
         pic->ram[(0x0000)|(P16E_INTCON & 0x007F)]|=0x02;//INTF
         pic->ram[(0x0080)|(P16E_INTCON & 0x007F)]|=0x02;
         pic->ram[(0x0100)|(P16E_INTCON & 0x007F)]|=0x02;
         pic->ram[(0x0180)|(P16E_INTCON & 0x007F)]|=0x02;
      } 
    } 
    pic->int0v=pic->pins[pic->int0-1].value;
  */

}