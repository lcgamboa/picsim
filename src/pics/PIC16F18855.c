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

void PIC16F18855_map(_pic* pic) {
    memset(&pic->P16Emap, 0, sizeof(P16Emap_t));

    pic->P16Emap.FSR0L = &pic->ram[0x4];
    pic->P16Emap.FSR0H = &pic->ram[0x5];
    pic->P16Emap.FSR1L = &pic->ram[0x6];
    pic->P16Emap.FSR1H = &pic->ram[0x7];
    pic->P16Emap.ADRESL = &pic->ram[0x8C];
    pic->P16Emap.ADRESH = &pic->ram[0x8D];
    /*
    pic->P16Emap.ADPREVL = &pic->ram[0x8E];
    pic->P16Emap.ADPREVH = &pic->ram[0x8F];
    pic->P16Emap.ADACCL = &pic->ram[0x90];
    pic->P16Emap.ADACCH = &pic->ram[0x91];
    pic->P16Emap.ADLTHL = &pic->ram[0x10E];
    pic->P16Emap.ADLTHH = &pic->ram[0x10F];
    pic->P16Emap.ADUTHL = &pic->ram[0x110];
    pic->P16Emap.ADUTHH = &pic->ram[0x111];
    pic->P16Emap.ADSTPTL = &pic->ram[0x112];
    pic->P16Emap.ADSTPTH = &pic->ram[0x113];
    pic->P16Emap.ADFLTRL = &pic->ram[0x114];
    pic->P16Emap.ADFLTRH = &pic->ram[0x115];
    pic->P16Emap.ADERRL = &pic->ram[0x116];
    pic->P16Emap.ADERRH = &pic->ram[0x117];
    */
    pic->P16Emap.SP1BRGL = &pic->ram[0x11B];
    pic->P16Emap.SP1BRGH = &pic->ram[0x11C];
    pic->P16Emap.TMR1L = &pic->ram[0x20C];
    pic->P16Emap.TMR1H = &pic->ram[0x20D];
    /*
    pic->P16Emap.TMR3L = &pic->ram[0x212];
    pic->P16Emap.TMR3H = &pic->ram[0x213];
    pic->P16Emap.TMR5L = &pic->ram[0x218];
    pic->P16Emap.TMR5H = &pic->ram[0x219];
    */
    pic->P16Emap.CCPR1L = &pic->ram[0x30C];
    pic->P16Emap.CCPR1H = &pic->ram[0x30D];
    pic->P16Emap.CCPR2L = &pic->ram[0x310];
    pic->P16Emap.CCPR2H = &pic->ram[0x311];
    /*
    pic->P16Emap.CCPR3L = &pic->ram[0x314];
    pic->P16Emap.CCPR3H = &pic->ram[0x315];
    pic->P16Emap.CCPR4L = &pic->ram[0x318];
    pic->P16Emap.CCPR4H = &pic->ram[0x319];
    pic->P16Emap.CCPR5L = &pic->ram[0x31C];
    pic->P16Emap.CCPR5H = &pic->ram[0x31D];
    pic->P16Emap.PWM6DCL = &pic->ram[0x38C];
    pic->P16Emap.PWM6DCH = &pic->ram[0x38D];
    pic->P16Emap.PWM7DCL = &pic->ram[0x390];
    pic->P16Emap.PWM7DCH = &pic->ram[0x391];
    pic->P16Emap.CRCDATL = &pic->ram[0x416];
    pic->P16Emap.CRCDATH = &pic->ram[0x417];
    pic->P16Emap.CRCACCL = &pic->ram[0x418];
    pic->P16Emap.CRCACCH = &pic->ram[0x419];
    pic->P16Emap.CRCSHIFTL = &pic->ram[0x41A];
    pic->P16Emap.CRCSHIFTH = &pic->ram[0x41B];
    pic->P16Emap.CRCXORL = &pic->ram[0x41C];
    pic->P16Emap.CRCXORH = &pic->ram[0x41D];
    pic->P16Emap.SMT1TMRL = &pic->ram[0x48C];
    pic->P16Emap.SMT1TMRH = &pic->ram[0x48D];
    pic->P16Emap.SMT1TMRU = &pic->ram[0x48E];
    pic->P16Emap.SMT1CPRL = &pic->ram[0x48F];
    pic->P16Emap.SMT1CPRH = &pic->ram[0x490];
    pic->P16Emap.SMT1CPRU = &pic->ram[0x491];
    pic->P16Emap.SMT1CPWL = &pic->ram[0x492];
    pic->P16Emap.SMT1CPWH = &pic->ram[0x493];
    pic->P16Emap.SMT1CPWU = &pic->ram[0x494];
    pic->P16Emap.SMT1PRL = &pic->ram[0x495];
    pic->P16Emap.SMT1PRH = &pic->ram[0x496];
    pic->P16Emap.SMT1PRU = &pic->ram[0x497];
    pic->P16Emap.SMT2TMRL = &pic->ram[0x50C];
    pic->P16Emap.SMT2TMRH = &pic->ram[0x50D];
    pic->P16Emap.SMT2TMRU = &pic->ram[0x50E];
    pic->P16Emap.SMT2CPRL = &pic->ram[0x50F];
    pic->P16Emap.SMT2CPRH = &pic->ram[0x510];
    pic->P16Emap.SMT2CPRU = &pic->ram[0x511];
    pic->P16Emap.SMT2CPWL = &pic->ram[0x512];
    pic->P16Emap.SMT2CPWH = &pic->ram[0x513];
    pic->P16Emap.SMT2CPWU = &pic->ram[0x514];
    pic->P16Emap.SMT2PRL = &pic->ram[0x515];
    pic->P16Emap.SMT2PRH = &pic->ram[0x516];
    pic->P16Emap.SMT2PRU = &pic->ram[0x517];
    pic->P16Emap.NCO1ACCL = &pic->ram[0x58C];
    pic->P16Emap.NCO1ACCH = &pic->ram[0x58D];
    pic->P16Emap.NCO1ACCU = &pic->ram[0x58E];
    pic->P16Emap.NCO1INCL = &pic->ram[0x58F];
    pic->P16Emap.NCO1INCH = &pic->ram[0x590];
    pic->P16Emap.NCO1INCU = &pic->ram[0x591];
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
    pic->P16Emap.PORTE = &pic->ram[0x10];
    pic->P16Emap.TRISA = &pic->ram[0x11];
    pic->P16Emap.TRISB = &pic->ram[0x12];
    pic->P16Emap.TRISC = &pic->ram[0x13];
    pic->P16Emap.LATA = &pic->ram[0x16];
    pic->P16Emap.LATB = &pic->ram[0x17];
    pic->P16Emap.LATC = &pic->ram[0x18];
    pic->P16Emap.TMR0L = &pic->ram[0x1C];
    pic->P16Emap.TMR0H = &pic->ram[0x1D];
    pic->P16Emap.T0CON0 = &pic->ram[0x1E];
    pic->P16Emap.T0CON1 = &pic->ram[0x1F];
    pic->P16Emap.ADCON0 = &pic->ram[0x93];
    pic->P16Emap.ADCON1 = &pic->ram[0x94];
    /*
    pic->P16Emap.ADCON2 = &pic->ram[0x95];
    pic->P16Emap.ADCON3 = &pic->ram[0x96];
    pic->P16Emap.ADSTAT = &pic->ram[0x97];
    pic->P16Emap.ADCLK = &pic->ram[0x98];
    pic->P16Emap.ADACT = &pic->ram[0x99];
    pic->P16Emap.ADREF = &pic->ram[0x9A];
    pic->P16Emap.ADCAP = &pic->ram[0x9B];
    pic->P16Emap.ADPRE = &pic->ram[0x9C];
    pic->P16Emap.ADACQ = &pic->ram[0x9D];
    */
    pic->P16Emap.ADPCH = &pic->ram[0x9E];
    /*
    pic->P16Emap.ADCNT = &pic->ram[0x10C];
    pic->P16Emap.ADRPT = &pic->ram[0x10D];
    */
    pic->P16Emap.RC1REG = &pic->ram[0x119];
    pic->P16Emap.TX1REG = &pic->ram[0x11A];
    pic->P16Emap.RC1STA = &pic->ram[0x11D];
    pic->P16Emap.TX1STA = &pic->ram[0x11E];
    // pic->P16Emap.BAUD1CON = &pic->ram[0x11F];
    pic->P16Emap.SSP1BUF = &pic->ram[0x18C];
    pic->P16Emap.SSP1ADD = &pic->ram[0x18D];
    // pic->P16Emap.SSP1MSK = &pic->ram[0x18E];
    pic->P16Emap.SSP1STAT = &pic->ram[0x18F];
    pic->P16Emap.SSP1CON1 = &pic->ram[0x190];
    pic->P16Emap.SSP1CON2 = &pic->ram[0x191];
    /*
    pic->P16Emap.SSP1CON3 = &pic->ram[0x192];
    pic->P16Emap.SSP2BUF = &pic->ram[0x196];
    pic->P16Emap.SSP2ADD = &pic->ram[0x197];
    pic->P16Emap.SSP2MSK = &pic->ram[0x198];
    pic->P16Emap.SSP2STAT = &pic->ram[0x199];
    pic->P16Emap.SSP2CON1 = &pic->ram[0x19A];
    pic->P16Emap.SSP2CON2 = &pic->ram[0x19B];
    pic->P16Emap.SSP2CON3 = &pic->ram[0x19C];
    */
    pic->P16Emap.T1CON = &pic->ram[0x20E];
    /*
    pic->P16Emap.T1GCON = &pic->ram[0x20F];
    pic->P16Emap.T1GATE = &pic->ram[0x210];
    pic->P16Emap.T1CLK = &pic->ram[0x211];
    pic->P16Emap.T3CON = &pic->ram[0x214];
    pic->P16Emap.T3GCON = &pic->ram[0x215];
    pic->P16Emap.T3GATE = &pic->ram[0x216];
    pic->P16Emap.T3CLK = &pic->ram[0x217];
    pic->P16Emap.T5CON = &pic->ram[0x21A];
    pic->P16Emap.T5GCON = &pic->ram[0x21B];
    pic->P16Emap.T5GATE = &pic->ram[0x21C];
    pic->P16Emap.T5CLK = &pic->ram[0x21D];
    pic->P16Emap.CCPTMRS0 = &pic->ram[0x21E];
    pic->P16Emap.CCPTMRS1 = &pic->ram[0x21F];
    pic->P16Emap.T2TMR = &pic->ram[0x28C];
    pic->P16Emap.T2PR = &pic->ram[0x28D];
    */
    pic->P16Emap.T2CON = &pic->ram[0x28E];
    /*
    pic->P16Emap.T2HLT = &pic->ram[0x28F];
    pic->P16Emap.T2CLKCON = &pic->ram[0x290];
    pic->P16Emap.T2RST = &pic->ram[0x291];
    pic->P16Emap.T4TMR = &pic->ram[0x292];
    pic->P16Emap.T4PR = &pic->ram[0x293];
    pic->P16Emap.T4CON = &pic->ram[0x294];
    pic->P16Emap.T4HLT = &pic->ram[0x295];
    pic->P16Emap.T4CLKCON = &pic->ram[0x296];
    pic->P16Emap.T4RST = &pic->ram[0x297];
    pic->P16Emap.T6TMR = &pic->ram[0x298];
    pic->P16Emap.T6PR = &pic->ram[0x299];
    pic->P16Emap.T6CON = &pic->ram[0x29A];
    pic->P16Emap.T6HLT = &pic->ram[0x29B];
    pic->P16Emap.T6CLKCON = &pic->ram[0x29C];
    pic->P16Emap.T6RST = &pic->ram[0x29D];
    */
    pic->P16Emap.CCP1CON = &pic->ram[0x30E];
    // pic->P16Emap.CCP1CAP = &pic->ram[0x30F];
    pic->P16Emap.CCP2CON = &pic->ram[0x312];
    /*
    pic->P16Emap.CCP2CAP = &pic->ram[0x313];
    pic->P16Emap.CCP3CON = &pic->ram[0x316];
    pic->P16Emap.CCP3CAP = &pic->ram[0x317];
    pic->P16Emap.CCP4CON = &pic->ram[0x31A];
    pic->P16Emap.CCP4CAP = &pic->ram[0x31B];
    pic->P16Emap.CCP5CON = &pic->ram[0x31E];
    pic->P16Emap.CCP5CAP = &pic->ram[0x31F];
    pic->P16Emap.PWM6CON = &pic->ram[0x38E];
    pic->P16Emap.PWM7CON = &pic->ram[0x392];
    pic->P16Emap.SCANLADRL = &pic->ram[0x40C];
    pic->P16Emap.SCANLADRH = &pic->ram[0x40D];
    pic->P16Emap.SCANHADRL = &pic->ram[0x40E];
    pic->P16Emap.SCANHADRH = &pic->ram[0x40F];
    pic->P16Emap.SCANCON0 = &pic->ram[0x410];
    pic->P16Emap.SCANTRIG = &pic->ram[0x411];
    pic->P16Emap.CRCCON0 = &pic->ram[0x41E];
    pic->P16Emap.CRCCON1 = &pic->ram[0x41F];
    pic->P16Emap.SMT1CON0 = &pic->ram[0x498];
    pic->P16Emap.SMT1CON1 = &pic->ram[0x499];
    pic->P16Emap.SMT1STAT = &pic->ram[0x49A];
    pic->P16Emap.SMT1CLK = &pic->ram[0x49B];
    pic->P16Emap.SMT1SIG = &pic->ram[0x49C];
    pic->P16Emap.SMT1WIN = &pic->ram[0x49D];
    pic->P16Emap.SMT2CON0 = &pic->ram[0x518];
    pic->P16Emap.SMT2CON1 = &pic->ram[0x519];
    pic->P16Emap.SMT2STAT = &pic->ram[0x51A];
    pic->P16Emap.SMT2CLK = &pic->ram[0x51B];
    pic->P16Emap.SMT2SIG = &pic->ram[0x51C];
    pic->P16Emap.SMT2WIN = &pic->ram[0x51D];
    pic->P16Emap.NCO1CON = &pic->ram[0x592];
    pic->P16Emap.NCO1CLK = &pic->ram[0x593];
    pic->P16Emap.CWG1CLKCON = &pic->ram[0x60C];
    pic->P16Emap.CWG1ISM = &pic->ram[0x60D];
    pic->P16Emap.CWG1DBR = &pic->ram[0x60E];
    pic->P16Emap.CWG1DBF = &pic->ram[0x60F];
    pic->P16Emap.CWG1CON0 = &pic->ram[0x610];
    pic->P16Emap.CWG1CON1 = &pic->ram[0x611];
    pic->P16Emap.CWG1AS0 = &pic->ram[0x612];
    pic->P16Emap.CWG1AS1 = &pic->ram[0x613];
    pic->P16Emap.CWG1STR = &pic->ram[0x614];
    pic->P16Emap.CWG2CLKCON = &pic->ram[0x616];
    pic->P16Emap.CWG2ISM = &pic->ram[0x617];
    pic->P16Emap.CWG2DBR = &pic->ram[0x618];
    pic->P16Emap.CWG2DBF = &pic->ram[0x619];
    pic->P16Emap.CWG2CON0 = &pic->ram[0x61A];
    pic->P16Emap.CWG2CON1 = &pic->ram[0x61B];
    pic->P16Emap.CWG2AS0 = &pic->ram[0x61C];
    pic->P16Emap.CWG2AS1 = &pic->ram[0x61D];
    pic->P16Emap.CWG2STR = &pic->ram[0x61E];
    pic->P16Emap.CWG3CLKCON = &pic->ram[0x68C];
    pic->P16Emap.CWG3ISM = &pic->ram[0x68D];
    pic->P16Emap.CWG3DBR = &pic->ram[0x68E];
    pic->P16Emap.CWG3DBF = &pic->ram[0x68F];
    pic->P16Emap.CWG3CON0 = &pic->ram[0x690];
    pic->P16Emap.CWG3CON1 = &pic->ram[0x691];
    pic->P16Emap.CWG3AS0 = &pic->ram[0x692];
    pic->P16Emap.CWG3AS1 = &pic->ram[0x693];
    pic->P16Emap.CWG3STR = &pic->ram[0x694];
     */
    pic->P16Emap.PIR0 = &pic->ram[0x70C];
    pic->P16Emap.PIR1 = &pic->ram[0x70D];
    pic->P16Emap.PIR2 = &pic->ram[0x70E];
    /*
    pic->P16Emap.PIR3 = &pic->ram[0x70F];
    pic->P16Emap.PIR4 = &pic->ram[0x710];
    pic->P16Emap.PIR5 = &pic->ram[0x711];
    pic->P16Emap.PIR6 = &pic->ram[0x712];
    pic->P16Emap.PIR7 = &pic->ram[0x713];
    pic->P16Emap.PIR8 = &pic->ram[0x714];
     */
    pic->P16Emap.PIE0 = &pic->ram[0x716];
    pic->P16Emap.PIE1 = &pic->ram[0x717];
    pic->P16Emap.PIE2 = &pic->ram[0x718];
    /*
    pic->P16Emap.PIE3 = &pic->ram[0x719];
    pic->P16Emap.PIE4 = &pic->ram[0x71A];
    pic->P16Emap.PIE5 = &pic->ram[0x71B];
    pic->P16Emap.PIE6 = &pic->ram[0x71C];
    pic->P16Emap.PIE7 = &pic->ram[0x71D];
    pic->P16Emap.PIE8 = &pic->ram[0x71E];
    pic->P16Emap.PMD0 = &pic->ram[0x796];
    pic->P16Emap.PMD1 = &pic->ram[0x797];
    pic->P16Emap.PMD2 = &pic->ram[0x798];
    pic->P16Emap.PMD3 = &pic->ram[0x799];
    pic->P16Emap.PMD4 = &pic->ram[0x79A];
    pic->P16Emap.PMD5 = &pic->ram[0x79B];
    */
    pic->P16Emap.WDTCON0 = &pic->ram[0x80C];
    /*
    pic->P16Emap.WDTCON1 = &pic->ram[0x80D];
    pic->P16Emap.WDTPSL = &pic->ram[0x80E];
    pic->P16Emap.WDTPSH = &pic->ram[0x80F];
    pic->P16Emap.WDTTMR = &pic->ram[0x810];
    pic->P16Emap.BORCON = &pic->ram[0x811];
    pic->P16Emap.VREGCON = &pic->ram[0x812];
    pic->P16Emap.PCON0 = &pic->ram[0x813];
    pic->P16Emap.CCDCON = &pic->ram[0x814];
    */
    pic->P16Emap.NVMADRL = &pic->ram[0x81A];
    pic->P16Emap.NVMADRH = &pic->ram[0x81B];
    pic->P16Emap.NVMDATL = &pic->ram[0x81C];
    pic->P16Emap.NVMDATH = &pic->ram[0x81D];
    pic->P16Emap.NVMCON1 = &pic->ram[0x81E];
    pic->P16Emap.NVMCON2 = &pic->ram[0x81F];
    /*
   pic->P16Emap.CPUDOZE = &pic->ram[0x88C];
   pic->P16Emap.OSCCON1 = &pic->ram[0x88D];
   pic->P16Emap.OSCCON2 = &pic->ram[0x88E];
   pic->P16Emap.OSCCON3 = &pic->ram[0x88F];
   pic->P16Emap.OSCSTAT = &pic->ram[0x890];
   pic->P16Emap.OSCEN = &pic->ram[0x891];
   pic->P16Emap.OSCTUNE = &pic->ram[0x892];
   pic->P16Emap.OSCFRQ = &pic->ram[0x893];
   pic->P16Emap.CLKRCON = &pic->ram[0x895];
   pic->P16Emap.CLKRCLK = &pic->ram[0x896];
   pic->P16Emap.MDCON0 = &pic->ram[0x897];
   pic->P16Emap.MDCON1 = &pic->ram[0x898];
   pic->P16Emap.MDSRC = &pic->ram[0x899];
   pic->P16Emap.MDCARL = &pic->ram[0x89A];
   pic->P16Emap.MDCARH = &pic->ram[0x89B];
   pic->P16Emap.FVRCON = &pic->ram[0x90C];
   pic->P16Emap.DAC1CON0 = &pic->ram[0x90E];
   pic->P16Emap.DAC1CON1 = &pic->ram[0x90F];
   pic->P16Emap.ZCD1CON = &pic->ram[0x91F];
   pic->P16Emap.CMOUT = &pic->ram[0x98F];
   pic->P16Emap.CM1CON0 = &pic->ram[0x990];
   pic->P16Emap.CM1CON1 = &pic->ram[0x991];
   pic->P16Emap.CM1NSEL = &pic->ram[0x992];
   pic->P16Emap.CM1PSEL = &pic->ram[0x993];
   pic->P16Emap.CM2CON0 = &pic->ram[0x994];
   pic->P16Emap.CM2CON1 = &pic->ram[0x995];
   pic->P16Emap.CM2NSEL = &pic->ram[0x996];
   pic->P16Emap.CM2PSEL = &pic->ram[0x997];
   pic->P16Emap.CLCDATA = &pic->ram[0xE0F];
   pic->P16Emap.CLC1CON = &pic->ram[0xE10];
   pic->P16Emap.CLC1POL = &pic->ram[0xE11];
   pic->P16Emap.CLC1SEL0 = &pic->ram[0xE12];
   pic->P16Emap.CLC1SEL1 = &pic->ram[0xE13];
   pic->P16Emap.CLC1SEL2 = &pic->ram[0xE14];
   pic->P16Emap.CLC1SEL3 = &pic->ram[0xE15];
   pic->P16Emap.CLC1GLS0 = &pic->ram[0xE16];
   pic->P16Emap.CLC1GLS1 = &pic->ram[0xE17];
   pic->P16Emap.CLC1GLS2 = &pic->ram[0xE18];
   pic->P16Emap.CLC1GLS3 = &pic->ram[0xE19];
   pic->P16Emap.CLC2CON = &pic->ram[0xE1A];
   pic->P16Emap.CLC2POL = &pic->ram[0xE1B];
   pic->P16Emap.CLC2SEL0 = &pic->ram[0xE1C];
   pic->P16Emap.CLC2SEL1 = &pic->ram[0xE1D];
   pic->P16Emap.CLC2SEL2 = &pic->ram[0xE1E];
   pic->P16Emap.CLC2SEL3 = &pic->ram[0xE1F];
   pic->P16Emap.CLC2GLS0 = &pic->ram[0xE20];
   pic->P16Emap.CLC2GLS1 = &pic->ram[0xE21];
   pic->P16Emap.CLC2GLS2 = &pic->ram[0xE22];
   pic->P16Emap.CLC2GLS3 = &pic->ram[0xE23];
   pic->P16Emap.CLC3CON = &pic->ram[0xE24];
   pic->P16Emap.CLC3POL = &pic->ram[0xE25];
   pic->P16Emap.CLC3SEL0 = &pic->ram[0xE26];
   pic->P16Emap.CLC3SEL1 = &pic->ram[0xE27];
   pic->P16Emap.CLC3SEL2 = &pic->ram[0xE28];
   pic->P16Emap.CLC3SEL3 = &pic->ram[0xE29];
   pic->P16Emap.CLC3GLS0 = &pic->ram[0xE2A];
   pic->P16Emap.CLC3GLS1 = &pic->ram[0xE2B];
   pic->P16Emap.CLC3GLS2 = &pic->ram[0xE2C];
   pic->P16Emap.CLC3GLS3 = &pic->ram[0xE2D];
   pic->P16Emap.CLC4CON = &pic->ram[0xE2E];
   pic->P16Emap.CLC4POL = &pic->ram[0xE2F];
   pic->P16Emap.CLC4SEL0 = &pic->ram[0xE30];
   pic->P16Emap.CLC4SEL1 = &pic->ram[0xE31];
   pic->P16Emap.CLC4SEL2 = &pic->ram[0xE32];
   pic->P16Emap.CLC4SEL3 = &pic->ram[0xE33];
   pic->P16Emap.CLC4GLS0 = &pic->ram[0xE34];
   pic->P16Emap.CLC4GLS1 = &pic->ram[0xE35];
   pic->P16Emap.CLC4GLS2 = &pic->ram[0xE36];
   pic->P16Emap.CLC4GLS3 = &pic->ram[0xE37];
   pic->P16Emap.PPSLOCK = &pic->ram[0xE8F];
   pic->P16Emap.INTPPS = &pic->ram[0xE90];
   pic->P16Emap.T0CKIPPS = &pic->ram[0xE91];
   pic->P16Emap.T1CKIPPS = &pic->ram[0xE92];
   pic->P16Emap.T1GPPS = &pic->ram[0xE93];
   pic->P16Emap.T3CKIPPS = &pic->ram[0xE94];
   pic->P16Emap.T3GPPS = &pic->ram[0xE95];
   pic->P16Emap.T5CKIPPS = &pic->ram[0xE96];
   pic->P16Emap.T5GPPS = &pic->ram[0xE97];
   pic->P16Emap.T2AINPPS = &pic->ram[0xE9C];
   pic->P16Emap.T4AINPPS = &pic->ram[0xE9D];
   pic->P16Emap.T6AINPPS = &pic->ram[0xE9E];
   pic->P16Emap.CCP1PPS = &pic->ram[0xEA1];
   pic->P16Emap.CCP2PPS = &pic->ram[0xEA2];
   pic->P16Emap.CCP3PPS = &pic->ram[0xEA3];
   pic->P16Emap.CCP4PPS = &pic->ram[0xEA4];
   pic->P16Emap.CCP5PPS = &pic->ram[0xEA5];
   pic->P16Emap.SMT1WINPPS = &pic->ram[0xEA9];
   pic->P16Emap.SMT1SIGPPS = &pic->ram[0xEAA];
   pic->P16Emap.SMT2WINPPS = &pic->ram[0xEAB];
   pic->P16Emap.SMT2SIGPPS = &pic->ram[0xEAC];
   pic->P16Emap.CWG1PPS = &pic->ram[0xEB1];
   pic->P16Emap.CWG2PPS = &pic->ram[0xEB2];
   pic->P16Emap.CWG3PPS = &pic->ram[0xEB3];
   pic->P16Emap.MDCARLPPS = &pic->ram[0xEB8];
   pic->P16Emap.MDCARHPPS = &pic->ram[0xEB9];
   pic->P16Emap.MDSRCPPS = &pic->ram[0xEBA];
   pic->P16Emap.CLCIN0PPS = &pic->ram[0xEBB];
   pic->P16Emap.CLCIN1PPS = &pic->ram[0xEBC];
   pic->P16Emap.CLCIN2PPS = &pic->ram[0xEBD];
   pic->P16Emap.CLCIN3PPS = &pic->ram[0xEBE];
   pic->P16Emap.ADCACTPPS = &pic->ram[0xEC3];
   pic->P16Emap.SSP1CLKPPS = &pic->ram[0xEC5];
   pic->P16Emap.SSP1DATPPS = &pic->ram[0xEC6];
   pic->P16Emap.SSP1SSPPS = &pic->ram[0xEC7];
   pic->P16Emap.SSP2CLKPPS = &pic->ram[0xEC8];
   pic->P16Emap.SSP2DATPPS = &pic->ram[0xEC9];
   pic->P16Emap.SSP2SSPPS = &pic->ram[0xECA];
   pic->P16Emap.RXPPS = &pic->ram[0xECB];
   pic->P16Emap.TXPPS = &pic->ram[0xECC];
   */
    pic->P16Emap.RA0PPS = &pic->ram[0xF10];
    pic->P16Emap.RA1PPS = &pic->ram[0xF11];
    pic->P16Emap.RA2PPS = &pic->ram[0xF12];
    pic->P16Emap.RA3PPS = &pic->ram[0xF13];
    pic->P16Emap.RA4PPS = &pic->ram[0xF14];
    pic->P16Emap.RA5PPS = &pic->ram[0xF15];
    pic->P16Emap.RA6PPS = &pic->ram[0xF16];
    pic->P16Emap.RA7PPS = &pic->ram[0xF17];
    pic->P16Emap.RB0PPS = &pic->ram[0xF18];
    pic->P16Emap.RB1PPS = &pic->ram[0xF19];
    pic->P16Emap.RB2PPS = &pic->ram[0xF1A];
    pic->P16Emap.RB3PPS = &pic->ram[0xF1B];
    pic->P16Emap.RB4PPS = &pic->ram[0xF1C];
    pic->P16Emap.RB5PPS = &pic->ram[0xF1D];
    pic->P16Emap.RB6PPS = &pic->ram[0xF1E];
    pic->P16Emap.RB7PPS = &pic->ram[0xF1F];
    pic->P16Emap.RC0PPS = &pic->ram[0xF20];
    pic->P16Emap.RC1PPS = &pic->ram[0xF21];
    pic->P16Emap.RC2PPS = &pic->ram[0xF22];
    pic->P16Emap.RC3PPS = &pic->ram[0xF23];
    pic->P16Emap.RC4PPS = &pic->ram[0xF24];
    pic->P16Emap.RC5PPS = &pic->ram[0xF25];
    pic->P16Emap.RC6PPS = &pic->ram[0xF26];
    pic->P16Emap.RC7PPS = &pic->ram[0xF27];
    pic->P16Emap.ANSELA = &pic->ram[0xF38];
    /*
    pic->P16Emap.WPUA = &pic->ram[0xF39];
    pic->P16Emap.ODCONA = &pic->ram[0xF3A];
    pic->P16Emap.SLRCONA = &pic->ram[0xF3B];
    pic->P16Emap.INLVLA = &pic->ram[0xF3C];
    pic->P16Emap.IOCAP = &pic->ram[0xF3D];
    pic->P16Emap.IOCAN = &pic->ram[0xF3E];
    pic->P16Emap.IOCAF = &pic->ram[0xF3F];
    pic->P16Emap.CCDNA = &pic->ram[0xF40];
    pic->P16Emap.CCDPA = &pic->ram[0xF41];
    */
    pic->P16Emap.ANSELB = &pic->ram[0xF43];
    /*
    pic->P16Emap.WPUB = &pic->ram[0xF44];
    pic->P16Emap.ODCONB = &pic->ram[0xF45];
    pic->P16Emap.SLRCONB = &pic->ram[0xF46];
    pic->P16Emap.INLVLB = &pic->ram[0xF47];
     */
    pic->P16Emap.IOCBP = &pic->ram[0xF48];
    pic->P16Emap.IOCBN = &pic->ram[0xF49];
    pic->P16Emap.IOCBF = &pic->ram[0xF4A];
    /*
    pic->P16Emap.CCDNB = &pic->ram[0xF4B];
    pic->P16Emap.CCDPB = &pic->ram[0xF4C];
    */
    pic->P16Emap.ANSELC = &pic->ram[0xF4E];
    /*
    pic->P16Emap.WPUC = &pic->ram[0xF4F];
    pic->P16Emap.ODCONC = &pic->ram[0xF50];
    pic->P16Emap.SLRCONC = &pic->ram[0xF51];
    pic->P16Emap.INLVLC = &pic->ram[0xF52];
    pic->P16Emap.IOCCP = &pic->ram[0xF53];
    pic->P16Emap.IOCCN = &pic->ram[0xF54];
    pic->P16Emap.IOCCF = &pic->ram[0xF55];
    pic->P16Emap.CCDNC = &pic->ram[0xF56];
    pic->P16Emap.CCDPC = &pic->ram[0xF57];
    pic->P16Emap.WPUE = &pic->ram[0xF65];
    pic->P16Emap.INLVLE = &pic->ram[0xF68];
    pic->P16Emap.IOCEP = &pic->ram[0xF69];
    pic->P16Emap.IOCEN = &pic->ram[0xF6A];
    pic->P16Emap.IOCEF = &pic->ram[0xF6B];
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

01 - VPP MCLR_n ICD_n IOCE3 RE3 MCLR
02 - ANA0 C1IN0- C2IN0- IOCA0 RA0
03 - ANA1 C1IN1- C2IN1- IOCA1 RA1
04 - DAC1OUT1 VREF- ANA2 C1IN0+ C2IN0+ IOCA2 RA2
05 - VREF+ ANA3 C1IN1+ IOCA3 RA3
06 - ANA4 IOCA4 RA4
07 - ANA5 IOCA5 RA5
08 - AVSS VSS
09 - OSC1 CLKIN ANA7 IOCA7 RA7
10 - OSC2 CLKOUT ANA6 IOCA6 RA6
11 - SOSCO ANC0 IOCC0 RC0
12 - SOSCI ANC1 IOCC1 RC1
13 - ANC2 IOCC2 RC2
14 - ANC3 SMB_I2C IOCC3 RC3
15 - ANC4 SMB_I2C IOCC4 RC4
16 - ANC5 IOCC5 RC5
17 - ANC6 IOCC6 RC6
18 - ANC7 IOCC7 RC7
19 - VSS
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

/*
======================
Family=P16E
processor=PIC16F18855
deviceid=0x306C
 */

void PIC16F18855_reset(_pic* pic) {
    if (pic->pkg == PDIP) {
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

        pic->adc[16] = 15;
        pic->adc[17] = 16;
        pic->adc[18] = 17;
        pic->adc[19] = 18;
        pic->adc[20] = 23;
        pic->adc[21] = 24;
        pic->adc[22] = 25;
        pic->adc[23] = 26;

        pic->pgc = 27;
        pic->pgd = 28;

        // Default values

        pic->ccp[0].pin = 13;
        pic->ccp[1].pin = 12;
        pic->ccp[2].pin = 26;
        pic->ccp[3].pin = 21;
        pic->ccp[4].pin = 6;

        pic->usart_rx[0] = 18;
        pic->usart_tx[0] = 17;

        pic->sck = 14;
        pic->sdo = 10;
        pic->sdi = 15;

        pic->t0cki = 6;
        pic->t1cki = 11;

    } else if (pic->pkg == QFN) {
        // QFN !!!!
        pic->pins[0].port = pic->P16Emap.PORTA;
        pic->pins[0].pord = 2;
        pic->pins[1].port = pic->P16Emap.PORTA;
        pic->pins[1].pord = 3;
        pic->pins[2].port = pic->P16Emap.PORTA;
        pic->pins[2].pord = 4;
        pic->pins[3].port = pic->P16Emap.PORTA;
        pic->pins[3].pord = 5;
        pic->pins[4].port = P_VSS;
        pic->pins[4].pord = -1;
        pic->pins[5].port = pic->P16Emap.PORTA;
        pic->pins[5].pord = 6;
        pic->pins[6].port = pic->P16Emap.PORTA;
        pic->pins[6].pord = 7;
        pic->pins[7].port = pic->P16Emap.PORTC;
        pic->pins[7].pord = 0;
        pic->pins[8].port = pic->P16Emap.PORTC;
        pic->pins[8].pord = 1;
        pic->pins[9].port = pic->P16Emap.PORTC;
        pic->pins[9].pord = 2;
        pic->pins[10].port = pic->P16Emap.PORTC;
        pic->pins[10].pord = 3;
        pic->pins[11].port = pic->P16Emap.PORTC;
        pic->pins[11].pord = 4;
        pic->pins[12].port = pic->P16Emap.PORTC;
        pic->pins[12].pord = 5;
        pic->pins[13].port = pic->P16Emap.PORTC;
        pic->pins[13].pord = 6;
        pic->pins[14].port = pic->P16Emap.PORTC;
        pic->pins[14].pord = 7;
        pic->pins[15].port = P_VSS;
        pic->pins[15].pord = -1;
        pic->pins[16].port = P_VDD;
        pic->pins[16].pord = -1;
        pic->pins[16].value = 1;
        pic->pins[17].port = pic->P16Emap.PORTB;
        pic->pins[17].pord = 0;
        pic->pins[18].port = pic->P16Emap.PORTB;
        pic->pins[18].pord = 1;
        pic->pins[19].port = pic->P16Emap.PORTB;
        pic->pins[19].pord = 2;
        pic->pins[20].port = pic->P16Emap.PORTB;
        pic->pins[20].pord = 3;
        pic->pins[21].port = pic->P16Emap.PORTB;
        pic->pins[21].pord = 4;
        pic->pins[22].port = pic->P16Emap.PORTB;
        pic->pins[22].pord = 5;
        pic->pins[23].port = pic->P16Emap.PORTB;
        pic->pins[23].pord = 6;
        pic->pins[24].port = pic->P16Emap.PORTB;
        pic->pins[24].pord = 7;
        pic->pins[25].port = pic->P16Emap.PORTE;
        pic->pins[25].pord = 3;
        pic->pins[26].port = pic->P16Emap.PORTA;
        pic->pins[26].pord = 0;
        pic->pins[27].port = pic->P16Emap.PORTA;
        pic->pins[27].pord = 1;

        pic->mclr = 26;

        pic->adc[0] = 27;
        pic->adc[1] = 28;
        pic->adc[2] = 1;
        pic->adc[3] = 2;
        pic->adc[4] = 3;
        pic->adc[5] = 4;
        pic->adc[6] = 7;
        pic->adc[7] = 6;

        pic->adc[8] = 18;
        pic->adc[9] = 19;
        pic->adc[10] = 20;
        pic->adc[11] = 21;
        pic->adc[12] = 22;
        pic->adc[13] = 23;
        pic->adc[14] = 24;
        pic->adc[15] = 25;

        pic->adc[16] = 8;
        pic->adc[17] = 9;
        pic->adc[18] = 10;
        pic->adc[19] = 11;
        pic->adc[20] = 12;
        pic->adc[21] = 13;
        pic->adc[22] = 14;
        pic->adc[23] = 15;

        pic->pgc = 17;
        pic->pgd = 18;

        // Default values

        pic->ccp[0].pin = 10;
        pic->ccp[1].pin = 9;
        pic->ccp[2].pin = 23;
        pic->ccp[3].pin = 18;
        pic->ccp[4].pin = 3;

        pic->usart_rx[0] = 9;
        pic->usart_tx[0] = 8;

        pic->sck = 11;
        pic->sdo = 7;
        pic->sdi = 12;

        pic->t0cki = 3;
        pic->t1cki = 8;
    }

    // TODO add P16E pin interrupt support
    /*
    pic->int0 = 0;
    pic->int1 = 0;
    pic->int2 = 0;
     */

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

void PIC16F18855_periferic(_pic* pic) {
    p16e_pps_out(pic);
    p16e_mssp(pic);
    p16e_adc_2(pic);
    p16e_int_pin_2(pic);
    p16e_int_ports(pic);
    p16e_tmr0_2(pic);
    p16e_wdt(pic);
    p16e_eeprom_2(pic);
    p16e_tmr1(pic);
    p16e_tmr2(pic);
    p16e_uart(pic, 0);
}

int PIC16F18855_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return (pic->config[1] & 0x0001);
            break;
        case CFG_WDT:
            return (pic->config[2] & 0x0060);
            break;
        case CFG_DEBUG:
            return !(pic->config[1] & 0x0200);
            break;
    }
    return 0;
}

void PIC16F18855_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0200;
}

void PIC16F18855_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F18855_start(_pic* pic) {
    pic->ROMSIZE = 8192;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 28;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 5;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 5;
    pic->ADCCOUNT = 24;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F18855_reset;
    pic->mmap = PIC16F18855_map;
    pic->getconf = PIC16F18855_getconf;
    pic->periferic = PIC16F18855_periferic;
    pic->interrupt = interrupt16E_2;
    pic->stop = PIC16F18855_stop;
    pic->disable_debug = PIC16F18855_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F18855, P16E, 0x306C);
