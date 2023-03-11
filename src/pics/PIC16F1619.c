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

void PIC16F1619_map(_pic* pic) {
    memset(&pic->P16Emap, 0, sizeof(P16Emap_t));

    pic->P16Emap.FSR0L = &pic->ram[0x4];
    pic->P16Emap.FSR0H = &pic->ram[0x5];
    pic->P16Emap.FSR1L = &pic->ram[0x6];
    pic->P16Emap.FSR1H = &pic->ram[0x7];
    pic->P16Emap.TMR1L = &pic->ram[0x16];
    pic->P16Emap.TMR1H = &pic->ram[0x17];
    pic->P16Emap.ADRESL = &pic->ram[0x9B];
    pic->P16Emap.ADRESH = &pic->ram[0x9C];
    /*
    pic->P16Emap.PMADRL = &pic->ram[0x191];
    pic->P16Emap.PMADRH = &pic->ram[0x192];
    pic->P16Emap.PMDATL = &pic->ram[0x193];
    pic->P16Emap.PMDATH = &pic->ram[0x194];
     */
    pic->P16Emap.SP1BRGL = &pic->ram[0x19B];
    pic->P16Emap.SP1BRGH = &pic->ram[0x19C];
    pic->P16Emap.CCPR1L = &pic->ram[0x291];
    pic->P16Emap.CCPR1H = &pic->ram[0x292];
    pic->P16Emap.CCPR2L = &pic->ram[0x298];
    pic->P16Emap.CCPR2H = &pic->ram[0x299];
    /*
    pic->P16Emap.PID1SETL = &pic->ram[0x58C];
    pic->P16Emap.PID1SETH = &pic->ram[0x58D];
    pic->P16Emap.PID1INL = &pic->ram[0x58E];
    pic->P16Emap.PID1INH = &pic->ram[0x58F];
    pic->P16Emap.PID1K1L = &pic->ram[0x590];
    pic->P16Emap.PID1K1H = &pic->ram[0x591];
    pic->P16Emap.PID1K2L = &pic->ram[0x592];
    pic->P16Emap.PID1K2H = &pic->ram[0x593];
    pic->P16Emap.PID1K3L = &pic->ram[0x594];
    pic->P16Emap.PID1K3H = &pic->ram[0x595];
    pic->P16Emap.PID1OUTLL = &pic->ram[0x596];
    pic->P16Emap.PID1OUTLH = &pic->ram[0x597];
    pic->P16Emap.PID1OUTHL = &pic->ram[0x598];
    pic->P16Emap.PID1OUTHH = &pic->ram[0x599];
    pic->P16Emap.PID1OUTU = &pic->ram[0x59A];
    pic->P16Emap.PID1Z1L = &pic->ram[0x59B];
    pic->P16Emap.PID1Z1H = &pic->ram[0x59C];
    pic->P16Emap.PID1Z1U = &pic->ram[0x59D];
    pic->P16Emap.PID1Z2L = &pic->ram[0x60C];
    pic->P16Emap.PID1Z2H = &pic->ram[0x60D];
    pic->P16Emap.PID1Z2U = &pic->ram[0x60E];
    pic->P16Emap.PID1ACCLL = &pic->ram[0x60F];
    pic->P16Emap.PID1ACCLH = &pic->ram[0x610];
    pic->P16Emap.PID1ACCHL = &pic->ram[0x611];
    pic->P16Emap.PID1ACCHH = &pic->ram[0x612];
    pic->P16Emap.PID1ACCU = &pic->ram[0x613];
    pic->P16Emap.PWM3DCL = &pic->ram[0x617];
    pic->P16Emap.PWM3DCH = &pic->ram[0x618];
    pic->P16Emap.PWM4DCL = &pic->ram[0x61A];
    pic->P16Emap.PWM4DCH = &pic->ram[0x61B];
    pic->P16Emap.SCANLADRL = &pic->ram[0x718];
    pic->P16Emap.SCANLADRH = &pic->ram[0x719];
    pic->P16Emap.SCANHADRL = &pic->ram[0x71A];
    pic->P16Emap.SCANHADRH = &pic->ram[0x71B];
    pic->P16Emap.CRCDATL = &pic->ram[0x791];
    pic->P16Emap.CRCDATH = &pic->ram[0x792];
    pic->P16Emap.CRCACCL = &pic->ram[0x793];
    pic->P16Emap.CRCACCH = &pic->ram[0x794];
    pic->P16Emap.CRCSHIFTL = &pic->ram[0x795];
    pic->P16Emap.CRCSHIFTH = &pic->ram[0x796];
    pic->P16Emap.CRCXORL = &pic->ram[0x797];
    pic->P16Emap.CRCXORH = &pic->ram[0x798];
    pic->P16Emap.AT1RESL = &pic->ram[0x80C];
    pic->P16Emap.AT1RESH = &pic->ram[0x80D];
    pic->P16Emap.AT1MISSL = &pic->ram[0x80E];
    pic->P16Emap.AT1MISSH = &pic->ram[0x80F];
    pic->P16Emap.AT1PERL = &pic->ram[0x810];
    pic->P16Emap.AT1PERH = &pic->ram[0x811];
    pic->P16Emap.AT1PHSL = &pic->ram[0x812];
    pic->P16Emap.AT1PHSH = &pic->ram[0x813];
    pic->P16Emap.AT1STPTL = &pic->ram[0x81A];
    pic->P16Emap.AT1STPTH = &pic->ram[0x81B];
    pic->P16Emap.AT1ERRL = &pic->ram[0x81C];
    pic->P16Emap.AT1ERRH = &pic->ram[0x81D];
    pic->P16Emap.AT1CC1L = &pic->ram[0x88F];
    pic->P16Emap.AT1CC1H = &pic->ram[0x890];
    pic->P16Emap.AT1CC2L = &pic->ram[0x893];
    pic->P16Emap.AT1CC2H = &pic->ram[0x894];
    pic->P16Emap.AT1CC3L = &pic->ram[0x897];
    pic->P16Emap.AT1CC3H = &pic->ram[0x898];
    pic->P16Emap.SMT1TMRL = &pic->ram[0xD8C];
    pic->P16Emap.SMT1TMRH = &pic->ram[0xD8D];
    pic->P16Emap.SMT1TMRU = &pic->ram[0xD8E];
    pic->P16Emap.SMT1CPRL = &pic->ram[0xD8F];
    pic->P16Emap.SMT1CPRH = &pic->ram[0xD90];
    pic->P16Emap.SMT1CPRU = &pic->ram[0xD91];
    pic->P16Emap.SMT1CPWL = &pic->ram[0xD92];
    pic->P16Emap.SMT1CPWH = &pic->ram[0xD93];
    pic->P16Emap.SMT1CPWU = &pic->ram[0xD94];
    pic->P16Emap.SMT1PRL = &pic->ram[0xD95];
    pic->P16Emap.SMT1PRH = &pic->ram[0xD96];
    pic->P16Emap.SMT1PRU = &pic->ram[0xD97];
    pic->P16Emap.SMT2TMRL = &pic->ram[0xD9E];
    pic->P16Emap.SMT2TMRH = &pic->ram[0xD9F];
    pic->P16Emap.SMT2TMRU = &pic->ram[0xDA0];
    pic->P16Emap.SMT2CPRL = &pic->ram[0xDA1];
    pic->P16Emap.SMT2CPRH = &pic->ram[0xDA2];
    pic->P16Emap.SMT2CPRU = &pic->ram[0xDA3];
    pic->P16Emap.SMT2CPWL = &pic->ram[0xDA4];
    pic->P16Emap.SMT2CPWH = &pic->ram[0xDA5];
    pic->P16Emap.SMT2CPWU = &pic->ram[0xDA6];
    pic->P16Emap.SMT2PRL = &pic->ram[0xDA7];
    pic->P16Emap.SMT2PRH = &pic->ram[0xDA8];
    pic->P16Emap.SMT2PRU = &pic->ram[0xDA9];
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
    pic->P16Emap.PIR1 = &pic->ram[0x10];
    pic->P16Emap.PIR2 = &pic->ram[0x11];
    /*
    pic->P16Emap.PIR3 = &pic->ram[0x12];
    pic->P16Emap.PIR4 = &pic->ram[0x13];
    pic->P16Emap.PIR5 = &pic->ram[0x14];
    */
    pic->P16Emap.TMR0 = &pic->ram[0x15];
    pic->P16Emap.T1CON = &pic->ram[0x18];
    /*
    pic->P16Emap.T1GCON = &pic->ram[0x19];
    pic->P16Emap.T2TMR = &pic->ram[0x1A];
    pic->P16Emap.T2PR = &pic->ram[0x1B];
    */
    pic->P16Emap.T2CON = &pic->ram[0x1C];
    /*
    pic->P16Emap.T2HLT = &pic->ram[0x1D];
    pic->P16Emap.T2CLKCON = &pic->ram[0x1E];
    pic->P16Emap.T2RST = &pic->ram[0x1F];
    */
    pic->P16Emap.TRISA = &pic->ram[0x8C];
    pic->P16Emap.TRISB = &pic->ram[0x8D];
    pic->P16Emap.TRISC = &pic->ram[0x8E];
    pic->P16Emap.PIE1 = &pic->ram[0x90];
    pic->P16Emap.PIE2 = &pic->ram[0x91];
    /*
    pic->P16Emap.PIE3 = &pic->ram[0x92];
    pic->P16Emap.PIE4 = &pic->ram[0x93];
    pic->P16Emap.PIE5 = &pic->ram[0x94];
    */
    pic->P16Emap.OPTION_REG = &pic->ram[0x95];
    /*
    pic->P16Emap.PCON = &pic->ram[0x96];
    pic->P16Emap.OSCTUNE = &pic->ram[0x98];
    pic->P16Emap.OSCCON = &pic->ram[0x99];
    pic->P16Emap.OSCSTAT = &pic->ram[0x9A];
    */
    pic->P16Emap.ADCON0 = &pic->ram[0x9D];
    pic->P16Emap.ADCON1 = &pic->ram[0x9E];
    // pic->P16Emap.ADCON2 = &pic->ram[0x9F];
    pic->P16Emap.LATA = &pic->ram[0x10C];
    pic->P16Emap.LATB = &pic->ram[0x10D];
    pic->P16Emap.LATC = &pic->ram[0x10E];
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
    pic->P16Emap.ZCD1CON = &pic->ram[0x11C];
    */
    pic->P16Emap.ANSELA = &pic->ram[0x18C];
    pic->P16Emap.ANSELB = &pic->ram[0x18D];
    pic->P16Emap.ANSELC = &pic->ram[0x18E];
    /*
    pic->P16Emap.PMCON1 = &pic->ram[0x195];
    pic->P16Emap.PMCON2 = &pic->ram[0x196];
    pic->P16Emap.VREGCON = &pic->ram[0x197];
    */
    pic->P16Emap.RC1REG = &pic->ram[0x199];
    pic->P16Emap.TX1REG = &pic->ram[0x19A];
    pic->P16Emap.RC1STA = &pic->ram[0x19D];
    pic->P16Emap.TX1STA = &pic->ram[0x19E];
    /*
    pic->P16Emap.BAUD1CON = &pic->ram[0x19F];
    pic->P16Emap.WPUA = &pic->ram[0x20C];
    pic->P16Emap.WPUB = &pic->ram[0x20D];
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
    pic->P16Emap.ODCONB = &pic->ram[0x28D];
    pic->P16Emap.ODCONC = &pic->ram[0x28E];
    */
    pic->P16Emap.CCP1CON = &pic->ram[0x293];
    // pic->P16Emap.CCP1CAP = &pic->ram[0x294];
    pic->P16Emap.CCP2CON = &pic->ram[0x29A];
    /*
    pic->P16Emap.CCP2CAP = &pic->ram[0x29B];
    pic->P16Emap.CCPTMRS = &pic->ram[0x29E];
    pic->P16Emap.SLRCONA = &pic->ram[0x30C];
    pic->P16Emap.SLRCONB = &pic->ram[0x30D];
    pic->P16Emap.SLRCONC = &pic->ram[0x30E];
    pic->P16Emap.INLVLA = &pic->ram[0x38C];
    pic->P16Emap.INLVLB = &pic->ram[0x38D];
    pic->P16Emap.INLVLC = &pic->ram[0x38E];
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
    pic->P16Emap.HIDRVC = &pic->ram[0x40E];
    pic->P16Emap.T4TMR = &pic->ram[0x413];
    pic->P16Emap.T4PR = &pic->ram[0x414];
    pic->P16Emap.T4CON = &pic->ram[0x415];
    pic->P16Emap.T4HLT = &pic->ram[0x416];
    pic->P16Emap.T4CLKCON = &pic->ram[0x417];
    pic->P16Emap.T4RST = &pic->ram[0x418];
    pic->P16Emap.T6TMR = &pic->ram[0x41A];
    pic->P16Emap.T6PR = &pic->ram[0x41B];
    pic->P16Emap.T6CON = &pic->ram[0x41C];
    pic->P16Emap.T6HLT = &pic->ram[0x41D];
    pic->P16Emap.T6CLKCON = &pic->ram[0x41E];
    pic->P16Emap.T6RST = &pic->ram[0x41F];
    pic->P16Emap.TMR3L = &pic->ram[0x493];
    pic->P16Emap.TMR3H = &pic->ram[0x494];
    pic->P16Emap.T3CON = &pic->ram[0x495];
    pic->P16Emap.T3GCON = &pic->ram[0x496];
    pic->P16Emap.TMR5L = &pic->ram[0x49A];
    pic->P16Emap.TMR5H = &pic->ram[0x49B];
    pic->P16Emap.T5CON = &pic->ram[0x49C];
    pic->P16Emap.T5GCON = &pic->ram[0x49D];
    pic->P16Emap.PID1CON = &pic->ram[0x614];
    pic->P16Emap.PWM3CON = &pic->ram[0x619];
    pic->P16Emap.PWM4CON = &pic->ram[0x61C];
    pic->P16Emap.CWG1DBR = &pic->ram[0x691];
    pic->P16Emap.CWG1DBF = &pic->ram[0x692];
    pic->P16Emap.CWG1AS0 = &pic->ram[0x693];
    pic->P16Emap.CWG1AS1 = &pic->ram[0x694];
    pic->P16Emap.CWG1OCON0 = &pic->ram[0x695];
    pic->P16Emap.CWG1CON0 = &pic->ram[0x696];
    pic->P16Emap.CWG1CON1 = &pic->ram[0x697];
    pic->P16Emap.CWG1CLKCON = &pic->ram[0x699];
    pic->P16Emap.CWG1ISM = &pic->ram[0x69A];
    */
    pic->P16Emap.WDTCON0 = &pic->ram[0x711];
    /*
    pic->P16Emap.WDTCON1 = &pic->ram[0x712];
    pic->P16Emap.WDTPSL = &pic->ram[0x713];
    pic->P16Emap.WDTPSH = &pic->ram[0x714];
    pic->P16Emap.WDTTMR = &pic->ram[0x715];
    pic->P16Emap.SCANCON0 = &pic->ram[0x71C];
    pic->P16Emap.SCANTRIG = &pic->ram[0x71D];
    pic->P16Emap.CRCCON0 = &pic->ram[0x799];
    pic->P16Emap.CRCCON1 = &pic->ram[0x79A];
    pic->P16Emap.AT1CON0 = &pic->ram[0x814];
    pic->P16Emap.AT1CON1 = &pic->ram[0x815];
    pic->P16Emap.AT1IR0 = &pic->ram[0x816];
    pic->P16Emap.AT1IE0 = &pic->ram[0x817];
    pic->P16Emap.AT1IR1 = &pic->ram[0x818];
    pic->P16Emap.AT1IE1 = &pic->ram[0x819];
    pic->P16Emap.AT1CLK = &pic->ram[0x88C];
    pic->P16Emap.AT1SIG = &pic->ram[0x88D];
    pic->P16Emap.AT1CSEL1 = &pic->ram[0x88E];
    pic->P16Emap.AT1CCON1 = &pic->ram[0x891];
    pic->P16Emap.AT1CSEL2 = &pic->ram[0x892];
    pic->P16Emap.AT1CCON2 = &pic->ram[0x895];
    pic->P16Emap.AT1CSEL3 = &pic->ram[0x896];
    pic->P16Emap.AT1CCON3 = &pic->ram[0x899];
    pic->P16Emap.SMT1CON0 = &pic->ram[0xD98];
    pic->P16Emap.SMT1CON1 = &pic->ram[0xD99];
    pic->P16Emap.SMT1STAT = &pic->ram[0xD9A];
    pic->P16Emap.SMT1CLK = &pic->ram[0xD9B];
    pic->P16Emap.SMT1SIG = &pic->ram[0xD9C];
    pic->P16Emap.SMT1WIN = &pic->ram[0xD9D];
    pic->P16Emap.SMT2CON0 = &pic->ram[0xDAA];
    pic->P16Emap.SMT2CON1 = &pic->ram[0xDAB];
    pic->P16Emap.SMT2STAT = &pic->ram[0xDAC];
    pic->P16Emap.SMT2CLK = &pic->ram[0xDAD];
    pic->P16Emap.SMT2SIG = &pic->ram[0xDAE];
    pic->P16Emap.SMT2WIN = &pic->ram[0xDAF];
    pic->P16Emap.PPSLOCK = &pic->ram[0xE0F];
    pic->P16Emap.INTPPS = &pic->ram[0xE10];
    pic->P16Emap.T0CKIPPS = &pic->ram[0xE11];
    pic->P16Emap.T1CKIPPS = &pic->ram[0xE12];
    pic->P16Emap.T1GPPS = &pic->ram[0xE13];
    pic->P16Emap.CCP1PPS = &pic->ram[0xE14];
    pic->P16Emap.CCP2PPS = &pic->ram[0xE15];
    pic->P16Emap.ATINPPS = &pic->ram[0xE16];
    pic->P16Emap.CWGINPPS = &pic->ram[0xE17];
    pic->P16Emap.T2PPS = &pic->ram[0xE18];
    pic->P16Emap.T3CKIPPS = &pic->ram[0xE19];
    pic->P16Emap.T3GPPS = &pic->ram[0xE1A];
    pic->P16Emap.T4PPS = &pic->ram[0xE1B];
    pic->P16Emap.T5CKIPPS = &pic->ram[0xE1C];
    pic->P16Emap.T5GPPS = &pic->ram[0xE1D];
    pic->P16Emap.T6PPS = &pic->ram[0xE1E];
    pic->P16Emap.ATCC1PPS = &pic->ram[0xE1F];
    pic->P16Emap.SSPCLKPPS = &pic->ram[0xE20];
    pic->P16Emap.SSPDATPPS = &pic->ram[0xE21];
    pic->P16Emap.SSPSSPPS = &pic->ram[0xE22];
    pic->P16Emap.ATCC2PPS = &pic->ram[0xE23];
    pic->P16Emap.RXPPS = &pic->ram[0xE24];
    pic->P16Emap.CKPPS = &pic->ram[0xE25];
    pic->P16Emap.SMT1SIGPPS = &pic->ram[0xE26];
    pic->P16Emap.SMT1WINPPS = &pic->ram[0xE27];
    pic->P16Emap.CLCIN0PPS = &pic->ram[0xE28];
    pic->P16Emap.CLCIN1PPS = &pic->ram[0xE29];
    pic->P16Emap.CLCIN2PPS = &pic->ram[0xE2A];
    pic->P16Emap.CLCIN3PPS = &pic->ram[0xE2B];
    pic->P16Emap.SMT2SIGPPS = &pic->ram[0xE2C];
    pic->P16Emap.SMT2WINPPS = &pic->ram[0xE2D];
    pic->P16Emap.ATCC3PPS = &pic->ram[0xE2E];
    pic->P16Emap.RA0PPS = &pic->ram[0xE90];
    pic->P16Emap.RA1PPS = &pic->ram[0xE91];
    pic->P16Emap.RA2PPS = &pic->ram[0xE92];
    pic->P16Emap.RA4PPS = &pic->ram[0xE94];
    pic->P16Emap.RA5PPS = &pic->ram[0xE95];
    pic->P16Emap.RB4PPS = &pic->ram[0xE9C];
    pic->P16Emap.RB5PPS = &pic->ram[0xE9D];
    pic->P16Emap.RB6PPS = &pic->ram[0xE9E];
    pic->P16Emap.RB7PPS = &pic->ram[0xE9F];
    pic->P16Emap.RC0PPS = &pic->ram[0xEA0];
    pic->P16Emap.RC1PPS = &pic->ram[0xEA1];
    pic->P16Emap.RC2PPS = &pic->ram[0xEA2];
    pic->P16Emap.RC3PPS = &pic->ram[0xEA3];
    pic->P16Emap.RC4PPS = &pic->ram[0xEA4];
    pic->P16Emap.RC5PPS = &pic->ram[0xEA5];
    pic->P16Emap.RC6PPS = &pic->ram[0xEA6];
    pic->P16Emap.RC7PPS = &pic->ram[0xEA7];
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
02 - RA5 CLKIN
03 - RA4 AN3 CLKOUT
04 - RA3 VPP nMCLR MCLR
05 - RC5 HIDC5
06 - RC4 HIDC4
07 - RC3 AN7 C1IN3- C2IN3-
08 - RC6 AN8
09 - RC7 AN9
10 - RB7
11 - RB6
12 - RB5 AN11
13 - RB4 I2C AN10
14 - RC2 AN6 C1IN2- C2IN2-
15 - RC1 AN5 C1IN1- C2IN1-
16 - RC0 AN4 C2IN+
17 - RA2 AN2 ZCDIN
18 - RA1 AN1 C2IN0- C1IN0- VREF+ ICSPCLK
19 - RA0 AN0 C1IN+ DACOUT ICSPDAT
20 - VSS
 */

/*
======================
Family=P16E
processor=PIC16F1619
deviceid=0x307D
 */

void PIC16F1619_reset(_pic* pic) {
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

    pic->pgc = 17;
    pic->pgd = 18;

    // default values

    pic->ccp[0].pin = 5;
    pic->ccp[1].pin = 7;

    pic->usart_rx[0] = 12;
    pic->usart_tx[0] = 10;

    pic->sck = 11;
    pic->sdo = 9;
    pic->sdi = 13;

    pic->t0cki = 17;
    pic->t1cki = 2;
    // TODO add P16E pin interrupt support
    /*
    pic->int0 = 0;
    pic->int1 = 0;
    pic->int2 = 0;
   */

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

void PIC16F1619_periferic(_pic* pic) {
    p16e_mssp(pic);
    p16e_adc(pic);
    p16e_int_pin(pic);
    p16e_int_ports(pic);
    p16e_tmr0(pic);
    p16e_wdt(pic);
    // p16e_eeprom (pic);
    p16e_tmr1(pic);
    p16e_tmr2(pic);
    p16e_uart(pic, 0);
}

int PIC16F1619_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[0] & 0x0040) > 0);
            break;
        case CFG_WDT:
            return (pic->config[2] & 0x0060);
            break;
        case CFG_DEBUG:
            return !(pic->config[1] & 0x0100);
            break;
    }
    return 0;
}

void PIC16F1619_disable_debug(_pic* pic) {
    pic->config[1] |= 0x0100;
}

void PIC16F1619_stop(_pic* pic) {
    p16e_uart_stop(pic, 0);
}

void PIC16F1619_start(_pic* pic) {
    pic->ROMSIZE = 8192;
    pic->EEPROMSIZE = 0;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 20;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 3;
    pic->STACKSIZE = 16;
    pic->CCPCOUNT = 2;
    pic->ADCCOUNT = 12;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC16F1619_reset;
    pic->mmap = PIC16F1619_map;
    pic->getconf = PIC16F1619_getconf;
    pic->periferic = PIC16F1619_periferic;
    pic->interrupt = interrupt16E;
    pic->stop = PIC16F1619_stop;
    pic->disable_debug = PIC16F1619_disable_debug;

    p16e_uart_start(pic, 0);
}

init_pic(PIC16F1619, P16E, 0x307D);
