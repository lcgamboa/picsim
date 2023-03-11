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

void PIC16F1947_map(_pic* pic) {
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
    pic->P16Emap.PORTD = &pic->ram[0xF];
    pic->P16Emap.PORTE = &pic->ram[0x10];
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
    pic->P16Emap.TRISD = &pic->ram[0x8F];
    pic->P16Emap.TRISE = &pic->ram[0x90];
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
    pic->P16Emap.CM3CON0 = &pic->ram[0x11E];
    pic->P16Emap.CM3CON1 = &pic->ram[0x11F];
    */
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELE = &pic->ram[0x190];
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
    // pic->P16Emap.BAUD1CON = &pic->ram[0x19F];
    // pic->P16Emap.WPUB = &pic->ram[0x20D];
    pic->P16Emap.SSP1BUF = &pic->ram[0x211];
    pic->P16Emap.SSP1ADD = &pic->ram[0x212];
    // pic->P16Emap.SSP1MSK = &pic->ram[0x213];
    pic->P16Emap.SSP1STAT = &pic->ram[0x214];
    pic->P16Emap.SSP1CON1 = &pic->ram[0x215];
    pic->P16Emap.SSP1CON2 = &pic->ram[0x216];
    /*
    pic->P16Emap.SSP1CON3 = &pic->ram[0x217];
    pic->P16Emap.SSP2BUF = &pic->ram[0x219];
    pic->P16Emap.SSP2ADD = &pic->ram[0x21A];
    pic->P16Emap.SSP2MSK = &pic->ram[0x21B];
    pic->P16Emap.SSP2STAT = &pic->ram[0x21C];
    pic->P16Emap.SSP2CON1 = &pic->ram[0x21D];
    pic->P16Emap.SSP2CON2 = &pic->ram[0x21E];
    pic->P16Emap.SSP2CON3 = &pic->ram[0x21F];
    */
    pic->P16Emap.PORTF = &pic->ram[0x28C];
    pic->P16Emap.PORTG = &pic->ram[0x28D];
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    /*
    pic->P16Emap.PWM1CON = &pic->ram[0x294];
    pic->P16Emap.CCP1AS = &pic->ram[0x295];
    pic->P16Emap.PSTR1CON = &pic->ram[0x296];
    */
    pic->P16Emap.CCPR2L = &pic->ram[0x298];
    pic->P16Emap.CCPR2H = &pic->ram[0x299];
    pic->P16Emap.CCP2CON = &pic->ram[0x29A];
    /*
    pic->P16Emap.PWM2CON = &pic->ram[0x29B];
    pic->P16Emap.CCP2AS = &pic->ram[0x29C];
    pic->P16Emap.PSTR2CON = &pic->ram[0x29D];
    pic->P16Emap.CCPTMRS0 = &pic->ram[0x29E];
    pic->P16Emap.CCPTMRS1 = &pic->ram[0x29F];
    */
    pic->P16Emap.TRISF = &pic->ram[0x30C];
    pic->P16Emap.TRISG = &pic->ram[0x30D];
    /*
    pic->P16Emap.CCPR3L = &pic->ram[0x311];
    pic->P16Emap.CCPR3H = &pic->ram[0x312];
    pic->P16Emap.CCP3CON = &pic->ram[0x313];
    pic->P16Emap.PWM3CON = &pic->ram[0x314];
    pic->P16Emap.CCP3AS = &pic->ram[0x315];
    pic->P16Emap.PSTR3CON = &pic->ram[0x316];
    pic->P16Emap.CCPR4L = &pic->ram[0x318];
    pic->P16Emap.CCPR4H = &pic->ram[0x319];
    pic->P16Emap.CCP4CON = &pic->ram[0x31A];
    pic->P16Emap.CCPR5L = &pic->ram[0x31C];
    pic->P16Emap.CCPR5H = &pic->ram[0x31D];
    pic->P16Emap.CCP5CON = &pic->ram[0x31E];
    */
    pic->P16Emap.LATF = &pic->ram[0x38C];
    pic->P16Emap.LATG = &pic->ram[0x38D];
    pic->P16Emap.IOCBP = &pic->ram[0x394];
    pic->P16Emap.IOCBN = &pic->ram[0x395];
    pic->P16Emap.IOCBF = &pic->ram[0x396];
    pic->P16Emap.ANSELF = &pic->ram[0x40C];
    pic->P16Emap.ANSELG = &pic->ram[0x40D];
    /*
    pic->P16Emap.TMR4 = &pic->ram[0x415];
    pic->P16Emap.PR4 = &pic->ram[0x416];
    pic->P16Emap.T4CON = &pic->ram[0x417];
    pic->P16Emap.TMR6 = &pic->ram[0x41C];
    pic->P16Emap.PR6 = &pic->ram[0x41D];
    pic->P16Emap.T6CON = &pic->ram[0x41E];
    pic->P16Emap.WPUG = &pic->ram[0x48D];
    pic->P16Emap.RC2REG = &pic->ram[0x491];
    pic->P16Emap.TX2REG = &pic->ram[0x492];
    pic->P16Emap.SP2BRGL = &pic->ram[0x493];
    pic->P16Emap.SP2BRGH = &pic->ram[0x494];
    pic->P16Emap.RC2STA = &pic->ram[0x495];
    pic->P16Emap.TX2STA = &pic->ram[0x496];
    pic->P16Emap.BAUD2CON = &pic->ram[0x497];
    pic->P16Emap.LCDCON = &pic->ram[0x791];
    pic->P16Emap.LCDPS = &pic->ram[0x792];
    pic->P16Emap.LCDREF = &pic->ram[0x793];
    pic->P16Emap.LCDCST = &pic->ram[0x794];
    pic->P16Emap.LCDRL = &pic->ram[0x795];
    pic->P16Emap.LCDSE0 = &pic->ram[0x798];
    pic->P16Emap.LCDSE1 = &pic->ram[0x799];
    pic->P16Emap.LCDSE2 = &pic->ram[0x79A];
    pic->P16Emap.LCDSE3 = &pic->ram[0x79B];
    pic->P16Emap.LCDSE4 = &pic->ram[0x79C];
    pic->P16Emap.LCDSE5 = &pic->ram[0x79D];
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
    pic->P16Emap.LCDDATA12 = &pic->ram[0x7AC];
    pic->P16Emap.LCDDATA13 = &pic->ram[0x7AD];
    pic->P16Emap.LCDDATA14 = &pic->ram[0x7AE];
    pic->P16Emap.LCDDATA15 = &pic->ram[0x7AF];
    pic->P16Emap.LCDDATA16 = &pic->ram[0x7B0];
    pic->P16Emap.LCDDATA17 = &pic->ram[0x7B1];
    pic->P16Emap.LCDDATA18 = &pic->ram[0x7B2];
    pic->P16Emap.LCDDATA19 = &pic->ram[0x7B3];
    pic->P16Emap.LCDDATA20 = &pic->ram[0x7B4];
    pic->P16Emap.LCDDATA21 = &pic->ram[0x7B5];
    pic->P16Emap.LCDDATA22 = &pic->ram[0x7B6];
    pic->P16Emap.LCDDATA23 = &pic->ram[0x7B7];
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

01 - RE1 P2C VLCD2
02 - RE0 P2D VLCD1
03 - RG0 CCP3 P3A SEG42
04 - RG1 AN15 CPS15 TX2 CK2 C3OUT SEG43
05 - RG2 AN14 CPS14 RX2 DT2 C3IN+ SEG44
06 - RG3 AN13 CPS13 C3IN0- CCP4 P3D SEG45
07 - RG5 MCLR Vpp
08 - RG4 AN12 CPS12 C3IN1- CCP5 P1D SEG26
09 - Vss
10 - Vdd
11 - RF7 AN5 CPS5 C3IN3- C2IN3- C1IN3- SS1 SEG25
12 - RF6 AN11 CPS11 C1IN+ SEG24
13 - RF5 AN10 CPS10 C2IN1- C1IN1- DACOUT SEG23
14 - RF4 AN9 CPS9 C2IN+ SEG22
15 - RF3 AN8 CPS8 C3IN2- C2IN2- C1IN2- SEG21
16 - RF2 AN7 CPS7 C1OUT SRQ SEG20
17 - RF1 AN6 CPS6 C2OUT SRNQ SEG19
18 - RF0 AN16 CPS16 C2IN0- C1IN0- SEG41 Vcap
19 - AVdd
20 - AVss
21 - RA3 AN3 Vref+ CPS3 SEG35
22 - RA2 AN2 Vref- CPS2 SEG34
23 - RA1 AN1 CPS1 SEG18
24 - RA0 AN0 CPS0 SEG33
25 - Vss
26 - Vdd
27 - RA5 AN4 CPS4 SEG15
28 - RA4 T0CKI SEG14
29 - RC1 T1OSI P2A CCP2 SEG32
30 - RC0 T1OSO T1CKI SEG40
31 - RC6 TX1 CK1 SEG27
32 - RC7 RX1 DT1 SEG28
33 - RC2 CCP1 P1A SEG13
34 - RC3 SCK1 SCL1 SEG17
35 - RC4 SDI1 SDA1 SEG16
36 - RC5 SDO1 SEG12
37 - RB7 ICSPDAT ICDDAT SEG39
38 - Vdd
39 - RA7 OSC1 CLKIN SEG37
40 - RA6 OSC2 CLKOUT SEG36
41 - Vss
42 - RB6 ICSPCLK ICDCLK SEG38
43 - RB5 T1G SEG29
44 - RB4 SEG11
45 - RB3 SEG10
46 - RB2 SEG9
47 - RB1 SEG8
48 - RB0 INT SRI FLT0 SEG30
49 - RD7 SS2 SEG7
50 - RD6 SCK2 SCL2 P1B SEG6
51 - RD5 SDI2 SDA2 P1C SEG5
52 - RD4 SDO2 P3B SEG4
53 - RD3 P3C SEG3
54 - RD2 P2B SEG2
55 - RD1 P2C SEG1
56 - Vss
57 - Vdd
58 - RD0 P2D SEG0
59 - RE7 CCP2 P2A SEG31
60 - RE6 P1B COM3
61 - RE5 P1C COM2
62 - RE4 P3B COM1
63 - RE3 P3C COM0
64 - RE2 P2B VLCD3
 */

#include "../p16e/p16e_periferic.h"

/*
======================
Family=P16E
processor=PIC16F1947
deviceid=0x2520
 */

void PIC16F1947_reset(_pic* pic) {
    pic->pins[0].port = pic->P16Emap.PORTE;
    pic->pins[0].pord = 1;
    pic->pins[1].port = pic->P16Emap.PORTE;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P16Emap.PORTG;
    pic->pins[2].pord = 0;
    pic->pins[3].port = pic->P16Emap.PORTG;
    pic->pins[3].pord = 1;
    pic->pins[4].port = pic->P16Emap.PORTG;
    pic->pins[4].pord = 2;
    pic->pins[5].port = pic->P16Emap.PORTG;
    pic->pins[5].pord = 3;
    pic->pins[6].port = pic->P16Emap.PORTG;
    pic->pins[6].pord = 5;
    pic->pins[7].port = pic->P16Emap.PORTG;
    pic->pins[7].pord = 4;
    pic->pins[8].port = P_VSS;
    pic->pins[8].pord = -1;
    pic->pins[9].port = P_VDD;
    pic->pins[9].pord = -1;
    pic->pins[9].value = 1;
    pic->pins[10].port = pic->P16Emap.PORTF;
    pic->pins[10].pord = 7;
    pic->pins[11].port = pic->P16Emap.PORTF;
    pic->pins[11].pord = 6;
    pic->pins[12].port = pic->P16Emap.PORTF;
    pic->pins[12].pord = 5;
    pic->pins[13].port = pic->P16Emap.PORTF;
    pic->pins[13].pord = 4;
    pic->pins[14].port = pic->P16Emap.PORTF;
    pic->pins[14].pord = 3;
    pic->pins[15].port = pic->P16Emap.PORTF;
    pic->pins[15].pord = 2;
    pic->pins[16].port = pic->P16Emap.PORTF;
    pic->pins[16].pord = 1;
    pic->pins[17].port = pic->P16Emap.PORTF;
    pic->pins[17].pord = 0;
    pic->pins[18].port = P_VDD;
    pic->pins[18].pord = -1;
    pic->pins[18].value = 1;
    pic->pins[19].port = P_VSS;
    pic->pins[19].pord = -1;
    pic->pins[20].port = pic->P16Emap.PORTA;
    pic->pins[20].pord = 3;
    pic->pins[21].port = pic->P16Emap.PORTA;
    pic->pins[21].pord = 2;
    pic->pins[22].port = pic->P16Emap.PORTA;
    pic->pins[22].pord = 1;
    pic->pins[23].port = pic->P16Emap.PORTA;
    pic->pins[23].pord = 0;
    pic->pins[24].port = P_VSS;
    pic->pins[24].pord = -1;
    pic->pins[25].port = P_VDD;
    pic->pins[25].pord = -1;
    pic->pins[25].value = 1;
    pic->pins[26].port = pic->P16Emap.PORTA;
    pic->pins[26].pord = 5;
    pic->pins[27].port = pic->P16Emap.PORTA;
    pic->pins[27].pord = 4;
    pic->pins[28].port = pic->P16Emap.PORTC;
    pic->pins[28].pord = 1;
    pic->pins[29].port = pic->P16Emap.PORTC;
    pic->pins[29].pord = 0;
    pic->pins[30].port = pic->P16Emap.PORTC;
    pic->pins[30].pord = 6;
    pic->pins[31].port = pic->P16Emap.PORTC;
    pic->pins[31].pord = 7;
    pic->pins[32].port = pic->P16Emap.PORTC;
    pic->pins[32].pord = 2;
    pic->pins[33].port = pic->P16Emap.PORTC;
    pic->pins[33].pord = 3;
    pic->pins[34].port = pic->P16Emap.PORTC;
    pic->pins[34].pord = 4;
    pic->pins[35].port = pic->P16Emap.PORTC;
    pic->pins[35].pord = 5;
    pic->pins[36].port = pic->P16Emap.PORTB;
    pic->pins[36].pord = 7;
    pic->pins[37].port = P_VDD;
    pic->pins[37].pord = -1;
    pic->pins[37].value = 1;
    pic->pins[38].port = pic->P16Emap.PORTA;
    pic->pins[38].pord = 7;
    pic->pins[39].port = pic->P16Emap.PORTA;
    pic->pins[39].pord = 6;
    pic->pins[40].port = P_VSS;
    pic->pins[40].pord = -1;
    pic->pins[41].port = pic->P16Emap.PORTB;
    pic->pins[41].pord = 6;
    pic->pins[42].port = pic->P16Emap.PORTB;
    pic->pins[42].pord = 5;
    pic->pins[43].port = pic->P16Emap.PORTB;
    pic->pins[43].pord = 4;
    pic->pins[44].port = pic->P16Emap.PORTB;
    pic->pins[44].pord = 3;
    pic->pins[45].port = pic->P16Emap.PORTB;
    pic->pins[45].pord = 2;
    pic->pins[46].port = pic->P16Emap.PORTB;
    pic->pins[46].pord = 1;
    pic->pins[47].port = pic->P16Emap.PORTB;
    pic->pins[47].pord = 0;
    pic->pins[48].port = pic->P16Emap.PORTD;
    pic->pins[48].pord = 7;
    pic->pins[49].port = pic->P16Emap.PORTD;
    pic->pins[49].pord = 6;
    pic->pins[50].port = pic->P16Emap.PORTD;
    pic->pins[50].pord = 5;
    pic->pins[51].port = pic->P16Emap.PORTD;
    pic->pins[51].pord = 4;
    pic->pins[52].port = pic->P16Emap.PORTD;
    pic->pins[52].pord = 3;
    pic->pins[53].port = pic->P16Emap.PORTD;
    pic->pins[53].pord = 2;
    pic->pins[54].port = pic->P16Emap.PORTD;
    pic->pins[54].pord = 1;
    pic->pins[55].port = P_VSS;
    pic->pins[55].pord = -1;
    pic->pins[56].port = P_VDD;
    pic->pins[56].pord = -1;
    pic->pins[56].value = 1;
    pic->pins[57].port = pic->P16Emap.PORTD;
    pic->pins[57].pord = 0;
    pic->pins[58].port = pic->P16Emap.PORTE;
    pic->pins[58].pord = 7;
    pic->pins[59].port = pic->P16Emap.PORTE;
    pic->pins[59].pord = 6;
    pic->pins[60].port = pic->P16Emap.PORTE;
    pic->pins[60].pord = 5;
    pic->pins[61].port = pic->P16Emap.PORTE;
    pic->pins[61].pord = 4;
    pic->pins[62].port = pic->P16Emap.PORTE;
    pic->pins[62].pord = 3;
    pic->pins[63].port = pic->P16Emap.PORTE;
    pic->pins[63].pord = 2;

    pic->mclr = 7;

    pic->ccp[0].pin = 33;
    pic->ccp[1].pin = 59;
    pic->ccp[2].pin = 3;
    pic->ccp[3].pin = 6;
    pic->ccp[4].pin = 8;

    pic->adc[0] = 24;
    pic->adc[1] = 23;
    pic->adc[2] = 22;
    pic->adc[3] = 21;
    pic->adc[4] = 27;
    pic->adc[5] = 11;
    pic->adc[6] = 17;
    pic->adc[7] = 16;
    pic->adc[8] = 15;
    pic->adc[9] = 14;
    pic->adc[10] = 13;
    pic->adc[11] = 12;
    pic->adc[12] = 8;
    pic->adc[13] = 6;
    pic->adc[14] = 5;
    pic->adc[15] = 4;
    pic->adc[16] = 18;

    pic->usart_rx[0] = 32;
    pic->usart_tx[0] = 31;

    pic->pgc = 42;
    pic->pgd = 37;

    pic->sck = 50;
    pic->sdo = 52;
    pic->sdi = 51;

    pic->t0cki = 28;
    pic->t1cki = 30;

    pic->int0 = 48;
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

void PIC16F1947_periferic(_pic* pic) {
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

int PIC16F1947_getconf(_pic* pic, unsigned int cfg) {
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

void PIC16F1947_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0100;
}

void PIC16F1947_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F1947_start(_pic* pic) {
    pic->ROMSIZE = 16384;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 64;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 2;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 5;
    pic->ADCCOUNT = 17;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F1947_reset;
    pic->mmap = PIC16F1947_map;
    pic->getconf = PIC16F1947_getconf;
    pic->periferic = PIC16F1947_periferic;
    pic->interrupt = interrupt16E;
    pic->stop = PIC16F1947_stop;
    pic->disable_debug = PIC16F1947_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F1947, P16E, 0x2520);
