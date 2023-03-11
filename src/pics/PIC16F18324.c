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
#include "../p16e/p16e_periferic.h"

void PIC16F18324_map(_pic* pic) {
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
    pic->P16Emap.PORTC = &pic->ram[0xE];
    pic->P16Emap.PIR0 = &pic->ram[0x10];
    pic->P16Emap.PIR1 = &pic->ram[0x11];
    pic->P16Emap.PIR2 = &pic->ram[0x12];
    /*
    pic->P16Emap.PIR3 = &pic->ram[0x13];
    pic->P16Emap.PIR4 = &pic->ram[0x14];
    */
    pic->P16Emap.TMR0L = &pic->ram[0x15];
    pic->P16Emap.TMR0H = &pic->ram[0x16];
    pic->P16Emap.T0CON0 = &pic->ram[0x17];
    pic->P16Emap.T0CON1 = &pic->ram[0x18];
    pic->P16Emap.TMR1L = &pic->ram[0x19];
    pic->P16Emap.TMR1H = &pic->ram[0x1A];
    pic->P16Emap.T1CON = &pic->ram[0x1B];
    // pic->P16Emap.T1GCON = &pic->ram[0x1C];
    pic->P16Emap.TMR2 = &pic->ram[0x1D];
    pic->P16Emap.PR2 = &pic->ram[0x1E];
    pic->P16Emap.T2CON = &pic->ram[0x1F];
    pic->P16Emap.TRISA = &pic->ram[0x8C];
    pic->P16Emap.TRISC = &pic->ram[0x8E];
    pic->P16Emap.PIE0 = &pic->ram[0x90];
    pic->P16Emap.PIE1 = &pic->ram[0x91];
    pic->P16Emap.PIE2 = &pic->ram[0x92];
    /*
    pic->P16Emap.PIE3 = &pic->ram[0x93];
    pic->P16Emap.PIE4 = &pic->ram[0x94];
    */
    pic->P16Emap.WDTCON = &pic->ram[0x97];
    pic->P16Emap.ADRESL = &pic->ram[0x9B];
    pic->P16Emap.ADRESH = &pic->ram[0x9C];
    pic->P16Emap.ADCON0 = &pic->ram[0x9D];
    pic->P16Emap.ADCON1 = &pic->ram[0x9E];
    // pic->P16Emap.ADACT = &pic->ram[0x9F];
    pic->P16Emap.LATA = &pic->ram[0x10C];
    pic->P16Emap.LATC = &pic->ram[0x10E];
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
    */
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELC = &pic->ram[0x18E];
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
    pic->P16Emap.WPUC = &pic->ram[0x20E];
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
    pic->P16Emap.ODCONC = &pic->ram[0x28E];
    */
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    // pic->P16Emap.CCP1CAP = &pic->ram[0x294];
    pic->P16Emap.CCPR2L = &pic->ram[0x295];
    pic->P16Emap.CCPR2H = &pic->ram[0x296];
    pic->P16Emap.CCP2CON = &pic->ram[0x297];
    /*/
    pic->P16Emap.CCP2CAP = &pic->ram[0x298];
    pic->P16Emap.CCPTMRS = &pic->ram[0x29F];
    pic->P16Emap.SLRCONA = &pic->ram[0x30C];
    pic->P16Emap.SLRCONC = &pic->ram[0x30E];
    pic->P16Emap.CCPR3L = &pic->ram[0x311];
    pic->P16Emap.CCPR3H = &pic->ram[0x312];
    pic->P16Emap.CCP3CON = &pic->ram[0x313];
    pic->P16Emap.CCP3CAP = &pic->ram[0x314];
    pic->P16Emap.CCPR4L = &pic->ram[0x315];
    pic->P16Emap.CCPR4H = &pic->ram[0x316];
    pic->P16Emap.CCP4CON = &pic->ram[0x317];
    pic->P16Emap.CCP4CAP = &pic->ram[0x318];
    pic->P16Emap.INLVLA = &pic->ram[0x38C];
    pic->P16Emap.INLVLC = &pic->ram[0x38E];
    pic->P16Emap.IOCAP = &pic->ram[0x391];
    pic->P16Emap.IOCAN = &pic->ram[0x392];
    pic->P16Emap.IOCAF = &pic->ram[0x393];
    pic->P16Emap.IOCCP = &pic->ram[0x397];
    pic->P16Emap.IOCCN = &pic->ram[0x398];
    pic->P16Emap.IOCCF = &pic->ram[0x399];
    pic->P16Emap.CLKRCON = &pic->ram[0x39A];
    pic->P16Emap.MDCON = &pic->ram[0x39C];
    pic->P16Emap.MDSRC = &pic->ram[0x39D];
    pic->P16Emap.MDCARH = &pic->ram[0x39E];
    pic->P16Emap.MDCARL = &pic->ram[0x39F];
    pic->P16Emap.TMR3L = &pic->ram[0x411];
    pic->P16Emap.TMR3H = &pic->ram[0x412];
    pic->P16Emap.T3CON = &pic->ram[0x413];
    pic->P16Emap.T3GCON = &pic->ram[0x414];
    pic->P16Emap.TMR4 = &pic->ram[0x415];
    pic->P16Emap.PR4 = &pic->ram[0x416];
    pic->P16Emap.T4CON = &pic->ram[0x417];
    pic->P16Emap.TMR5L = &pic->ram[0x418];
    pic->P16Emap.TMR5H = &pic->ram[0x419];
    pic->P16Emap.T5CON = &pic->ram[0x41A];
    pic->P16Emap.T5GCON = &pic->ram[0x41B];
    pic->P16Emap.TMR6 = &pic->ram[0x41C];
    pic->P16Emap.PR6 = &pic->ram[0x41D];
    pic->P16Emap.T6CON = &pic->ram[0x41E];
    pic->P16Emap.CCDCON = &pic->ram[0x41F];
    pic->P16Emap.NCO1ACCL = &pic->ram[0x498];
    pic->P16Emap.NCO1ACCH = &pic->ram[0x499];
    pic->P16Emap.NCO1ACCU = &pic->ram[0x49A];
    pic->P16Emap.NCO1INCL = &pic->ram[0x49B];
    pic->P16Emap.NCO1INCH = &pic->ram[0x49C];
    pic->P16Emap.NCO1INCU = &pic->ram[0x49D];
    pic->P16Emap.NCO1CON = &pic->ram[0x49E];
    pic->P16Emap.NCO1CLK = &pic->ram[0x49F];
    pic->P16Emap.PWM5DCL = &pic->ram[0x617];
    pic->P16Emap.PWM5DCH = &pic->ram[0x618];
    pic->P16Emap.PWM5CON = &pic->ram[0x619];
    pic->P16Emap.PWM6DCL = &pic->ram[0x61A];
    pic->P16Emap.PWM6DCH = &pic->ram[0x61B];
    pic->P16Emap.PWM6CON = &pic->ram[0x61C];
    pic->P16Emap.PWMTMRS = &pic->ram[0x61F];
    pic->P16Emap.CWG1CLKCON = &pic->ram[0x691];
    pic->P16Emap.CWG1DAT = &pic->ram[0x692];
    pic->P16Emap.CWG1DBR = &pic->ram[0x693];
    pic->P16Emap.CWG1DBF = &pic->ram[0x694];
    pic->P16Emap.CWG1CON0 = &pic->ram[0x695];
    pic->P16Emap.CWG1CON1 = &pic->ram[0x696];
    pic->P16Emap.CWG1AS0 = &pic->ram[0x697];
    pic->P16Emap.CWG1AS1 = &pic->ram[0x698];
    pic->P16Emap.CWG1STR = &pic->ram[0x699];
    pic->P16Emap.CWG2CLKCON = &pic->ram[0x711];
    pic->P16Emap.CWG2DAT = &pic->ram[0x712];
    pic->P16Emap.CWG2DBR = &pic->ram[0x713];
    pic->P16Emap.CWG2DBF = &pic->ram[0x714];
    pic->P16Emap.CWG2CON0 = &pic->ram[0x715];
    pic->P16Emap.CWG2CON1 = &pic->ram[0x716];
    pic->P16Emap.CWG2AS0 = &pic->ram[0x717];
    pic->P16Emap.CWG2AS1 = &pic->ram[0x718];
    pic->P16Emap.CWG2STR = &pic->ram[0x719];
    */
    pic->P16Emap.NVMADRL = &pic->ram[0x891];
    pic->P16Emap.NVMADRH = &pic->ram[0x892];
    pic->P16Emap.NVMDATL = &pic->ram[0x893];
    pic->P16Emap.NVMDATH = &pic->ram[0x894];
    pic->P16Emap.NVMCON1 = &pic->ram[0x895];
    pic->P16Emap.NVMCON2 = &pic->ram[0x896];
    /*
    pic->P16Emap.PCON0 = &pic->ram[0x89B];
    pic->P16Emap.PMD0 = &pic->ram[0x911];
    pic->P16Emap.PMD1 = &pic->ram[0x912];
    pic->P16Emap.PMD2 = &pic->ram[0x913];
    pic->P16Emap.PMD3 = &pic->ram[0x914];
    pic->P16Emap.PMD4 = &pic->ram[0x915];
    pic->P16Emap.PMD5 = &pic->ram[0x916];
    pic->P16Emap.CPUDOZE = &pic->ram[0x918];
    pic->P16Emap.OSCCON1 = &pic->ram[0x919];
    pic->P16Emap.OSCCON2 = &pic->ram[0x91A];
    pic->P16Emap.OSCCON3 = &pic->ram[0x91B];
    pic->P16Emap.OSCSTAT1 = &pic->ram[0x91C];
    pic->P16Emap.OSCEN = &pic->ram[0x91D];
    pic->P16Emap.OSCTUNE = &pic->ram[0x91E];
    pic->P16Emap.OSCFRQ = &pic->ram[0x91F];
    pic->P16Emap.PPSLOCK = &pic->ram[0xE0F];
    pic->P16Emap.INTPPS = &pic->ram[0xE10];
    pic->P16Emap.T0CKIPPS = &pic->ram[0xE11];
    pic->P16Emap.T1CKIPPS = &pic->ram[0xE12];
    pic->P16Emap.T1GPPS = &pic->ram[0xE13];
    pic->P16Emap.CCP1PPS = &pic->ram[0xE14];
    pic->P16Emap.CCP2PPS = &pic->ram[0xE15];
    pic->P16Emap.CCP3PPS = &pic->ram[0xE16];
    pic->P16Emap.CCP4PPS = &pic->ram[0xE17];
    pic->P16Emap.CWG1PPS = &pic->ram[0xE18];
    pic->P16Emap.CWG2PPS = &pic->ram[0xE19];
    pic->P16Emap.MDCIN1PPS = &pic->ram[0xE1A];
    pic->P16Emap.MDCIN2PPS = &pic->ram[0xE1B];
    pic->P16Emap.MDMINPPS = &pic->ram[0xE1C];
    pic->P16Emap.SSP1CLKPPS = &pic->ram[0xE20];
    pic->P16Emap.SSP1DATPPS = &pic->ram[0xE21];
    pic->P16Emap.SSP1SSPPS = &pic->ram[0xE22];
    pic->P16Emap.RXPPS = &pic->ram[0xE24];
    pic->P16Emap.TXPPS = &pic->ram[0xE25];
    pic->P16Emap.CLCIN0PPS = &pic->ram[0xE28];
    pic->P16Emap.CLCIN1PPS = &pic->ram[0xE29];
    pic->P16Emap.CLCIN2PPS = &pic->ram[0xE2A];
    pic->P16Emap.CLCIN3PPS = &pic->ram[0xE2B];
    pic->P16Emap.T3CKIPPS = &pic->ram[0xE2C];
    pic->P16Emap.T3GPPS = &pic->ram[0xE2D];
    pic->P16Emap.T5CKIPPS = &pic->ram[0xE2E];
    pic->P16Emap.T5GPPS = &pic->ram[0xE2F];
    */
    pic->P16Emap.RA0PPS = &pic->ram[0xE90];
    pic->P16Emap.RA1PPS = &pic->ram[0xE91];
    pic->P16Emap.RA2PPS = &pic->ram[0xE92];
    pic->P16Emap.RA4PPS = &pic->ram[0xE94];
    pic->P16Emap.RA5PPS = &pic->ram[0xE95];
    pic->P16Emap.RC0PPS = &pic->ram[0xEA0];
    pic->P16Emap.RC1PPS = &pic->ram[0xEA1];
    pic->P16Emap.RC2PPS = &pic->ram[0xEA2];
    pic->P16Emap.RC3PPS = &pic->ram[0xEA3];
    pic->P16Emap.RC4PPS = &pic->ram[0xEA4];
    pic->P16Emap.RC5PPS = &pic->ram[0xEA5];
    /*
    pic->P16Emap.CLCDATA = &pic->ram[0xF0F];
    pic->P16Emap.CLC1CON = &pic->ram[0xF10];
    pic->P16Emap.CLC1POL = &pic->ram[0xF11];
    pic->P16Emap.CLC1SEL0 = &pic->ram[0xF12];
    pic->P16Emap.CLC1SEL1 = &pic->ram[0xF13];
    pic->P16Emap.CLC1SEL2 = &pic->ram[0xF14];
    pic->P16Emap.CLC1SEL3 = &pic->ram[0xF15];
    pic->P16Emap.CLC1GLS0 = &pic->ram[0xF16];
    pic->P16Emap.CLC1GLS1 = &pic->ram[0xF17];
    pic->P16Emap.CLC1GLS2 = &pic->ram[0xF18];
    pic->P16Emap.CLC1GLS3 = &pic->ram[0xF19];
    pic->P16Emap.CLC2CON = &pic->ram[0xF1A];
    pic->P16Emap.CLC2POL = &pic->ram[0xF1B];
    pic->P16Emap.CLC2SEL0 = &pic->ram[0xF1C];
    pic->P16Emap.CLC2SEL1 = &pic->ram[0xF1D];
    pic->P16Emap.CLC2SEL2 = &pic->ram[0xF1E];
    pic->P16Emap.CLC2SEL3 = &pic->ram[0xF1F];
    pic->P16Emap.CLC2GLS0 = &pic->ram[0xF20];
    pic->P16Emap.CLC2GLS1 = &pic->ram[0xF21];
    pic->P16Emap.CLC2GLS2 = &pic->ram[0xF22];
    pic->P16Emap.CLC2GLS3 = &pic->ram[0xF23];
    pic->P16Emap.CLC3CON = &pic->ram[0xF24];
    pic->P16Emap.CLC3POL = &pic->ram[0xF25];
    pic->P16Emap.CLC3SEL0 = &pic->ram[0xF26];
    pic->P16Emap.CLC3SEL1 = &pic->ram[0xF27];
    pic->P16Emap.CLC3SEL2 = &pic->ram[0xF28];
    pic->P16Emap.CLC3SEL3 = &pic->ram[0xF29];
    pic->P16Emap.CLC3GLS0 = &pic->ram[0xF2A];
    pic->P16Emap.CLC3GLS1 = &pic->ram[0xF2B];
    pic->P16Emap.CLC3GLS2 = &pic->ram[0xF2C];
    pic->P16Emap.CLC3GLS3 = &pic->ram[0xF2D];
    pic->P16Emap.CLC4CON = &pic->ram[0xF2E];
    pic->P16Emap.CLC4POL = &pic->ram[0xF2F];
    pic->P16Emap.CLC4SEL0 = &pic->ram[0xF30];
    pic->P16Emap.CLC4SEL1 = &pic->ram[0xF31];
    pic->P16Emap.CLC4SEL2 = &pic->ram[0xF32];
    pic->P16Emap.CLC4SEL3 = &pic->ram[0xF33];
    pic->P16Emap.CLC4GLS0 = &pic->ram[0xF34];
    pic->P16Emap.CLC4GLS1 = &pic->ram[0xF35];
    pic->P16Emap.CLC4GLS2 = &pic->ram[0xF36];
    pic->P16Emap.CLC4GLS3 = &pic->ram[0xF37];
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

01 - VDD
02 - ECIN OSC1 SOSCI SOSCIN CLKIN ANA5 IOCA5 RA5
03 - OSC2 SOSCO CLKOUT ANA4 IOCA4 RA4
04 - MCLR VPP IOCA3 RA3
05 - ANC5 IOCC5 RC5
06 - ANC4 IOCC4 RC4
07 - ANC3 C1IN3- C2IN3- IOCC3 RC3
08 - ANC2 C1IN2- C2IN2- IOCC2 RC2
09 - ANC1 C1IN1- C2IN1- SMB_I2C IOCC1 RC1
10 - ANC0 C2IN0+ SMB_I2C IOCC0 RC0
11 - DAC1REF- VREF- ANA2 IOCA2 RA2
12 - ICSPCLK ICDCLK DAC1REF+ ANA1 C1IN0- C2IN0- IOCA1 RA1
13 - ICSPDAT ICDDAT DAC1OUT ANA0 C1IN0+ IOCA0 RA0
14 - VSS
 */

/*
======================
Family=P16E
processor=PIC16F18324
deviceid=0x303A
 */

void PIC16F18324_reset(_pic* pic) {
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
    pic->pins[7].pord = 2;
    pic->pins[8].port = pic->P16Emap.PORTC;
    pic->pins[8].pord = 1;
    pic->pins[9].port = pic->P16Emap.PORTC;
    pic->pins[9].pord = 0;
    pic->pins[10].port = pic->P16Emap.PORTA;
    pic->pins[10].pord = 2;
    pic->pins[11].port = pic->P16Emap.PORTA;
    pic->pins[11].pord = 1;
    pic->pins[12].port = pic->P16Emap.PORTA;
    pic->pins[12].pord = 0;
    pic->pins[13].port = P_VSS;
    pic->pins[13].pord = -1;

    pic->mclr = 4;

    pic->ccp[0].pin = 5;
    pic->ccp[1].pin = 7;
    pic->ccp[2].pin = 11;
    pic->ccp[3].pin = 9;

    pic->adc[0] = 13;
    pic->adc[1] = 12;
    pic->adc[2] = 11;
    pic->adc[3] = 0;
    pic->adc[4] = 3;
    pic->adc[5] = 2;
    pic->adc[6] = 0;
    pic->adc[7] = 0;
    pic->adc[8] = 0;
    pic->adc[9] = 0;
    pic->adc[10] = 0;
    pic->adc[11] = 0;
    pic->adc[12] = 0;
    pic->adc[13] = 0;
    pic->adc[14] = 0;
    pic->adc[15] = 0;
    pic->adc[16] = 10;
    pic->adc[17] = 9;
    pic->adc[18] = 8;
    pic->adc[19] = 7;
    pic->adc[20] = 6;
    pic->adc[21] = 5;

    pic->usart_rx[0] = 5;
    pic->usart_tx[0] = 6;

    pic->pgc = 12;
    pic->pgd = 13;

    pic->sck = 10;
    pic->sdo = 8;
    pic->sdi = 9;

    pic->t0cki = 11;
    pic->t1cki = 2;

    pic->int0 = 11;
    pic->int1 = 0;
    pic->int2 = 0;

    p16e_pps_out_rst(pic);
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

void PIC16F18324_periferic(_pic* pic) {
    p16e_pps_out(pic);
    p16e_mssp(pic);
    p16e_adc(pic);
    p16e_int_pin_2(pic);
    // p16e_int_ports (pic);
    p16e_tmr0_2(pic);
    p16e_wdt_3(pic);
    p16e_eeprom_2(pic);
    p16e_tmr1(pic);
    p16e_tmr2(pic);
    p16e_uart(pic, 0);
}

int PIC16F18324_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return (pic->config[1] & 0x0001);
            break;
        case CFG_WDT:
            return (pic->config[1] & 0x000C);
            break;
        case CFG_DEBUG:
            return !(pic->config[1] & 0x0200);
            break;
    }
    return 0;
}

void PIC16F18324_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0200;
}

void PIC16F18324_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F18324_start(_pic* pic) {
    pic->ROMSIZE = 4096;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 14;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 4;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 4;
    pic->ADCCOUNT = 22;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F18324_reset;
    pic->mmap = PIC16F18324_map;
    pic->getconf = PIC16F18324_getconf;
    pic->periferic = PIC16F18324_periferic;
    pic->interrupt = interrupt16E_2;
    pic->stop = PIC16F18324_stop;
    pic->disable_debug = PIC16F18324_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F18324, P16E, 0x303A);
