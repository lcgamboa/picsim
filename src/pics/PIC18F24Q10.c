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

void PIC18F24Q10_map(_pic* pic) {
    memset(&pic->P18map, 0, sizeof(P18map_t));

    /*
    pic->P18map.PPSLOCK = &pic->ram[0xE9B];
    pic->P18map.INT0PPS = &pic->ram[0xE9C];
    pic->P18map.INT1PPS = &pic->ram[0xE9D];
    pic->P18map.INT2PPS = &pic->ram[0xE9E];
    pic->P18map.T0CKIPPS = &pic->ram[0xE9F];
    pic->P18map.T1CKIPPS = &pic->ram[0xEA0];
    pic->P18map.T1GPPS = &pic->ram[0xEA1];
    pic->P18map.T3CKIPPS = &pic->ram[0xEA2];
    pic->P18map.T3GPPS = &pic->ram[0xEA3];
    pic->P18map.T5CKIPPS = &pic->ram[0xEA4];
    pic->P18map.T5GPPS = &pic->ram[0xEA5];
    pic->P18map.T2INPPS = &pic->ram[0xEA6];
    pic->P18map.T4INPPS = &pic->ram[0xEA7];
    pic->P18map.T6INPPS = &pic->ram[0xEA8];
    pic->P18map.ADACTPPS = &pic->ram[0xEA9];
    pic->P18map.CCP1PPS = &pic->ram[0xEAA];
    pic->P18map.CCP2PPS = &pic->ram[0xEAB];
    pic->P18map.CWG1PPS = &pic->ram[0xEAC];
    pic->P18map.MDCARLPPS = &pic->ram[0xEAD];
    pic->P18map.MDCARHPPS = &pic->ram[0xEAE];
    pic->P18map.MDSRCPPS = &pic->ram[0xEAF];
    pic->P18map.RX1PPS = &pic->ram[0xEB0];
    pic->P18map.CK1PPS = &pic->ram[0xEB1];
    pic->P18map.SSP1CLKPPS = &pic->ram[0xEB2];
    pic->P18map.SSP1DATPPS = &pic->ram[0xEB3];
    pic->P18map.SSP1SSPPS = &pic->ram[0xEB4];
    */
    pic->P18map.IPR0 = &pic->ram[0xEB5];
    pic->P18map.IPR1 = &pic->ram[0xEB6];
    pic->P18map.IPR2 = &pic->ram[0xEB7];
    pic->P18map.IPR3 = &pic->ram[0xEB8];
    pic->P18map.IPR4 = &pic->ram[0xEB9];
    pic->P18map.IPR5 = &pic->ram[0xEBA];
    pic->P18map.IPR6 = &pic->ram[0xEBB];
    // pic->P18map.IPR7 = &pic->ram[0xEBC];
    pic->P18map.PIE0 = &pic->ram[0xEBD];
    pic->P18map.PIE1 = &pic->ram[0xEBE];
    pic->P18map.PIE2 = &pic->ram[0xEBF];
    pic->P18map.PIE3 = &pic->ram[0xEC0];
    pic->P18map.PIE4 = &pic->ram[0xEC1];
    pic->P18map.PIE5 = &pic->ram[0xEC2];
    pic->P18map.PIE6 = &pic->ram[0xEC3];
    // pic->P18map.PIE7 = &pic->ram[0xEC4];
    pic->P18map.PIR0 = &pic->ram[0xEC5];
    pic->P18map.PIR1 = &pic->ram[0xEC6];
    pic->P18map.PIR2 = &pic->ram[0xEC7];
    pic->P18map.PIR3 = &pic->ram[0xEC8];
    pic->P18map.PIR4 = &pic->ram[0xEC9];
    pic->P18map.PIR5 = &pic->ram[0xECA];
    pic->P18map.PIR6 = &pic->ram[0xECB];
    // pic->P18map.PIR7 = &pic->ram[0xECC];
    pic->P18map.WDTCON0 = &pic->ram[0xECD];
    /*
    pic->P18map.WDTCON1 = &pic->ram[0xECE];
    pic->P18map.WDTPSL = &pic->ram[0xECF];
    pic->P18map.WDTPSH = &pic->ram[0xED0];
    pic->P18map.WDTTMR = &pic->ram[0xED1];
    pic->P18map.CPUDOZE = &pic->ram[0xED2];
    pic->P18map.OSCCON1 = &pic->ram[0xED3];
    pic->P18map.OSCCON2 = &pic->ram[0xED4];
    pic->P18map.OSCCON3 = &pic->ram[0xED5];
    pic->P18map.OSCSTAT = &pic->ram[0xED6];
    pic->P18map.OSCEN = &pic->ram[0xED7];
    pic->P18map.OSCTUNE = &pic->ram[0xED8];
    pic->P18map.OSCFRQ = &pic->ram[0xED9];
    pic->P18map.VREGCON = &pic->ram[0xEDA];
    pic->P18map.BORCON = &pic->ram[0xEDB];
    pic->P18map.PMD0 = &pic->ram[0xEDC];
    pic->P18map.PMD1 = &pic->ram[0xEDD];
    pic->P18map.PMD2 = &pic->ram[0xEDE];
    pic->P18map.PMD3 = &pic->ram[0xEDF];
    pic->P18map.PMD4 = &pic->ram[0xEE0];
    pic->P18map.PMD5 = &pic->ram[0xEE1];
    */
    pic->P18map.RA0PPS = &pic->ram[0xEE2];
    pic->P18map.RA1PPS = &pic->ram[0xEE3];
    pic->P18map.RA2PPS = &pic->ram[0xEE4];
    pic->P18map.RA3PPS = &pic->ram[0xEE5];
    pic->P18map.RA4PPS = &pic->ram[0xEE6];
    pic->P18map.RA5PPS = &pic->ram[0xEE7];
    pic->P18map.RA6PPS = &pic->ram[0xEE8];
    pic->P18map.RA7PPS = &pic->ram[0xEE9];
    pic->P18map.RB0PPS = &pic->ram[0xEEA];
    pic->P18map.RB1PPS = &pic->ram[0xEEB];
    pic->P18map.RB2PPS = &pic->ram[0xEEC];
    pic->P18map.RB3PPS = &pic->ram[0xEED];
    pic->P18map.RB4PPS = &pic->ram[0xEEE];
    pic->P18map.RB5PPS = &pic->ram[0xEEF];
    pic->P18map.RB6PPS = &pic->ram[0xEF0];
    pic->P18map.RB7PPS = &pic->ram[0xEF1];
    pic->P18map.RC0PPS = &pic->ram[0xEF2];
    pic->P18map.RC1PPS = &pic->ram[0xEF3];
    pic->P18map.RC2PPS = &pic->ram[0xEF4];
    pic->P18map.RC3PPS = &pic->ram[0xEF5];
    pic->P18map.RC4PPS = &pic->ram[0xEF6];
    pic->P18map.RC5PPS = &pic->ram[0xEF7];
    pic->P18map.RC6PPS = &pic->ram[0xEF8];
    pic->P18map.RC7PPS = &pic->ram[0xEF9];
    /*
    pic->P18map.IOCAF = &pic->ram[0xF05];
    pic->P18map.IOCAN = &pic->ram[0xF06];
    pic->P18map.IOCAP = &pic->ram[0xF07];
    pic->P18map.INLVLA = &pic->ram[0xF08];
    pic->P18map.SLRCONA = &pic->ram[0xF09];
    pic->P18map.ODCONA = &pic->ram[0xF0A];
    pic->P18map.WPUA = &pic->ram[0xF0B];
    */
    pic->P18map.ANSELA = &pic->ram[0xF0C];
    pic->P18map.IOCBF = &pic->ram[0xF0D];
    pic->P18map.IOCBN = &pic->ram[0xF0E];
    pic->P18map.IOCBP = &pic->ram[0xF0F];
    /*
    pic->P18map.INLVLB = &pic->ram[0xF10];
    pic->P18map.SLRCONB = &pic->ram[0xF11];
    pic->P18map.ODCONB = &pic->ram[0xF12];
    pic->P18map.WPUB = &pic->ram[0xF13];
    */
    pic->P18map.ANSELB = &pic->ram[0xF14];
    /*
    pic->P18map.IOCCF = &pic->ram[0xF15];
    pic->P18map.IOCCN = &pic->ram[0xF16];
    pic->P18map.IOCCP = &pic->ram[0xF17];
    pic->P18map.INLVLC = &pic->ram[0xF18];
    pic->P18map.SLRCONC = &pic->ram[0xF19];
    pic->P18map.ODCONC = &pic->ram[0xF1A];
    pic->P18map.WPUC = &pic->ram[0xF1B];
    */
    pic->P18map.ANSELC = &pic->ram[0xF1C];
    /*
    pic->P18map.IOCEF = &pic->ram[0xF22];
    pic->P18map.IOCEN = &pic->ram[0xF23];
    pic->P18map.IOCEP = &pic->ram[0xF24];
    pic->P18map.INLVLE = &pic->ram[0xF25];
    pic->P18map.WPUE = &pic->ram[0xF28];
    pic->P18map.HLVDCON0 = &pic->ram[0xF2A];
    pic->P18map.HLVDCON1 = &pic->ram[0xF2B];
    pic->P18map.FVRCON = &pic->ram[0xF2C];
    pic->P18map.ZCDCON = &pic->ram[0xF2D];
    pic->P18map.DAC1CON0 = &pic->ram[0xF2E];
    pic->P18map.DAC1CON1 = &pic->ram[0xF2F];
    pic->P18map.CM2CON0 = &pic->ram[0xF30];
    pic->P18map.CM2CON1 = &pic->ram[0xF31];
    pic->P18map.CM2NCH = &pic->ram[0xF32];
    pic->P18map.CM2PCH = &pic->ram[0xF33];
    pic->P18map.CM1CON0 = &pic->ram[0xF34];
    pic->P18map.CM1CON1 = &pic->ram[0xF35];
    pic->P18map.CM1NCH = &pic->ram[0xF36];
    pic->P18map.CM1PCH = &pic->ram[0xF37];
    pic->P18map.CMOUT = &pic->ram[0xF38];
    pic->P18map.CLKRCON = &pic->ram[0xF39];
    pic->P18map.CLKRCLK = &pic->ram[0xF3A];
    pic->P18map.CWG1CLK = &pic->ram[0xF3B];
    pic->P18map.CWG1ISM = &pic->ram[0xF3C];
    pic->P18map.CWG1DBR = &pic->ram[0xF3D];
    pic->P18map.CWG1DBF = &pic->ram[0xF3E];
    pic->P18map.CWG1CON0 = &pic->ram[0xF3F];
    pic->P18map.CWG1CON1 = &pic->ram[0xF40];
    pic->P18map.CWG1AS0 = &pic->ram[0xF41];
    pic->P18map.CWG1AS1 = &pic->ram[0xF42];
    pic->P18map.CWG1STR = &pic->ram[0xF43];
    pic->P18map.SCANLADRL = &pic->ram[0xF44];
    pic->P18map.SCANLADRH = &pic->ram[0xF45];
    pic->P18map.SCANLADRU = &pic->ram[0xF46];
    pic->P18map.SCANHADRL = &pic->ram[0xF47];
    pic->P18map.SCANHADRH = &pic->ram[0xF48];
    pic->P18map.SCANHADRU = &pic->ram[0xF49];
    pic->P18map.SCANCON0 = &pic->ram[0xF4A];
    pic->P18map.SCANTRIG = &pic->ram[0xF4B];
    pic->P18map.MDCON0 = &pic->ram[0xF4C];
    pic->P18map.MDCON1 = &pic->ram[0xF4D];
    pic->P18map.MDSRC = &pic->ram[0xF4E];
    pic->P18map.MDCARL = &pic->ram[0xF4F];
    pic->P18map.MDCARH = &pic->ram[0xF50];
    pic->P18map.ADACT = &pic->ram[0xF51];
    pic->P18map.ADCLK = &pic->ram[0xF52];
    pic->P18map.ADREF = &pic->ram[0xF53];
    */
    pic->P18map.ADCON1 = &pic->ram[0xF54];
    pic->P18map.ADCON2 = &pic->ram[0xF55];
    pic->P18map.ADCON3 = &pic->ram[0xF56];
    /*
    pic->P18map.ADACQ = &pic->ram[0xF57];
    pic->P18map.ADCAP = &pic->ram[0xF58];
    pic->P18map.ADPRE = &pic->ram[0xF59];
    */
    pic->P18map.ADPCH = &pic->ram[0xF5A];
    pic->P18map.ADCON0 = &pic->ram[0xF5B];
    /*
    pic->P18map.ADPREVL = &pic->ram[0xF5C];
    pic->P18map.ADPREVH = &pic->ram[0xF5D];
    */
    pic->P18map.ADRESL = &pic->ram[0xF5E];
    pic->P18map.ADRESH = &pic->ram[0xF5F];
    /*
    pic->P18map.ADSTAT = &pic->ram[0xF60];
    pic->P18map.ADRPT = &pic->ram[0xF61];
    pic->P18map.ADCNT = &pic->ram[0xF62];
    pic->P18map.ADSTPTL = &pic->ram[0xF63];
    pic->P18map.ADSTPTH = &pic->ram[0xF64];
    pic->P18map.ADLTHL = &pic->ram[0xF65];
    pic->P18map.ADLTHH = &pic->ram[0xF66];
    pic->P18map.ADUTHL = &pic->ram[0xF67];
    pic->P18map.ADUTHH = &pic->ram[0xF68];
    pic->P18map.ADERRL = &pic->ram[0xF69];
    pic->P18map.ADERRH = &pic->ram[0xF6A];
    pic->P18map.ADACCL = &pic->ram[0xF6B];
    pic->P18map.ADACCH = &pic->ram[0xF6C];
    pic->P18map.ADFLTRL = &pic->ram[0xF6D];
    pic->P18map.ADFLTRH = &pic->ram[0xF6E];
    pic->P18map.CRCDATL = &pic->ram[0xF6F];
    pic->P18map.CRCDATH = &pic->ram[0xF70];
    pic->P18map.CRCACCL = &pic->ram[0xF71];
    pic->P18map.CRCACCH = &pic->ram[0xF72];
    pic->P18map.CRCSHIFTL = &pic->ram[0xF73];
    pic->P18map.CRCSHIFTH = &pic->ram[0xF74];
    pic->P18map.CRCXORL = &pic->ram[0xF75];
    pic->P18map.CRCXORH = &pic->ram[0xF76];
    pic->P18map.CRCCON0 = &pic->ram[0xF77];
    pic->P18map.CRCCON1 = &pic->ram[0xF78];
    */
    pic->P18map.NVMADRL = &pic->ram[0xF79];
    pic->P18map.NVMADRH = &pic->ram[0xF7A];
    // pic->P18map.NVMADRU = &pic->ram[0xF7B];
    pic->P18map.NVMDAT = &pic->ram[0xF7C];
    // pic->P18map.NVMDATH = &pic->ram[0xF7D];
    // pic->P18map.NVMCON0 = &pic->ram[0xF7F];
    pic->P18map.NVMCON1 = &pic->ram[0xF80];
    pic->P18map.NVMCON2 = &pic->ram[0xF81];
    pic->P18map.LATA = &pic->ram[0xF82];
    pic->P18map.LATB = &pic->ram[0xF83];
    pic->P18map.LATC = &pic->ram[0xF84];
    pic->P18map.TRISA = &pic->ram[0xF87];
    pic->P18map.TRISB = &pic->ram[0xF88];
    pic->P18map.TRISC = &pic->ram[0xF89];
    pic->P18map.PORTA = &pic->ram[0xF8C];
    pic->P18map.PORTB = &pic->ram[0xF8D];
    pic->P18map.PORTC = &pic->ram[0xF8E];
    pic->P18map.PORTE = &pic->ram[0xF90];
    pic->P18map.SSP1BUF = &pic->ram[0xF91];
    pic->P18map.SSP1ADD = &pic->ram[0xF92];
    // pic->P18map.SSP1MSK = &pic->ram[0xF93];
    pic->P18map.SSP1STAT = &pic->ram[0xF94];
    pic->P18map.SSP1CON1 = &pic->ram[0xF95];
    pic->P18map.SSP1CON2 = &pic->ram[0xF96];
    // pic->P18map.SSP1CON3 = &pic->ram[0xF97];
    pic->P18map.RC1REG = &pic->ram[0xF98];
    pic->P18map.TX1REG = &pic->ram[0xF99];
    pic->P18map.SP1BRGL = &pic->ram[0xF9A];
    pic->P18map.SP1BRGH = &pic->ram[0xF9B];
    pic->P18map.RC1STA = &pic->ram[0xF9C];
    pic->P18map.TX1STA = &pic->ram[0xF9D];
    /*
    pic->P18map.BAUD1CON = &pic->ram[0xF9E];
    pic->P18map.PWM4DCL = &pic->ram[0xF9F];
    pic->P18map.PWM4DCH = &pic->ram[0xFA0];
    pic->P18map.PWM4CON = &pic->ram[0xFA1];
    pic->P18map.PWM3DCL = &pic->ram[0xFA2];
    pic->P18map.PWM3DCH = &pic->ram[0xFA3];
    pic->P18map.PWM3CON = &pic->ram[0xFA4];
    */
    pic->P18map.CCPR2L = &pic->ram[0xFA5];
    pic->P18map.CCPR2H = &pic->ram[0xFA6];
    pic->P18map.CCP2CON = &pic->ram[0xFA7];
    // pic->P18map.CCP2CAP = &pic->ram[0xFA8];
    pic->P18map.CCPR1L = &pic->ram[0xFA9];
    pic->P18map.CCPR1H = &pic->ram[0xFAA];
    pic->P18map.CCP1CON = &pic->ram[0xFAB];
    /*
    pic->P18map.CCP1CAP = &pic->ram[0xFAC];
    pic->P18map.CCPTMRS = &pic->ram[0xFAD];
    pic->P18map.T6TMR = &pic->ram[0xFAE];
    pic->P18map.T6PR = &pic->ram[0xFAF];
    pic->P18map.T6CON = &pic->ram[0xFB0];
    pic->P18map.T6HLT = &pic->ram[0xFB1];
    pic->P18map.T6CLKCON = &pic->ram[0xFB2];
    pic->P18map.T6RST = &pic->ram[0xFB3];
    pic->P18map.T4TMR = &pic->ram[0xFB4];
    pic->P18map.T4PR = &pic->ram[0xFB5];
    pic->P18map.T4CON = &pic->ram[0xFB6];
    pic->P18map.T4HLT = &pic->ram[0xFB7];
    pic->P18map.T4CLKCON = &pic->ram[0xFB8];
    pic->P18map.T4RST = &pic->ram[0xFB9];
    */
    pic->P18map.T2TMR = &pic->ram[0xFBA];
    pic->P18map.T2PR = &pic->ram[0xFBB];
    pic->P18map.T2CON = &pic->ram[0xFBC];
    /*
    pic->P18map.T2HLT = &pic->ram[0xFBD];
    pic->P18map.T2CLKCON = &pic->ram[0xFBE];
    pic->P18map.T2RST = &pic->ram[0xFBF];
    pic->P18map.TMR5L = &pic->ram[0xFC0];
    pic->P18map.TMR5H = &pic->ram[0xFC1];
    pic->P18map.T5CON = &pic->ram[0xFC2];
    pic->P18map.T5GCON = &pic->ram[0xFC3];
    pic->P18map.T5GATE = &pic->ram[0xFC4];
    pic->P18map.T5CLK = &pic->ram[0xFC5];
    */
    pic->P18map.TMR3L = &pic->ram[0xFC6];
    pic->P18map.TMR3H = &pic->ram[0xFC7];
    pic->P18map.T3CON = &pic->ram[0xFC8];
    /*
    pic->P18map.T3GCON = &pic->ram[0xFC9];
    pic->P18map.T3GATE = &pic->ram[0xFCA];
    pic->P18map.T3CLK = &pic->ram[0xFCB];
    */
    pic->P18map.TMR1L = &pic->ram[0xFCC];
    pic->P18map.TMR1H = &pic->ram[0xFCD];
    pic->P18map.T1CON = &pic->ram[0xFCE];
    /*
    pic->P18map.T1GCON = &pic->ram[0xFCF];
    pic->P18map.T1GATE = &pic->ram[0xFD0];
    */
    pic->P18map.T1CLK = &pic->ram[0xFD1];
    pic->P18map.TMR0L = &pic->ram[0xFD2];
    pic->P18map.TMR0H = &pic->ram[0xFD3];
    pic->P18map.T0CON0 = &pic->ram[0xFD4];
    pic->P18map.T0CON1 = &pic->ram[0xFD5];
    /*
    pic->P18map.PCON1 = &pic->ram[0xFD6];
    pic->P18map.PCON0 = &pic->ram[0xFD7];
    */
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

01 - VPP MCLR_n ICD_n IOCE3 RE3
02 - ANA0 C1IN0- C2IN0- IOCA0 RA0
03 - ANA1 C1IN1- C2IN1- IOCA1 RA1
04 - DAC1OUT1 VREF- ANA2 C1IN0+ C2IN0+ IOCA2 RA2
05 - VREF+ ANA3 C1IN1+ IOCA3 RA3
06 - ANA4 IOCA4 RA4
07 - ANA5 IOCA5 RA5
08 - AVSS VSS
09 - CLKIN OSC1 ANA7 IOCA7 RA7
10 - OSC2 CLKOUT ANA6 IOCA6 RA6
11 - SOSCO ANC0 IOCC0 RC0
12 - SOSCI ANC1 IOCC1 RC1
13 - ANC2 IOCC2 RC2
14 - SMB_I2C ANC3 IOCC3 RC3
15 - SMB_I2C ANC4 IOCC4 RC4
16 - ANC5 IOCC5 RC5
17 - ANC6 IOCC6 RC6
18 - ANC7 IOCC7 RC7
19 - VSS VSEL0
20 - AVDD VDD
21 - ZCD ANB0 C2IN1+ IOCB0 RB0
22 - ANB1 C1IN3- C2IN3- SMB_I2C IOCB1 RB1
23 - ANB2 SMB_I2C IOCB2 RB2
24 - ANB3 C1IN2- C2IN2- IOCB3 RB3
25 - ANB4 IOCB4 RB4
26 - ANB5 IOCB5 RB5
27 - ICSPCLK ICDCLK ANB6 IOCB6 RB6
28 - ICSPDAT ICDDAT DAC1OUT2 ANB7 IOCB7 RB7
 */

#include "../p18/p18_periferic.h"

/*
======================
Family=P18
processor=PIC18F24Q10
deviceid=0x71C0
 */

void PIC18F24Q10_reset(_pic* pic) {
    pic->pins[0].port = pic->P18map.PORTE;
    pic->pins[0].pord = 3;
    pic->pins[1].port = pic->P18map.PORTA;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P18map.PORTA;
    pic->pins[2].pord = 1;
    pic->pins[3].port = pic->P18map.PORTA;
    pic->pins[3].pord = 2;
    pic->pins[4].port = pic->P18map.PORTA;
    pic->pins[4].pord = 3;
    pic->pins[5].port = pic->P18map.PORTA;
    pic->pins[5].pord = 4;
    pic->pins[6].port = pic->P18map.PORTA;
    pic->pins[6].pord = 5;
    pic->pins[7].port = P_VSS;
    pic->pins[7].pord = -1;
    pic->pins[8].port = pic->P18map.PORTA;
    pic->pins[8].pord = 7;
    pic->pins[9].port = pic->P18map.PORTA;
    pic->pins[9].pord = 6;
    pic->pins[10].port = pic->P18map.PORTC;
    pic->pins[10].pord = 0;
    pic->pins[11].port = pic->P18map.PORTC;
    pic->pins[11].pord = 1;
    pic->pins[12].port = pic->P18map.PORTC;
    pic->pins[12].pord = 2;
    pic->pins[13].port = pic->P18map.PORTC;
    pic->pins[13].pord = 3;
    pic->pins[14].port = pic->P18map.PORTC;
    pic->pins[14].pord = 4;
    pic->pins[15].port = pic->P18map.PORTC;
    pic->pins[15].pord = 5;
    pic->pins[16].port = pic->P18map.PORTC;
    pic->pins[16].pord = 6;
    pic->pins[17].port = pic->P18map.PORTC;
    pic->pins[17].pord = 7;
    pic->pins[18].port = P_VSS;
    pic->pins[18].pord = -1;
    pic->pins[19].port = P_VDD;
    pic->pins[19].pord = -1;
    pic->pins[19].value = 1;
    pic->pins[20].port = pic->P18map.PORTB;
    pic->pins[20].pord = 0;
    pic->pins[21].port = pic->P18map.PORTB;
    pic->pins[21].pord = 1;
    pic->pins[22].port = pic->P18map.PORTB;
    pic->pins[22].pord = 2;
    pic->pins[23].port = pic->P18map.PORTB;
    pic->pins[23].pord = 3;
    pic->pins[24].port = pic->P18map.PORTB;
    pic->pins[24].pord = 4;
    pic->pins[25].port = pic->P18map.PORTB;
    pic->pins[25].pord = 5;
    pic->pins[26].port = pic->P18map.PORTB;
    pic->pins[26].pord = 6;
    pic->pins[27].port = pic->P18map.PORTB;
    pic->pins[27].pord = 7;

    pic->mclr = 1;

    pic->adc[0] = 2;
    pic->adc[1] = 3;
    pic->adc[2] = 4;
    pic->adc[3] = 5;
    pic->adc[4] = 6;
    pic->adc[5] = 7;
    pic->adc[6] = 10;
    pic->adc[7] = 9;
    pic->adc[8] = 21;
    pic->adc[9] = 22;
    pic->adc[10] = 23;
    pic->adc[11] = 24;
    pic->adc[12] = 25;
    pic->adc[13] = 26;
    pic->adc[14] = 27;
    pic->adc[15] = 28;
    pic->adc[16] = 11;
    pic->adc[17] = 12;
    pic->adc[18] = 13;
    pic->adc[19] = 14;
    pic->adc[20] = 15;
    pic->adc[21] = 16;
    pic->adc[22] = 17;
    pic->adc[23] = 18;

    pic->usart_rx[0] = 0;
    pic->usart_tx[0] = 0;

    pic->pgc = 27;
    pic->pgd = 28;

    pic->sck = 0;
    pic->sdo = 0;
    pic->sdi = 0;

    pic->t0cki = 0;
    pic->t1cki = 0;

    pic->int0 = 0;
    pic->int1 = 0;
    pic->int2 = 0;

    p18_tmr0_rst(pic);
    p18_tmr1_rst(pic);
    p18_tmr2_rst(pic);
    p18_adc_rst(pic);
    p18_wdt_rst(pic);
    p18_eeprom_rst(pic);
    p18_mssp_rst(pic);
    p18_int_pin_rst(pic);
    p18_int_portb_rst(pic);
    p18_int_ports_rst(pic);
    p18_uart_rst_3(pic, 0);
}

void PIC18F24Q10_periferic(_pic* pic) {
    p18_mssp_2(pic);
    p18_adc(pic);
    p18_int_pin(pic);
    p18_int_portb(pic);
    p18_int_ports(pic);
    p18_tmr0(pic);
    p18_wdt_2(pic);
    p18_eeprom_2(pic);
    p18_tmr1(pic);
    p18_tmr2(pic);
    p18_uart(pic, 0);
}

int PIC18F24Q10_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[1] & 0x0001) > 0);
            break;
        case CFG_WDT:
            return ((pic->config[2] & 0x0060) > 0);
            break;
        case CFG_WDT_DIV:
            return ((pic->config[2] & 0x001F));
            break;
        case CFG_DEBUG:
            return ((pic->config[1] & 0x0200) == 0);
            break;
    }
    return 0;
}

void PIC18F24Q10_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0200;
}

void PIC18F24Q10_stop(_pic* pic) {
    p18_uart_stop(pic, 0);
}

void PIC18F24Q10_start(_pic* pic) {
    pic->ROMSIZE = 8192;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 28;
    pic->IDSIZE = 256;
    pic->CONFIGSIZE = 6;
    pic->STACKSIZE = 31;
    pic->CCPCOUNT = 0;
    pic->ADCCOUNT = 24;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC18F24Q10_reset;
    pic->mmap = PIC18F24Q10_map;
    pic->getconf = PIC18F24Q10_getconf;
    pic->periferic = PIC18F24Q10_periferic;
    pic->interrupt = interrupt18;
    pic->stop = PIC18F24Q10_stop;
    pic->disable_debug = PIC18F24Q10_disable_debug;

    p18_uart_start(pic, 0);
}

init_pic(PIC18F24Q10, P18, 0x71C0);
