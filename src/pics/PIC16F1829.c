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

void PIC16F1829_map(_pic* pic) {
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
    pic->P16Emap.PIR1 = &pic->ram[0x11];
    pic->P16Emap.PIR2 = &pic->ram[0x12];
    // pic->P16Emap.PIR3 = &pic->ram[0x13];
    // pic->P16Emap.PIR4 = &pic->ram[0x14];
    pic->P16Emap.TMR0 = &pic->ram[0x15];
    pic->P16Emap.TMR1L = &pic->ram[0x16];
    pic->P16Emap.TMR1H = &pic->ram[0x17];
    pic->P16Emap.T1CON = &pic->ram[0x18];
    // pic->P16Emap.T1GCON = &pic->ram[0x19];
    pic->P16Emap.TMR2 = &pic->ram[0x1A];
    pic->P16Emap.PR2 = &pic->ram[0x1B];
    pic->P16Emap.T2CON = &pic->ram[0x1C];
    // pic->P16Emap.CPSCON0 = &pic->ram[0x1E];
    // pic->P16Emap.CPSCON1 = &pic->ram[0x1F];
    pic->P16Emap.TRISA = &pic->ram[0x8C];
    pic->P16Emap.TRISB = &pic->ram[0x8D];
    pic->P16Emap.TRISC = &pic->ram[0x8E];
    pic->P16Emap.PIE1 = &pic->ram[0x91];
    pic->P16Emap.PIE2 = &pic->ram[0x92];
    // pic->P16Emap.PIE3 = &pic->ram[0x93];
    // pic->P16Emap.PIE4 = &pic->ram[0x94];
    pic->P16Emap.OPTION_REG = &pic->ram[0x95];
    // pic->P16Emap.PCON = &pic->ram[0x96];
    pic->P16Emap.WDTCON = &pic->ram[0x97];
    // pic->P16Emap.OSCTUNE = &pic->ram[0x98];
    // pic->P16Emap.OSCCON = &pic->ram[0x99];
    // pic->P16Emap.OSCSTAT = &pic->ram[0x9A];
    pic->P16Emap.ADRESL = &pic->ram[0x9B];
    pic->P16Emap.ADRESH = &pic->ram[0x9C];
    pic->P16Emap.ADCON0 = &pic->ram[0x9D];
    pic->P16Emap.ADCON1 = &pic->ram[0x9E];
    pic->P16Emap.LATA = &pic->ram[0x10C];
    pic->P16Emap.LATB = &pic->ram[0x10D];
    pic->P16Emap.LATC = &pic->ram[0x10E];
    // pic->P16Emap.CM1CON0 = &pic->ram[0x111];
    // pic->P16Emap.CM1CON1 = &pic->ram[0x112];
    // pic->P16Emap.CM2CON0 = &pic->ram[0x113];
    // pic->P16Emap.CM2CON1 = &pic->ram[0x114];
    // pic->P16Emap.CMOUT = &pic->ram[0x115];
    // pic->P16Emap.BORCON = &pic->ram[0x116];
    // pic->P16Emap.FVRCON = &pic->ram[0x117];
    // pic->P16Emap.DACCON0 = &pic->ram[0x118];
    // pic->P16Emap.DACCON1 = &pic->ram[0x119];
    // pic->P16Emap.SRCON0 = &pic->ram[0x11A];
    // pic->P16Emap.SRCON1 = &pic->ram[0x11B];
    // pic->P16Emap.APFCON0 = &pic->ram[0x11D];
    // pic->P16Emap.APFCON1 = &pic->ram[0x11E];
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELB = &pic->ram[0x18D];
    pic->P16Emap.ANSELC = &pic->ram[0x18E];
    pic->P16Emap.EEADRL = &pic->ram[0x191];
    pic->P16Emap.EEADRH = &pic->ram[0x192];
    pic->P16Emap.EEDATL = &pic->ram[0x193];
    pic->P16Emap.EEDATH = &pic->ram[0x194];
    pic->P16Emap.EECON1 = &pic->ram[0x195];
    pic->P16Emap.EECON2 = &pic->ram[0x196];
    pic->P16Emap.RC1REG = &pic->ram[0x199];
    pic->P16Emap.TX1REG = &pic->ram[0x19A];
    pic->P16Emap.SP1BRGL = &pic->ram[0x19B];
    pic->P16Emap.SP1BRGH = &pic->ram[0x19C];
    pic->P16Emap.RC1STA = &pic->ram[0x19D];
    pic->P16Emap.TX1STA = &pic->ram[0x19E];
    pic->P16Emap.BAUDCON1 = &pic->ram[0x19F];
    // pic->P16Emap.WPUA = &pic->ram[0x20C];
    // pic->P16Emap.WPUB = &pic->ram[0x20D];
    // pic->P16Emap.WPUC = &pic->ram[0x20E];
    pic->P16Emap.SSP1BUF = &pic->ram[0x211];
    pic->P16Emap.SSP1ADD = &pic->ram[0x212];
    // pic->P16Emap.SSP1MSK = &pic->ram[0x213];
    pic->P16Emap.SSP1STAT = &pic->ram[0x214];
    pic->P16Emap.SSP1CON1 = &pic->ram[0x215];
    pic->P16Emap.SSP1CON2 = &pic->ram[0x216];
    // pic->P16Emap.SSP1CON3 = &pic->ram[0x217];
    // pic->P16Emap.SSP2BUF = &pic->ram[0x219];
    // pic->P16Emap.SSP2ADD = &pic->ram[0x21A];
    // pic->P16Emap.SSP2MSK = &pic->ram[0x21B];
    // pic->P16Emap.SSP2STAT = &pic->ram[0x21C];
    // pic->P16Emap.SSP2CON1 = &pic->ram[0x21D];
    // pic->P16Emap.SSP2CON2 = &pic->ram[0x21E];
    // pic->P16Emap.SSP2CON3 = &pic->ram[0x21F];
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    // pic->P16Emap.PWM1CON = &pic->ram[0x294];
    //  pic->P16Emap.CCP1AS = &pic->ram[0x295];
    //  pic->P16Emap.PSTR1CON = &pic->ram[0x296];
    pic->P16Emap.CCPR2L = &pic->ram[0x298];
    pic->P16Emap.CCPR2H = &pic->ram[0x299];
    pic->P16Emap.CCP2CON = &pic->ram[0x29A];
    // pic->P16Emap.PWM2CON = &pic->ram[0x29B];
    // pic->P16Emap.CCP2AS = &pic->ram[0x29C];
    // pic->P16Emap.PSTR2CON = &pic->ram[0x29D];
    // pic->P16Emap.CCPTMRS = &pic->ram[0x29E];
    // pic->P16Emap.CCPR3L = &pic->ram[0x311];
    // pic->P16Emap.CCPR3H = &pic->ram[0x312];
    // pic->P16Emap.CCP3CON = &pic->ram[0x313];
    // pic->P16Emap.CCPR4L = &pic->ram[0x318];
    // pic->P16Emap.CCPR4H = &pic->ram[0x319];
    // pic->P16Emap.CCP4CON = &pic->ram[0x31A];
    // pic->P16Emap.INLVLA = &pic->ram[0x38C];
    // pic->P16Emap.INLVLB = &pic->ram[0x38D];
    // pic->P16Emap.INLVLC = &pic->ram[0x38E];
    // pic->P16Emap.IOCAP = &pic->ram[0x391];
    // pic->P16Emap.IOCAN = &pic->ram[0x392];
    // pic->P16Emap.IOCAF = &pic->ram[0x393];
    pic->P16Emap.IOCBP = &pic->ram[0x394];
    pic->P16Emap.IOCBN = &pic->ram[0x395];
    pic->P16Emap.IOCBF = &pic->ram[0x396];
    // pic->P16Emap.CLKRCON = &pic->ram[0x39A];
    // pic->P16Emap.MDCON = &pic->ram[0x39C];
    // pic->P16Emap.MDSRC = &pic->ram[0x39D];
    // pic->P16Emap.MDCARL = &pic->ram[0x39E];
    // pic->P16Emap.MDCARH = &pic->ram[0x39F];
    // pic->P16Emap.TMR4 = &pic->ram[0x415];
    // pic->P16Emap.PR4 = &pic->ram[0x416];
    // pic->P16Emap.T4CON = &pic->ram[0x417];
    // pic->P16Emap.TMR6 = &pic->ram[0x41C];
    // pic->P16Emap.PR6 = &pic->ram[0x41D];
    // pic->P16Emap.T6CON = &pic->ram[0x41E];
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

01 - Vdd
02 - RA5 CLKIN OSC1 T1OSI SDO2 T1CKI P2A CCP2
03 - RA4 AN3 CPS3 OSC2 CLKOUT T1OSO CLKR SS2 P2B T1G
04 - RA3 T1G Vpp MCLR
05 - RC5 CCP1 P1A DT RX MDCIN2
06 - RC4 C2OUT SRNQ P1B CK TX MDOUT
07 - RC3 AN7 CPS7 C12IN3- P1C CCP2 P2A MDMIN
08 - RC6 AN8 CPS8 CCP4 SS1
09 - RC7 AN9 CPS9 SDO
10 - RB7 CK TX SCK2 SCL2
11 - RB6 SCL1 SCK1
12 - RB5 AN11 CPS11 RX DT SDA2 SDI2
13 - RB4 AN10 CPS10 SDA1 SDI1
14 - RC2 AN6 CPS6 C12IN2- P1D P2B MDCIN1
15 - RC1 AN5 CPS5 C12IN1- P1C SDO2
16 - RC0 AN4 CPS4 C2IN+ P1D SS2
17 - RA2 AN2 CPS2 T0CKI INT C1OUT SRQ CCP3 FLT0
18 - RA1 AN1 CPS1 C12IN0- Vref+ SRI ICSPCLK ICDCLK
19 - RA0 AN0 CPS0 C1IN+ Vref- DACOUT ICSPDAT ICDDAT
20 - Vss
 */

#include "../p16e/p16e_periferic.h"

/*
======================
Family=P16E
processor=PIC16F1829
deviceid=0x27E0
 */

void PIC16F1829_reset(_pic* pic) {
    pic->pins[0].port = P_VDD;
    pic->pins[0].pord = -1;
    pic->pins[0].value = 1;
    pic->pins[1].port = pic->P16Emap.PORTA;
    pic->pins[1].pord = 5;
    pic->pins[2].port = pic->P16Emap.PORTA;
    pic->pins[2].pord = 4;
    pic->pins[3].port = pic->P16Emap.PORTA;
    pic->pins[3].pord = 3;
    pic->pins[4].port = pic->P16Emap.PORTC;
    pic->pins[4].pord = 5;
    pic->pins[5].port = pic->P16Emap.PORTC;
    pic->pins[5].pord = 4;
    pic->pins[6].port = pic->P16Emap.PORTC;
    pic->pins[6].pord = 3;
    pic->pins[7].port = pic->P16Emap.PORTC;
    pic->pins[7].pord = 6;
    pic->pins[8].port = pic->P16Emap.PORTC;
    pic->pins[8].pord = 7;
    pic->pins[9].port = pic->P16Emap.PORTB;
    pic->pins[9].pord = 7;
    pic->pins[10].port = pic->P16Emap.PORTB;
    pic->pins[10].pord = 6;
    pic->pins[11].port = pic->P16Emap.PORTB;
    pic->pins[11].pord = 5;
    pic->pins[12].port = pic->P16Emap.PORTB;
    pic->pins[12].pord = 4;
    pic->pins[13].port = pic->P16Emap.PORTC;
    pic->pins[13].pord = 2;
    pic->pins[14].port = pic->P16Emap.PORTC;
    pic->pins[14].pord = 1;
    pic->pins[15].port = pic->P16Emap.PORTC;
    pic->pins[15].pord = 0;
    pic->pins[16].port = pic->P16Emap.PORTA;
    pic->pins[16].pord = 2;
    pic->pins[17].port = pic->P16Emap.PORTA;
    pic->pins[17].pord = 1;
    pic->pins[18].port = pic->P16Emap.PORTA;
    pic->pins[18].pord = 0;
    pic->pins[19].port = P_VSS;
    pic->pins[19].pord = -1;

    pic->mclr = 4;

    pic->ccp[0].pin = 5;
    pic->ccp[1].pin = 7;
    pic->ccp[2].pin = 17;
    pic->ccp[3].pin = 8;

    pic->adc[0] = 19;
    pic->adc[1] = 18;
    pic->adc[2] = 17;
    pic->adc[3] = 3;
    pic->adc[4] = 16;
    pic->adc[5] = 15;
    pic->adc[6] = 14;
    pic->adc[7] = 7;
    pic->adc[8] = 8;
    pic->adc[9] = 9;
    pic->adc[10] = 13;
    pic->adc[11] = 12;

    pic->usart_rx[0] = 12;
    pic->usart_tx[0] = 10;

    pic->pgc = 18;
    pic->pgd = 19;

    pic->sck = 11;
    pic->sdo = 15;
    pic->sdi = 13;

    pic->t0cki = 17;
    pic->t1cki = 2;

    pic->int0 = 17;
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
    p16e_uart_rst_2(pic, 0);
}

void PIC16F1829_periferic(_pic* pic) {
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

int PIC16F1829_getconf(_pic* pic, unsigned int cfg) {
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

void PIC16F1829_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0100;
}

void PIC16F1829_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F1829_start(_pic* pic) {
    pic->ROMSIZE = 8192;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 20;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 2;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 4;
    pic->ADCCOUNT = 12;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F1829_reset;
    pic->mmap = PIC16F1829_map;
    pic->getconf = PIC16F1829_getconf;
    pic->periferic = PIC16F1829_periferic;
    pic->interrupt = interrupt16E;
    pic->stop = PIC16F1829_stop;
    pic->disable_debug = PIC16F1829_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F1829, P16E, 0x27E0);
