/* //########################################################################

   PICsim - PIC simulator

   //########################################################################

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
   //######################################################################## */

#ifdef __cplusplus
extern "C" {
#endif


#define P18_TOSU	0xFFF
#define P18_TOSH	0xFFE
#define P18_TOSL	0xFFD
#define P18_STKPTR	0xFFC
#define P18_PCLATU	0xFFB
#define P18_PCLATH	0xFFA
#define P18_PCL		0xFF9
#define P18_TBLPTRU 	0xFF8
#define P18_TBLPTRH 	0xFF7
#define P18_TBLPTRL 	0xFF6
#define P18_TABLAT 	0xFF5
#define P18_PRODH	0xFF4
#define P18_PRODL	0xFF3
#define P18_INTCON  	0xFF2
#define P18_INTCON2  	0xFF1
#define P18_INTCON3 	0xFF0
#define P18_INDF0	0xFEF
#define P18_POSTINC0	0xFEE
#define P18_POSTDEC0	0xFED
#define P18_PREINC0	0xFEC
#define P18_PLUSW0	0xFEB
#define P18_FSR0H	0xFEA
#define P18_FSR0L	0xFE9
#define P18_WREG	0xFE8
#define P18_INDF1	0xFE7
#define P18_POSTINC1	0xFE6
#define P18_POSTDEC1	0xFE5
#define P18_PREINC1	0xFE4
#define P18_PLUSW1	0xFE3
#define P18_FSR1H	0xFE2
#define P18_FSR1L	0xFE1
#define P18_BSR		0xFE0
#define P18_INDF2	0xFDF
#define P18_POSTINC2	0xFDE
#define P18_POSTDEC2	0xFDD
#define P18_PREINC2	0xFDC
#define P18_PLUSW2	0xFDB
#define P18_FSR2H	0xFDA
#define P18_FSR2L	0xFD9
#define P18_STATUS 	0xFD8
#define P18_TMR0H	0xFD7
#define P18_TMR0L	0xFD6
#define P18_T0CON	0xFD5
#define P18_DEBUG	0xFD4
#define P18_OSCCON	0xFD3 
#define P18_LVDCON	0xFD2 
#define P18_WDTCON	0xFD1
#define P18_RCON	0xFD0
#define P18_TMR1H	0xFCF
#define P18_TMR1L	0xFCE
#define P18_T1CON	0xFCD
#define P18_TMR2	0xFCC
#define P18_PR2		0xFCB
#define P18_T2CON	0xFCA
#define P18_SSPBUF	0xFC9
#define P18_SSPADD	0xFC8
#define P18_SSPSTAT	0xFC7
#define P18_SSPCON1	0xFC6
#define P18_SSPCON2	0xFC5
#define P18_ADRESH	0xFC4
#define P18_ADRESL 	0xFC3
#define P18_ADCON0	0xFC2
#define P18_ADCON1	0xFC1
#define P18_ADCON2	0xFC0
#define P18_CCPR1H	0xFBF
#define P18_CCPR1L	0xFBE
#define P18_CCP1CON	0xFBD
#define P18_CCPR2H	0xFBC
#define P18_CCPR2L	0xFBB
#define P18_CCP2CON	0xFBA

#define P18_BDMSR2	0xFB9 //DEBUG 452
#define P18_BDMSR1	0xFB8 //?
#define P18_BDMSR0	0xFB7 //?

#define P18_BAUDCON	0xFB8
#define P18_PWM1CON	0xFB7
#define P18_ECCP1AS	0xFB6
#define P18_CVRCON	0xFB5
#define P18_CMCON	0xFB4
#define P18_TMR3H	0xFB3
#define P18_TMR3L	0xFB2
#define P18_T3CON	0xFB1
#define P18_SPBRGH 	0xFB0
#define P18_SPBRG 	0xFAF
#define P18_RCREG 	0xFAE
#define P18_TXREG 	0xFAD
#define P18_TXSTA 	0xFAC
#define P18_RCSTA 	0xFAB
#define P18_EEADRH	0XFAA
#define P18_EEADR	0XFA9
#define P18_EEDATA	0XFA8
#define P18_EECON2	0XFA7
#define P18_EECON1	0XFA6

#define P18_IPR2	0xFA2
#define P18_PIR2	0xFA1
#define P18_PIE2	0xFA0
#define P18_IPR1	0xF9F
#define P18_PIR1	0xF9E
#define P18_PIE1	0xF9D

#define P18_OSCTUNE	0xF9B

#define P18_TRISE	0xF96
#define P18_TRISD	0xF95
#define P18_TRISC	0xF94
#define P18_TRISB	0xF93
#define P18_TRISA	0xF92

#define P18_LATE	0xF8D
#define P18_LATD	0xF8C
#define P18_LATC	0xF8B
#define P18_LATB	0xF8A
#define P18_LATA	0xF89

#define P18_PORTE	0xF84
#define P18_PORTD	0xF83
#define P18_PORTC	0xF82
#define P18_PORTB	0xF81
#define P18_PORTA	0xF80

//PIC18F4550
#define P18_UEP15	0xF7F
#define P18_UEP14	0xF7E
#define P18_UEP13	0xF7D
#define P18_UEP12	0xF7C
#define P18_UEP11	0xF7B
#define P18_UEP10	0xF7A
#define P18_UEP9	0xF79
#define P18_UEP8	0xF78
#define P18_UEP7	0xF77
#define P18_UEP6	0xF76
#define P18_UEP5	0xF75
#define P18_UEP4	0xF74
#define P18_UEP3	0xF73
#define P18_UEP2	0xF72
#define P18_UEP1	0xF71
#define P18_UEP0	0xF70
#define P18_UCFG	0xF6F
#define P18_UADDR	0xF6E
#define P18_UCON	0xF6D
#define P18_USTAT	0xF6C
#define P18_UEIE	0xF6B
#define P18_UIER 	0xF6A
#define P18_UIE 	0xF69
#define P18_UIR 	0xF68
#define P18_UFRMH	0xF67
#define P18_UFRML	0xF66
#define P18_SPPCON	0xF65
#define P18_SPPEPS	0xF64
#define P18_SPPCFG	0xF63
#define P18_SPPDATA	0xF62



//shadow
#define P18_WS		0xF00
#define P18_STATUSS	0xF01
#define P18_BSRS	0xF02

#ifdef __cplusplus
}
#endif 

