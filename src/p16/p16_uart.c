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

void p16_uart_rst(_pic *pic) {
  pic->serial[0].serial_PIR = pic->P16map.PIR1;
  pic->serial[0].serial_PIE = pic->P16map.PIE1;
  pic->serial[0].RXIF_mask = 0x20;
  pic->serial[0].TXIF_mask = 0x10;
  pic->serial[0].serial_TXSTA = pic->P16map.TXSTA;
  pic->serial[0].serial_RCSTA = pic->P16map.RCSTA;
  pic->serial[0].serial_SPBRG = pic->P16map.SPBRG;
  pic->serial[0].serial_RCREG = pic->P16map.RCREG;
  pic->serial[0].serial_TXREG = pic->P16map.TXREG;
  pic->serial[0].serial_TXREG_ADDR = sfr_addr(pic->P16map.TXREG);
  pic->serial[0].serial_RCSTA_ADDR = sfr_addr(pic->P16map.RCSTA);
  pic->serial[0].serial_RCREG_ADDR = sfr_addr(pic->P16map.RCREG);
  pic->serial[0].serial_TRIS_RX =
      &pic->ram[sfr_addr(pic->pins[pic->usart_rx[0] - 1].port) + 0x80];
  pic->serial[0].serial_TRIS_RX_MASK =
      (0x01 << pic->pins[pic->usart_rx[0] - 1].pord);
  pic->serial[0].s_open = 1;

  bb_uart_rst(&pic->serial[0].bbuart);
}

/*
void
p16_uart(void)
{
}
 */
