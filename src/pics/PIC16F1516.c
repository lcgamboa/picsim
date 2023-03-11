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

void PIC16F1516_map(_pic* pic) {
    memset(&pic->P16Emap, 0, sizeof(P16Emap_t));

    pic->P16Emap.INDF0 = &pic->ram[0x0];
    pic->P16Emap.INDF1 = &pic->ram[0x1];
    pic->P16Emap.PCL = &pic->ram[0x2];
    pic->P16Emap.STATUS = &pic->ram[0x3];
    pic->P16Emap.FSR0L = &pic->ram[0x4];
    pic->P16Emap.FSR0H = &pic->ram[0x5];
    pic->P16Emap.FSR1L = &pic->ram[0x6];
    pic->P16Emap.FSR1H = &pic->ram[0x7];
    pic->P16Emap.BSR = &pic->ram[0x8];
    pic->P16Emap.WREG = &pic->ram[0x9];
    pic->P16Emap.PCLATH = &pic->ram[0xA];
    pic->P16Emap.INTCON = &pic->ram[0xB];
    pic->P16Emap.PORTA = &pic->ram[0xC];
    pic->P16Emap.PORTB = &pic->ram[0xD];
    pic->P16Emap.PORTC = &pic->ram[0xE];
    pic->P16Emap.PORTE = &pic->ram[0x10];
    pic->P16Emap.PIR1 = &pic->ram[0x11];
    pic->P16Emap.PIR2 = &pic->ram[0x12];
    pic->P16Emap.TMR0 = &pic->ram[0x15];
    pic->P16Emap.TMR1L = &pic->ram[0x16];
    pic->P16Emap.TMR1H = &pic->ram[0x17];
    pic->P16Emap.T1CON = &pic->ram[0x18];
    // pic->P16Emap.T1GCON = &pic->ram[0x19];
    pic->P16Emap.TMR2 = &pic->ram[0x1A];
    pic->P16Emap.PR2 = &pic->ram[0x1B];
    pic->P16Emap.T2CON = &pic->ram[0x1C];
    pic->P16Emap.TRISA = &pic->ram[0x8C];
    pic->P16Emap.TRISB = &pic->ram[0x8D];
    pic->P16Emap.TRISC = &pic->ram[0x8E];
    pic->P16Emap.TRISE = &pic->ram[0x90];
    pic->P16Emap.PIE1 = &pic->ram[0x91];
    pic->P16Emap.PIE2 = &pic->ram[0x92];
    pic->P16Emap.OPTION_REG = &pic->ram[0x95];
    // pic->P16Emap.PCON = &pic->ram[0x96];
    pic->P16Emap.WDTCON = &pic->ram[0x97];
    // pic->P16Emap.OSCCON = &pic->ram[0x99];
    // pic->P16Emap.OSCSTAT = &pic->ram[0x9A];
    pic->P16Emap.ADRESL = &pic->ram[0x9B];
    pic->P16Emap.ADRESH = &pic->ram[0x9C];
    pic->P16Emap.ADCON0 = &pic->ram[0x9D];
    pic->P16Emap.ADCON1 = &pic->ram[0x9E];
    pic->P16Emap.LATA = &pic->ram[0x10C];
    pic->P16Emap.LATB = &pic->ram[0x10D];
    pic->P16Emap.LATC = &pic->ram[0x10E];
    /*
    pic->P16Emap.BORCON = &pic->ram[0x116];
    pic->P16Emap.FVRCON = &pic->ram[0x117];
    pic->P16Emap.APFCON = &pic->ram[0x11D];
    */
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELB = &pic->ram[0x18D];
    pic->P16Emap.ANSELC = &pic->ram[0x18E];
    /*
    pic->P16Emap.PMADRL = &pic->ram[0x191];
    pic->P16Emap.PMADRH = &pic->ram[0x192];
    pic->P16Emap.PMDATL = &pic->ram[0x193];
    pic->P16Emap.PMDATH = &pic->ram[0x194];
    pic->P16Emap.PMCON1 = &pic->ram[0x195];
    pic->P16Emap.PMCON2 = &pic->ram[0x196];
    pic->P16Emap.VREGCON = &pic->ram[0x197];
    */
    pic->P16Emap.RCREG = &pic->ram[0x199];
    pic->P16Emap.TXREG = &pic->ram[0x19A];
    pic->P16Emap.SP1BRGL = &pic->ram[0x19B];
    pic->P16Emap.SP1BRGH = &pic->ram[0x19C];
    pic->P16Emap.RCSTA = &pic->ram[0x19D];
    pic->P16Emap.TXSTA = &pic->ram[0x19E];
    pic->P16Emap.BAUDCON1 = &pic->ram[0x19F];
    /*
    pic->P16Emap.WPUB = &pic->ram[0x20D];
    pic->P16Emap.WPUE = &pic->ram[0x210];
    */
    pic->P16Emap.SSP1BUF = &pic->ram[0x211];
    pic->P16Emap.SSP1ADD = &pic->ram[0x212];
    // pic->P16Emap.SSP1MSK = &pic->ram[0x213];
    pic->P16Emap.SSP1STAT = &pic->ram[0x214];
    pic->P16Emap.SSP1CON1 = &pic->ram[0x215];
    /*
    pic->P16Emap.SSPCON2 = &pic->ram[0x216];
    pic->P16Emap.SSPCON3 = &pic->ram[0x217];
    */
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    pic->P16Emap.CCPR2L = &pic->ram[0x298];
    pic->P16Emap.CCPR2H = &pic->ram[0x299];
    pic->P16Emap.CCP2CON = &pic->ram[0x29A];
    pic->P16Emap.IOCBP = &pic->ram[0x394];
    pic->P16Emap.IOCBN = &pic->ram[0x395];
    pic->P16Emap.IOCBF = &pic->ram[0x396];
    pic->P16Emap.STATUS_SHAD = &pic->ram[0xFE4];
    pic->P16Emap.WREG_SHAD = &pic->ram[0xFE5];
    pic->P16Emap.BSR_SHAD = &pic->ram[0xFE6];
    pic->P16Emap.PCLATH_SHAD = &pic->ram[0xFE7];
    pic->P16Emap.FSR0L_SHAD = &pic->ram[0xFE8];
    pic->P16Emap.FSR0H_SHAD = &pic->ram[0xFE9];
    pic->P16Emap.FSR1L_SHAD = &pic->ram[0xFEA];
    pic->P16Emap.FSR1H_SHAD = &pic->ram[0xFEB];
    pic->P16Emap.STKPTR = &pic->ram[0xFED];
    pic->P16Emap.TOSL = &pic->ram[0xFEE];
    pic->P16Emap.TOSH = &pic->ram[0xFEF];
}

/*PINS

01 - RE3 MCLR Vpp
02 - RA0 AN0 SS
03 - RA1 AN1
04 - RA2 AN2
05 - RA3 AN3 Vref+
06 - RA4 T0CKI
07 - RA5 AN4 SS Vcap
08 - Vss
09 - RA7 OSC1 CLKIN
10 - RA6 OSC2 CLKOUT
11 - RC0 SOSCO T1CKI
12 - RC1 SOSCI CCP2
13 - RC2 AN14 CCP1
14 - RC3 AN15 SCK SCL
15 - RC4 AN16 SDI SDA
16 - RC5 AN17 SDO
17 - RC6 AN18 TX CK
18 - RC7 AN19 RX DT
19 - Vss
20 - Vdd
21 - RB0 AN12 INT
22 - RB1 AN10
23 - RB2 AN8
24 - RB3 AN9 CCP2
25 - RB4 AN11
26 - RB5 AN13 T1G
27 - RB6 ICSPCLK ICDCLK
28 - RB7 ICSPDAT ICDDAT
 */

#include "../p16e/p16e_periferic.h"

/*
======================
Family=P16E
processor=PIC16F1516
deviceid=0x1680
 */

void PIC16F1516_reset(_pic* pic) {
    pic->pins[0].port = pic->P16Emap.PORTE;
    pic->pins[0].pord = 3;
    pic->pins[1].port = pic->P16Emap.PORTA;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P16Emap.PORTA;
    pic->pins[2].pord = 1;
    pic->pins[3].port = pic->P16Emap.PORTA;
    pic->pins[3].pord = 2;
    pic->pins[4].port = pic->P16Emap.PORTA;
    pic->pins[4].pord = 3;
    pic->pins[5].port = pic->P16Emap.PORTA;
    pic->pins[5].pord = 4;
    pic->pins[6].port = pic->P16Emap.PORTA;
    pic->pins[6].pord = 5;
    pic->pins[7].port = P_VSS;
    pic->pins[7].pord = -1;
    pic->pins[8].port = pic->P16Emap.PORTA;
    pic->pins[8].pord = 7;
    pic->pins[9].port = pic->P16Emap.PORTA;
    pic->pins[9].pord = 6;
    pic->pins[10].port = pic->P16Emap.PORTC;
    pic->pins[10].pord = 0;
    pic->pins[11].port = pic->P16Emap.PORTC;
    pic->pins[11].pord = 1;
    pic->pins[12].port = pic->P16Emap.PORTC;
    pic->pins[12].pord = 2;
    pic->pins[13].port = pic->P16Emap.PORTC;
    pic->pins[13].pord = 3;
    pic->pins[14].port = pic->P16Emap.PORTC;
    pic->pins[14].pord = 4;
    pic->pins[15].port = pic->P16Emap.PORTC;
    pic->pins[15].pord = 5;
    pic->pins[16].port = pic->P16Emap.PORTC;
    pic->pins[16].pord = 6;
    pic->pins[17].port = pic->P16Emap.PORTC;
    pic->pins[17].pord = 7;
    pic->pins[18].port = P_VSS;
    pic->pins[18].pord = -1;
    pic->pins[19].port = P_VDD;
    pic->pins[19].pord = -1;
    pic->pins[19].value = 1;
    pic->pins[20].port = pic->P16Emap.PORTB;
    pic->pins[20].pord = 0;
    pic->pins[21].port = pic->P16Emap.PORTB;
    pic->pins[21].pord = 1;
    pic->pins[22].port = pic->P16Emap.PORTB;
    pic->pins[22].pord = 2;
    pic->pins[23].port = pic->P16Emap.PORTB;
    pic->pins[23].pord = 3;
    pic->pins[24].port = pic->P16Emap.PORTB;
    pic->pins[24].pord = 4;
    pic->pins[25].port = pic->P16Emap.PORTB;
    pic->pins[25].pord = 5;
    pic->pins[26].port = pic->P16Emap.PORTB;
    pic->pins[26].pord = 6;
    pic->pins[27].port = pic->P16Emap.PORTB;
    pic->pins[27].pord = 7;

    pic->mclr = 1;

    pic->ccp[0].pin = 13;
    pic->ccp[1].pin = 24;

    pic->adc[0] = 2;
    pic->adc[1] = 3;
    pic->adc[2] = 4;
    pic->adc[3] = 5;
    pic->adc[4] = 7;
    pic->adc[5] = 0;
    pic->adc[6] = 0;
    pic->adc[7] = 0;
    pic->adc[8] = 23;
    pic->adc[9] = 24;
    pic->adc[10] = 22;
    pic->adc[11] = 25;
    pic->adc[12] = 21;
    pic->adc[13] = 26;
    pic->adc[14] = 13;
    pic->adc[15] = 14;
    pic->adc[16] = 15;

    pic->usart_rx[0] = 18;
    pic->usart_tx[0] = 17;

    pic->pgc = 27;
    pic->pgd = 28;

    pic->sck = 14;
    pic->sdo = 16;
    pic->sdi = 15;

    pic->t0cki = 6;
    pic->t1cki = 11;

    pic->int0 = 21;
    pic->int1 = 0;
    pic->int2 = 0;

    p16e_tmr0_rst(pic);
    p16e_tmr1_rst(pic);
    p16e_tmr2_rst(pic);
    p16e_adc_rst(pic);
    p16e_wdt_rst(pic);
    p16e_eeprom_rst(pic);
    p16e_mssp_rst(pic);
    p16e_int_pin_rst(pic);
    p16e_int_ports_rst(pic);
    p16e_uart_rst(pic, 0);
}

void PIC16F1516_periferic(_pic* pic) {
    p16e_mssp(pic);
    p16e_adc(pic);
    p16e_int_pin(pic);
    p16e_int_ports(pic);
    p16e_tmr0(pic);
    p16e_wdt(pic);
    p16e_eeprom(pic);
    p16e_tmr1(pic);
    p16e_tmr2(pic);
    p16e_uart(pic, 0);
}

int PIC16F1516_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[0] & 0x0040) > 0);
            break;
        case CFG_WDT:
            return (pic->config[0] & 0x0018);
            break;
        case CFG_DEBUG:
            return ((pic->config[1] & 0x0100) == 0);
            break;
    }
    return 0;
}

void PIC16F1516_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0100;
}

void PIC16F1516_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F1516_start(_pic* pic) {
    pic->ROMSIZE = 8192;
    pic->EEPROMSIZE = 0;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 28;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 2;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 2;
    pic->ADCCOUNT = 17;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F1516_reset;
    pic->mmap = PIC16F1516_map;
    pic->getconf = PIC16F1516_getconf;
    pic->periferic = PIC16F1516_periferic;
    pic->interrupt = interrupt16E;
    pic->stop = PIC16F1516_stop;
    pic->disable_debug = PIC16F1516_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F1516, P16E, 0x1680);
