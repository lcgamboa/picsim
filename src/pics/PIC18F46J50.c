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

#include <string.h>
#include "../../include/picsim.h"

#define RCREG1 RC1REG
#define TXREG1 TX1REG
#define SPBRG1 SP1BRGL
#define SPBRGH1 SP1BRGH
#define RCSTA1 RC1STA
#define TXSTA1 TX1STA

#define RCREG2 RC2REG
#define TXREG2 TX2REG
#define SPBRG2 SP2BRGL
#define SPBRGH2 SP2BRGH
#define RCSTA2 RC2STA
#define TXSTA2 TX2STA

void PIC18F46J50_map(_pic* pic) {
    memset(&pic->P18map, 0, sizeof(P18map_t));
    /*
     pic->P18map.RPOR0 = &pic->ram[0xEC6];
     pic->P18map.RPOR1 = &pic->ram[0xEC7];
     pic->P18map.RPOR2 = &pic->ram[0xEC8];
     pic->P18map.RPOR3 = &pic->ram[0xEC9];
     pic->P18map.RPOR4 = &pic->ram[0xECA];
     pic->P18map.RPOR5 = &pic->ram[0xECB];
     pic->P18map.RPOR6 = &pic->ram[0xECC];
     pic->P18map.RPOR7 = &pic->ram[0xECD];
     pic->P18map.RPOR8 = &pic->ram[0xECE];
     pic->P18map.RPOR9 = &pic->ram[0xECF];
     pic->P18map.RPOR10 = &pic->ram[0xED0];
     pic->P18map.RPOR11 = &pic->ram[0xED1];
     pic->P18map.RPOR12 = &pic->ram[0xED2];
     pic->P18map.RPOR13 = &pic->ram[0xED3];
     pic->P18map.RPOR17 = &pic->ram[0xED7];
     pic->P18map.RPOR18 = &pic->ram[0xED8];
     pic->P18map.RPOR19 = &pic->ram[0xED9];
     pic->P18map.RPOR20 = &pic->ram[0xEDA];
     pic->P18map.RPOR21 = &pic->ram[0xEDB];
     pic->P18map.RPOR22 = &pic->ram[0xEDC];
     pic->P18map.RPOR23 = &pic->ram[0xEDD];
     pic->P18map.RPOR24 = &pic->ram[0xEDE];
     pic->P18map.RPINR1 = &pic->ram[0xEE7];
     pic->P18map.RPINR2 = &pic->ram[0xEE8];
     pic->P18map.RPINR3 = &pic->ram[0xEE9];
     pic->P18map.RPINR4 = &pic->ram[0xEEA];
     pic->P18map.RPINR6 = &pic->ram[0xEEC];
     pic->P18map.RPINR7 = &pic->ram[0xEED];
     pic->P18map.RPINR8 = &pic->ram[0xEEE];
     pic->P18map.RPINR12 = &pic->ram[0xEF2];
     pic->P18map.RPINR13 = &pic->ram[0xEF3];
     pic->P18map.RPINR16 = &pic->ram[0xEF6];
     pic->P18map.RPINR17 = &pic->ram[0xEF7];
     pic->P18map.RPINR21 = &pic->ram[0xEFB];
     pic->P18map.RPINR22 = &pic->ram[0xEFC];
     pic->P18map.RPINR23 = &pic->ram[0xEFD];
     pic->P18map.RPINR24 = &pic->ram[0xEFE];
     pic->P18map.PPSCON = &pic->ram[0xEFF];
     pic->P18map.UEP0 = &pic->ram[0xF26];
     pic->P18map.UEP1 = &pic->ram[0xF27];
     pic->P18map.UEP2 = &pic->ram[0xF28];
     pic->P18map.UEP3 = &pic->ram[0xF29];
     pic->P18map.UEP4 = &pic->ram[0xF2A];
     pic->P18map.UEP5 = &pic->ram[0xF2B];
     pic->P18map.UEP6 = &pic->ram[0xF2C];
     pic->P18map.UEP7 = &pic->ram[0xF2D];
     pic->P18map.UEP8 = &pic->ram[0xF2E];
     pic->P18map.UEP9 = &pic->ram[0xF2F];
     pic->P18map.UEP10 = &pic->ram[0xF30];
     pic->P18map.UEP11 = &pic->ram[0xF31];
     pic->P18map.UEP12 = &pic->ram[0xF32];
     pic->P18map.UEP13 = &pic->ram[0xF33];
     pic->P18map.UEP14 = &pic->ram[0xF34];
     pic->P18map.UEP15 = &pic->ram[0xF35];
     pic->P18map.UIE = &pic->ram[0xF36];
     pic->P18map.UEIE = &pic->ram[0xF37];
     pic->P18map.UADDR = &pic->ram[0xF38];
     pic->P18map.UCFG = &pic->ram[0xF39];
     pic->P18map.PADCFG1 = &pic->ram[0xF3C];
     pic->P18map.REFOCON = &pic->ram[0xF3D];
     pic->P18map.RTCCAL = &pic->ram[0xF3E];
     pic->P18map.RTCCFG = &pic->ram[0xF3F];
     pic->P18map.ODCON3 = &pic->ram[0xF40];
     pic->P18map.ODCON2 = &pic->ram[0xF41];
     pic->P18map.ODCON1 = &pic->ram[0xF42];
     pic->P18map.ANCON0 = &pic->ram[0xF48];
     pic->P18map.ANCON1 = &pic->ram[0xF49];
     pic->P18map.DSWAKEL = &pic->ram[0xF4A];
     pic->P18map.DSWAKEH = &pic->ram[0xF4B];
     pic->P18map.DSCONL = &pic->ram[0xF4C];
     pic->P18map.DSCONH = &pic->ram[0xF4D];
     pic->P18map.DSGPR0 = &pic->ram[0xF4E];
     pic->P18map.DSGPR1 = &pic->ram[0xF4F];
     pic->P18map.TCLKCON = &pic->ram[0xF52];
     pic->P18map.CVRCON = &pic->ram[0xF53];
     pic->P18map.PMSTATL = &pic->ram[0xF54];
     pic->P18map.PMSTATH = &pic->ram[0xF55];
     pic->P18map.PMEL = &pic->ram[0xF56];
     pic->P18map.PMEH = &pic->ram[0xF57];
     pic->P18map.PMDIN2L = &pic->ram[0xF58];
     pic->P18map.PMDIN2H = &pic->ram[0xF59];
     pic->P18map.PMDOUT2L = &pic->ram[0xF5A];
     pic->P18map.PMDOUT2H = &pic->ram[0xF5B];
     pic->P18map.PMMODEL = &pic->ram[0xF5C];
     pic->P18map.PMMODEH = &pic->ram[0xF5D];
     pic->P18map.PMCONL = &pic->ram[0xF5E];
     pic->P18map.PMCONH = &pic->ram[0xF5F];
     pic->P18map.UFRML = &pic->ram[0xF60];
     pic->P18map.UFRMH = &pic->ram[0xF61];
     pic->P18map.UIR = &pic->ram[0xF62];
     pic->P18map.UEIR = &pic->ram[0xF63];
     pic->P18map.USTAT = &pic->ram[0xF64];
     pic->P18map.UCON = &pic->ram[0xF65];
     pic->P18map.DMABCH = &pic->ram[0xF66];
     pic->P18map.DMABCL = &pic->ram[0xF67];
     pic->P18map.RXADDRH = &pic->ram[0xF68];
     pic->P18map.RXADDRL = &pic->ram[0xF69];
     pic->P18map.TXADDRH = &pic->ram[0xF6A];
     pic->P18map.TXADDRL = &pic->ram[0xF6B];
     pic->P18map.PMDIN1L = &pic->ram[0xF6C];
     pic->P18map.PMDIN1H = &pic->ram[0xF6D];
     pic->P18map.CMSTAT = &pic->ram[0xF70];
     pic->P18map.SSP2CON2 = &pic->ram[0xF71];
     pic->P18map.SSP2CON1 = &pic->ram[0xF72];
     pic->P18map.SSP2STAT = &pic->ram[0xF73];
     pic->P18map.SSP2ADD = &pic->ram[0xF74];
     pic->P18map.SSP2BUF = &pic->ram[0xF75];
     pic->P18map.T4CON = &pic->ram[0xF76];
     pic->P18map.PR4 = &pic->ram[0xF77];
     pic->P18map.TMR4 = &pic->ram[0xF78];
     */
    pic->P18map.T3CON = &pic->ram[0xF79];
    pic->P18map.TMR3L = &pic->ram[0xF7A];
    pic->P18map.TMR3H = &pic->ram[0xF7B];
    pic->P18map.BAUDCON2 = &pic->ram[0xF7C];
    pic->P18map.SPBRGH2 = &pic->ram[0xF7D];
    pic->P18map.BAUDCON1 = &pic->ram[0xF7E];
    pic->P18map.SPBRGH1 = &pic->ram[0xF7F];
    pic->P18map.PORTA = &pic->ram[0xF80];
    pic->P18map.PORTB = &pic->ram[0xF81];
    pic->P18map.PORTC = &pic->ram[0xF82];
    pic->P18map.PORTD = &pic->ram[0xF83];
    pic->P18map.PORTE = &pic->ram[0xF84];
    /*
    pic->P18map.HLVDCON = &pic->ram[0xF85];
    pic->P18map.DMACON2 = &pic->ram[0xF86];
    pic->P18map.DMACON1 = &pic->ram[0xF88];
    */
    pic->P18map.LATA = &pic->ram[0xF89];
    pic->P18map.LATB = &pic->ram[0xF8A];
    pic->P18map.LATC = &pic->ram[0xF8B];
    pic->P18map.LATD = &pic->ram[0xF8C];
    pic->P18map.LATE = &pic->ram[0xF8D];
    /*
    pic->P18map.ALRMVALL = &pic->ram[0xF8E];
    pic->P18map.ALRMVALH = &pic->ram[0xF8F];
    pic->P18map.ALRMRPT = &pic->ram[0xF90];
    pic->P18map.ALRMCFG = &pic->ram[0xF91];
    */
    pic->P18map.TRISA = &pic->ram[0xF92];
    pic->P18map.TRISB = &pic->ram[0xF93];
    pic->P18map.TRISC = &pic->ram[0xF94];
    pic->P18map.TRISD = &pic->ram[0xF95];
    pic->P18map.TRISE = &pic->ram[0xF96];
    /*
    pic->P18map.T3GCON = &pic->ram[0xF97];
    pic->P18map.RTCVALL = &pic->ram[0xF98];
    pic->P18map.RTCVALH = &pic->ram[0xF99];
    pic->P18map.T1GCON = &pic->ram[0xF9A];
    pic->P18map.OSCTUNE = &pic->ram[0xF9B];
     */
    pic->P18map.RCSTA2 = &pic->ram[0xF9C];
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
    pic->P18map.TXSTA2 = &pic->ram[0xFA8];
    pic->P18map.TXREG2 = &pic->ram[0xFA9];
    pic->P18map.RCREG2 = &pic->ram[0xFAA];
    pic->P18map.SPBRG2 = &pic->ram[0xFAB];
    pic->P18map.RCSTA1 = &pic->ram[0xFAC];
    pic->P18map.TXSTA1 = &pic->ram[0xFAD];
    pic->P18map.TXREG1 = &pic->ram[0xFAE];
    pic->P18map.RCREG1 = &pic->ram[0xFAF];
    pic->P18map.SPBRG1 = &pic->ram[0xFB0];
    /*
    pic->P18map.CTMUICON = &pic->ram[0xFB1];
    pic->P18map.CTMUCONL = &pic->ram[0xFB2];
    pic->P18map.CTMUCONH = &pic->ram[0xFB3];
    */
    pic->P18map.CCP2CON = &pic->ram[0xFB4];
    pic->P18map.CCPR2L = &pic->ram[0xFB5];
    pic->P18map.CCPR2H = &pic->ram[0xFB6];
    /*
    pic->P18map.ECCP2DEL = &pic->ram[0xFB7];
    pic->P18map.ECCP2AS = &pic->ram[0xFB8];
    pic->P18map.PSTR2CON = &pic->ram[0xFB9];
    */
    pic->P18map.CCP1CON = &pic->ram[0xFBA];
    pic->P18map.CCPR1L = &pic->ram[0xFBB];
    pic->P18map.CCPR1H = &pic->ram[0xFBC];
    /*
    pic->P18map.ECCP1DEL = &pic->ram[0xFBD];
    pic->P18map.ECCP1AS = &pic->ram[0xFBE];
    pic->P18map.PSTR1CON = &pic->ram[0xFBF];
    */
    pic->P18map.WDTCON = &pic->ram[0xFC0];
    pic->P18map.ADCON1 = &pic->ram[0xFC1];
    pic->P18map.ADCON0 = &pic->ram[0xFC2];
    pic->P18map.ADRESL = &pic->ram[0xFC3];
    pic->P18map.ADRESH = &pic->ram[0xFC4];
    pic->P18map.SSP1CON2 = &pic->ram[0xFC5];
    pic->P18map.SSP1CON1 = &pic->ram[0xFC6];
    pic->P18map.SSP1STAT = &pic->ram[0xFC7];
    pic->P18map.SSP1ADD = &pic->ram[0xFC8];
    pic->P18map.SSP1BUF = &pic->ram[0xFC9];
    pic->P18map.T2CON = &pic->ram[0xFCA];
    pic->P18map.PR2 = &pic->ram[0xFCB];
    pic->P18map.TMR2 = &pic->ram[0xFCC];
    pic->P18map.T1CON = &pic->ram[0xFCD];
    pic->P18map.TMR1L = &pic->ram[0xFCE];
    pic->P18map.TMR1H = &pic->ram[0xFCF];
    pic->P18map.RCON = &pic->ram[0xFD0];
    /*
    pic->P18map.CM2CON = &pic->ram[0xFD1];
    pic->P18map.CM1CON = &pic->ram[0xFD2];
    pic->P18map.OSCCON = &pic->ram[0xFD3];
    */
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

01 - RC7 PMA4 RX1 DT1 SDO1 RP18
02 - RD4 PMD4 RP21
03 - RD5 PMD5 RP22
04 - RD6 PMD6 RP23
05 - RD7 PMD7 RP24
06 - Vss
07 - AVdd
08 - Vdd
09 - RB0 AN12 INT0 RP3
10 - RB1 AN10 PMBE RTCC RP4
11 - RB2 AN8 CTED1 PMA3 VMO REFO RP5
12 - RB3 AN9 CTED2 PMA2 VPO RP6
13 - RB4 PMA1 KBI0 SCK1 SCL1 RP7
14 - RB5 PMA0 KBI1 SDI1 SDA1 RP8
15 - RB6 KBI2 PGC RP9
16 - RB7 KBI3 PGD RP10
17 - MCLR
18 - RA0 AN0 C1INA ULPWU PMA6 RP0
19 - RA1 AN1 C2INA PMA7 RP1
20 - RA2 AN2 Vref- CVref C2INB
21 - RA3 AN3 Vref+ C1INB
22 - Vddcore Vcap
23 - RA5 AN4 SS1 HLVDIN RCV RP2
24 - RE0 AN5 PMRD
25 - RE1 AN6 PMWR
26 - RE2 AN7 PMCS
27 - AVdd
28 - Vdd
29 - AVss
30 - Vss
31 - OSC1 CLKI RA7
32 - OSC2 CLKO RA6
33 - RC0 T1OSO T1CKI RP11
34 - RC1 T1OSI UOE RP12
35 - RC2 AN11 CTPLS RP13
36 - Vusb
37 - RD0 PMD0 SCL2
38 - RD1 PMD1 SDA2
39 - RD2 PMD2 RP19
40 - RD3 PMD3 RP20
41 - RC4 D- VM
42 - RC5 D+ VP
43 - RC6 PMA5 TX1 CK1 RP17
 */

#include "../p18/p18_periferic.h"

/*
======================
Family=P18
processor=PIC18F46J50
deviceid=0x4CA0
 */

void PIC18F46J50_reset(_pic* pic) {
    pic->pins[0].port = pic->P18map.PORTC;
    pic->pins[0].pord = 7;
    pic->pins[1].port = pic->P18map.PORTD;
    pic->pins[1].pord = 4;
    pic->pins[2].port = pic->P18map.PORTD;
    pic->pins[2].pord = 5;
    pic->pins[3].port = pic->P18map.PORTD;
    pic->pins[3].pord = 6;
    pic->pins[4].port = pic->P18map.PORTD;
    pic->pins[4].pord = 7;
    pic->pins[5].port = P_VSS;
    pic->pins[5].pord = -1;
    pic->pins[6].port = P_VDD;
    pic->pins[6].pord = -1;
    pic->pins[6].value = 1;
    pic->pins[7].port = pic->P18map.PORTB;
    pic->pins[7].pord = 0;
    pic->pins[8].port = pic->P18map.PORTB;
    pic->pins[8].pord = 1;
    pic->pins[9].port = pic->P18map.PORTB;
    pic->pins[9].pord = 2;
    pic->pins[10].port = pic->P18map.PORTB;
    pic->pins[10].pord = 3;
    pic->pins[11].port = P_NC;
    pic->pins[11].pord = -1;
    pic->pins[12].port = P_NC;
    pic->pins[12].pord = -1;
    pic->pins[13].port = pic->P18map.PORTB;
    pic->pins[13].pord = 4;
    pic->pins[14].port = pic->P18map.PORTB;
    pic->pins[14].pord = 5;
    pic->pins[15].port = pic->P18map.PORTB;
    pic->pins[15].pord = 6;
    pic->pins[16].port = pic->P18map.PORTB;
    pic->pins[16].pord = 7;
    pic->pins[17].port = P_RST;
    pic->pins[17].pord = -1;
    pic->pins[18].port = pic->P18map.PORTA;
    pic->pins[18].pord = 0;
    pic->pins[19].port = pic->P18map.PORTA;
    pic->pins[19].pord = 1;
    pic->pins[20].port = pic->P18map.PORTA;
    pic->pins[20].pord = 2;
    pic->pins[21].port = pic->P18map.PORTA;
    pic->pins[21].pord = 3;
    pic->pins[22].port = P_VDD;
    pic->pins[22].pord = -1;
    pic->pins[22].value = 1;  // vddcore
    pic->pins[23].port = pic->P18map.PORTA;
    pic->pins[23].pord = 5;
    pic->pins[24].port = pic->P18map.PORTE;
    pic->pins[24].pord = 0;
    pic->pins[25].port = pic->P18map.PORTE;
    pic->pins[25].pord = 1;
    pic->pins[26].port = pic->P18map.PORTE;
    pic->pins[26].pord = 2;
    pic->pins[27].port = P_VDD;
    pic->pins[27].pord = -1;
    pic->pins[27].value = 1;
    pic->pins[28].port = P_VSS;
    pic->pins[28].pord = -1;
    pic->pins[29].port = pic->P18map.PORTA;
    pic->pins[29].pord = 7;
    pic->pins[30].port = pic->P18map.PORTA;
    pic->pins[30].pord = 6;
    pic->pins[31].port = pic->P18map.PORTC;
    pic->pins[31].pord = 0;
    pic->pins[32].port = P_NC;
    pic->pins[32].pord = -1;
    pic->pins[33].port = P_NC;
    pic->pins[33].pord = -1;
    pic->pins[34].port = pic->P18map.PORTC;
    pic->pins[34].pord = 1;
    pic->pins[35].port = pic->P18map.PORTC;
    pic->pins[35].pord = 2;
    pic->pins[36].port = P_USB;
    pic->pins[36].pord = -1;
    pic->pins[37].port = pic->P18map.PORTD;
    pic->pins[37].pord = 0;
    pic->pins[38].port = pic->P18map.PORTD;
    pic->pins[38].pord = 1;
    pic->pins[39].port = pic->P18map.PORTD;
    pic->pins[39].pord = 2;
    pic->pins[40].port = pic->P18map.PORTD;
    pic->pins[40].pord = 3;
    pic->pins[41].port = pic->P18map.PORTC;
    pic->pins[41].pord = 4;
    pic->pins[42].port = pic->P18map.PORTC;
    pic->pins[42].pord = 5;
    pic->pins[43].port = pic->P18map.PORTC;
    pic->pins[43].pord = 6;

    pic->mclr = 18;

    pic->adc[0] = 19;
    pic->adc[1] = 20;
    pic->adc[2] = 21;
    pic->adc[3] = 22;
    pic->adc[4] = 24;
    pic->adc[5] = 25;
    pic->adc[6] = 26;
    pic->adc[7] = 27;
    pic->adc[8] = 10;
    pic->adc[9] = 11;
    pic->adc[10] = 9;
    pic->adc[11] = 36;
    pic->adc[12] = 8;

    pic->usart_rx[0] = 1;
    pic->usart_tx[0] = 44;

    pic->usart_rx[1] = 2;
    pic->usart_tx[1] = 3;

    pic->pgc = 16;
    pic->pgd = 17;

    pic->sck = 14;
    pic->sdo = 1;
    pic->sdi = 15;

    pic->t0cki = 31;  // virtual
    pic->t1cki = 32;

    pic->int0 = 8;
    pic->int1 = 9;   // virtual
    pic->int2 = 10;  // virtual

    // p18_pps_out_rst(pic);
    p18_tmr0_rst(pic);
    p18_tmr1_rst(pic);
    p18_tmr2_rst(pic);
    p18_adc_rst(pic);
    p18_wdt_rst(pic);
    p18_mssp_rst(pic);
    p18_int_pin_rst(pic);
    p18_int_portb_rst(pic);
    p18_uart_rst_2(pic, 0);
    // p18_uart_rst_2 (pic, 1);
}

void PIC18F46J50_periferic(_pic* pic) {
    // p18_pps_out(pic);
    // p18_mssp (pic);
    // p18_adc (pic);
    p18_int_pin(pic);
    p18_int_portb(pic);
    p18_tmr0(pic);
    p18_wdt(pic);
    p18_tmr1(pic);
    p18_tmr2(pic);
    p18_uart(pic, 0);
    // p18_uart (pic, 1);
}

int PIC18F46J50_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return 1;
            break;
        case CFG_WDT:
            return ((pic->config[0] & 0x0001) > 0);
            break;
        case CFG_WDT_DIV:
            return ((pic->config[1] & 0x0F00) >> 8);
            break;
        case CFG_DEBUG:
            return ((pic->config[0] & 0x0080) == 0);
            break;
    }
    return 0;
}

void PIC18F46J50_disable_debug(_pic* pic) {
    pic->config[0] |= 0x0080;
}

void PIC18F46J50_stop(_pic* pic) {
    p18_uart_stop(pic, 0);
    // p18_uart_stop (pic, 1);
}

void PIC18F46J50_start(_pic* pic) {
    pic->ROMSIZE = 32768;
    pic->EEPROMSIZE = 0;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 44;
    pic->IDSIZE = 0;
    pic->CONFIGSIZE = 4;
    pic->STACKSIZE = 31;
    pic->CCPCOUNT = 0;
    pic->ADCCOUNT = 13;
    pic->USARTCOUNT = 2;
    pic->WDT_MS = 4;
    pic->reset = PIC18F46J50_reset;
    pic->mmap = PIC18F46J50_map;
    pic->getconf = PIC18F46J50_getconf;
    pic->periferic = PIC18F46J50_periferic;
    pic->interrupt = interrupt18;
    pic->stop = PIC18F46J50_stop;
    pic->disable_debug = PIC18F46J50_disable_debug;

    p18_uart_start(pic, 0);
}

init_pic(PIC18F46J50, P18, 0x4CA0)
