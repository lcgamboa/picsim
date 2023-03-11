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

void PIC16F1789_map(_pic* pic) {
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
    /*
    pic->P16Emap.PCON = &pic->ram[0x96];
    */
    pic->P16Emap.WDTCON = &pic->ram[0x97];
    /*
    pic->P16Emap.OSCTUNE = &pic->ram[0x98];
    pic->P16Emap.OSCCON = &pic->ram[0x99];
    pic->P16Emap.OSCSTAT = &pic->ram[0x9A];
     */
    pic->P16Emap.ADRESL = &pic->ram[0x9B];
    pic->P16Emap.ADRESH = &pic->ram[0x9C];
    pic->P16Emap.ADCON0 = &pic->ram[0x9D];
    pic->P16Emap.ADCON1 = &pic->ram[0x9E];
    // pic->P16Emap.ADCON2 = &pic->ram[0x9F];
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
    pic->P16Emap.DAC1CON0 = &pic->ram[0x118];
    pic->P16Emap.DAC1CON1 = &pic->ram[0x119];
    pic->P16Emap.CM4CON0 = &pic->ram[0x11A];
    pic->P16Emap.CM4CON1 = &pic->ram[0x11B];
    pic->P16Emap.APFCON2 = &pic->ram[0x11C];
    pic->P16Emap.APFCON1 = &pic->ram[0x11D];
    pic->P16Emap.CM3CON0 = &pic->ram[0x11E];
    pic->P16Emap.CM3CON1 = &pic->ram[0x11F];
     */
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELB = &pic->ram[0x18D];
    pic->P16Emap.ANSELC = &pic->ram[0x18E];
    pic->P16Emap.ANSELD = &pic->ram[0x18F];
    pic->P16Emap.ANSELE = &pic->ram[0x190];
    pic->P16Emap.EEADRL = &pic->ram[0x191];
    pic->P16Emap.EEADRH = &pic->ram[0x192];
    pic->P16Emap.EEDATL = &pic->ram[0x193];
    pic->P16Emap.EEDATH = &pic->ram[0x194];
    pic->P16Emap.EECON1 = &pic->ram[0x195];
    pic->P16Emap.EECON2 = &pic->ram[0x196];
    // pic->P16Emap.VREGCON = &pic->ram[0x197];
    pic->P16Emap.RC1REG = &pic->ram[0x199];
    pic->P16Emap.TX1REG = &pic->ram[0x19A];
    pic->P16Emap.SP1BRGL = &pic->ram[0x19B];
    pic->P16Emap.SP1BRGH = &pic->ram[0x19C];
    pic->P16Emap.RC1STA = &pic->ram[0x19D];
    pic->P16Emap.TX1STA = &pic->ram[0x19E];
    /*
    pic->P16Emap.BAUD1CON = &pic->ram[0x19F];
    pic->P16Emap.WPUA = &pic->ram[0x20C];
    pic->P16Emap.WPUB = &pic->ram[0x20D];
    pic->P16Emap.WPUC = &pic->ram[0x20E];
    pic->P16Emap.WPUD = &pic->ram[0x20F];
    pic->P16Emap.WPUE = &pic->ram[0x210];
     */
    pic->P16Emap.SSP1BUF = &pic->ram[0x211];
    pic->P16Emap.SSP1ADD = &pic->ram[0x212];
    // pic->P16Emap.SSP1MSK = &pic->ram[0x213];
    pic->P16Emap.SSP1STAT = &pic->ram[0x214];
    pic->P16Emap.SSP1CON1 = &pic->ram[0x215];
    pic->P16Emap.SSP1CON2 = &pic->ram[0x216];
    /*
    pic->P16Emap.SSP1CON3 = &pic->ram[0x217];
    pic->P16Emap.ODCONA = &pic->ram[0x28C];
    pic->P16Emap.ODCONB = &pic->ram[0x28D];
    pic->P16Emap.ODCONC = &pic->ram[0x28E];
    pic->P16Emap.ODCOND = &pic->ram[0x28F];
    pic->P16Emap.ODCONE = &pic->ram[0x290];
     */
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    pic->P16Emap.CCPR2L = &pic->ram[0x298];
    pic->P16Emap.CCPR2H = &pic->ram[0x299];
    pic->P16Emap.CCP2CON = &pic->ram[0x29A];
    /*
    pic->P16Emap.SLRCONA = &pic->ram[0x30C];
    pic->P16Emap.SLRCONB = &pic->ram[0x30D];
    pic->P16Emap.SLRCONC = &pic->ram[0x30E];
    pic->P16Emap.SLRCOND = &pic->ram[0x30F];
    pic->P16Emap.SLRCONE = &pic->ram[0x310];
    pic->P16Emap.CCPR3L = &pic->ram[0x311];
    pic->P16Emap.CCPR3H = &pic->ram[0x312];
    pic->P16Emap.CCP3CON = &pic->ram[0x313];
    pic->P16Emap.INLVLA = &pic->ram[0x38C];
    pic->P16Emap.INLVLB = &pic->ram[0x38D];
    pic->P16Emap.INLVLC = &pic->ram[0x38E];
    pic->P16Emap.INLVLD = &pic->ram[0x38F];
    pic->P16Emap.INLVLE = &pic->ram[0x390];
    pic->P16Emap.IOCAP = &pic->ram[0x391];
    pic->P16Emap.IOCAN = &pic->ram[0x392];
    pic->P16Emap.IOCAF = &pic->ram[0x393];
     */
    pic->P16Emap.IOCBP = &pic->ram[0x394];
    pic->P16Emap.IOCBN = &pic->ram[0x395];
    pic->P16Emap.IOCBF = &pic->ram[0x396];
    /*
    pic->P16Emap.IOCCP = &pic->ram[0x397];
    pic->P16Emap.IOCCN = &pic->ram[0x398];
    pic->P16Emap.IOCCF = &pic->ram[0x399];
    pic->P16Emap.IOCEP = &pic->ram[0x39D];
    pic->P16Emap.IOCEN = &pic->ram[0x39E];
    pic->P16Emap.IOCEF = &pic->ram[0x39F];
    pic->P16Emap.OPA1CON = &pic->ram[0x511];
    pic->P16Emap.OPA2CON = &pic->ram[0x513];
    pic->P16Emap.OPA3CON = &pic->ram[0x515];
    pic->P16Emap.CLKRCON = &pic->ram[0x51A];
    pic->P16Emap.DAC2CON0 = &pic->ram[0x591];
    pic->P16Emap.DAC2REF = &pic->ram[0x592];
    pic->P16Emap.DAC3CON0 = &pic->ram[0x593];
    pic->P16Emap.DAC3REF = &pic->ram[0x594];
    pic->P16Emap.DAC4CON0 = &pic->ram[0x595];
    pic->P16Emap.DAC4REF = &pic->ram[0x596];
    pic->P16Emap.PSMC1CON = &pic->ram[0xE91];
    pic->P16Emap.PSMC1MDL = &pic->ram[0xE92];
    pic->P16Emap.PSMC1SYNC = &pic->ram[0xE93];
    pic->P16Emap.PSMC1CLK = &pic->ram[0xE94];
    pic->P16Emap.PSMC1OEN = &pic->ram[0xE95];
    pic->P16Emap.PSMC1POL = &pic->ram[0xE96];
    pic->P16Emap.PSMC1BLNK = &pic->ram[0xE97];
    pic->P16Emap.PSMC1REBS = &pic->ram[0xE98];
    pic->P16Emap.PSMC1FEBS = &pic->ram[0xE99];
    pic->P16Emap.PSMC1PHS = &pic->ram[0xE9A];
    pic->P16Emap.PSMC1DCS = &pic->ram[0xE9B];
    pic->P16Emap.PSMC1PRS = &pic->ram[0xE9C];
    pic->P16Emap.PSMC1ASDC = &pic->ram[0xE9D];
    pic->P16Emap.PSMC1ASDL = &pic->ram[0xE9E];
    pic->P16Emap.PSMC1ASDS = &pic->ram[0xE9F];
    pic->P16Emap.PSMC1INT = &pic->ram[0xEA0];
    pic->P16Emap.PSMC1PHL = &pic->ram[0xEA1];
    pic->P16Emap.PSMC1PHH = &pic->ram[0xEA2];
    pic->P16Emap.PSMC1DCL = &pic->ram[0xEA3];
    pic->P16Emap.PSMC1DCH = &pic->ram[0xEA4];
    pic->P16Emap.PSMC1PRL = &pic->ram[0xEA5];
    pic->P16Emap.PSMC1PRH = &pic->ram[0xEA6];
    pic->P16Emap.PSMC1TMRL = &pic->ram[0xEA7];
    pic->P16Emap.PSMC1TMRH = &pic->ram[0xEA8];
    pic->P16Emap.PSMC1DBR = &pic->ram[0xEA9];
    pic->P16Emap.PSMC1DBF = &pic->ram[0xEAA];
    pic->P16Emap.PSMC1BLKR = &pic->ram[0xEAB];
    pic->P16Emap.PSMC1BLKF = &pic->ram[0xEAC];
    pic->P16Emap.PSMC1FFA = &pic->ram[0xEAD];
    pic->P16Emap.PSMC1STR0 = &pic->ram[0xEAE];
    pic->P16Emap.PSMC1STR1 = &pic->ram[0xEAF];
    pic->P16Emap.PSMC2CON = &pic->ram[0xEB1];
    pic->P16Emap.PSMC2MDL = &pic->ram[0xEB2];
    pic->P16Emap.PSMC2SYNC = &pic->ram[0xEB3];
    pic->P16Emap.PSMC2CLK = &pic->ram[0xEB4];
    pic->P16Emap.PSMC2OEN = &pic->ram[0xEB5];
    pic->P16Emap.PSMC2POL = &pic->ram[0xEB6];
    pic->P16Emap.PSMC2BLNK = &pic->ram[0xEB7];
    pic->P16Emap.PSMC2REBS = &pic->ram[0xEB8];
    pic->P16Emap.PSMC2FEBS = &pic->ram[0xEB9];
    pic->P16Emap.PSMC2PHS = &pic->ram[0xEBA];
    pic->P16Emap.PSMC2DCS = &pic->ram[0xEBB];
    pic->P16Emap.PSMC2PRS = &pic->ram[0xEBC];
    pic->P16Emap.PSMC2ASDC = &pic->ram[0xEBD];
    pic->P16Emap.PSMC2ASDL = &pic->ram[0xEBE];
    pic->P16Emap.PSMC2ASDS = &pic->ram[0xEBF];
    pic->P16Emap.PSMC2INT = &pic->ram[0xEC0];
    pic->P16Emap.PSMC2PHL = &pic->ram[0xEC1];
    pic->P16Emap.PSMC2PHH = &pic->ram[0xEC2];
    pic->P16Emap.PSMC2DCL = &pic->ram[0xEC3];
    pic->P16Emap.PSMC2DCH = &pic->ram[0xEC4];
    pic->P16Emap.PSMC2PRL = &pic->ram[0xEC5];
    pic->P16Emap.PSMC2PRH = &pic->ram[0xEC6];
    pic->P16Emap.PSMC2TMRL = &pic->ram[0xEC7];
    pic->P16Emap.PSMC2TMRH = &pic->ram[0xEC8];
    pic->P16Emap.PSMC2DBR = &pic->ram[0xEC9];
    pic->P16Emap.PSMC2DBF = &pic->ram[0xECA];
    pic->P16Emap.PSMC2BLKR = &pic->ram[0xECB];
    pic->P16Emap.PSMC2BLKF = &pic->ram[0xECC];
    pic->P16Emap.PSMC2FFA = &pic->ram[0xECD];
    pic->P16Emap.PSMC2STR0 = &pic->ram[0xECE];
    pic->P16Emap.PSMC2STR1 = &pic->ram[0xECF];
    pic->P16Emap.PSMC3CON = &pic->ram[0xED1];
    pic->P16Emap.PSMC3MDL = &pic->ram[0xED2];
    pic->P16Emap.PSMC3SYNC = &pic->ram[0xED3];
    pic->P16Emap.PSMC3CLK = &pic->ram[0xED4];
    pic->P16Emap.PSMC3OEN = &pic->ram[0xED5];
    pic->P16Emap.PSMC3POL = &pic->ram[0xED6];
    pic->P16Emap.PSMC3BLNK = &pic->ram[0xED7];
    pic->P16Emap.PSMC3REBS = &pic->ram[0xED8];
    pic->P16Emap.PSMC3FEBS = &pic->ram[0xED9];
    pic->P16Emap.PSMC3PHS = &pic->ram[0xEDA];
    pic->P16Emap.PSMC3DCS = &pic->ram[0xEDB];
    pic->P16Emap.PSMC3PRS = &pic->ram[0xEDC];
    pic->P16Emap.PSMC3ASDC = &pic->ram[0xEDD];
    pic->P16Emap.PSMC3ASDL = &pic->ram[0xEDE];
    pic->P16Emap.PSMC3ASDS = &pic->ram[0xEDF];
    pic->P16Emap.PSMC3INT = &pic->ram[0xEE0];
    pic->P16Emap.PSMC3PHL = &pic->ram[0xEE1];
    pic->P16Emap.PSMC3PHH = &pic->ram[0xEE2];
    pic->P16Emap.PSMC3DCL = &pic->ram[0xEE3];
    pic->P16Emap.PSMC3DCH = &pic->ram[0xEE4];
    pic->P16Emap.PSMC3PRL = &pic->ram[0xEE5];
    pic->P16Emap.PSMC3PRH = &pic->ram[0xEE6];
    pic->P16Emap.PSMC3TMRL = &pic->ram[0xEE7];
    pic->P16Emap.PSMC3TMRH = &pic->ram[0xEE8];
    pic->P16Emap.PSMC3DBR = &pic->ram[0xEE9];
    pic->P16Emap.PSMC3DBF = &pic->ram[0xEEA];
    pic->P16Emap.PSMC3BLKR = &pic->ram[0xEEB];
    pic->P16Emap.PSMC3BLKF = &pic->ram[0xEEC];
    pic->P16Emap.PSMC3FFA = &pic->ram[0xEED];
    pic->P16Emap.PSMC3STR0 = &pic->ram[0xEEE];
    pic->P16Emap.PSMC3STR1 = &pic->ram[0xEEF];
    pic->P16Emap.PSMC4CON = &pic->ram[0xF11];
    pic->P16Emap.PSMC4MDL = &pic->ram[0xF12];
    pic->P16Emap.PSMC4SYNC = &pic->ram[0xF13];
    pic->P16Emap.PSMC4CLK = &pic->ram[0xF14];
    pic->P16Emap.PSMC4OEN = &pic->ram[0xF15];
    pic->P16Emap.PSMC4POL = &pic->ram[0xF16];
    pic->P16Emap.PSMC4BLNK = &pic->ram[0xF17];
    pic->P16Emap.PSMC4REBS = &pic->ram[0xF18];
    pic->P16Emap.PSMC4FEBS = &pic->ram[0xF19];
    pic->P16Emap.PSMC4PHS = &pic->ram[0xF1A];
    pic->P16Emap.PSMC4DCS = &pic->ram[0xF1B];
    pic->P16Emap.PSMC4PRS = &pic->ram[0xF1C];
    pic->P16Emap.PSMC4ASDC = &pic->ram[0xF1D];
    pic->P16Emap.PSMC4ASDL = &pic->ram[0xF1E];
    pic->P16Emap.PSMC4ASDS = &pic->ram[0xF1F];
    pic->P16Emap.PSMC4INT = &pic->ram[0xF20];
    pic->P16Emap.PSMC4PHL = &pic->ram[0xF21];
    pic->P16Emap.PSMC4PHH = &pic->ram[0xF22];
    pic->P16Emap.PSMC4DCL = &pic->ram[0xF23];
    pic->P16Emap.PSMC4DCH = &pic->ram[0xF24];
    pic->P16Emap.PSMC4PRL = &pic->ram[0xF25];
    pic->P16Emap.PSMC4PRH = &pic->ram[0xF26];
    pic->P16Emap.PSMC4TMRL = &pic->ram[0xF27];
    pic->P16Emap.PSMC4TMRH = &pic->ram[0xF28];
    pic->P16Emap.PSMC4DBR = &pic->ram[0xF29];
    pic->P16Emap.PSMC4DBF = &pic->ram[0xF2A];
    pic->P16Emap.PSMC4BLKR = &pic->ram[0xF2B];
    pic->P16Emap.PSMC4BLKF = &pic->ram[0xF2C];
    pic->P16Emap.PSMC4FFA = &pic->ram[0xF2D];
    pic->P16Emap.PSMC4STR0 = &pic->ram[0xF2E];
    pic->P16Emap.PSMC4STR1 = &pic->ram[0xF2F];
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
02 - RA0 AN0 C1IN0- C2IN0- C3IN0- C4IN0- SS
03 - RA1 AN1 C1IN1- C2IN1- C3IN1- C4IN1- OPA1OUT
04 - RA2 AN2 C1IN0+ C2IN0+ C3IN0+ C4IN0+ DAC1OUT1 Vref- DAC1Vref-
05 - RA3 AN3 Vref+ C1IN1+ DAC1Vref+ DAC2Vref+ DAC3Vref+ DAC4Vref+
06 - RA4 C1OUT OPA1IN+ T0CKI
07 - RA5 AN4 C2OUT OPA1IN- SS DAC2OUT1
08 - RE0 AN5 CCP3 PSMC4B
09 - RE1 AN6 PSMC3B
10 - RE2 AN7 PSMC3A
11 - Vdd
12 - Vss
13 - RA7 Vref+ PSMC1CLK PSMC2CLK PSMC3CLK PSMC4CLK OSC1 CLKIN
14 - RA6 C2OUT OSC2 CLKOUT VCAP
15 - RC0 SOSCO T1CKI PSMC1A
16 - RC1 SOSCI PSMC1B CCP2
17 - RC2 PSMC1C CCP1
18 - RC3 PSMC1D SCK SCL
19 - RD0 OPA3IN+
20 - RD1 AN21 C1IN4- C2IN4- C3IN4- C4IN4- OPA3OUT
21 - RD2 OPA3IN- DAC4OUT1
22 - RD3 PSMC4A
23 - RC4 PSMC1E SDI SDA
24 - RC5 PSMC1F SDO
25 - RC6 PSMC2A TX CK
26 - RC7 PSMC2B RX DT
27 - RD4 PSMC3F
28 - RD5 PSMC3E
29 - RD6 PSMC3D C3OUT
30 - RD7 PSMC3C C4OUT
31 - Vss
32 - Vdd
33 - RB0 AN12 C2IN1+ PSMC1IN PSMC2IN PSMC3IN PSMC4IN CCP1 INT
34 - RB1 AN10 C1IN3- C2IN3- C3IN3- C4IN3- OPA2OUT
35 - RB2 AN8 OPA2IN- CLKR DAC3OUT1
36 - RB3 AN9 C1IN2- C2IN2- C3IN2- OPA2IN+ CCP2
37 - RB4 AN11 C3IN1+ SS
38 - RB5 AN13 T1G SDO CCP3 C4IN2-
39 - RB6 TX CK SDI SDA C4IN1+ ICSPCLK ICDCLK
40 - RB7 DAC1OUT2 DAC2OUT2 DAC3OUT2 DAC4OUT2 RX DT SCK SCL ICSPDAT ICDDAT
 */

/*
======================
Family=P16E
processor=PIC16F1789
deviceid=0x302A
 */

void PIC16F1789_reset(_pic* pic) {
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

    pic->ccp[0].pin = 33;
    pic->ccp[1].pin = 36;
    pic->ccp[2].pin = 38;

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
    pic->adc[14] = 20;

    pic->usart_rx[0] = 40;
    pic->usart_tx[0] = 39;

    pic->pgc = 0;
    pic->pgd = 40;

    pic->sck = 40;
    pic->sdo = 38;
    pic->sdi = 39;

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
    p16e_uart_rst_2(pic, 0);
}

void PIC16F1789_periferic(_pic* pic) {
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

int PIC16F1789_getconf(_pic* pic, unsigned int cfg) {
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

void PIC16F1789_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0100;
}

void PIC16F1789_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F1789_start(_pic* pic) {
    pic->ROMSIZE = 16384;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 40;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 2;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 3;
    pic->ADCCOUNT = 15;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F1789_reset;
    pic->mmap = PIC16F1789_map;
    pic->getconf = PIC16F1789_getconf;
    pic->periferic = PIC16F1789_periferic;
    pic->interrupt = interrupt16E;
    pic->stop = PIC16F1789_stop;
    pic->disable_debug = PIC16F1789_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F1789, P16E, 0x302A);
