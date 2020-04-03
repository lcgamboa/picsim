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
p18_uart_rst(void)
{
 pic->serial_PIR1 = pic->P18map.PIR1;
 pic->serial_PIE1 = pic->P18map.PIE1;
 pic->serial_TXSTA = pic->P18map.TXSTA;
 pic->serial_RCSTA = pic->P18map.RCSTA;
 pic->serial_SPBRG = pic->P18map.SPBRG;
 pic->serial_RCREG = pic->P18map.RCREG;
 pic->serial_TXREG = pic->P18map.TXREG;
 pic->serial_TXREG_ADDR = sfr_addr (pic->P18map.TXREG);
 pic->serial_RCSTA_ADDR = sfr_addr (pic->P18map.RCSTA);
 pic->serial_RCREG_ADDR = sfr_addr (pic->P18map.RCREG);
 pic->serial_TRIS_RX = &pic->ram[sfr_addr (pic->pins[pic->usart[0] - 1].port) + 0x12];
 pic->serial_TRIS_RX_MASK = (0x01 << pic->pins[pic->usart[0] - 1].pord);
 
  pic->s_open = 1;
}

void
p18_uart_rst_2(void)
{
 //serial compat
 pic->P18map.TXSTA = &pic->ram[0xFAC];
 pic->P18map.RCSTA = &pic->ram[0xFAB];
 pic->P18map.SPBRG = &pic->ram[0xFAF];
 pic->P18map.RCREG = &pic->ram[0xFAE];
 pic->P18map.TXREG = &pic->ram[0xFAD];
 p18_uart_rst();
}

void
p18_uart_rst_3(void)
{
 //serial compat
 pic->P18map.TXSTA = &pic->ram[0xF9E];
 pic->P18map.RCSTA = &pic->ram[0xF9D];
 pic->P18map.SPBRG = &pic->ram[0xF9B];
 pic->P18map.RCREG = &pic->ram[0xF99];
 pic->P18map.TXREG = &pic->ram[0xF9A];
 p18_uart_rst();
}

/*
void
p18_uart(void)
{
}
 */