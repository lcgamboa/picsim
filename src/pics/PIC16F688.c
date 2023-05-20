/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2023  Luis Claudio Gamboa Lopes

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

#include <string.h>
#include "../../include/picsim.h"

void PIC16F688_map(_pic* pic) {
    memset(&pic->P16map, 0, sizeof(P16map_t));

    pic->P16map.INDF = &pic->ram[0x0];
    pic->P16map.TMR0 = &pic->ram[0x1];
    pic->P16map.PCL = &pic->ram[0x2];
    pic->P16map.STATUS = &pic->ram[0x3];
    pic->P16map.FSR = &pic->ram[0x4];
    pic->P16map.PORTA = &pic->ram[0x5];
    pic->P16map.PORTC = &pic->ram[0x7];
    pic->P16map.PCLATH = &pic->ram[0xA];
    pic->P16map.INTCON = &pic->ram[0xB];
    pic->P16map.PIR1 = &pic->ram[0xC];
    pic->P16map.TMR1L = &pic->ram[0xE];
    pic->P16map.TMR1H = &pic->ram[0xF];
    pic->P16map.T1CON = &pic->ram[0x10];
    pic->P16map.BAUDCTL = &pic->ram[0x11];
    pic->P16map.SPBRGH = &pic->ram[0x12];
    pic->P16map.SPBRG = &pic->ram[0x13];
    pic->P16map.RCREG = &pic->ram[0x14];
    pic->P16map.TXREG = &pic->ram[0x15];
    pic->P16map.TXSTA = &pic->ram[0x16];
    pic->P16map.RCSTA = &pic->ram[0x17];
    //pic->P16map.WDTCON = &pic->ram[0x18];
    //pic->P16map.CMCON0 = &pic->ram[0x19];
    //pic->P16map.CMCON1 = &pic->ram[0x1A];
    pic->P16map.ADRESH = &pic->ram[0x1E];
    pic->P16map.ADCON0 = &pic->ram[0x1F];
    pic->P16map.OPTION_REG = &pic->ram[0x81];
    pic->P16map.TRISA = &pic->ram[0x85];
    pic->P16map.TRISC = &pic->ram[0x87];
    pic->P16map.PIE1 = &pic->ram[0x8C];
    //pic->P16map.PCON = &pic->ram[0x8E];
    //pic->P16map.OSCCON = &pic->ram[0x8F];
    //pic->P16map.OSCTUNE = &pic->ram[0x90];
    pic->P16map.ANSEL = &pic->ram[0x91];
    //pic->P16map.WPUA = &pic->ram[0x95];
    //pic->P16map.IOCA = &pic->ram[0x96];
    pic->P16map.EEDATH = &pic->ram[0x97];
    pic->P16map.EEADRH = &pic->ram[0x98];
    //pic->P16map.VRCON = &pic->ram[0x99];
    pic->P16map.EEDATA = &pic->ram[0x9A];
    pic->P16map.EEADR = &pic->ram[0x9B];
    pic->P16map.EECON1 = &pic->ram[0x9C];
    pic->P16map.EECON2 = &pic->ram[0x9D];
    pic->P16map.ADRESL = &pic->ram[0x9E];
    pic->P16map.ADCON1 = &pic->ram[0x9F];
}

/*PINS

01 - Vdd
02 - RA5 T1CKI OSC1 CLKIN
03 - RA4 AN3 T1G OSC2 CLKOUT
04 - RA3 MCLR Vpp
05 - RC5 RX DT
06 - RC4 C2OUT TX CK
07 - RC3 AN7
08 - RC2 AN6
09 - RC1 AN5 C2IN-
10 - RC0 AN4 C2IN+
11 - RA2 AN2 T0CKI INT C1OUT
12 - RA1 AN1 C1IN- Vref ICSPCLK
13 - RA0 AN0 C1IN+ ICSPDAT ULPWU
14 - Vss
 */

#include "../p16/p16_periferic.h"

/*
======================
Family=P16
processor=PIC16F688
deviceid=0x1180
 */

void PIC16F688_reset(_pic* pic) {
    pic->pins[0].port = P_VDD;
    pic->pins[0].pord = -1;
    pic->pins[0].value = 1;
    pic->pins[1].port = pic->P16map.PORTA;
    pic->pins[1].pord = 5;
    pic->pins[2].port = pic->P16map.PORTA;
    pic->pins[2].pord = 4;
    pic->pins[3].port = pic->P16map.PORTA;
    pic->pins[3].pord = 3;
    pic->pins[4].port = pic->P16map.PORTC;
    pic->pins[4].pord = 5;
    pic->pins[5].port = pic->P16map.PORTC;
    pic->pins[5].pord = 4;
    pic->pins[6].port = pic->P16map.PORTC;
    pic->pins[6].pord = 3;
    pic->pins[7].port = pic->P16map.PORTC;
    pic->pins[7].pord = 2;
    pic->pins[8].port = pic->P16map.PORTC;
    pic->pins[8].pord = 1;
    pic->pins[9].port = pic->P16map.PORTC;
    pic->pins[9].pord = 0;
    pic->pins[10].port = pic->P16map.PORTA;
    pic->pins[10].pord = 2;
    pic->pins[11].port = pic->P16map.PORTA;
    pic->pins[11].pord = 1;
    pic->pins[12].port = pic->P16map.PORTA;
    pic->pins[12].pord = 0;
    pic->pins[13].port = P_VSS;
    pic->pins[13].pord = -1;

    pic->mclr = 4;

    pic->adc[0] = 13;
    pic->adc[1] = 12;
    pic->adc[2] = 11;
    pic->adc[3] = 3;
    pic->adc[4] = 10;
    pic->adc[5] = 9;
    pic->adc[6] = 8;
    pic->adc[7] = 7;

    pic->usart_rx[0] = 5;
    pic->usart_tx[0] = 6;

    pic->pgc = 12;
    pic->pgd = 13;

    pic->sck = 0;
    pic->sdo = 0;
    pic->sdi = 0;

    pic->t0cki = 11;
    pic->t1cki = 2;

    pic->int0 = 11;
    pic->int1 = 0;
    pic->int2 = 0;

    p16_tmr0_rst(pic);
    p16_tmr1_rst(pic);
    p16_adc_rst(pic);
    p16_wdt_rst(pic);
    p16_eeprom_rst(pic);
    p16_int_pin_rst(pic);
    p16_uart_rst(pic);
}

void PIC16F688_periferic(_pic* pic) {
    p16_adc_2(pic);
    p16_int_pin(pic);
    p16_tmr0(pic);
    p16_wdt(pic);
    p16_eeprom(pic);
    p16_tmr1(pic);
    p16_uart(pic, 0);
}

int PIC16F688_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[0] & 0x0020) > 0);
            break;
        case CFG_WDT:
            return ((pic->config[0] & 0x0008) > 0);
            break;
    }
    return 0;
}

void PIC16F688_disable_debug(_pic* pic) {}

void PIC16F688_stop(_pic* pic) {
    p16_uart_stop(pic, 0);
}

void PIC16F688_start(_pic* pic) {
    pic->ROMSIZE = 4096;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 512;
    pic->PINCOUNT = 14;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 1;
    pic->STACKSIZE = 8;
    pic->CCPCOUNT = 0;
    pic->ADCCOUNT = 8;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F688_reset;
    pic->mmap = PIC16F688_map;
    pic->getconf = PIC16F688_getconf;
    pic->periferic = PIC16F688_periferic;
    pic->stop = PIC16F688_stop;
    pic->disable_debug = PIC16F688_disable_debug;

    p16_uart_start(pic, 0);
}

init_pic(PIC16F688, P16, 0x1180);
