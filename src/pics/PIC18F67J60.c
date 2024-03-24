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

void PIC18F67J60_map(_pic* pic) {
    memset(&pic->P18map, 0, sizeof(P18map_t));
    /*
        pic->P18map.MAADR5 = &pic->ram[0xE80];
        pic->P18map.MAADR6 = &pic->ram[0xE81];
        pic->P18map.MAADR3 = &pic->ram[0xE82];
        pic->P18map.MAADR4 = &pic->ram[0xE83];
        pic->P18map.MAADR1 = &pic->ram[0xE84];
        pic->P18map.MAADR2 = &pic->ram[0xE85];
        pic->P18map.MISTAT = &pic->ram[0xE8A];
        pic->P18map.EFLOCON = &pic->ram[0xE97];
        pic->P18map.EPAUSL = &pic->ram[0xE98];
        pic->P18map.EPAUSH = &pic->ram[0xE99];
        pic->P18map.MACON1 = &pic->ram[0xEA0];
        pic->P18map.MACON3 = &pic->ram[0xEA2];
        pic->P18map.MACON4 = &pic->ram[0xEA3];
        pic->P18map.MABBIPG = &pic->ram[0xEA4];
        pic->P18map.MAIPGL = &pic->ram[0xEA6];
        pic->P18map.MAIPGH = &pic->ram[0xEA7];
        pic->P18map.MAMXFLL = &pic->ram[0xEAA];
        pic->P18map.MAMXFLH = &pic->ram[0xEAB];
        pic->P18map.MICMD = &pic->ram[0xEB2];
        pic->P18map.MIREGADR = &pic->ram[0xEB4];
        pic->P18map.MIWRL = &pic->ram[0xEB6];
        pic->P18map.MIWRH = &pic->ram[0xEB7];
        pic->P18map.MIRDL = &pic->ram[0xEB8];
        pic->P18map.MIRDH = &pic->ram[0xEB9];
        pic->P18map.EHT0 = &pic->ram[0xEC0];
        pic->P18map.EHT1 = &pic->ram[0xEC1];
        pic->P18map.EHT2 = &pic->ram[0xEC2];
        pic->P18map.EHT3 = &pic->ram[0xEC3];
        pic->P18map.EHT4 = &pic->ram[0xEC4];
        pic->P18map.EHT5 = &pic->ram[0xEC5];
        pic->P18map.EHT6 = &pic->ram[0xEC6];
        pic->P18map.EHT7 = &pic->ram[0xEC7];
        pic->P18map.EPMM0 = &pic->ram[0xEC8];
        pic->P18map.EPMM1 = &pic->ram[0xEC9];
        pic->P18map.EPMM2 = &pic->ram[0xECA];
        pic->P18map.EPMM3 = &pic->ram[0xECB];
        pic->P18map.EPMM4 = &pic->ram[0xECC];
        pic->P18map.EPMM5 = &pic->ram[0xECD];
        pic->P18map.EPMM6 = &pic->ram[0xECE];
        pic->P18map.EPMM7 = &pic->ram[0xECF];
        pic->P18map.EPMCSL = &pic->ram[0xED0];
        pic->P18map.EPMCSH = &pic->ram[0xED1];
        pic->P18map.EPMOL = &pic->ram[0xED4];
        pic->P18map.EPMOH = &pic->ram[0xED5];
        pic->P18map.ERXFCON = &pic->ram[0xED8];
        pic->P18map.EPKTCNT = &pic->ram[0xED9];
        pic->P18map.EWRPTL = &pic->ram[0xEE2];
        pic->P18map.EWRPTH = &pic->ram[0xEE3];
        pic->P18map.ETXSTL = &pic->ram[0xEE4];
        pic->P18map.ETXSTH = &pic->ram[0xEE5];
        pic->P18map.ETXNDL = &pic->ram[0xEE6];
        pic->P18map.ETXNDH = &pic->ram[0xEE7];
        pic->P18map.ERXSTL = &pic->ram[0xEE8];
        pic->P18map.ERXSTH = &pic->ram[0xEE9];
        pic->P18map.ERXNDL = &pic->ram[0xEEA];
        pic->P18map.ERXNDH = &pic->ram[0xEEB];
        pic->P18map.ERXRDPTL = &pic->ram[0xEEC];
        pic->P18map.ERXRDPTH = &pic->ram[0xEED];
        pic->P18map.ERXWRPTL = &pic->ram[0xEEE];
        pic->P18map.ERXWRPTH = &pic->ram[0xEEF];
        pic->P18map.EDMASTL = &pic->ram[0xEF0];
        pic->P18map.EDMASTH = &pic->ram[0xEF1];
        pic->P18map.EDMANDL = &pic->ram[0xEF2];
        pic->P18map.EDMANDH = &pic->ram[0xEF3];
        pic->P18map.EDMADSTL = &pic->ram[0xEF4];
        pic->P18map.EDMADSTH = &pic->ram[0xEF5];
        pic->P18map.EDMACSL = &pic->ram[0xEF6];
        pic->P18map.EDMACSH = &pic->ram[0xEF7];
        pic->P18map.EIE = &pic->ram[0xEFB];
        pic->P18map.ESTAT = &pic->ram[0xEFD];
        pic->P18map.ECON2 = &pic->ram[0xEFE];
        pic->P18map.EIR = &pic->ram[0xF60];
        pic->P18map.EDATA = &pic->ram[0xF61];
        pic->P18map.ECCP2DEL = &pic->ram[0xF67];
        pic->P18map.ECCP2AS = &pic->ram[0xF68];
        pic->P18map.ECCP3DEL = &pic->ram[0xF69];
        pic->P18map.ECCP3AS = &pic->ram[0xF6A];
        pic->P18map.CCP5CON = &pic->ram[0xF70];
        pic->P18map.CCPR5L = &pic->ram[0xF71];
        pic->P18map.CCPR5H = &pic->ram[0xF72];
        pic->P18map.CCP4CON = &pic->ram[0xF73];
        pic->P18map.CCPR4L = &pic->ram[0xF74];
        pic->P18map.CCPR4H = &pic->ram[0xF75];
        pic->P18map.T4CON = &pic->ram[0xF76];
        pic->P18map.PR4 = &pic->ram[0xF77];
        pic->P18map.TMR4 = &pic->ram[0xF78];
        pic->P18map.ECCP1DEL = &pic->ram[0xF79];
        pic->P18map.ERDPTL = &pic->ram[0xF7A];
        pic->P18map.ERDPTH = &pic->ram[0xF7B];
    */
    pic->P18map.BAUDCON1 = &pic->ram[0xF7E];
    pic->P18map.SPBRGH1 = &pic->ram[0xF7F];
    pic->P18map.PORTA = &pic->ram[0xF80];
    pic->P18map.PORTB = &pic->ram[0xF81];
    pic->P18map.PORTC = &pic->ram[0xF82];
    pic->P18map.PORTD = &pic->ram[0xF83];
    pic->P18map.PORTE = &pic->ram[0xF84];
    pic->P18map.PORTF = &pic->ram[0xF85];
    pic->P18map.PORTG = &pic->ram[0xF86];
    pic->P18map.LATA = &pic->ram[0xF89];
    pic->P18map.LATB = &pic->ram[0xF8A];
    pic->P18map.LATC = &pic->ram[0xF8B];
    pic->P18map.LATD = &pic->ram[0xF8C];
    pic->P18map.LATE = &pic->ram[0xF8D];
    pic->P18map.LATF = &pic->ram[0xF8E];
    pic->P18map.LATG = &pic->ram[0xF8F];
    pic->P18map.TRISA = &pic->ram[0xF92];
    pic->P18map.TRISB = &pic->ram[0xF93];
    pic->P18map.TRISC = &pic->ram[0xF94];
    pic->P18map.TRISD = &pic->ram[0xF95];
    pic->P18map.TRISE = &pic->ram[0xF96];
    pic->P18map.TRISF = &pic->ram[0xF97];
    pic->P18map.TRISG = &pic->ram[0xF98];
    // pic->P18map.OSCTUNE = &pic->ram[0xF9B];
    pic->P18map.PIE1 = &pic->ram[0xF9D];
    pic->P18map.PIR1 = &pic->ram[0xF9E];
    pic->P18map.IPR1 = &pic->ram[0xF9F];
    pic->P18map.PIE2 = &pic->ram[0xFA0];
    pic->P18map.PIR2 = &pic->ram[0xFA1];
    pic->P18map.IPR2 = &pic->ram[0xFA2];
    pic->P18map.PIE3 = &pic->ram[0xFA3];
    pic->P18map.PIR3 = &pic->ram[0xFA4];
    pic->P18map.IPR3 = &pic->ram[0xFA5];
    pic->P18map.EECON1 = &pic->ram[0xFA6];
    pic->P18map.EECON2 = &pic->ram[0xFA7];
    pic->P18map.RCSTA = &pic->ram[0xFAB];
    pic->P18map.TXSTA = &pic->ram[0xFAC];
    pic->P18map.TXREG = &pic->ram[0xFAD];
    pic->P18map.RCREG = &pic->ram[0xFAE];
    pic->P18map.SPBRG = &pic->ram[0xFAF];
    pic->P18map.T3CON = &pic->ram[0xFB1];
    pic->P18map.TMR3L = &pic->ram[0xFB2];
    pic->P18map.TMR3H = &pic->ram[0xFB3];
    /*
        pic->P18map.CMCON = &pic->ram[0xFB4];
        pic->P18map.CVRCON = &pic->ram[0xFB5];
        pic->P18map.ECCP1AS = &pic->ram[0xFB6];
        pic->P18map.CCP3CON = &pic->ram[0xFB7];
        pic->P18map.CCPR3L = &pic->ram[0xFB8];
        pic->P18map.CCPR3H = &pic->ram[0xFB9];
    */
    pic->P18map.CCP2CON = &pic->ram[0xFBA];
    pic->P18map.CCPR2L = &pic->ram[0xFBB];
    pic->P18map.CCPR2H = &pic->ram[0xFBC];
    pic->P18map.CCP1CON = &pic->ram[0xFBD];
    pic->P18map.CCPR1L = &pic->ram[0xFBE];
    pic->P18map.CCPR1H = &pic->ram[0xFBF];
    pic->P18map.ADCON2 = &pic->ram[0xFC0];
    pic->P18map.ADCON1 = &pic->ram[0xFC1];
    pic->P18map.ADCON0 = &pic->ram[0xFC2];
    pic->P18map.ADRESL = &pic->ram[0xFC3];
    pic->P18map.ADRESH = &pic->ram[0xFC4];
    pic->P18map.SSPCON2 = &pic->ram[0xFC5];
    pic->P18map.SSPCON1 = &pic->ram[0xFC6];
    pic->P18map.SSPSTAT = &pic->ram[0xFC7];
    pic->P18map.SSPADD = &pic->ram[0xFC8];
    pic->P18map.SSPBUF = &pic->ram[0xFC9];
    pic->P18map.T2CON = &pic->ram[0xFCA];
    pic->P18map.PR2 = &pic->ram[0xFCB];
    pic->P18map.TMR2 = &pic->ram[0xFCC];
    pic->P18map.T1CON = &pic->ram[0xFCD];
    pic->P18map.TMR1L = &pic->ram[0xFCE];
    pic->P18map.TMR1H = &pic->ram[0xFCF];
    pic->P18map.RCON = &pic->ram[0xFD0];
    pic->P18map.WDTCON = &pic->ram[0xFD1];
    // pic->P18map.ECON1 = &pic->ram[0xFD2];
    // pic->P18map.OSCCON = &pic->ram[0xFD3];
    pic->P18map.T0CON = &pic->ram[0xFD5];
    pic->P18map.TMR0L = &pic->ram[0xFD6];
    pic->P18map.TMR0H = &pic->ram[0xFD7];
    pic->P18map.STATUS = &pic->ram[0xFD8];
    pic->P18map.FSR2L = &pic->ram[0xFD9];
    pic->P18map.FSR2H = &pic->ram[0xFDA];
    pic->P18map.PLUSW2 = &pic->ram[0xFDB];
    pic->P18map.PREINC2 = &pic->ram[0xFDC];
    pic->P18map.POSTDEC2 = &pic->ram[0xFDD];
    pic->P18map.POSTINC2 = &pic->ram[0xFDE];
    pic->P18map.INDF2 = &pic->ram[0xFDF];
    pic->P18map.BSR = &pic->ram[0xFE0];
    pic->P18map.FSR1L = &pic->ram[0xFE1];
    pic->P18map.FSR1H = &pic->ram[0xFE2];
    pic->P18map.PLUSW1 = &pic->ram[0xFE3];
    pic->P18map.PREINC1 = &pic->ram[0xFE4];
    pic->P18map.POSTDEC1 = &pic->ram[0xFE5];
    pic->P18map.POSTINC1 = &pic->ram[0xFE6];
    pic->P18map.INDF1 = &pic->ram[0xFE7];
    pic->P18map.WREG = &pic->ram[0xFE8];
    pic->P18map.FSR0L = &pic->ram[0xFE9];
    pic->P18map.FSR0H = &pic->ram[0xFEA];
    pic->P18map.PLUSW0 = &pic->ram[0xFEB];
    pic->P18map.PREINC0 = &pic->ram[0xFEC];
    pic->P18map.POSTDEC0 = &pic->ram[0xFED];
    pic->P18map.POSTINC0 = &pic->ram[0xFEE];
    pic->P18map.INDF0 = &pic->ram[0xFEF];
    pic->P18map.INTCON3 = &pic->ram[0xFF0];
    pic->P18map.INTCON2 = &pic->ram[0xFF1];
    pic->P18map.INTCON = &pic->ram[0xFF2];
    pic->P18map.PRODL = &pic->ram[0xFF3];
    pic->P18map.PRODH = &pic->ram[0xFF4];
    pic->P18map.TABLAT = &pic->ram[0xFF5];
    pic->P18map.TBLPTRL = &pic->ram[0xFF6];
    pic->P18map.TBLPTRH = &pic->ram[0xFF7];
    pic->P18map.TBLPTRU = &pic->ram[0xFF8];
    pic->P18map.PCL = &pic->ram[0xFF9];
    pic->P18map.PCLATH = &pic->ram[0xFFA];
    pic->P18map.PCLATU = &pic->ram[0xFFB];
    pic->P18map.STKPTR = &pic->ram[0xFFC];
    pic->P18map.TOSL = &pic->ram[0xFFD];
    pic->P18map.TOSH = &pic->ram[0xFFE];
    pic->P18map.TOSU = &pic->ram[0xFFF];
}

/*PINS

01 - RE1 P2C
02 - RE0 P2D
03 - RB0 INT0 FLT0
04 - RB1 INT1
05 - RB2 INT2
06 - RB3 INT3
07 - MCLR
08 - RG4 CCP5 P1D
09 - Vss
10 - Vddcore Vcap
11 - RF7 SS1
12 - RF6 AN11
13 - RF5 AN10 CVref
14 - RF4 AN9
15 - RF3 AN8
16 - RF2 AN7 C1OUT
17 - RF1 AN6 C2OUT
18 - ENVREG
19 - AVdd
20 - AVss
21 - RA3 AN3 Vref+
22 - RA2 AN2 Vref-
23 - RA1 LEDB AN1
24 - RA0 LEDA AN0
25 - Vss
26 - Vdd
27 - RA5 AN4
28 - RA4 T0CKI
29 - RC1 T1OSI ECCP2 P2A
30 - RC0 T1OSO T13CKI
31 - RC6 TX1 CK1
32 - RC7 RX1 DT1
33 - RC2 ECCP1 P1A
34 - RC3 SCK1 SCL1
35 - RC4 SDI1 SDA1
36 - RC5 SDO1
37 - RB7 KBI3 PGD
38 - Vdd
39 - OSC1 CLKI
40 - OSC2 CLKO
41 - Vss
42 - RB6 KBI2 PGC
43 - RB5 KBI1
44 - RB4 KBI0
45 - Vssrx
46 - TPIN-
47 - TPIN+
48 - Vddrx
49 - Vddtx
50 - TPOUT-
51 - TPOUT+
52 - Vsstx
53 - RBIAS
54 - Vddpll
55 - Vsspll
56 - Vss
57 - Vdd
58 - RD2 CCP4 P3D
59 - RD1 ECCP3 P3A
60 - RD0 P1B
61 - RE5 P1C
62 - RE4 P3B
63 - RE3 P3C
64 - RE2 P2B
 */

#include "../p18/p18_periferic.h"

/*
======================
Family=P18
processor=PIC18F67J60
deviceid=0x1f20
 */

void PIC18F67J60_reset(_pic* pic) {
    pic->pins[0].port = pic->P18map.PORTE;
    pic->pins[0].pord = 1;
    pic->pins[1].port = pic->P18map.PORTE;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P18map.PORTB;
    pic->pins[2].pord = 0;
    pic->pins[3].port = pic->P18map.PORTB;
    pic->pins[3].pord = 1;
    pic->pins[4].port = pic->P18map.PORTB;
    pic->pins[4].pord = 2;
    pic->pins[5].port = pic->P18map.PORTB;
    pic->pins[5].pord = 3;
    pic->pins[6].port = P_RST;
    pic->pins[6].pord = -1;
    pic->pins[7].port = pic->P18map.PORTG;
    pic->pins[7].pord = 4;
    pic->pins[8].port = P_VSS;
    pic->pins[8].pord = -1;
    pic->pins[10].port = pic->P18map.PORTF;
    pic->pins[10].pord = 7;
    pic->pins[11].port = pic->P18map.PORTF;
    pic->pins[11].pord = 6;
    pic->pins[12].port = pic->P18map.PORTF;
    pic->pins[12].pord = 5;
    pic->pins[13].port = pic->P18map.PORTF;
    pic->pins[13].pord = 4;
    pic->pins[14].port = pic->P18map.PORTF;
    pic->pins[14].pord = 3;
    pic->pins[15].port = pic->P18map.PORTF;
    pic->pins[15].pord = 2;
    pic->pins[16].port = pic->P18map.PORTF;
    pic->pins[16].pord = 1;
    pic->pins[17].port = P_NC;
    pic->pins[17].pord = -1;
    pic->pins[18].port = P_VDD;
    pic->pins[18].pord = -1;
    pic->pins[18].value = 1;
    pic->pins[19].port = P_VSS;
    pic->pins[19].pord = -1;
    pic->pins[20].port = pic->P18map.PORTA;
    pic->pins[20].pord = 3;
    pic->pins[21].port = pic->P18map.PORTA;
    pic->pins[21].pord = 2;
    pic->pins[22].port = pic->P18map.PORTA;
    pic->pins[22].pord = 1;
    pic->pins[23].port = pic->P18map.PORTA;
    pic->pins[23].pord = 0;
    pic->pins[24].port = P_VSS;
    pic->pins[24].pord = -1;
    pic->pins[25].port = P_VDD;
    pic->pins[25].pord = -1;
    pic->pins[25].value = 1;
    pic->pins[26].port = pic->P18map.PORTA;
    pic->pins[26].pord = 5;
    pic->pins[27].port = pic->P18map.PORTA;
    pic->pins[27].pord = 4;
    pic->pins[28].port = pic->P18map.PORTC;
    pic->pins[28].pord = 1;
    pic->pins[29].port = pic->P18map.PORTC;
    pic->pins[29].pord = 0;
    pic->pins[30].port = pic->P18map.PORTC;
    pic->pins[30].pord = 6;
    pic->pins[31].port = pic->P18map.PORTC;
    pic->pins[31].pord = 7;
    pic->pins[32].port = pic->P18map.PORTC;
    pic->pins[32].pord = 2;
    pic->pins[33].port = pic->P18map.PORTC;
    pic->pins[33].pord = 3;
    pic->pins[34].port = pic->P18map.PORTC;
    pic->pins[34].pord = 4;
    pic->pins[35].port = pic->P18map.PORTC;
    pic->pins[35].pord = 5;
    pic->pins[36].port = pic->P18map.PORTB;
    pic->pins[36].pord = 7;
    pic->pins[37].port = P_VDD;
    pic->pins[37].pord = -1;
    pic->pins[37].value = 1;
    pic->pins[38].port = P_OSC;
    pic->pins[38].pord = -1;
    pic->pins[39].port = P_OSC;
    pic->pins[39].pord = -1;
    pic->pins[40].port = P_VSS;
    pic->pins[40].pord = -1;
    pic->pins[41].port = pic->P18map.PORTB;
    pic->pins[41].pord = 6;
    pic->pins[42].port = pic->P18map.PORTB;
    pic->pins[42].pord = 5;
    pic->pins[43].port = pic->P18map.PORTB;
    pic->pins[43].pord = 4;

    pic->pins[45].port = P_NC;
    pic->pins[45].pord = -1;
    pic->pins[46].port = P_NC;
    pic->pins[46].pord = -1;
    pic->pins[47].port = P_NC;
    pic->pins[47].pord = -1;
    pic->pins[48].port = P_NC;
    pic->pins[48].pord = -1;
    pic->pins[49].port = P_NC;
    pic->pins[49].pord = -1;
    pic->pins[50].port = P_NC;
    pic->pins[50].pord = -1;
    pic->pins[51].port = P_NC;
    pic->pins[51].pord = -1;
    pic->pins[52].port = P_NC;
    pic->pins[52].pord = -1;
    pic->pins[53].port = P_NC;
    pic->pins[53].pord = -1;
    pic->pins[54].port = P_NC;
    pic->pins[54].pord = -1;
    pic->pins[55].port = P_NC;
    pic->pins[55].pord = -1;

    pic->pins[56].port = P_VDD;
    pic->pins[56].pord = -1;
    pic->pins[56].value = 1;
    pic->pins[57].port = pic->P18map.PORTD;
    pic->pins[57].pord = 2;
    pic->pins[58].port = pic->P18map.PORTD;
    pic->pins[58].pord = 1;
    pic->pins[59].port = pic->P18map.PORTD;
    pic->pins[59].pord = 0;
    pic->pins[60].port = pic->P18map.PORTE;
    pic->pins[60].pord = 5;
    pic->pins[61].port = pic->P18map.PORTE;
    pic->pins[61].pord = 4;
    pic->pins[62].port = pic->P18map.PORTE;
    pic->pins[62].pord = 3;
    pic->pins[63].port = pic->P18map.PORTE;
    pic->pins[63].pord = 2;

    pic->mclr = 7;

    pic->ccp[0].pin = 0;
    pic->ccp[1].pin = 0;
    pic->ccp[2].pin = 0;
    pic->ccp[3].pin = 59;
    pic->ccp[4].pin = 33;

    pic->adc[0] = 24;
    pic->adc[1] = 23;
    pic->adc[2] = 22;
    pic->adc[3] = 21;
    pic->adc[4] = 27;
    pic->adc[5] = 0;
    pic->adc[6] = 17;
    pic->adc[7] = 16;
    pic->adc[8] = 15;
    pic->adc[9] = 14;
    pic->adc[10] = 13;

    pic->usart_rx[0] = 48;
    pic->usart_tx[0] = 52;

    pic->pgc = 42;
    pic->pgd = 37;

    pic->sck = 34;
    pic->sdo = 36;
    pic->sdi = 35;

    pic->t0cki = 28;
    pic->t1cki = 30;

    pic->int0 = 3;
    pic->int1 = 4;
    pic->int2 = 5;

    p18_tmr0_rst(pic);
    p18_tmr1_rst(pic);
    p18_tmr2_rst(pic);
    p18_adc_rst(pic);
    p18_wdt_rst(pic);
    p18_eeprom_rst(pic);
    p18_mssp_rst(pic);
    p18_int_pin_rst(pic);
    p18_int_portb_rst(pic);
    // p18_int_ports_rst(pic);
    p18_uart_rst(pic, 0);
}

void PIC18F67J60_periferic(_pic* pic) {
    p18_mssp(pic);
    p18_adc(pic);
    p18_int_pin(pic);
    p18_int_portb(pic);
    // p18_int_ports(pic);
    p18_tmr0(pic);
    p18_wdt(pic);
    p18_eeprom(pic);
    p18_tmr1(pic);
    p18_tmr2(pic);
    p18_uart(pic, 0);
}

int PIC18F67J60_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return 1;
            break;
        case CFG_WDT:
            return ((pic->config[0] & 0x0001) > 0);
            break;
        case CFG_WDT_DIV:
            return (pic->config[3] & 0x000F);
            break;
        case CFG_DEBUG:
            return ((pic->config[0] & 0x8000) == 0);
            break;
    }
    return 0;
}

void PIC18F67J60_disable_debug(_pic* pic) {
    pic->config[0] |= 0x8000;
}

void PIC18F67J60_stop(_pic* pic) {
    p18_uart_stop(pic, 0);
}

void PIC18F67J60_start(_pic* pic) {
    pic->ROMSIZE = 65532;
    pic->EEPROMSIZE = 0;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 64;
    pic->IDSIZE = 0;
    pic->CONFIGSIZE = 3;
    pic->STACKSIZE = 31;
    pic->CCPCOUNT = 5;
    pic->ADCCOUNT = 11;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 4;
    pic->reset = PIC18F67J60_reset;
    pic->mmap = PIC18F67J60_map;
    pic->getconf = PIC18F67J60_getconf;
    pic->periferic = PIC18F67J60_periferic;
    pic->interrupt = interrupt18;
    pic->stop = PIC18F67J60_stop;
    pic->disable_debug = PIC18F67J60_disable_debug;

    p18_uart_start(pic, 0);
}

init_pic(PIC18F67J60, P18, 0x1f20);
