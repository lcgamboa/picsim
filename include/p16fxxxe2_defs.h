/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2015-2016  Luis Claudio Gambôa Lopes

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

#ifdef __cplusplus
extern "C" {
#endif

//bank 0    
//core    
#define P16E2_INDF0	0x000
#define P16E2_INDF1	0x001
#define P16E2_PCL	0x002
#define P16E2_STATUS 	0x003
#define P16E2_FSR0L	0x004
#define P16E2_FSR0H	0x005
#define P16E2_FSR1L	0x006
#define P16E2_FSR1H	0x007
#define P16E2_BSR	0x008
#define P16E2_WREG	0x009
#define P16E2_PCLATH	0x00A
#define P16E2_INTCON    0x00B
    
#define P16E2_PORTA	0x00C
#define P16E2_PORTB	0x00D
#define P16E2_PORTC	0x00E
#define P16E2_PORTD	0x00F
#define P16E2_PORTE	0x010
#define P16E2_TRISA	0x011
#define P16E2_TRISB	0x012
#define P16E2_TRISC     0x013
#define P16E2_TRISD     0x014
#define P16E2_TRISE	0x015
#define P16E2_LATA 	0x016
#define P16E2_LATB	0x017
#define P16E2_LATC	0x018
#define P16E2_LATD	0x019
#define P16E2_LATE	0x01A
//
#define P16E2_TMR0L 	0x01C
#define P16E2_TMR0H	0x01D
#define P16E2_T0CON0    0x01E
#define P16E2_T0CON1    0x01F

//bank 1   
#define P16E2_ADRESL    0x08C
#define P16E2_ADRESH    0x08D
#define P16E2_ADPREVL   0x08E
#define P16E2_ADPRVH    0x08F
#define P16E2_ADACCL    0x090
#define P16E2_ADACCH    0x091
//
#define P16E2_ADCON0    0x093    
#define P16E2_ADCON1    0x094
#define P16E2_ADCON2    0x095
#define P16E2_ADCON3    0x096
#define P16E2_ADSTAT    0x097    
#define P16E2_ADCLK     0x098
#define P16E2_ADACT     0x099
#define P16E2_ADREF     0x09A
#define P16E2_ADCAP     0x09B
#define P16E2_ADPRE     0x09C
#define P16E2_ASACQ     0x09D
#define P16E2_ADPCH     0x09E
    
//bank 2
    
//bank 3

//bank 4   
#define P16E2_TMR1L     0x20C
#define P16E2_TMR1H     0x20D
#define P16E2_T1CON     0x20E
    
//bank 5
#define P16E2_T2TMR     0x28C
#define P16E2_T2PR      0x28D
#define P16E2_T2CON     0x28E
    
//bank 6
#define P16E2_CCPR1L    0x30C
#define P16E2_CCPR1H    0x30D
#define P16E2_CCP1CON   0x30E
#define P16E2_CCP1CAP   0x30F
#define P16E2_CCPR2L    0x310
#define P16E2_CCPR2H    0x311
#define P16E2_CCP2CON   0x312
#define P16E2_CCP2CAP   0x313
#define P16E2_CCPR3L    0x314
#define P16E2_CCPR3H    0x315
#define P16E2_CCP3CON   0x316
#define P16E2_CCP3CAP   0x317
#define P16E2_CCPR4L    0x318
#define P16E2_CCPR4H    0x319
#define P16E2_CCP4CON   0x31A
#define P16E2_CCP4CAP   0x31B
#define P16E2_CCPR5L    0x31C
#define P16E2_CCPR5H    0x31D
#define P16E2_CCP5CON   0x31E
#define P16E2_CCP5CAP   0x31F

//bank 7
//bank 8
//bank 9
//bank 10
//bank 11
//bank 12
//bank 13
//bank 14 
#define P16E2_PIR0 0x70C
#define P16E2_PIR1 0x70D       
#define P16E2_PIR2 0x70E
#define P16E2_PIR3 0x70F
#define P16E2_PIR4 0x710
#define P16E2_PIR5 0x711
#define P16E2_PIR6 0x712
#define P16E2_PIR7 0x713
#define P16E2_PIR8 0x714
//
#define P16E2_PIE0 0x716
#define P16E2_PIE1 0x717
#define P16E2_PIE2 0x718
#define P16E2_PIE3 0x719
#define P16E2_PIE4 0x71A
#define P16E2_PIE5 0x71B
#define P16E2_PIE6 0x71C
#define P16E2_PIE7 0x71D
#define P16E2_PIE8 0x71E
    
//bank 15
//bank 16
#define P16E2_WDTCON0 0x80C
#define P16E2_WDTCON1 0x80D  
#define P16E2_WDTPSL  0x80E
#define P16E2_WDTPSH  0x80F
#define P16E2_WDTTMR  0x810
#define P16E2_BORCON  0x811   
    
//bank 17
//bank 18 
//bank 19  
//bank 20  Unimplemented
//bank 21  Unimplemented
//bank 22  Unimplemented
//bank 23  Unimplemented
//bank 24  Unimplemented
//bank 25  Unimplemented
//bank 26  Unimplemented
//bank 27  Unimplemented
//bank 28
//bank 29
//bank 30
//bank 31
#define P16E2_STATUS_SHAD    0xFE4  
#define P16E2_WREG_SHAD      0xFE5
#define P16E2_BSR_SHAD       0xFE6
#define P16E2_PCLATH_SHAD    0xFE7
#define P16E2_FSR0L_SHAD     0xFE8
#define P16E2_FSR0H_SHAD     0xFE9    
#define P16E2_FSR1L_SHAD     0xFEA
#define P16E2_FSR1H_SHAD     0xFEB
//
#define P16E2_STKPTR         0xFED
#define P16E2_TOSL           0xFEE
#define P16E2_TOSH           0xFEF    
    
    
/*  whwre is in the new core???    
#define ICKBUG	0x18E
#define BIGBUG  0x18F
*/




#ifdef __cplusplus
}
#endif 

