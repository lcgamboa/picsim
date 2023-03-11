/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2015-2020  Luis Claudio Gamb�a Lopes

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
extern "C"
{
#endif

    /*  where is in the new core???
    #define ICKBUG	0x18E
    #define BIGBUG  0x18F
     */

    /**
     * @brief PICsim P16E memory map structure
     *
     * Internal structure used to map P16E memory.
     */
    typedef struct
    {
        // core
        unsigned char *INDF0;
        unsigned char *INDF1;
        unsigned char *PCL;
        unsigned char *STATUS;
        unsigned char *FSR0L;
        unsigned char *FSR0H;
        unsigned char *FSR1L;
        unsigned char *FSR1H;
        unsigned char *BSR;
        unsigned char *WREG;
        unsigned char *PCLATH;
        unsigned char *INTCON;

        // SHADOW
        unsigned char *STATUS_SHAD;
        unsigned char *WREG_SHAD;
        unsigned char *BSR_SHAD;
        unsigned char *PCLATH_SHAD;
        unsigned char *FSR0L_SHAD;
        unsigned char *FSR0H_SHAD;
        unsigned char *FSR1L_SHAD;
        unsigned char *FSR1H_SHAD;

        unsigned char *STKPTR;
        unsigned char *TOSL;
        unsigned char *TOSH;
        unsigned char *OPTION_REG;

        // INTERRUPTS
        unsigned char *PIR0;
        unsigned char *PIR1;
        unsigned char *PIR2;
        unsigned char *PIE0;
        unsigned char *PIE1;
        unsigned char *PIE2;

        // IO
        unsigned char *PORTA;
        unsigned char *PORTB;
        unsigned char *PORTC;
        unsigned char *PORTD;
        unsigned char *PORTE;
        unsigned char *PORTF;
        unsigned char *PORTG;
        unsigned char *TRISA;
        unsigned char *TRISB;
        unsigned char *TRISC;
        unsigned char *TRISD;
        unsigned char *TRISE;
        unsigned char *TRISF;
        unsigned char *TRISG;
        unsigned char *LATA;
        unsigned char *LATB;
        unsigned char *LATC;
        unsigned char *LATD;
        unsigned char *LATE;
        unsigned char *LATF;
        unsigned char *LATG;
        unsigned char *ANSELA;
        unsigned char *ANSELB;
        unsigned char *ANSELC;
        unsigned char *ANSELD;
        unsigned char *ANSELE;
        unsigned char *ANSELF;
        unsigned char *ANSELG;

        // USART
        unsigned char *RC1REG;
        unsigned char *TX1REG;
        unsigned char *RC1STA;
        unsigned char *TX1STA;
        unsigned char *SP1BRGL;
        unsigned char *SP1BRGH;
        unsigned char *BAUDCON1;

        unsigned char *TXSTA;
        unsigned char *RCSTA;
        unsigned char *TXREG;
        unsigned char *RCREG;

        // TMR0
        unsigned char *TMR0;
        unsigned char *T0CON0;
        unsigned char *T0CON1;
        unsigned char *TMR0L;
        unsigned char *TMR0H;

        // TMR1
        unsigned char *T1CON;
        unsigned char *TMR1L;
        unsigned char *TMR1H;

        // CCP
        unsigned char *CCP1CON;
        unsigned char *CCP2CON;
        unsigned char *CCPR1L;
        unsigned char *CCPR1H;
        unsigned char *CCPR2L;
        unsigned char *CCPR2H;

        // TMR2
        unsigned char *T2CON;
        unsigned char *TMR2;
        unsigned char *PR2;

        // ADC
        unsigned char *ADCON0;
        unsigned char *ADCON1;
        unsigned char *ADRESL;
        unsigned char *ADRESH;

        unsigned char *ADPCH;

        // WDT
        unsigned char *WDTCON0;
        unsigned char *WDTCON;

        // EEPROM
        unsigned char *EECON2;
        unsigned char *EECON1;
        unsigned char *EEADRL;
        unsigned char *EEADRH;
        unsigned char *EEDATL;
        unsigned char *EEDATH;

        unsigned char *NVMCON1;
        unsigned char *NVMCON2;
        unsigned char *NVMDATL;
        unsigned char *NVMDATH;
        unsigned char *NVMADRL;
        unsigned char *NVMADRH;

        // MSSP
        unsigned char *SSP1STAT;
        unsigned char *SSP1CON2;
        unsigned char *SSP1CON1;
        unsigned char *SSP1BUF;
        unsigned char *SSP1ADD;

        // INTERRUPT-ON-CHANGE PORTB
        unsigned char *IOCBP;
        unsigned char *IOCBN;
        unsigned char *IOCBF;

        // PPS OUT
        unsigned char *RA0PPS;
        unsigned char *RA1PPS;
        unsigned char *RA2PPS;
        unsigned char *RA3PPS;
        unsigned char *RA4PPS;
        unsigned char *RA5PPS;
        unsigned char *RA6PPS;
        unsigned char *RA7PPS;
        unsigned char *RB0PPS;
        unsigned char *RB1PPS;
        unsigned char *RB2PPS;
        unsigned char *RB3PPS;
        unsigned char *RB4PPS;
        unsigned char *RB5PPS;
        unsigned char *RB6PPS;
        unsigned char *RB7PPS;
        unsigned char *RC0PPS;
        unsigned char *RC1PPS;
        unsigned char *RC2PPS;
        unsigned char *RC3PPS;
        unsigned char *RC4PPS;
        unsigned char *RC5PPS;
        unsigned char *RC6PPS;
        unsigned char *RC7PPS;
        unsigned char *RD0PPS;
        unsigned char *RD1PPS;
        unsigned char *RD2PPS;
        unsigned char *RD3PPS;
        unsigned char *RD4PPS;
        unsigned char *RD5PPS;
        unsigned char *RD6PPS;
        unsigned char *RD7PPS;
        unsigned char *RE0PPS;
        unsigned char *RE1PPS;
        unsigned char *RE2PPS;

        /*
        unsigned char * SSPCON3;
        unsigned char * CCP1CAP;
        unsigned char * CCP2CAP;
        unsigned char * WDTCON;
        unsigned char * ADPREVL;
        unsigned char * ADPREVH;
        unsigned char * ADACCL;
        unsigned char * ADACCH;
        unsigned char * ADLTHL;
        unsigned char * ADLTHH;
        unsigned char * ADUTHL;
        unsigned char * ADUTHH;
        unsigned char * ADSTPTL;
        unsigned char * ADSTPTH;
        unsigned char * ADFLTRL;
        unsigned char * ADFLTRH;
        unsigned char * ADERRL;
        unsigned char * ADERRH;

        unsigned char * TMR3L;
        unsigned char * TMR3H;
        unsigned char * TMR5L;
        unsigned char * TMR5H;

        unsigned char * CCPR3L;
        unsigned char * CCPR3H;
        unsigned char * CCPR4L;
        unsigned char * CCPR4H;
        unsigned char * CCPR5L;
        unsigned char * CCPR5H;
        unsigned char * PWM6DCL;
        unsigned char * PWM6DCH;
        unsigned char * PWM7DCL;
        unsigned char * PWM7DCH;
        unsigned char * CRCDATL;
        unsigned char * CRCDATH;
        unsigned char * CRCACCL;
        unsigned char * CRCACCH;
        unsigned char * CRCSHIFTL;
        unsigned char * CRCSHIFTH;
        unsigned char * CRCXORL;
        unsigned char * CRCXORH;
        unsigned char * SMT1TMRL;
        unsigned char * SMT1TMRH;
        unsigned char * SMT1TMRU;
        unsigned char * SMT1CPRL;
        unsigned char * SMT1CPRH;
        unsigned char * SMT1CPRU;
        unsigned char * SMT1CPWL;
        unsigned char * SMT1CPWH;
        unsigned char * SMT1CPWU;
        unsigned char * SMT1PRL;
        unsigned char * SMT1PRH;
        unsigned char * SMT1PRU;
        unsigned char * SMT2TMRL;
        unsigned char * SMT2TMRH;
        unsigned char * SMT2TMRU;
        unsigned char * SMT2CPRL;
        unsigned char * SMT2CPRH;
        unsigned char * SMT2CPRU;
        unsigned char * SMT2CPWL;
        unsigned char * SMT2CPWH;
        unsigned char * SMT2CPWU;
        unsigned char * SMT2PRL;
        unsigned char * SMT2PRH;
        unsigned char * SMT2PRU;
        unsigned char * NCO1ACCL;
        unsigned char * NCO1ACCH;
        unsigned char * NCO1ACCU;
        unsigned char * NCO1INCL;
        unsigned char * NCO1INCH;
        unsigned char * NCO1INCU;


        unsigned char * ADCON2;
        unsigned char * ADCON3;
        unsigned char * ADSTAT;
        unsigned char * ADCLK;
        unsigned char * ADACT;
        unsigned char * ADREF;
        unsigned char * ADCAP;
        unsigned char * ADPRE;
        unsigned char * ADACQ;
        unsigned char * ADPCH;
        unsigned char * ADCNT;
        unsigned char * ADRPT;

        unsigned char * BAUD1CON;
        unsigned char * WPUA;
        unsigned char * WPUB;
        unsigned char * WPUC;


        unsigned char * SSPMSK;


        unsigned char * BAUDCON; //duplicated ?
        unsigned char * SSP1BUF;
        unsigned char * SSP1ADD;
        unsigned char * SSP1MSK;
        unsigned char * SSP1STAT;
        unsigned char * SSP1CON1;
        unsigned char * SSP1CON2;
        unsigned char * SSP1CON3;
        unsigned char * SSP2BUF;
        unsigned char * SSP2ADD;
        unsigned char * SSP2MSK;
        unsigned char * SSP2STAT;
        unsigned char * SSP2CON1;
        unsigned char * SSP2CON2;
        unsigned char * SSP2CON3;
        unsigned char * T1GCON;
        unsigned char * T1GATE;
        unsigned char * T1CLK;
        unsigned char * T3CON;
        unsigned char * T3GCON;
        unsigned char * T3GATE;
        unsigned char * T3CLK;
        unsigned char * T5CON;
        unsigned char * T5GCON;
        unsigned char * T5GATE;
        unsigned char * T5CLK;
        unsigned char * CCPTMRS0;
        unsigned char * CCPTMRS1;
        unsigned char * T2TMR;
        unsigned char * T2PR;

        unsigned char * T2HLT;
        unsigned char * T2CLKCON;
        unsigned char * T2RST;
        unsigned char * T4TMR;
        unsigned char * T4PR;
        unsigned char * T4CON;
        unsigned char * T4HLT;
        unsigned char * T4CLKCON;
        unsigned char * T4RST;
        unsigned char * T6TMR;
        unsigned char * T6PR;
        unsigned char * T6CON;
        unsigned char * T6HLT;
        unsigned char * T6CLKCON;
        unsigned char * T6RST;
        unsigned char * CCP3CON;
        unsigned char * CCP3CAP;
        unsigned char * CCP4CON;
        unsigned char * CCP4CAP;
        unsigned char * CCP5CON;
        unsigned char * CCP5CAP;
        unsigned char * PWM6CON;
        unsigned char * PWM7CON;
        unsigned char * SCANLADRL;
        unsigned char * SCANLADRH;
        unsigned char * SCANHADRL;
        unsigned char * SCANHADRH;
        unsigned char * SCANCON0;
        unsigned char * SCANTRIG;
        unsigned char * CRCCON0;
        unsigned char * CRCCON1;
        unsigned char * AT1CON0;
        unsigned char * AT1CON1;
        unsigned char * AT1IR0;
        unsigned char * AT1IE0;
        unsigned char * AT1IR1;
        unsigned char * AT1IE1;
        unsigned char * AT1CLK;
        unsigned char * AT1SIG;
        unsigned char * AT1CSEL1;
        unsigned char * AT1CCON1;
        unsigned char * AT1CSEL2;
        unsigned char * AT1CCON2;
        unsigned char * AT1CSEL3;
        unsigned char * AT1CCON3;
        unsigned char * SMT1CON0;
        unsigned char * SMT1CON1;
        unsigned char * SMT1STAT;
        unsigned char * SMT1CLK;
        unsigned char * SMT1SIG;
        unsigned char * SMT1WIN;
        unsigned char * SMT2CON0;
        unsigned char * SMT2CON1;
        unsigned char * SMT2STAT;
        unsigned char * SMT2CLK;
        unsigned char * SMT2SIG;
        unsigned char * SMT2WIN;
        unsigned char * NCO1CON;
        unsigned char * NCO1CLK;
        unsigned char * CWG1CLKCON;
        unsigned char * CWG1ISM;
        unsigned char * CWG1DBR;
        unsigned char * CWG1DBF;
        unsigned char * CWG1CON0;
        unsigned char * CWG1CON1;
        unsigned char * CWG1AS0;
        unsigned char * CWG1AS1;
        unsigned char * CWG1STR;
        unsigned char * CWG2CLKCON;
        unsigned char * CWG2ISM;
        unsigned char * CWG2DBR;
        unsigned char * CWG2DBF;
        unsigned char * CWG2CON0;
        unsigned char * CWG2CON1;
        unsigned char * CWG2AS0;
        unsigned char * CWG2AS1;
        unsigned char * CWG2STR;
        unsigned char * CWG3CLKCON;
        unsigned char * CWG3ISM;
        unsigned char * CWG3DBR;
        unsigned char * CWG3DBF;
        unsigned char * CWG3CON0;
        unsigned char * CWG3CON1;
        unsigned char * CWG3AS0;
        unsigned char * CWG3AS1;
        unsigned char * CWG3STR;



        unsigned char * PIR3;
        unsigned char * PIR4;
        unsigned char * PIR5;
        unsigned char * PIR6;
        unsigned char * PIR7;
        unsigned char * PIR8;


        unsigned char * PIE3;
        unsigned char * PIE4;
        unsigned char * PIE5;
        unsigned char * PIE6;
        unsigned char * PIE7;
        unsigned char * PIE8;
        unsigned char * PMD0;
        unsigned char * PMD1;
        unsigned char * PMD2;
        unsigned char * PMD3;
        unsigned char * PMD4;
        unsigned char * PMD5;

        unsigned char * WDTCON1;
        unsigned char * WDTPSL;
        unsigned char * WDTPSH;
        unsigned char * WDTTMR;
        unsigned char * BORCON;
        unsigned char * VREGCON;
        unsigned char * PCON0;
        unsigned char * CCDCON;
        unsigned char * NVMADRL;
        unsigned char * NVMADRH;
        unsigned char * NVMDATL;
        unsigned char * NVMDATH;
        unsigned char * NVMCON1;
        unsigned char * NVMCON2;
        unsigned char * CPUDOZE;
        unsigned char * OSCCON1;
        unsigned char * OSCCON2;
        unsigned char * OSCCON3;
        unsigned char * OSCSTAT;
        unsigned char * OSCEN;
        unsigned char * OSCTUNE;
        unsigned char * OSCFRQ;
        unsigned char * CLKRCON;
        unsigned char * CLKRCLK;
        unsigned char * MDCON0;
        unsigned char * MDCON1;
        unsigned char * MDSRC;
        unsigned char * MDCARL;
        unsigned char * MDCARH;
        unsigned char * FVRCON;
        unsigned char * DAC1CON0;
        unsigned char * DAC1CON1;
        unsigned char * ZCD1CON;
        unsigned char * CMOUT;
        unsigned char * CM1CON0;
        unsigned char * CM1CON1;
        unsigned char * CM1NSEL;
        unsigned char * CM1PSEL;
        unsigned char * CM2CON0;
        unsigned char * CM2CON1;
        unsigned char * CM2NSEL;
        unsigned char * CM2PSEL;
        unsigned char * CLCDATA;
        unsigned char * CLC1CON;
        unsigned char * CLC1POL;
        unsigned char * CLC1SEL0;
        unsigned char * CLC1SEL1;
        unsigned char * CLC1SEL2;
        unsigned char * CLC1SEL3;
        unsigned char * CLC1GLS0;
        unsigned char * CLC1GLS1;
        unsigned char * CLC1GLS2;
        unsigned char * CLC1GLS3;
        unsigned char * CLC2CON;
        unsigned char * CLC2POL;
        unsigned char * CLC2SEL0;
        unsigned char * CLC2SEL1;
        unsigned char * CLC2SEL2;
        unsigned char * CLC2SEL3;
        unsigned char * CLC2GLS0;
        unsigned char * CLC2GLS1;
        unsigned char * CLC2GLS2;
        unsigned char * CLC2GLS3;
        unsigned char * CLC3CON;
        unsigned char * CLC3POL;
        unsigned char * CLC3SEL0;
        unsigned char * CLC3SEL1;
        unsigned char * CLC3SEL2;
        unsigned char * CLC3SEL3;
        unsigned char * CLC3GLS0;
        unsigned char * CLC3GLS1;
        unsigned char * CLC3GLS2;
        unsigned char * CLC3GLS3;
        unsigned char * CLC4CON;
        unsigned char * CLC4POL;
        unsigned char * CLC4SEL0;
        unsigned char * CLC4SEL1;
        unsigned char * CLC4SEL2;
        unsigned char * CLC4SEL3;
        unsigned char * CLC4GLS0;
        unsigned char * CLC4GLS1;
        unsigned char * CLC4GLS2;
        unsigned char * CLC4GLS3;
        unsigned char * PPSLOCK;
        unsigned char * INTPPS;
        unsigned char * T0CKIPPS;
        unsigned char * T1CKIPPS;
        unsigned char * T1GPPS;
        unsigned char * T3CKIPPS;
        unsigned char * T3GPPS;
        unsigned char * T5CKIPPS;
        unsigned char * T5GPPS;
        unsigned char * T2AINPPS;
        unsigned char * T4AINPPS;
        unsigned char * T6AINPPS;
        unsigned char * CCP1PPS;
        unsigned char * CCP2PPS;
        unsigned char * CCP3PPS;
        unsigned char * CCP4PPS;
        unsigned char * CCP5PPS;
        unsigned char * SMT1WINPPS;
        unsigned char * SMT1SIGPPS;
        unsigned char * SMT2WINPPS;
        unsigned char * SMT2SIGPPS;
        unsigned char * CWG1PPS;
        unsigned char * CWG2PPS;
        unsigned char * CWG3PPS;
        unsigned char * MDCARLPPS;
        unsigned char * MDCARHPPS;
        unsigned char * MDSRCPPS;
        unsigned char * CLCIN0PPS;
        unsigned char * CLCIN1PPS;
        unsigned char * CLCIN2PPS;
        unsigned char * CLCIN3PPS;
        unsigned char * ADCACTPPS;
        unsigned char * SSP1CLKPPS;
        unsigned char * SSP1DATPPS;
        unsigned char * SSP1SSPPS;
        unsigned char * SSP2CLKPPS;
        unsigned char * SSP2DATPPS;
        unsigned char * SSP2SSPPS;
        unsigned char * RXPPS;
        unsigned char * TXPPS;
        unsigned char * RA0PPS;
        unsigned char * RA1PPS;
        unsigned char * RA2PPS;
        unsigned char * RA3PPS;
        unsigned char * RA4PPS;
        unsigned char * RA5PPS;
        unsigned char * RA6PPS;
        unsigned char * RA7PPS;
        unsigned char * RB0PPS;
        unsigned char * RB1PPS;
        unsigned char * RB2PPS;
        unsigned char * RB3PPS;
        unsigned char * RB4PPS;
        unsigned char * RB5PPS;
        unsigned char * RB6PPS;
        unsigned char * RB7PPS;
        unsigned char * RC0PPS;
        unsigned char * RC1PPS;
        unsigned char * RC2PPS;
        unsigned char * RC3PPS;
        unsigned char * RC4PPS;
        unsigned char * RC5PPS;
        unsigned char * RC6PPS;
        unsigned char * RC7PPS;

        unsigned char * ODCONA;
        unsigned char * SLRCONA;
        unsigned char * INLVLA;
        unsigned char * IOCAP;
        unsigned char * IOCAN;
        unsigned char * IOCAF;
        unsigned char * CCDNA;
        unsigned char * CCDPA;

        unsigned char * ODCONB;
        unsigned char * SLRCONB;
        unsigned char * INLVLB;
        unsigned char * CCDNB;
        unsigned char * CCDPB;

        unsigned char * ODCONC;
        unsigned char * SLRCONC;
        unsigned char * INLVLC;
        unsigned char * IOCCP;
        unsigned char * IOCCN;
        unsigned char * IOCCF;
        unsigned char * CCDNC;
        unsigned char * CCDPC;
        unsigned char * WPUE;
        unsigned char * INLVLE;
        unsigned char * IOCEP;
        unsigned char * IOCEN;
        unsigned char * IOCEF;
        unsigned char * LCDCON;
        unsigned char * LCDPS;
        unsigned char * LCDREF;
        unsigned char * LCDCST;
        unsigned char * LCDRL;
        unsigned char * LCDSE0;
        unsigned char * LCDSE1;
        unsigned char * LCDSE2;
        unsigned char * LCDDATA0;
        unsigned char * LCDDATA1;
        unsigned char * LCDDATA2;
        unsigned char * LCDDATA3;
        unsigned char * LCDDATA4;
        unsigned char * LCDDATA5;
        unsigned char * LCDDATA6;
        unsigned char * LCDDATA7;
        unsigned char * LCDDATA8;
        unsigned char * LCDDATA9;
        unsigned char * LCDDATA10;
        unsigned char * LCDDATA11;

        unsigned char * ATCC1PPS;
        unsigned char * ATCC2PPS;
        unsigned char * ATCC3PPS;
        unsigned char * SSPSSPPS;
        unsigned char * T2PPS;
        unsigned char * T4PPS;
        unsigned char * T6PPS;
        unsigned char * SSPCLKPP;
        unsigned char * CKPPS;
        unsigned char * CWGINPPS;
        unsigned char * SSPDATPPS;
        unsigned char * SSPCLKPPS;
        unsigned char * ATINPPS;
        unsigned char * CWG1OCON0;
        unsigned char * PWM3CON;
        unsigned char * PWM4CON;
        unsigned char * PID1CON;
        unsigned char * HIDRVC;
        unsigned char * CCPTMRS;
        unsigned char * PMCON2;
        unsigned char * PMCON1;
        unsigned char * OSCCON;
        unsigned char * PCON;

        unsigned char * TMR4;
        unsigned char * TMR6;
        unsigned char * PR4;
        unsigned char * PR6;
        unsigned char * PSTR3CON;
        unsigned char * CCP3AS;
        unsigned char * PSTR2CON;
        unsigned char * CCP2AS;
        unsigned char * PWM2CON;
        unsigned char * PSTR1CON;
        unsigned char * CCP1AS;
        unsigned char * PWM1CON;
        unsigned char * APFCON;
        unsigned char * SRCON1;
        unsigned char * SRCON0;
        unsigned char * DACCON1;
        unsigned char * DACCON0;

        unsigned char * CPSCON1;
        unsigned char * CPSCON0;


         */
    } P16Emap_t;

#ifdef __cplusplus
}
#endif
