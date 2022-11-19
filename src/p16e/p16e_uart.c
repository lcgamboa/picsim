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

#include "../../include/periferic16e.h"
#include "../../include/picsim.h"
#include <stdio.h>

void p16e_uart_rst(_pic *pic) {
  pic->serial[0].serial_PIR = pic->P16Emap.PIR1;
  pic->serial[0].serial_PIE = pic->P16Emap.PIE1;
  pic->serial[0].RXIF_mask = 0x20;
  pic->serial[0].TXIF_mask = 0x10;
  pic->serial[0].serial_TXSTA = pic->P16Emap.TXSTA;
  pic->serial[0].serial_RCSTA = pic->P16Emap.RCSTA;
  pic->serial[0].serial_SPBRG = pic->P16Emap.SP1BRGL;
  pic->serial[0].serial_SPBRGH = pic->P16Emap.SP1BRGH;
  pic->serial[0].serial_BAUDCTL = pic->P16Emap.BAUDCON1;
  pic->serial[0].serial_RCREG = pic->P16Emap.RCREG;
  pic->serial[0].serial_TXREG = pic->P16Emap.TXREG;
  pic->serial[0].serial_TXREG_ADDR = sfr_addr(pic->P16Emap.TXREG);
  pic->serial[0].serial_RCSTA_ADDR = sfr_addr(pic->P16Emap.RCSTA);
  pic->serial[0].serial_RCREG_ADDR = sfr_addr(pic->P16Emap.RCREG);
  pic->serial[0].serial_TRIS_RX =
      &pic->ram[sfr_addr(pic->pins[pic->usart_rx[0] - 1].port) +
                (sfr_addr(pic->P16Emap.TRISA) - sfr_addr(pic->P16Emap.PORTA))];
  pic->serial[0].serial_TRIS_RX_MASK =
      (0x01 << pic->pins[pic->usart_rx[0] - 1].pord);
  pic->serial[0].s_open = 1;

  bb_uart_rst(&pic->serial[0].bbuart);
}

void p16e_uart_rst_2(_pic *pic) {
  pic->serial[0].serial_PIR = pic->P16Emap.PIR1;
  pic->serial[0].serial_PIE = pic->P16Emap.PIE1;
  pic->serial[0].RXIF_mask = 0x20;
  pic->serial[0].TXIF_mask = 0x10;
  pic->serial[0].serial_TXSTA = pic->P16Emap.TX1STA;
  pic->serial[0].serial_RCSTA = pic->P16Emap.RC1STA;
  pic->serial[0].serial_SPBRG = pic->P16Emap.SP1BRGL;
  pic->serial[0].serial_SPBRGH = pic->P16Emap.SP1BRGH;
  pic->serial[0].serial_BAUDCTL = pic->P16Emap.BAUDCON1;
  pic->serial[0].serial_RCREG = pic->P16Emap.RC1REG;
  pic->serial[0].serial_TXREG = pic->P16Emap.TX1REG;
  pic->serial[0].serial_TXREG_ADDR = sfr_addr(pic->P16Emap.TX1REG);
  pic->serial[0].serial_RCSTA_ADDR = sfr_addr(pic->P16Emap.RC1STA);
  pic->serial[0].serial_RCREG_ADDR = sfr_addr(pic->P16Emap.RC1REG);
  pic->serial[0].serial_TRIS_RX =
      &pic->ram[sfr_addr(pic->pins[pic->usart_rx[0] - 1].port) +
                (sfr_addr(pic->P16Emap.TRISA) - sfr_addr(pic->P16Emap.PORTA))];
  pic->serial[0].serial_TRIS_RX_MASK =
      (0x01 << pic->pins[pic->usart_rx[0] - 1].pord);
  pic->serial[0].s_open = 1;

  bb_uart_rst(&pic->serial[0].bbuart);
}

/*
void
p16e_uart(void)
{
}
 */
