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
#define P16E_INDF0	0x000
#define P16E_INDF1	0x001
#define P16E_PCL	0x002
#define P16E_STATUS 	0x003
#define P16E_FSR0L	0x004
#define P16E_FSR0H	0x005
#define P16E_FSR1L	0x006
#define P16E_FSR1H	0x007
#define P16E_BSR	0x008
#define P16E_WREG	0x009
#define P16E_PCLATH	0x00A
#define P16E_INTCON     0x00B
    
#define P16E_PORTA	0x00C
#define P16E_PORTB	0x00D
#define P16E_PORTC	0x00E
#define P16E_PORTD	0x00F
#define P16E_PIR1	0x010
#define P16E_PIR2	0x011
#define P16E_PIR3	0x012
#define P16E_PIR4       0x013
#define P16E_PIR5       0x014
#define P16E_TMR0	0x015
#define P16E_TMR1L 	0x016
#define P16E_TMR1H	0x017
#define P16E_T1CON	0x018
#define P16E_T1GCON	0x019
#define P16E_TMR2	0x01A
#define P16E_PR2	0x01B
#define P16E_T2CON 	0x01C
#define P16E_T2HLT	0x01D
#define P16E_T2CLKCON   0x01E
#define P16E_T2RST      0x01F

 //bank 1   
#define P16E_TRISA	0x08C
#define P16E_TRISB	0x08D
#define P16E_TRISC	0x08E
#define P16E_TRISD	0x08F
#define P16E_PIE1       0x090   
#define P16E_PIE2       0x091
#define P16E_PIE3	0x092
#define P16E_PIE4       0x093
#define P16E_PIE5       0x094
#define P16E_OPTION_REG 0x095
#define P16E_PCON       0x096
//    
#define P16E_OSCTUNE	0x098
#define	P16E_OSCCON	0x099
#define P16E_OSCSTAT    0x09A
#define P16E_ADRESL     0x09B
#define P16E_ADRESH     0x09C
#define P16E_ADCON0     0x09D
#define P16E_ADCON1     0x09E
#define P16E_ADCON2     0x09F
    
//bank 2
#define P16E_LATA       0x10C    
#define P16E_LATB       0x10D  
#define P16E_LATC       0x10E  
#define P16E_LATD       0x10F  
    
//bank 3
#define P16E_ANSELA     0x18C    
#define P16E_ANSELB     0x18D  
#define P16E_ANSELC     0x18E  
  
#define P16E_RC1REG     0x199
#define P16E_TX1REG     0x19A
#define P16E_SP1BGRL    0x19B
#define P16E_SP1BGRH    0x19C
#define P16E_RC1STA     0x19D
#define P16E_TX1STA     0x19E
#define P16E_BAUD1CON   0x19F    

    
//bank 4   
#define P16E_WPUA       0x20C    
#define P16E_WPUB       0x20D  
#define P16E_WPUC       0x20E      
//bank 5
#define P16E_ODCONA     0x28C    
#define P16E_ODCONB     0x28D 
#define P16E_ODCONC     0x28E 

#define P16E_CCP1RL     0x291
#define P16E_CCP1RH     0x292
#define P16E_CCP1CON    0x293
#define P16E_CCP1CAP    0x294

#define P16E_CCP2RL     0x298
#define P16E_CCP2RH     0x299
#define P16E_CCP2CON    0x29A
#define P16E_CCP2CAP    0x29B

#define P16E_CCPTMRS    0x29E    
//bank 6
//bank 7
//bank 8
//bank 9
//bank 10
//bank 11
//bank 12
//bank 13
//bank 14
#define P16E_WDTCON0    0x711
#define P16E_WDTCON1    0x712
#define P16E_WDTPSL     0x713
#define P16E_WDTPSH     0x714
#define P16E_WDTTMR     0x715    
//bank 15
//bank 16
//bank 17
//bank 18  Unimplemented
//bank 19  Unimplemented
//bank 20  Unimplemented
//bank 21  Unimplemented
//bank 22  Unimplemented
//bank 23  Unimplemented
//bank 24  Unimplemented
//bank 25  Unimplemented
//bank 26  Unimplemented
//bank 27
//bank 28
//bank 29
//bank 30
//bank 31
#define P16E_STATUS_SHAD    0xFE4  
#define P16E_WREG_SHAD      0xFE5
#define P16E_BSR_SHAD       0xFE6
#define P16E_PCLATH_SHAD    0xFE7
#define P16E_FSR0L_SHAD     0xFE8
#define P16E_FSR0H_SHAD     0xFE9    
#define P16E_FSR1L_SHAD     0xFEA
#define P16E_FSR1H_SHAD     0xFEB
//
#define P16E_STKPTR         0xFED
#define P16E_TOSL           0xFEE
#define P16E_TOSH           0xFEF    
    
    
/*  whwre is in the new core???    
#define ICKBUG	0x18E
#define BIGBUG  0x18F
*/




#ifdef __cplusplus
}
#endif 

