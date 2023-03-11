/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2020  Luis Claudio Gamboa Lopes

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
#include "../p16e/p16e_periferic.h"

void PIC16F1939_map(_pic* pic) {
    memset(&pic->P16Emap, 0, sizeof(P16Emap_t));

    pic->P16Emap.FSR0L = &pic->ram[0x4];
    pic->P16Emap.FSR0H = &pic->ram[0x5];
    pic->P16Emap.FSR1L = &pic->ram[0x6];
    pic->P16Emap.FSR1H = &pic->ram[0x7];
    pic->P16Emap.TMR1L = &pic->ram[0x16];
    pic->P16Emap.TMR1H = &pic->ram[0x17];
    pic->P16Emap.ADRESL = &pic->ram[0x9B];
    pic->P16Emap.ADRESH = &pic->ram[0x9C];
    pic->P16Emap.EEADRL = &pic->ram[0x191];
    pic->P16Emap.EEADRH = &pic->ram[0x192];
    pic->P16Emap.EEDATL = &pic->ram[0x193];
    pic->P16Emap.EEDATH = &pic->ram[0x194];
    pic->P16Emap.SP1BRGL = &pic->ram[0x19B];
    pic->P16Emap.SP1BRGH = &pic->ram[0x19C];
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCPR2L = &pic->ram[0x298];
    pic->P16Emap.CCPR2H = &pic->ram[0x299];
    /*
    pic->P16Emap.CCPR3L = &pic->ram[0x311];
    pic->P16Emap.CCPR3H = &pic->ram[0x312];
    pic->P16Emap.CCPR4L = &pic->ram[0x318];
    pic->P16Emap.CCPR4H = &pic->ram[0x319];
    pic->P16Emap.CCPR5L = &pic->ram[0x31C];
    pic->P16Emap.CCPR5H = &pic->ram[0x31D];
    */
    pic->P16Emap.INDF0 = &pic->ram[0x0];
    pic->P16Emap.INDF1 = &pic->ram[0x1];
    pic->P16Emap.PCL = &pic->ram[0x2];
    pic->P16Emap.STATUS = &pic->ram[0x3];
    pic->P16Emap.BSR = &pic->ram[0x8];
    pic->P16Emap.WREG = &pic->ram[0x9];
    pic->P16Emap.PCLATH = &pic->ram[0xA];
    pic->P16Emap.INTCON = &pic->ram[0xB];
    pic->P16Emap.PORTA = &pic->ram[0xC];
    pic->P16Emap.PORTB = &pic->ram[0xD];
    pic->P16Emap.PORTC = &pic->ram[0xE];
    pic->P16Emap.PORTD = &pic->ram[0xF];
    pic->P16Emap.PORTE = &pic->ram[0x10];
    pic->P16Emap.PIR1 = &pic->ram[0x11];
    pic->P16Emap.PIR2 = &pic->ram[0x12];
    // pic->P16Emap.PIR3 = &pic->ram[0x13];
    pic->P16Emap.TMR0 = &pic->ram[0x15];
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
    pic->P16Emap.TRISD = &pic->ram[0x8F];
    pic->P16Emap.TRISE = &pic->ram[0x90];
    pic->P16Emap.PIE1 = &pic->ram[0x91];
    pic->P16Emap.PIE2 = &pic->ram[0x92];
    // pic->P16Emap.PIE3 = &pic->ram[0x93];
    pic->P16Emap.OPTION_REG = &pic->ram[0x95];
    /*
    pic->P16Emap.PCON = &pic->ram[0x96];
    */
    pic->P16Emap.WDTCON = &pic->ram[0x97];
    /*
    pic->P16Emap.OSCTUNE = &pic->ram[0x98];
    pic->P16Emap.OSCCON = &pic->ram[0x99];
    pic->P16Emap.OSCSTAT = &pic->ram[0x9A];
    */
    pic->P16Emap.ADCON0 = &pic->ram[0x9D];
    pic->P16Emap.ADCON1 = &pic->ram[0x9E];
    pic->P16Emap.LATA = &pic->ram[0x10C];
    pic->P16Emap.LATB = &pic->ram[0x10D];
    pic->P16Emap.LATC = &pic->ram[0x10E];
    pic->P16Emap.LATD = &pic->ram[0x10F];
    pic->P16Emap.LATE = &pic->ram[0x110];
    /*
    pic->P16Emap.CM1CON0 = &pic->ram[0x111];
    pic->P16Emap.CM1CON1 = &pic->ram[0x112];
    pic->P16Emap.CM2CON0 = &pic->ram[0x113];
    pic->P16Emap.CM2CON1 = &pic->ram[0x114];
    pic->P16Emap.CMOUT = &pic->ram[0x115];
    pic->P16Emap.BORCON = &pic->ram[0x116];
    pic->P16Emap.FVRCON = &pic->ram[0x117];
    pic->P16Emap.DACCON0 = &pic->ram[0x118];
    pic->P16Emap.DACCON1 = &pic->ram[0x119];
    pic->P16Emap.SRCON0 = &pic->ram[0x11A];
    pic->P16Emap.SRCON1 = &pic->ram[0x11B];
    pic->P16Emap.APFCON = &pic->ram[0x11D];
    */
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELB = &pic->ram[0x18D];
    pic->P16Emap.ANSELD = &pic->ram[0x18F];
    pic->P16Emap.ANSELE = &pic->ram[0x190];
    pic->P16Emap.EECON1 = &pic->ram[0x195];
    pic->P16Emap.EECON2 = &pic->ram[0x196];
    pic->P16Emap.RCREG = &pic->ram[0x199];
    pic->P16Emap.TXREG = &pic->ram[0x19A];
    pic->P16Emap.RCSTA = &pic->ram[0x19D];
    pic->P16Emap.TXSTA = &pic->ram[0x19E];
    pic->P16Emap.BAUDCON1 = &pic->ram[0x19F];
    /*
    pic->P16Emap.WPUB = &pic->ram[0x20D];
    pic->P16Emap.WPUE = &pic->ram[0x210];
     */
    pic->P16Emap.SSP1BUF = &pic->ram[0x211];
    pic->P16Emap.SSP1ADD = &pic->ram[0x212];
    // pic->P16Emap.SSPMSK = &pic->ram[0x213];
    pic->P16Emap.SSP1STAT = &pic->ram[0x214];
    pic->P16Emap.SSP1CON1 = &pic->ram[0x215];
    pic->P16Emap.SSP1CON2 = &pic->ram[0x216];
    // pic->P16Emap.SSPCON3 = &pic->ram[0x217];
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    /*
    pic->P16Emap.PWM1CON = &pic->ram[0x294];
    pic->P16Emap.CCP1AS = &pic->ram[0x295];
    pic->P16Emap.PSTR1CON = &pic->ram[0x296];
    */
    pic->P16Emap.CCP2CON = &pic->ram[0x29A];
    /*
    pic->P16Emap.PWM2CON = &pic->ram[0x29B];
    pic->P16Emap.CCP2AS = &pic->ram[0x29C];
    pic->P16Emap.PSTR2CON = &pic->ram[0x29D];
    pic->P16Emap.CCPTMRS0 = &pic->ram[0x29E];
    pic->P16Emap.CCPTMRS1 = &pic->ram[0x29F];
    pic->P16Emap.CCP3CON = &pic->ram[0x313];
    pic->P16Emap.PWM3CON = &pic->ram[0x314];
    pic->P16Emap.CCP3AS = &pic->ram[0x315];
    pic->P16Emap.PSTR3CON = &pic->ram[0x316];
    pic->P16Emap.CCP4CON = &pic->ram[0x31A];
    pic->P16Emap.CCP5CON = &pic->ram[0x31E];
     */
    pic->P16Emap.IOCBP = &pic->ram[0x394];
    pic->P16Emap.IOCBN = &pic->ram[0x395];
    pic->P16Emap.IOCBF = &pic->ram[0x396];
    /*
    pic->P16Emap.TMR4 = &pic->ram[0x415];
    pic->P16Emap.PR4 = &pic->ram[0x416];
    pic->P16Emap.T4CON = &pic->ram[0x417];
    pic->P16Emap.TMR6 = &pic->ram[0x41C];
    pic->P16Emap.PR6 = &pic->ram[0x41D];
    pic->P16Emap.T6CON = &pic->ram[0x41E];
    pic->P16Emap.LCDCON = &pic->ram[0x791];
    pic->P16Emap.LCDPS = &pic->ram[0x792];
    pic->P16Emap.LCDREF = &pic->ram[0x793];
    pic->P16Emap.LCDCST = &pic->ram[0x794];
    pic->P16Emap.LCDRL = &pic->ram[0x795];
    pic->P16Emap.LCDSE0 = &pic->ram[0x798];
    pic->P16Emap.LCDSE1 = &pic->ram[0x799];
    pic->P16Emap.LCDSE2 = &pic->ram[0x79A];
    pic->P16Emap.LCDDATA0 = &pic->ram[0x7A0];
    pic->P16Emap.LCDDATA1 = &pic->ram[0x7A1];
    pic->P16Emap.LCDDATA2 = &pic->ram[0x7A2];
    pic->P16Emap.LCDDATA3 = &pic->ram[0x7A3];
    pic->P16Emap.LCDDATA4 = &pic->ram[0x7A4];
    pic->P16Emap.LCDDATA5 = &pic->ram[0x7A5];
    pic->P16Emap.LCDDATA6 = &pic->ram[0x7A6];
    pic->P16Emap.LCDDATA7 = &pic->ram[0x7A7];
    pic->P16Emap.LCDDATA8 = &pic->ram[0x7A8];
    pic->P16Emap.LCDDATA9 = &pic->ram[0x7A9];
    pic->P16Emap.LCDDATA10 = &pic->ram[0x7AA];
    pic->P16Emap.LCDDATA11 = &pic->ram[0x7AB];
    */
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
02 - RA0 AN0 C12IN0- C2OUT SRNQ SS Vcap SEG12
03 - RA1 AN1 C12IN1- SEG7
04 - RA2 AN2 C2IN+ Vref- DACOUT COM2
05 - RA3 AN3 C1IN+ Vref+ SEG15
06 - RA4 C1OUT CPS6 T0CKI SRQ SEG4
07 - RA5 AN4 C2OUT CPS7 SRNQ SS Vcap SEG5
08 - RE0 AN5 P3A CCP3 SEG21
09 - RE1 AN6 P3B SEG22
10 - RE2 AN7 CCP5 SEG23
11 - Vdd
12 - Vss
13 - RA7 OSC1 CLKIN SEG2
14 - RA6 OSC2 CLKOUT Vcap SEG1
15 - RC0 T1OSO T1CKI P2B
16 - RC1 T1OSI CCP2 P2A
17 - RC2 CCP1 P1A SEG3
18 - RC3 SCL SCK SEG6
19 - RD0 CPS8 COM3
20 - RD1 CPS9 CCP4
21 - RD2 CPS10 P2B
22 - RD3 CPS11 P2C SEG16
23 - RC4 SDI SDA T1G SEG11
24 - RC5 SDO SEG10
25 - RC6 TX CK SEG9
26 - RC7 RX DT SEG8
27 - RD4 CPS12 P2D SEG17
28 - RD5 CPS13 P1B SEG18
29 - RD6 CPS14 P1C SEG19
30 - RD7 CPS15 P1D SEG20
31 - Vss
32 - Vdd
33 - RB0 AN12 CPS0 SRI INT SEG0
34 - RB1 AN10 C12IN3- CPS1 VLCD1
35 - RB2 AN8 CPS2 VLCD2
36 - RB3 AN9 C12IN2- CPS3 CCP2 P2A VLCD3
37 - RB4 AN11 CPS4 COM0
38 - RB5 AN13 CPS5 CCP3 P3A T1G COM1
39 - RB6 ICSPCLK ICDCLK SEG14
40 - RB7 ICSPDAT ICDDAT SEG13
 */

/*
======================
Family=P16E
processor=PIC16F1939
deviceid=0x23C0
 */

void PIC16F1939_reset(_pic* pic) {
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
    pic->pins[7].port = pic->P16Emap.PORTE;
    pic->pins[7].pord = 0;
    pic->pins[8].port = pic->P16Emap.PORTE;
    pic->pins[8].pord = 1;
    pic->pins[9].port = pic->P16Emap.PORTE;
    pic->pins[9].pord = 2;
    pic->pins[10].port = P_VDD;
    pic->pins[10].pord = -1;
    pic->pins[10].value = 1;
    pic->pins[11].port = P_VSS;
    pic->pins[11].pord = -1;
    pic->pins[12].port = pic->P16Emap.PORTA;
    pic->pins[12].pord = 7;
    pic->pins[13].port = pic->P16Emap.PORTA;
    pic->pins[13].pord = 6;
    pic->pins[14].port = pic->P16Emap.PORTC;
    pic->pins[14].pord = 0;
    pic->pins[15].port = pic->P16Emap.PORTC;
    pic->pins[15].pord = 1;
    pic->pins[16].port = pic->P16Emap.PORTC;
    pic->pins[16].pord = 2;
    pic->pins[17].port = pic->P16Emap.PORTC;
    pic->pins[17].pord = 3;
    pic->pins[18].port = pic->P16Emap.PORTD;
    pic->pins[18].pord = 0;
    pic->pins[19].port = pic->P16Emap.PORTD;
    pic->pins[19].pord = 1;
    pic->pins[20].port = pic->P16Emap.PORTD;
    pic->pins[20].pord = 2;
    pic->pins[21].port = pic->P16Emap.PORTD;
    pic->pins[21].pord = 3;
    pic->pins[22].port = pic->P16Emap.PORTC;
    pic->pins[22].pord = 4;
    pic->pins[23].port = pic->P16Emap.PORTC;
    pic->pins[23].pord = 5;
    pic->pins[24].port = pic->P16Emap.PORTC;
    pic->pins[24].pord = 6;
    pic->pins[25].port = pic->P16Emap.PORTC;
    pic->pins[25].pord = 7;
    pic->pins[26].port = pic->P16Emap.PORTD;
    pic->pins[26].pord = 4;
    pic->pins[27].port = pic->P16Emap.PORTD;
    pic->pins[27].pord = 5;
    pic->pins[28].port = pic->P16Emap.PORTD;
    pic->pins[28].pord = 6;
    pic->pins[29].port = pic->P16Emap.PORTD;
    pic->pins[29].pord = 7;
    pic->pins[30].port = P_VSS;
    pic->pins[30].pord = -1;
    pic->pins[31].port = P_VDD;
    pic->pins[31].pord = -1;
    pic->pins[31].value = 1;
    pic->pins[32].port = pic->P16Emap.PORTB;
    pic->pins[32].pord = 0;
    pic->pins[33].port = pic->P16Emap.PORTB;
    pic->pins[33].pord = 1;
    pic->pins[34].port = pic->P16Emap.PORTB;
    pic->pins[34].pord = 2;
    pic->pins[35].port = pic->P16Emap.PORTB;
    pic->pins[35].pord = 3;
    pic->pins[36].port = pic->P16Emap.PORTB;
    pic->pins[36].pord = 4;
    pic->pins[37].port = pic->P16Emap.PORTB;
    pic->pins[37].pord = 5;
    pic->pins[38].port = pic->P16Emap.PORTB;
    pic->pins[38].pord = 6;
    pic->pins[39].port = pic->P16Emap.PORTB;
    pic->pins[39].pord = 7;

    pic->mclr = 1;

    pic->ccp[0].pin = 17;
    pic->ccp[1].pin = 36;
    pic->ccp[2].pin = 38;
    pic->ccp[3].pin = 20;
    pic->ccp[4].pin = 10;

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

void PIC16F1939_periferic(_pic* pic) {
    p16e_mssp(pic);
    p16e_adc(pic);
    p16e_int_pin(pic);
    p16e_int_ports(pic);
    p16e_tmr0(pic);
    p16e_wdt_2(pic);
    p16e_eeprom(pic);
    p16e_tmr1(pic);
    p16e_tmr2(pic);
    p16e_uart(pic, 0);
}

int PIC16F1939_getconf(_pic* pic, unsigned int cfg) {
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

void PIC16F1939_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0100;
}

void PIC16F1939_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F1939_start(_pic* pic) {
    pic->ROMSIZE = 16384;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 40;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 2;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 5;
    pic->ADCCOUNT = 14;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F1939_reset;
    pic->mmap = PIC16F1939_map;
    pic->getconf = PIC16F1939_getconf;
    pic->periferic = PIC16F1939_periferic;
    pic->interrupt = interrupt16E;
    pic->stop = PIC16F1939_stop;
    pic->disable_debug = PIC16F1939_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F1939, P16E, 0x23C0);
