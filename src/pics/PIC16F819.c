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

void PIC16F819_map(_pic* pic) {
    memset(&pic->P16map, 0, sizeof(P16map_t));

    pic->P16map.INDF = &pic->ram[0x0];
    pic->P16map.TMR0 = &pic->ram[0x1];
    pic->P16map.PCL = &pic->ram[0x2];
    pic->P16map.STATUS = &pic->ram[0x3];
    pic->P16map.FSR = &pic->ram[0x4];
    pic->P16map.PORTA = &pic->ram[0x5];
    pic->P16map.PORTB = &pic->ram[0x6];
    pic->P16map.PCLATH = &pic->ram[0xA];
    pic->P16map.INTCON = &pic->ram[0xB];
    pic->P16map.PIR1 = &pic->ram[0xC];
    pic->P16map.PIR2 = &pic->ram[0xD];
    pic->P16map.TMR1L = &pic->ram[0xE];
    pic->P16map.TMR1H = &pic->ram[0xF];
    pic->P16map.T1CON = &pic->ram[0x10];
    pic->P16map.TMR2 = &pic->ram[0x11];
    pic->P16map.T2CON = &pic->ram[0x12];
    pic->P16map.SSPBUF = &pic->ram[0x13];
    pic->P16map.SSPCON = &pic->ram[0x14];
    pic->P16map.CCPR1L = &pic->ram[0x15];
    pic->P16map.CCPR1H = &pic->ram[0x16];
    pic->P16map.CCP1CON = &pic->ram[0x17];
    pic->P16map.ADRESH = &pic->ram[0x1E];
    pic->P16map.ADCON0 = &pic->ram[0x1F];
    pic->P16map.OPTION_REG = &pic->ram[0x81];
    pic->P16map.TRISA = &pic->ram[0x85];
    pic->P16map.TRISB = &pic->ram[0x86];
    pic->P16map.PIE1 = &pic->ram[0x8C];
    pic->P16map.PIE2 = &pic->ram[0x8D];
    // pic->P16map.PCON = &pic->ram[0x8E];
    // pic->P16map.OSCCON = &pic->ram[0x8F];
    // pic->P16map.OSCTUNE = &pic->ram[0x90];
    pic->P16map.PR2 = &pic->ram[0x92];
    pic->P16map.SSPADD = &pic->ram[0x93];
    pic->P16map.SSPSTAT = &pic->ram[0x94];
    pic->P16map.ADRESL = &pic->ram[0x9E];
    pic->P16map.ADCON1 = &pic->ram[0x9F];
    pic->P16map.EEDATA = &pic->ram[0x10C];
    pic->P16map.EEADR = &pic->ram[0x10D];
    pic->P16map.EEDATH = &pic->ram[0x10E];
    pic->P16map.EEADRH = &pic->ram[0x10F];
    pic->P16map.EECON1 = &pic->ram[0x18C];
    pic->P16map.EECON2 = &pic->ram[0x18D];
}

/*PINS

01 - RA2 AN2 Vref-
02 - RA3 AN3 Vref+
03 - RA4 AN4 T0CKI
04 - RA5 MCLR Vpp
05 - Vss
06 - RB0 INT
07 - RB1 SDI SDA
08 - RB2 SDO CCP1
09 - RB3 CCP1 PGM
10 - RB4 SCK SCL
11 - RB5 SS
12 - RB6 T1OSO T1CKI PGC
13 - RB7 T1OSI PGD
14 - Vdd
15 - RA6 OSC2 CLKO
16 - RA7 OSC1 CLKI
17 - RA0 AN0
18 - RA1 AN1
 */

#include "../p16/p16_periferic.h"

/*
======================
Family=P16
processor=PIC16F819
deviceid=0x4e0
 */

void PIC16F819_reset(_pic* pic) {
    pic->pins[0].port = pic->P16map.PORTA;
    pic->pins[0].pord = 2;
    pic->pins[1].port = pic->P16map.PORTA;
    pic->pins[1].pord = 3;
    pic->pins[2].port = pic->P16map.PORTA;
    pic->pins[2].pord = 4;
    pic->pins[3].port = pic->P16map.PORTA;
    pic->pins[3].pord = 5;
    pic->pins[4].port = P_VSS;
    pic->pins[4].pord = -1;
    pic->pins[5].port = pic->P16map.PORTB;
    pic->pins[5].pord = 0;
    pic->pins[6].port = pic->P16map.PORTB;
    pic->pins[6].pord = 1;
    pic->pins[7].port = pic->P16map.PORTB;
    pic->pins[7].pord = 2;
    pic->pins[8].port = pic->P16map.PORTB;
    pic->pins[8].pord = 3;
    pic->pins[9].port = pic->P16map.PORTB;
    pic->pins[9].pord = 4;
    pic->pins[10].port = pic->P16map.PORTB;
    pic->pins[10].pord = 5;
    pic->pins[11].port = pic->P16map.PORTB;
    pic->pins[11].pord = 6;
    pic->pins[12].port = pic->P16map.PORTB;
    pic->pins[12].pord = 7;
    pic->pins[13].port = P_VDD;
    pic->pins[13].pord = -1;
    pic->pins[13].value = 1;
    pic->pins[14].port = pic->P16map.PORTA;
    pic->pins[14].pord = 6;
    pic->pins[15].port = pic->P16map.PORTA;
    pic->pins[15].pord = 7;
    pic->pins[16].port = pic->P16map.PORTA;
    pic->pins[16].pord = 0;
    pic->pins[17].port = pic->P16map.PORTA;
    pic->pins[17].pord = 1;

    pic->mclr = 4;

    pic->ccp[0].pin = 9;

    pic->adc[0] = 17;
    pic->adc[1] = 18;
    pic->adc[2] = 1;
    pic->adc[3] = 2;
    pic->adc[4] = 3;

    pic->usart_rx[0] = 0;
    pic->usart_tx[0] = 0;

    pic->pgc = 12;
    pic->pgd = 13;

    pic->sck = 10;
    pic->sdo = 8;
    pic->sdi = 7;

    pic->t0cki = 3;
    pic->t1cki = 12;

    pic->int0 = 6;
    pic->int1 = 0;
    pic->int2 = 0;

    p16_tmr0_rst(pic);
    p16_tmr1_rst(pic);
    p16_tmr2_rst(pic);
    p16_adc_rst(pic);
    p16_wdt_rst(pic);
    p16_eeprom_rst(pic);
    p16_mssp_rst(pic);
    p16_int_pin_rst(pic);
    p16_int_portb_rst(pic);
    // p16_int_ports_rst (pic);
    // p16_uart_rst(pic);
}

void PIC16F819_periferic(_pic* pic) {
    p16_mssp(pic);
    p16_adc(pic);
    p16_int_pin(pic);
    p16_int_portb(pic);
    // p16_int_ports (pic);
    p16_tmr0(pic);
    p16_wdt(pic);
    p16_eeprom(pic);
    p16_tmr1(pic);
    p16_tmr2(pic);
    // p16_uart(pic, 0);
}

int PIC16F819_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[0] & 0x0020) > 0);
            break;
        case CFG_WDT:
            break;
        case CFG_WDT_DIV:
            break;
        case CFG_DEBUG:
            return ((pic->config[0] & 0x0800) == 0);
            break;
    }
    return 0;
}

void PIC16F819_disable_debug(_pic* pic) {
    pic->config[0] |= 0x0800;
}

void PIC16F819_stop(_pic* pic) {
    p16_uart_stop(pic, 0);
}

void PIC16F819_start(_pic* pic) {
    pic->ROMSIZE = 2048;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 512;
    pic->PINCOUNT = 18;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 1;
    pic->STACKSIZE = 8;
    pic->CCPCOUNT = 1;
    pic->ADCCOUNT = 5;
    pic->USARTCOUNT = 0;
    pic->WDT_MS = 18;
    pic->reset = PIC16F819_reset;
    pic->mmap = PIC16F819_map;
    pic->getconf = PIC16F819_getconf;
    pic->periferic = PIC16F819_periferic;
    pic->stop = PIC16F819_stop;
    pic->disable_debug = PIC16F819_disable_debug;

    p16_uart_start(pic, 0);
}

init_pic(PIC16F819, P16, 0x4e0);
