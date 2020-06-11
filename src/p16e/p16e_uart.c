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
p16e_uart_rst(void)
{
 pic->serial_PIR1 = pic->P16Emap.PIR1;
 pic->serial_PIE1 = pic->P16Emap.PIE1;

 pic->serial_TXSTA = pic->P16Emap.TXSTA;
 pic->serial_RCSTA = pic->P16Emap.RCSTA;
 //FIXME only 16bits SPBRG
 pic->serial_SPBRG = pic->P16Emap.SP1BRGL; 
 pic->serial_RCREG = pic->P16Emap.RCREG;
 pic->serial_TXREG = pic->P16Emap.TXREG;
 pic->serial_TXREG_ADDR = sfr_addr (pic->P16Emap.TXREG);
 pic->serial_RCSTA_ADDR = sfr_addr (pic->P16Emap.RCSTA);
 pic->serial_RCREG_ADDR = sfr_addr (pic->P16Emap.RCREG);
 pic->serial_TRIS_RX = &pic->ram[sfr_addr (pic->pins[pic->usart[0] - 1].port)+(sfr_addr (pic->P16Emap.TRISA) - sfr_addr (pic->P16Emap.PORTA)) ];
 pic->serial_TRIS_RX_MASK = (0x01 << pic->pins[pic->usart[0] - 1].pord);
 pic->s_open = 1;
}

void
p16e_uart_rst_2(void)
{
 pic->serial_PIR1 = pic->P16Emap.PIR1;
 pic->serial_PIE1 = pic->P16Emap.PIE1;
 pic->serial_TXSTA = pic->P16Emap.TX1STA;
 pic->serial_RCSTA = pic->P16Emap.RC1STA;
 //FIXME only 16bits SPBRG
 pic->serial_SPBRG = pic->P16Emap.SP1BRGL; 
 pic->serial_RCREG = pic->P16Emap.RC1REG;
 pic->serial_TXREG = pic->P16Emap.TX1REG;
 pic->serial_TXREG_ADDR = sfr_addr (pic->P16Emap.TX1REG);
 pic->serial_RCSTA_ADDR = sfr_addr (pic->P16Emap.RC1STA);
 pic->serial_RCREG_ADDR = sfr_addr (pic->P16Emap.RC1REG);
 pic->serial_TRIS_RX = &pic->ram[sfr_addr (pic->pins[pic->usart[0] - 1].port)+(sfr_addr (pic->P16Emap.TRISA) - sfr_addr (pic->P16Emap.PORTA)) ];
 pic->serial_TRIS_RX_MASK = (0x01 << pic->pins[pic->usart[0] - 1].pord);
 pic->s_open = 1;
}



/*
void
p16e_uart(void)
{
}
 */