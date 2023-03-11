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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/picsim.h"

static int strCompare(const void* s1, const void* s2) {
    return strcmp((const char*)s1, (const char*)s2);
}

int getproclist(char list[][30], int size) {
    int i;

    if (size > PIC_count) {
        size = PIC_count;
    }

    for (i = 0; i < size; i++) {
        strcpy(list[i], PICS[i].name);
    }

    qsort(list, size, sizeof(const char) * 30, strCompare);

    return size;
}

unsigned int getprocbyname(const char* str) {
    int i;
    for (i = 0; i < PIC_count; i++) {
        if (strcmp(PICS[i].name, str) == 0) {
            return PICS[i].ID;
        }
    }

    return 0;
}

char* getnamebyproc(int proc, char* str) {
    int i;
    for (i = 0; i < PIC_count; i++) {
        if (PICS[i].ID == proc) {
            strcpy(str, PICS[i].name);
            return str;
        }
    }
    str = NULL;
    return str;
}

unsigned int getfprocbyname(const char* str) {
    int i;
    for (i = 0; i < PIC_count; i++) {
        if (strcmp(PICS[i].name, str) == 0) {
            return PICS[i].family;
        }
    }
    return 0;
}

unsigned int getfprocbynumber(int proc) {
    int i;
    for (i = 0; i < PIC_count; i++) {
        if (PICS[i].ID == proc) {
            return PICS[i].family;
        }
    }

    return 0;
}

char FSRname[20];

const char* getFSRname_16(unsigned int addr) {
    switch (addr) {
        case 0x00:
            return "INDF";
        case 0x01:
            return "TMR0";
        case 0x02:
            return "PCL";
        case 0x03:
            return "STATUS";
        case 0x04:
            return "FSR";
        case 0x05:
            return "PORTA";
        case 0x06:
            return "PORTB";
        case 0x07:
            return "PORTC";
        case 0x08:
            return "PORTD";
        case 0x09:
            return "PORTE";
        case 0x0A:
            return "PCLATH";
        case 0x0B:
            return "INTCON";
        case 0x0C:
            return "PIR1";
        case 0x0D:
            return "PIR2";
        case 0x0E:
            return "TMR1L";
        case 0x0F:
            return "TMR1H";
        case 0x10:
            return "T1CON";
        case 0x11:
            return "TMR2";
        case 0x12:
            return "T2CON";
        case 0x13:
            return "SSPBUF";
        case 0x14:
            return "SSPCON";
        case 0x15:
            return "CCPR1L";
        case 0x16:
            return "CCPR1H";
        case 0x17:
            return "CCP1CON";
        case 0x18:
            return "RCSTA";
        case 0x19:
            return "TXREG";
        case 0x1A:
            return "RCREG";
        case 0x1B:
            return "CCPR2L";
        case 0x1C:
            return "CCPR2H";
        case 0x1D:
            return "CCP2CON";
        case 0x1E:
            return "ADRESH";
        case 0x1F:
            return "CMCON/ADCON0";

        case 0x81:
            return "OPTION";
        case 0x85:
            return "TRISA";
        case 0x86:
            return "TRISB";
        case 0x87:
            return "TRISC";
        case 0x88:
            return "TRISD";
        case 0x89:
            return "TRISE";
        case 0x8C:
            return "PIE1";
        case 0x8D:
            return "PIE2";
        case 0x91:
            return "SSPCON2";
        case 0x92:
            return "PR2";
        case 0x93:
            return "SSPADD";
        case 0x94:
            return "SSPSTAT";
        case 0x95:
            return "CCPR3L";
        case 0x96:
            return "CCPR3H";
        case 0x97:
            return "CCP3CON";
        case 0x98:
            return "TXSTA";
        case 0x99:
            return "SPBRG";
        case 0x9B:
            return "EEADR/ADCON2";
        case 0x9E:
            return "ADRESL";
        case 0x9F:
            return "ADCON1";

        case 0x18E:
            return "ICKBUG";
        case 0x18F:
            return "BIGBUG";

        case 0x9A:
            return "P628_EEDATA";
            // case 0x9B: return "P628_EEADR";
        case 0x9C:
            return "P628_EECON1";
        case 0x9D:
            return "P628_EECON2";

        case 0x10C:
            return "P877_EEDATA";
        case 0x10D:
            return "P877_EEADR";
        case 0x10E:
            return "P877_EEDATAH";
        case 0x10F:
            return "P877_EEADRH";
        case 0x18C:
            return "P877_EECON1";
        case 0x18D:
            return "P877_EECON2";
        default:
            sprintf(FSRname, "0x%03X", addr);
            return FSRname;
    }
}

const char* getFSRname_16E(unsigned int addr) {
    switch (addr) {
            // bank 0
            // core
        case 0x000:
            return "INDF0";
        case 0x001:
            return "INDF1";
        case 0x002:
            return "PCL";
        case 0x003:
            return "STATUS";
        case 0x004:
            return "FSR0L";
        case 0x005:
            return "FSR0H";
        case 0x006:
            return "FSR1L";
        case 0x007:
            return "FSR1H";
        case 0x008:
            return "BSR";
        case 0x009:
            return "WREG";
        case 0x00A:
            return "PCLATH";
        case 0x00B:
            return "INTCON";

        case 0x00C:
            return "PORTA";
        case 0x00D:
            return "PORTB";
        case 0x00E:
            return "PORTC";
        case 0x00F:
            return "PORTD";
        case 0x010:
            return "PIR1";
        case 0x011:
            return "PIR2";
        case 0x012:
            return "PIR3";
        case 0x013:
            return "PIR4";
        case 0x014:
            return "PIR5";
        case 0x015:
            return "TMR0";
        case 0x016:
            return "TMR1L";
        case 0x017:
            return "TMR1H";
        case 0x018:
            return "T1CON";
        case 0x019:
            return "T1GCON";
        case 0x01A:
            return "TMR2";
        case 0x01B:
            return "PR2";
        case 0x01C:
            return "T2CON";
        case 0x01D:
            return "T2HLT";
        case 0x01E:
            return "T2CLKCON";
        case 0x01F:
            return "T2RST";

            // bank 1
        case 0x08C:
            return "TRISA";
        case 0x08D:
            return "TRISB";
        case 0x08E:
            return "TRISC";
        case 0x08F:
            return "TRISD";
        case 0x090:
            return "PIE1";
        case 0x091:
            return "PIE2";
        case 0x092:
            return "PIE3";
        case 0x093:
            return "PIE4";
        case 0x094:
            return "PIE5";
        case 0x095:
            return "OPTION_REG";
        case 0x096:
            return "PCON";
            //
        case 0x098:
            return "OSCTUNE";
        case 0x099:
            return "OSCCON";
        case 0x09A:
            return "OSCSTAT";
        case 0x09B:
            return "ADRESL";
        case 0x09C:
            return "ADRESH";
        case 0x09D:
            return "ADCON0";
        case 0x09E:
            return "ADCON1";
        case 0x09F:
            return "ADCON2";

            // bank 2
        case 0x10C:
            return "LATA";
        case 0x10D:
            return "LATB";
        case 0x10E:
            return "LATC";
        case 0x10F:
            return "LATD";

            // bank 3
        case 0x18C:
            return "ANSELA";
        case 0x18D:
            return "ANSELB";
        case 0x18E:
            return "ANSELC";

        case 0x199:
            return "RC1REG";
        case 0x19A:
            return "TX1REG";
        case 0x19B:
            return "SP1BGRL";
        case 0x19C:
            return "SP1BGRH";
        case 0x19D:
            return "RC1STA";
        case 0x19E:
            return "TX1STA";
        case 0x19F:
            return "BAUD1CON";

            // bank 4
        case 0x20C:
            return "WPUA";
        case 0x20D:
            return "WPUB";
        case 0x20E:
            return "WPUC";
            // bank 5
        case 0x28C:
            return "ODCONA";
        case 0x28D:
            return "ODCONB";
        case 0x28E:
            return "ODCONC";

        case 0x291:
            return "CCP1RL";
        case 0x292:
            return "CCP1RH";
        case 0x293:
            return "CCP1CON";
        case 0x294:
            return "CCP1CAP";

        case 0x298:
            return "CCP2RL";
        case 0x299:
            return "CCP2RH";
        case 0x29A:
            return "CCP2CON";
        case 0x29B:
            return "CCP2CAP";

        case 0x29E:
            return "CCPTMRS";
            // bank 6
            // bank 7
            // bank 8
            // bank 9
            // bank 10
            // bank 11
            // bank 12
            // bank 13
            // bank 14
        case 0x711:
            return "WDTCON0";
        case 0x712:
            return "WDTCON1";
        case 0x713:
            return "WDTPSL";
        case 0x714:
            return "WDTPSH";
        case 0x715:
            return "WDTTMR";
            // bank 15
            // bank 16
            // bank 17
            // bank 18  Unimplemented
            // bank 19  Unimplemented
            // bank 20  Unimplemented
            // bank 21  Unimplemented
            // bank 22  Unimplemented
            // bank 23  Unimplemented
            // bank 24  Unimplemented
            // bank 25  Unimplemented
            // bank 26  Unimplemented
            // bank 27
            // bank 28
            // bank 29
            // bank 30
            // bank 31
        case 0xFE4:
            return "STATUS_SHAD";
        case 0xFE5:
            return "WREG_SHAD";
        case 0xFE6:
            return "BSR_SHAD";
        case 0xFE7:
            return "PCLATH_SHAD";
        case 0xFE8:
            return "FSR0L_SHAD";
        case 0xFE9:
            return "FSR0H_SHAD";
        case 0xFEA:
            return "FSR1L_SHAD";
        case 0xFEB:
            return "FSR1H_SHAD";
            //
        case 0xFED:
            return "STKPTR";
        case 0xFEE:
            return "TOSL";
        case 0xFEF:
            return "TOSH";

        default:
            sprintf(FSRname, "0x%03X", addr);
            return FSRname;
    }
}

const char* getFSRname_16E2(unsigned int addr) {
    switch (addr) {
            // bank 0
            // core
        case 0x000:
            return "INDF0";
        case 0x001:
            return "INDF1";
        case 0x002:
            return "PCL";
        case 0x003:
            return "STATUS";
        case 0x004:
            return "FSR0L";
        case 0x005:
            return "FSR0H";
        case 0x006:
            return "FSR1L";
        case 0x007:
            return "FSR1H";
        case 0x008:
            return "BSR";
        case 0x009:
            return "WREG";
        case 0x00A:
            return "PCLATH";
        case 0x00B:
            return "INTCON";

        case 0x00C:
            return "PORTA";
        case 0x00D:
            return "PORTB";
        case 0x00E:
            return "PORTC";
        case 0x00F:
            return "PORTD";
        case 0x010:
            return "PORTE";
        case 0x011:
            return "TRISA";
        case 0x012:
            return "TRISB";
        case 0x013:
            return "TRISC";
        case 0x014:
            return "TRISD";
        case 0x015:
            return "TRISE";
        case 0x016:
            return "LATA";
        case 0x017:
            return "LATB";
        case 0x018:
            return "LATC";
        case 0x019:
            return "LATD";
        case 0x01A:
            return "LATE";
            //
        case 0x01C:
            return "TMR0L";
        case 0x01D:
            return "TMR0H";
        case 0x01E:
            return "T0CON0";
        case 0x01F:
            return "T0CON1";

            // bank 1
        case 0x08C:
            return "ADRESL";
        case 0x08D:
            return "ADRESH";
        case 0x08E:
            return "ADPREVL";
        case 0x08F:
            return "ADPRVH";
        case 0x090:
            return "ADACCL";
        case 0x091:
            return "ADACCH";
            //
        case 0x093:
            return "ADCON0";
        case 0x094:
            return "ADCON1";
        case 0x095:
            return "ADCON2";
        case 0x096:
            return "ADCON3";
        case 0x097:
            return "ADSTAT";
        case 0x098:
            return "ADCLK";
        case 0x099:
            return "ADACT";
        case 0x09A:
            return "ADREF";
        case 0x09B:
            return "ADCAP";
        case 0x09C:
            return "ADPRE";
        case 0x09D:
            return "ASACQ";
        case 0x09E:
            return "ADPCH";

            // bank 2

            // bank 3

            // bank 4
        case 0x20C:
            return "TMR1L";
        case 0x20D:
            return "TMR1H";
        case 0x20E:
            return "T1CON";

            // bank 5
        case 0x28C:
            return "T2TMR";
        case 0x28D:
            return "T2PR";
        case 0x28E:
            return "T2CON";

            // bank 6
        case 0x30C:
            return "CCPR1L";
        case 0x30D:
            return "CCPR1H";
        case 0x30E:
            return "CCP1CON";
        case 0x30F:
            return "CCP1CAP";
        case 0x310:
            return "CCPR2L";
        case 0x311:
            return "CCPR2H";
        case 0x312:
            return "CCP2CON";
        case 0x313:
            return "CCP2CAP";
        case 0x314:
            return "CCPR3L";
        case 0x315:
            return "CCPR3H";
        case 0x316:
            return "CCP3CON";
        case 0x317:
            return "CCP3CAP";
        case 0x318:
            return "CCPR4L";
        case 0x319:
            return "CCPR4H";
        case 0x31A:
            return "CCP4CON";
        case 0x31B:
            return "CCP4CAP";
        case 0x31C:
            return "CCPR5L";
        case 0x31D:
            return "CCPR5H";
        case 0x31E:
            return "CCP5CON";
        case 0x31F:
            return "CCP5CAP";

            // bank 7
            // bank 8
            // bank 9
            // bank 10
            // bank 11
            // bank 12
            // bank 13
            // bank 14
        case 0x70C:
            return "PIR0";
        case 0x70D:
            return "PIR1";
        case 0x70E:
            return "PIR2";
        case 0x70F:
            return "PIR3";
        case 0x710:
            return "PIR4";
        case 0x711:
            return "PIR5";
        case 0x712:
            return "PIR6";
        case 0x713:
            return "PIR7";
        case 0x714:
            return "PIR8";
            //
        case 0x716:
            return "PIE0";
        case 0x717:
            return "PIE1";
        case 0x718:
            return "PIE2";
        case 0x719:
            return "PIE3";
        case 0x71A:
            return "PIE4";
        case 0x71B:
            return "PIE5";
        case 0x71C:
            return "PIE6";
        case 0x71D:
            return "PIE7";
        case 0x71E:
            return "PIE8";

            // bank 15
            // bank 16
        case 0x80C:
            return "WDTCON0";
        case 0x80D:
            return "WDTCON1";
        case 0x80E:
            return "WDTPSL";
        case 0x80F:
            return "WDTPSH";
        case 0x810:
            return "WDTTMR";
        case 0x811:
            return "BORCON";

            // bank 17
            // bank 18
            // bank 19
            // bank 20  Unimplemented
            // bank 21  Unimplemented
            // bank 22  Unimplemented
            // bank 23  Unimplemented
            // bank 24  Unimplemented
            // bank 25  Unimplemented
            // bank 26  Unimplemented
            // bank 27  Unimplemented
            // bank 28
            // bank 29
            // bank 30
            // bank 31
        case 0xFE4:
            return "STATUS_SHAD";
        case 0xFE5:
            return "WREG_SHAD";
        case 0xFE6:
            return "BSR_SHAD";
        case 0xFE7:
            return "PCLATH_SHAD";
        case 0xFE8:
            return "FSR0L_SHAD";
        case 0xFE9:
            return "FSR0H_SHAD";
        case 0xFEA:
            return "FSR1L_SHAD";
        case 0xFEB:
            return "FSR1H_SHAD";
            //
        case 0xFED:
            return "STKPTR";
        case 0xFEE:
            return "TOSL";
        case 0xFEF:
            return "TOSH";

        default:
            sprintf(FSRname, "0x%03X", addr);
            return FSRname;
    }
}

const char* getFSRname_18(unsigned int addr) {
    switch (addr) {
        case 0xFFF:
            return "TOSU";
        case 0xFFE:
            return "TOSH";
        case 0xFFD:
            return "TOSL";
        case 0xFFC:
            return "STKPTR";
        case 0xFFB:
            return "PCLATU";
        case 0xFFA:
            return "PCLATH";
        case 0xFF9:
            return "PCL";
        case 0xFF8:
            return "TBLPTRU";
        case 0xFF7:
            return "TBLPTRH";
        case 0xFF6:
            return "TBLPTRL";
        case 0xFF5:
            return "TABLAT";
        case 0xFF4:
            return "PRODH";
        case 0xFF3:
            return "PRODL";
        case 0xFF2:
            return "INTCON";
        case 0xFF1:
            return "INTCON2";
        case 0xFF0:
            return "INTCON3";
        case 0xFEF:
            return "INDF0";
        case 0xFEE:
            return "POSTINC0";
        case 0xFED:
            return "POSTDEC0";
        case 0xFEC:
            return "PREINC0";
        case 0xFEB:
            return "PLUSW0";
        case 0xFEA:
            return "FSR0H";
        case 0xFE9:
            return "FSR0L";
        case 0xFE8:
            return "WREG";
        case 0xFE7:
            return "INDF1";
        case 0xFE6:
            return "POSTINC1";
        case 0xFE5:
            return "POSTDEC1";
        case 0xFE4:
            return "PREINC1";
        case 0xFE3:
            return "PLUSW1";
        case 0xFE2:
            return "FSR1H";
        case 0xFE1:
            return "FSR1L";
        case 0xFE0:
            return "BSR";
        case 0xFDF:
            return "INDF2";
        case 0xFDE:
            return "POSTINC2";
        case 0xFDD:
            return "POSTDEC2";
        case 0xFDC:
            return "PREINC2";
        case 0xFDB:
            return "PLUSW2";
        case 0xFDA:
            return "FSR2H";
        case 0xFD9:
            return "FSR2L";
        case 0xFD8:
            return "STATUS";
        case 0xFD7:
            return "TMR0H";
        case 0xFD6:
            return "TMR0L";
        case 0xFD5:
            return "T0CON";
        case 0xFD4:
            return "DEBUG";
        case 0xFD3:
            return "OSCCON";
        case 0xFD2:
            return "LVDCON";
        case 0xFD1:
            return "WDTCON";
        case 0xFD0:
            return "RCON";
        case 0xFCF:
            return "TMR1H";
        case 0xFCE:
            return "TMR1L";
        case 0xFCD:
            return "T1CON";
        case 0xFCC:
            return "TMR2";
        case 0xFCB:
            return "PR2";
        case 0xFCA:
            return "T2CON";
        case 0xFC9:
            return "SSPBUF";
        case 0xFC8:
            return "SSPADD";
        case 0xFC7:
            return "SSPSTAT";
        case 0xFC6:
            return "SSPCON1";
        case 0xFC5:
            return "SSPCON2";
        case 0xFC4:
            return "ADRESH";
        case 0xFC3:
            return "ADRESL";
        case 0xFC2:
            return "ADCON0";
        case 0xFC1:
            return "ADCON1";
        case 0xFC0:
            return "ADCON2";
        case 0xFBF:
            return "CCPR1H";
        case 0xFBE:
            return "CCPR1L";
        case 0xFBD:
            return "CCP1CON";
        case 0xFBC:
            return "CCPR2H";
        case 0xFBB:
            return "CCPR2L";
        case 0xFBA:
            return "CCP2CON";

        case 0xFB9:
            return "BDMSR2";
            //   case 0xFB8: return "BDMSR1";
            //   case 0xFB7: return "BDMSR0";

        case 0xFB8:
            return "BAUDCON";
        case 0xFB7:
            return "PWM1CON";
        case 0xFB6:
            return "ECCP1AS";
        case 0xFB5:
            return "CVRCON";
        case 0xFB4:
            return "CMCON";
        case 0xFB3:
            return "TMR3H";
        case 0xFB2:
            return "TMR3L";
        case 0xFB1:
            return "T3CON";
        case 0xFB0:
            return "SPBRGH";
        case 0xFAF:
            return "SPBRG";
        case 0xFAE:
            return "RCREG";
        case 0xFAD:
            return "TXREG";
        case 0xFAC:
            return "TXSTA";
        case 0xFAB:
            return "RCSTA";
        case 0XFAA:
            return "EEADRH";
        case 0XFA9:
            return "EEADR";
        case 0XFA8:
            return "EEDATA";
        case 0XFA7:
            return "EECON2";
        case 0XFA6:
            return "EECON1";

        case 0xFA2:
            return "IPR2";
        case 0xFA1:
            return "PIR2";
        case 0xFA0:
            return "PIE2";
        case 0xF9F:
            return "IPR1";
        case 0xF9E:
            return "PIR1";
        case 0xF9D:
            return "PIE1";

        case 0xF9B:
            return "OSCTUNE";

        case 0xF96:
            return "TRISE";
        case 0xF95:
            return "TRISD";
        case 0xF94:
            return "TRISC";
        case 0xF93:
            return "TRISB";
        case 0xF92:
            return "TRISA";

        case 0xF8D:
            return "LATE";
        case 0xF8C:
            return "LATD";
        case 0xF8B:
            return "LATC";
        case 0xF8A:
            return "LATB";
        case 0xF89:
            return "LATA";

        case 0xF84:
            return "PORTE";
        case 0xF83:
            return "PORTD";
        case 0xF82:
            return "PORTC";
        case 0xF81:
            return "PORTB";
        case 0xF80:
            return "PORTA";

            // PIC18F4550
        case 0xF7F:
            return "UEP15";
        case 0xF7E:
            return "UEP14";
        case 0xF7D:
            return "UEP13";
        case 0xF7C:
            return "UEP12";
        case 0xF7B:
            return "UEP11";
        case 0xF7A:
            return "UEP10";
        case 0xF79:
            return "UEP9";
        case 0xF78:
            return "UEP8";
        case 0xF77:
            return "UEP7";
        case 0xF76:
            return "UEP6";
        case 0xF75:
            return "UEP5";
        case 0xF74:
            return "UEP4";
        case 0xF73:
            return "UEP3";
        case 0xF72:
            return "UEP2";
        case 0xF71:
            return "UEP1";
        case 0xF70:
            return "UEP0";
        case 0xF6F:
            return "UCFG";
        case 0xF6E:
            return "UADDR";
        case 0xF6D:
            return "UCON";
        case 0xF6C:
            return "USTAT";
        case 0xF6B:
            return "UEIE";
        case 0xF6A:
            return "UIER";
        case 0xF69:
            return "UIE";
        case 0xF68:
            return "UIR";
        case 0xF67:
            return "UFRMH";
        case 0xF66:
            return "UFRML";
        case 0xF65:
            return "SPPCON";
        case 0xF64:
            return "SPPEPS";
        case 0xF63:
            return "SPPCFG";
        case 0xF62:
            return "SPPDATA";

            // shadow
        case 0xF00:
            return "WS";
        case 0xF01:
            return "STATUSS";
        case 0xF02:
            return "BSRS";
        default:
            sprintf(FSRname, "0x%03X", addr);
            return FSRname;
    }
}

const char* getPinName(_pic* pic, int pin, char* pname) {
    pin = pin - 1;
    switch (pic->family) {
        case P16:
            if (pic->pins[pin].port == P_VDD) {
                sprintf(pname, "+5V");
            } else if (pic->pins[pin].port == P_VSS) {
                sprintf(pname, "GND");
            } else if (pic->pins[pin].port == P_RST) {
                sprintf(pname, "RST");
            } else if (pic->pins[pin].port == P_OSC) {
                sprintf(pname, "OSC");
            } else if (pic->pins[pin].port == P_USB) {
                sprintf(pname, "USB");
            } else if (pic->pins[pin].port == pic->P16map.PORTA) {
                sprintf(pname, "RA%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16map.PORTB) {
                sprintf(pname, "RB%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16map.PORTC) {
                sprintf(pname, "RC%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16map.PORTD) {
                sprintf(pname, "RD%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16map.PORTE) {
                sprintf(pname, "RE%i", pic->pins[pin].pord);
            } else {
                strcpy(pname, "error");
            }
            break;
        case P16E:
            if (pic->pins[pin].port == P_VDD) {
                sprintf(pname, "+5V");
            } else if (pic->pins[pin].port == P_VSS) {
                sprintf(pname, "GND");
            } else if (pic->pins[pin].port == P_RST) {
                sprintf(pname, "RST");
            } else if (pic->pins[pin].port == P_OSC) {
                sprintf(pname, "OSC");
            } else if (pic->pins[pin].port == P_USB) {
                sprintf(pname, "USB");
            } else if (pic->pins[pin].port == pic->P16Emap.PORTA) {
                sprintf(pname, "RA%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16Emap.PORTB) {
                sprintf(pname, "RB%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16Emap.PORTC) {
                sprintf(pname, "RC%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16Emap.PORTD) {
                sprintf(pname, "RD%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16Emap.PORTE) {
                sprintf(pname, "RE%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16Emap.PORTF) {
                sprintf(pname, "RF%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P16Emap.PORTG) {
                sprintf(pname, "RG%i", pic->pins[pin].pord);
            } else {
                strcpy(pname, "error");
            }
            break;
        case P18:
            if (pic->pins[pin].port == P_VDD) {
                sprintf(pname, "+5V");
            } else if (pic->pins[pin].port == P_VSS) {
                sprintf(pname, "GND");
            } else if (pic->pins[pin].port == P_RST) {
                sprintf(pname, "RST");
            } else if (pic->pins[pin].port == P_OSC) {
                sprintf(pname, "OSC");
            } else if (pic->pins[pin].port == P_USB) {
                sprintf(pname, "USB");
            } else if (pic->pins[pin].port == pic->P18map.PORTA) {
                sprintf(pname, "RA%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P18map.PORTB) {
                sprintf(pname, "RB%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P18map.PORTC) {
                sprintf(pname, "RC%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P18map.PORTD) {
                sprintf(pname, "RD%i", pic->pins[pin].pord);
            } else if (pic->pins[pin].port == pic->P18map.PORTE) {
                sprintf(pname, "RE%i", pic->pins[pin].pord);
            } else {
                strcpy(pname, "error");
            }

            break;
        default:
            strcpy(pname, "error");
            break;
    }

    return pname;
}
