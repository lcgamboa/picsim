/* //########################################################################

   PICsim - PIC simulator

   //########################################################################

   Copyright (c) : 2008-2020  Luis Claudio Gambôa Lopes

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

/*
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
*/
    
typedef struct
{    
//not mapped    
#ifdef ICSPDBG  
unsigned char * DEBUG;
unsigned char * BDMSR2;
unsigned char * BDMSR1;
unsigned char * BDMSR0;
#endif

unsigned char * WS;
unsigned char * STATUSS;
unsigned char * BSRS;
    
//maped 
unsigned char * STATUS;
unsigned char * PLUSW2;
unsigned char * PREINC2;
unsigned char * POSTDEC2;
unsigned char * POSTINC2;
unsigned char * INDF2;
unsigned char * BSR;
unsigned char * PLUSW1;
unsigned char * PREINC1;
unsigned char * POSTDEC1;
unsigned char * POSTINC1;
unsigned char * INDF1;
unsigned char * WREG;
unsigned char * PLUSW0;
unsigned char * PREINC0;
unsigned char * POSTDEC0;
unsigned char * POSTINC0;
unsigned char * INDF0;
unsigned char * INTCON3;
unsigned char * INTCON2;
unsigned char * INTCON;
unsigned char * TABLAT;
unsigned char * STKPTR; 
unsigned char * FSR2L;
unsigned char * FSR2H;
unsigned char * FSR1L;
unsigned char * FSR1H;
unsigned char * FSR0L;
unsigned char * FSR0H;
unsigned char * PRODL;
unsigned char * PRODH;
unsigned char * TBLPTRL;
unsigned char * TBLPTRH;
unsigned char * TBLPTRU;
unsigned char * PCL;
unsigned char * PCLATH;
unsigned char * PCLATU;
unsigned char * TOSL;
unsigned char * TOSH;
unsigned char * TOSU;
unsigned char * RCON;

unsigned char * PIE1;
unsigned char * PIR1;
unsigned char * IPR1;
unsigned char * PIE2;
unsigned char * PIR2;
unsigned char * IPR2;
unsigned char * PIE3;
unsigned char * PIR3;
unsigned char * IPR3;

unsigned char * PORTA;
unsigned char * PORTB;
unsigned char * PORTC;
unsigned char * PORTD;
unsigned char * PORTE;
unsigned char * LATA;
unsigned char * LATB;
unsigned char * LATC;
unsigned char * LATD;
unsigned char * LATE;
unsigned char * TRISA;
unsigned char * TRISB;
unsigned char * TRISC;
unsigned char * TRISD;
unsigned char * TRISE;
unsigned char * ANSELA;
unsigned char * ANSELB;
unsigned char * ANSELC;
unsigned char * ANSELD;
unsigned char * ANSELE;

unsigned char * ADCON2;
unsigned char * ADCON1;
unsigned char * ADCON0;
unsigned char * ADRESL;
unsigned char * ADRESH;

unsigned char * T0CON;
unsigned char * TMR0L;
unsigned char * TMR0H;

unsigned char * T1CON;
unsigned char * TMR1L;
unsigned char * TMR1H;

unsigned char * T3CON;
unsigned char * TMR3L;
unsigned char * TMR3H;

unsigned char * CCP2CON;
unsigned char * CCP1CON;
unsigned char * CCPR2L;
unsigned char * CCPR2H;
unsigned char * CCPR1L;
unsigned char * CCPR1H;

unsigned char * SSPCON2;
unsigned char * SSPCON1;
unsigned char * SSPSTAT;
unsigned char * SSPADD;
unsigned char * SSPBUF;

unsigned char * EECON1;
unsigned char * EECON2;
unsigned char * EEDATA;
unsigned char * EEADR;
unsigned char * EEADRH;

unsigned char * RCSTA;
unsigned char * TXSTA;
unsigned char * TXREG;
unsigned char * RCREG;
unsigned char * SPBRG;
unsigned char * SPBRGH;

unsigned char * T2CON;
unsigned char * PR2;
unsigned char * TMR2;

unsigned char * WDTCON;

/*
unsigned char * TXREG1;
unsigned char * RCREG1;
unsigned char * SPBRG1;
unsigned char * SPBRGH1;
unsigned char * RCSTA1;
unsigned char * TXSTA1;
 
unsigned char * UFRML;
unsigned char * UFRMH;
 * 
unsigned char * SPPCON;
unsigned char * SPPDATA;
unsigned char * SPPCFG;
unsigned char * SPPEPS;
unsigned char * SRCON1;
unsigned char * SRCON0;
unsigned char * CCPTMRS;
unsigned char * VREGCON;
unsigned char * UIR;
unsigned char * UIE;
unsigned char * UEIR;
unsigned char * UEIE;
unsigned char * USTAT;
unsigned char * UCON;
unsigned char * UADDR;
unsigned char * UCFG;
unsigned char * UEP0;
unsigned char * UEP1;
unsigned char * UEP2;
unsigned char * UEP3;
unsigned char * UEP4;
unsigned char * UEP5;
unsigned char * UEP6;
unsigned char * UEP7;
unsigned char * UEP8;
unsigned char * UEP9;
unsigned char * UEP10;
unsigned char * UEP11;
unsigned char * UEP12;
unsigned char * UEP13;
unsigned char * UEP14;
unsigned char * UEP15;
unsigned char * SLRCON;
unsigned char * VREFCON2;
unsigned char * VREFCON1;
unsigned char * VREFCON0;
unsigned char * PMD0;
unsigned char * PMD1;
unsigned char * WPUB;
unsigned char * IOCB;
unsigned char * IOCC;
unsigned char * CTMUICON;
unsigned char * CTMUCONL;
unsigned char * CTMUCONH;
unsigned char * CM1CON0;
unsigned char * CM2CON0;
unsigned char * CM2CON1;
unsigned char * OSCTUNE;
unsigned char * T3GCON;
unsigned char * ACTCON;
unsigned char * CMCON;
unsigned char * CVRCON;
unsigned char * ECCP1AS;
unsigned char * ECCP1DEL;
unsigned char * BAUDCON;
unsigned char * PWM1CON;
unsigned char * BAUDCON1;
unsigned char * PSTR1CON;
unsigned char * SSP1CON2;
unsigned char * SSP1CON1;
unsigned char * SSP1STAT;
unsigned char * SSP1ADD;
unsigned char * SSP1BUF;
unsigned char * SSP1MSK;
unsigned char * SSP1CON3;
unsigned char * T1GCON;
unsigned char * LVDCON; 
unsigned char * HLVDCON;
unsigned char * OSCCON2;
unsigned char * OSCCON;
 */ 
}P18map_t;

#ifdef __cplusplus
}
#endif 

