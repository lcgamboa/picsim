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

#define INDF	0x00
#define TMR0	0x01
#define PCL	0x02
#define STATUS 	0x03
#define FSR	0x04
#define PORTA	0x05
#define PORTB	0x06
#define PORTC	0x07
#define PORTD	0x08
#define PORTE	0x09
#define PCLATH	0x0A
#define INTCON  0x0B
#define PIR1	0x0C
#define PIR2	0x0D
#define TMR1L	0x0E
#define TMR1H	0x0F
#define T1CON	0x10
#define TMR2	0x11
#define T2CON	0x12
#define SSPBUF  0x13
#define SSPCON  0x14
#define CCPR1L	0x15
#define CCPR1H 	0x16
#define CCP1CON	0x17
#define RCSTA	0x18
#define TXREG	0x19
#define RCREG	0x1A
#define CCPR2L	0x1B
#define CCPR2H 	0x1C
#define CCP2CON	0x1D
#define ADRESH  0x1E
#define ADCON0  0x1F
#define CMCON   0x1F


#define OPTION  0x81
#define TRISA	0x85
#define TRISB	0x86
#define TRISC	0x87
#define TRISD	0x88
#define TRISE	0x89
#define PIE1	0x8C
#define PIE2	0x8D
#define SSPCON2 0x91
#define PR2	0x92
#define SSPADD  0x93
#define SSPSTAT 0x94
#define CCPR3L  0x95
#define CCPR3H  0x96
#define CCP3CON 0x97
#define TXSTA	0x98
#define	SPBRG	0x99
#define ADCON2  0x9B
#define ADRESL  0x9E
#define ADCON1  0x9F

#define ICKBUG	0x18E
#define BIGBUG  0x18F

#define P628_EEDATA  0x9A
#define P628_EEADR   0x9B
#define P628_EECON1  0x9C
#define P628_EECON2  0x9D

#define P877_EEDATA  0x10C
#define P877_EEADR   0x10D
#define P877_EEDATAH 0x10E
#define P877_EEADRH  0x10F
#define P877_EECON1  0x18C
#define P877_EECON2  0x18D



#ifdef __cplusplus
}
#endif 

