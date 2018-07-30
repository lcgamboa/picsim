/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2015  Luis Claudio Gambôa Lopes

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

#define P16_INDF	0x00
#define P16_TMR0	0x01
#define P16_PCL	0x02
#define P16_STATUS 	0x03
#define P16_FSR	0x04
#define P16_PORTA	0x05
#define P16_PORTB	0x06
#define P16_PORTC	0x07
#define P16_PORTD	0x08
#define P16_PORTE	0x09
#define P16_PCLATH	0x0A
#define P16_INTCON  0x0B
#define P16_PIR1	0x0C
#define P16_PIR2	0x0D
#define P16_TMR1L	0x0E
#define P16_TMR1H	0x0F
#define P16_T1CON	0x10
#define P16_TMR2	0x11
#define P16_T2CON	0x12
#define P16_SSPBUF  0x13
#define P16_SSPCON  0x14
#define P16_CCPR1L	0x15
#define P16_CCPR1H 	0x16
#define P16_CCP1CON	0x17
#define P16_RCSTA	0x18
#define P16_TXREG	0x19
#define P16_RCREG	0x1A
#define P16_CCPR2L	0x1B
#define P16_CCPR2H 	0x1C
#define P16_CCP2CON	0x1D
#define P16_ADRESH  0x1E
#define P16_ADCON0  0x1F
#define P16_CMCON   0x1F


#define P16_OPTION  0x81
#define P16_TRISA	0x85
#define P16_TRISB	0x86
#define P16_TRISC	0x87
#define P16_TRISD	0x88
#define P16_TRISE	0x89
#define P16_PIE1	0x8C
#define P16_PIE2	0x8D
#define P16_SSPCON2 0x91
#define P16_PR2	0x92
#define P16_SSPADD  0x93
#define P16_SSPSTAT 0x94
#define P16_CCPR3L  0x95
#define P16_CCPR3H  0x96
#define P16_CCP3CON 0x97
#define P16_TXSTA	0x98
#define	P16_SPBRG	0x99
#define P16_ADCON2  0x9B
#define P16_ADRESL  0x9E
#define P16_ADCON1  0x9F

#define P16_ICKBUG	0x18E
#define P16_BIGBUG  0x18F

#define P16_P628_EEDATA  0x9A
#define P16_P628_EEADR   0x9B
#define P16_P628_EECON1  0x9C
#define P16_P628_EECON2  0x9D

#define P16_P877_EEDATA  0x10C
#define P16_P877_EEADR   0x10D
#define P16_P877_EEDATAH 0x10E
#define P16_P877_EEADRH  0x10F
#define P16_P877_EECON1  0x18C
#define P16_P877_EECON2  0x18D



#ifdef __cplusplus
}
#endif 

