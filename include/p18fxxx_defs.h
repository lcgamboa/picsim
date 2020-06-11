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

    /**
     * @brief PICsim P18 memory map structure
     *
     * Internal structure used to map P18 memory.
     */
    typedef struct {            
        //shadow stack	
        unsigned char WS;
        unsigned char STATUSS;
        unsigned char BSRS;

        //not mapped    
#ifdef ICSPDBG  
        unsigned char * DEBUG;
        unsigned char * BDMSR2;
        unsigned char * BDMSR1;
        unsigned char * BDMSR0;
#endif
        
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

        unsigned char * PIE0;
        unsigned char * PIR0;
        unsigned char * IPR0;
        unsigned char * PIE1;
        unsigned char * PIR1;
        unsigned char * IPR1;
        unsigned char * PIE2;
        unsigned char * PIR2;
        unsigned char * IPR2;
        unsigned char * PIE3;
        unsigned char * PIR3;
        unsigned char * IPR3;
        unsigned char * PIE4;
        unsigned char * PIR4;
        unsigned char * IPR4;

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

        unsigned char * IOCBF;
        unsigned char * IOCBN;
        unsigned char * IOCBP;

        unsigned char * ADCON2;
        unsigned char * ADCON1;
        unsigned char * ADCON0;
        unsigned char * ADRESL;
        unsigned char * ADRESH;
        unsigned char * ADCON3;
        unsigned char * ADPCH;

        unsigned char * T0CON;
        unsigned char * TMR0L;
        unsigned char * TMR0H;
        unsigned char * T0CON0;
        unsigned char * T0CON1;

        unsigned char * T1CON;
        unsigned char * TMR1L;
        unsigned char * TMR1H;
        unsigned char * T1CLK;

        unsigned char * T3CON;
        unsigned char * TMR3L;
        unsigned char * TMR3H;

        unsigned char * CCP2CON;
        unsigned char * CCP1CON;
        unsigned char * CCPR2L;
        unsigned char * CCPR2H;
        unsigned char * CCPR1L;
        unsigned char * CCPR1H;

        unsigned char * SSPCON1;
        unsigned char * SSPCON2;
        unsigned char * SSPSTAT;
        unsigned char * SSPADD;
        unsigned char * SSPBUF;

        unsigned char * SSP1CON1;
        unsigned char * SSP1CON2;
        unsigned char * SSP1STAT;
        unsigned char * SSP1ADD;
        unsigned char * SSP1BUF;

        unsigned char * EECON1;
        unsigned char * EECON2;
        unsigned char * EEDATA;
        unsigned char * EEADR;
        unsigned char * EEADRH;

        unsigned char * NVMCON1;
        unsigned char * NVMCON2;
        unsigned char * NVMDAT;
        unsigned char * NVMADRL;
        unsigned char * NVMADRH;


        unsigned char * RCSTA;
        unsigned char * TXSTA;
        unsigned char * TXREG;
        unsigned char * RCREG;
        unsigned char * SPBRG;
        unsigned char * SPBRGH;

        unsigned char * T2CON;
        unsigned char * PR2;
        unsigned char * TMR2;

        unsigned char * T2TMR;
        unsigned char * T2PR;

        unsigned char * WDTCON;

        unsigned char * WDTCON0;

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
    } P18map_t;

#ifdef __cplusplus
}
#endif 

