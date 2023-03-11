/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2021  Luis Claudio Gamboa Lopes

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

void PIC16F887_map(_pic* pic) {
    memset(&pic->P16map, 0, sizeof(P16map_t));

    pic->P16map.INDF = &pic->ram[0x0];
    pic->P16map.TMR0 = &pic->ram[0x1];
    pic->P16map.PCL = &pic->ram[0x2];
    pic->P16map.STATUS = &pic->ram[0x3];
    pic->P16map.FSR = &pic->ram[0x4];
    pic->P16map.PORTA = &pic->ram[0x5];
    pic->P16map.PORTB = &pic->ram[0x6];
    pic->P16map.PORTC = &pic->ram[0x7];
    pic->P16map.PORTD = &pic->ram[0x8];
    pic->P16map.PORTE = &pic->ram[0x9];
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
    pic->P16map.RCSTA = &pic->ram[0x18];
    pic->P16map.TXREG = &pic->ram[0x19];
    pic->P16map.RCREG = &pic->ram[0x1A];
    pic->P16map.CCPR2L = &pic->ram[0x1B];
    pic->P16map.CCPR2H = &pic->ram[0x1C];
    pic->P16map.CCP2CON = &pic->ram[0x1D];
    pic->P16map.ADRESH = &pic->ram[0x1E];
    pic->P16map.ADCON0 = &pic->ram[0x1F];
    pic->P16map.OPTION_REG = &pic->ram[0x81];
    pic->P16map.TRISA = &pic->ram[0x85];
    pic->P16map.TRISB = &pic->ram[0x86];
    pic->P16map.TRISC = &pic->ram[0x87];
    pic->P16map.TRISD = &pic->ram[0x88];
    pic->P16map.TRISE = &pic->ram[0x89];
    pic->P16map.PIE1 = &pic->ram[0x8C];
    pic->P16map.PIE2 = &pic->ram[0x8D];
    // pic->P16map.PCON = &pic->ram[0x8E];
    // pic->P16map.OSCCON = &pic->ram[0x8F];
    // pic->P16map.OSCTUNE = &pic->ram[0x90];
    pic->P16map.SSPCON2 = &pic->ram[0x91];
    pic->P16map.PR2 = &pic->ram[0x92];
    pic->P16map.SSPADD = &pic->ram[0x93];
    pic->P16map.SSPSTAT = &pic->ram[0x94];
    // pic->P16map.WPUB = &pic->ram[0x95];
    // pic->P16map.IOCB = &pic->ram[0x96];
    // pic->P16map.VRCON = &pic->ram[0x97];
    pic->P16map.TXSTA = &pic->ram[0x98];
    pic->P16map.SPBRG = &pic->ram[0x99];
    pic->P16map.SPBRGH = &pic->ram[0x9A];
    // pic->P16map.PWM1CON = &pic->ram[0x9B];
    // pic->P16map.ECCPAS = &pic->ram[0x9C];
    // pic->P16map.PSTRCON = &pic->ram[0x9D];
    pic->P16map.ADRESL = &pic->ram[0x9E];
    pic->P16map.ADCON1 = &pic->ram[0x9F];
    // pic->P16map.WDTCON = &pic->ram[0x105];
    // pic->P16map.CM1CON0 = &pic->ram[0x107];
    // pic->P16map.CM2CON0 = &pic->ram[0x108];
    // pic->P16map.CM2CON1 = &pic->ram[0x109];
    pic->P16map.EEDATA = &pic->ram[0x10C];
    pic->P16map.EEADR = &pic->ram[0x10D];
    pic->P16map.EEDATH = &pic->ram[0x10E];
    pic->P16map.EEADRH = &pic->ram[0x10F];
    // pic->P16map.SRCON = &pic->ram[0x185];
    pic->P16map.BAUDCTL = &pic->ram[0x187];
    pic->P16map.ANSEL = &pic->ram[0x188];
    pic->P16map.ANSELH = &pic->ram[0x189];
    pic->P16map.EECON1 = &pic->ram[0x18C];
    pic->P16map.EECON2 = &pic->ram[0x18D];
}

/*PINS

01 - RE3 nMCLR VPP
02 - RA0 AN0 ULPWU C12IN0-
03 - RA1 AN1 C12IN1-
04 - RA2 AN2 VREF- CVREF C2IN+
05 - RA3 AN3 VREF+ C1IN+
06 - RA4 T0CKI C1OUT
07 - RA5 AN4 nSS C2OUT
08 - RE0 AN5
09 - RE1 AN6
10 - RE2 AN7
11 - VDD
12 - VSS
13 - RA7 OSC1 CLKIN
14 - RA6 OSC2 CLKOUT
15 - RC0 T1OSO T1CKI
16 - RC1 T1OSCI CCP2
17 - RC2 P1A CCP1
18 - RC3 SCK SCL
19 - RD0
20 - RD1
21 - RD2
22 - RD3
23 - RC4 SDI SDA
24 - RC5 SDO
25 - RC6 TX CK
26 - RC7 RX DT
27 - RD4
28 - RD5 P1B
29 - RD6 P1C
30 - RD7 P1D
31 - VSS
32 - VDD
33 - RB0 AN12 INT
34 - RB1 AN10 C12IN3-
35 - RB2 AN8
36 - RB3 AN9 PGM C12IN2-
37 - RB4 AN11
38 - RB5 AN13 T1G
39 - RB6 ICSPCLK
40 - RB7 ICSPDAT
 */

#include "../p16/p16_periferic.h"

/*
======================
Family=P16
processor=PIC16F887
deviceid=0x2080
 */

void PIC16F887_reset(_pic* pic) {
    pic->pins[0].port = pic->P16map.PORTE;
    pic->pins[0].pord = 3;
    pic->pins[1].port = pic->P16map.PORTA;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P16map.PORTA;
    pic->pins[2].pord = 1;
    pic->pins[3].port = pic->P16map.PORTA;
    pic->pins[3].pord = 2;
    pic->pins[4].port = pic->P16map.PORTA;
    pic->pins[4].pord = 3;
    pic->pins[5].port = pic->P16map.PORTA;
    pic->pins[5].pord = 4;
    pic->pins[6].port = pic->P16map.PORTA;
    pic->pins[6].pord = 5;
    pic->pins[7].port = pic->P16map.PORTE;
    pic->pins[7].pord = 0;
    pic->pins[8].port = pic->P16map.PORTE;
    pic->pins[8].pord = 1;
    pic->pins[9].port = pic->P16map.PORTE;
    pic->pins[9].pord = 2;
    pic->pins[10].port = P_VDD;
    pic->pins[10].pord = -1;
    pic->pins[10].value = 1;
    pic->pins[11].port = P_VSS;
    pic->pins[11].pord = -1;
    pic->pins[12].port = pic->P16map.PORTA;
    pic->pins[12].pord = 7;
    pic->pins[13].port = pic->P16map.PORTA;
    pic->pins[13].pord = 6;
    pic->pins[14].port = pic->P16map.PORTC;
    pic->pins[14].pord = 0;
    pic->pins[15].port = pic->P16map.PORTC;
    pic->pins[15].pord = 1;
    pic->pins[16].port = pic->P16map.PORTC;
    pic->pins[16].pord = 2;
    pic->pins[17].port = pic->P16map.PORTC;
    pic->pins[17].pord = 3;
    pic->pins[18].port = pic->P16map.PORTD;
    pic->pins[18].pord = 0;
    pic->pins[19].port = pic->P16map.PORTD;
    pic->pins[19].pord = 1;
    pic->pins[20].port = pic->P16map.PORTD;
    pic->pins[20].pord = 2;
    pic->pins[21].port = pic->P16map.PORTD;
    pic->pins[21].pord = 3;
    pic->pins[22].port = pic->P16map.PORTC;
    pic->pins[22].pord = 4;
    pic->pins[23].port = pic->P16map.PORTC;
    pic->pins[23].pord = 5;
    pic->pins[24].port = pic->P16map.PORTC;
    pic->pins[24].pord = 6;
    pic->pins[25].port = pic->P16map.PORTC;
    pic->pins[25].pord = 7;
    pic->pins[26].port = pic->P16map.PORTD;
    pic->pins[26].pord = 4;
    pic->pins[27].port = pic->P16map.PORTD;
    pic->pins[27].pord = 5;
    pic->pins[28].port = pic->P16map.PORTD;
    pic->pins[28].pord = 6;
    pic->pins[29].port = pic->P16map.PORTD;
    pic->pins[29].pord = 7;
    pic->pins[30].port = P_VSS;
    pic->pins[30].pord = -1;
    pic->pins[31].port = P_VDD;
    pic->pins[31].pord = -1;
    pic->pins[31].value = 1;
    pic->pins[32].port = pic->P16map.PORTB;
    pic->pins[32].pord = 0;
    pic->pins[33].port = pic->P16map.PORTB;
    pic->pins[33].pord = 1;
    pic->pins[34].port = pic->P16map.PORTB;
    pic->pins[34].pord = 2;
    pic->pins[35].port = pic->P16map.PORTB;
    pic->pins[35].pord = 3;
    pic->pins[36].port = pic->P16map.PORTB;
    pic->pins[36].pord = 4;
    pic->pins[37].port = pic->P16map.PORTB;
    pic->pins[37].pord = 5;
    pic->pins[38].port = pic->P16map.PORTB;
    pic->pins[38].pord = 6;
    pic->pins[39].port = pic->P16map.PORTB;
    pic->pins[39].pord = 7;

    pic->mclr = 1;

    pic->ccp[0].pin = 17;
    pic->ccp[1].pin = 16;

    pic->adc[0] = 2;
    pic->adc[1] = 3;
    pic->adc[2] = 4;
    pic->adc[3] = 5;
    pic->adc[4] = 7;
    pic->adc[5] = 8;
    pic->adc[6] = 9;
    pic->adc[7] = 10;
    pic->adc[8] = 35;
    pic->adc[9] = 36;
    pic->adc[10] = 34;
    pic->adc[11] = 37;
    pic->adc[12] = 33;
    pic->adc[13] = 38;

    pic->usart_rx[0] = 26;
    pic->usart_tx[0] = 25;

    pic->pgc = 39;
    pic->pgd = 40;

    pic->sck = 18;
    pic->sdo = 24;
    pic->sdi = 23;

    pic->t0cki = 6;
    pic->t1cki = 15;

    pic->int0 = 33;
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
    p16_uart_rst(pic);
}

void PIC16F887_periferic(_pic* pic) {
    p16_mssp(pic);
    p16_adc_2(pic);
    p16_int_pin(pic);
    p16_int_portb_2(pic);
    p16_tmr0(pic);
    p16_wdt(pic);
    p16_eeprom_2(pic);
    p16_tmr1(pic);
    p16_tmr2(pic);
    p16_uart(pic, 0);
}

int PIC16F887_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[0] & 0x0020) > 0);
            break;
        case CFG_WDT:
            return ((pic->config[0] & 0x0008) > 0);
            break;
        case CFG_DEBUG:
            return ((pic->config[0] & 0x2000) == 0);
            break;
    }
    return 0;
}

void PIC16F887_disable_debug(_pic* pic) {
    pic->config[0] |= 0x2000;
}

void PIC16F887_stop(_pic* pic) {
    p16_uart_stop(pic, 0);
}

void PIC16F887_start(_pic* pic) {
    pic->ROMSIZE = 8192;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 512;
    pic->PINCOUNT = 40;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 2;
    pic->STACKSIZE = 8;
    pic->CCPCOUNT = 2;
    pic->ADCCOUNT = 14;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F887_reset;
    pic->mmap = PIC16F887_map;
    pic->getconf = PIC16F887_getconf;
    pic->periferic = PIC16F887_periferic;
    pic->stop = PIC16F887_stop;
    pic->disable_debug = PIC16F887_disable_debug;

    p16_uart_start(pic, 0);
}

init_pic(PIC16F887, P16, 0x2080);
