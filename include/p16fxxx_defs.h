/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2022  Luis Claudio Gamb�a Lopes

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

/**
 * @brief PICsim P16 memory map structure
 *
 * Internal structure used to map P16 memory.
 */
typedef struct {
#ifdef ICSPDBG
  unsigned char *ICKBUG; // 0x18E
  unsigned char *BIGBUG; // 0x18F
#endif

  unsigned char *OPTION_REG;
  unsigned char *INDF;
  unsigned char *STATUS;
  unsigned char *FSR;
  unsigned char *PCL;
  unsigned char *PCLATH;

  unsigned char *INTCON;
  unsigned char *PIR1;
  unsigned char *PIR2;
  unsigned char *PIE1;
  unsigned char *PIE2;

  unsigned char *PORTA;
  unsigned char *PORTB;
  unsigned char *PORTC;
  unsigned char *PORTD;
  unsigned char *PORTE;
  unsigned char *TRISA;
  unsigned char *TRISB;
  unsigned char *TRISC;
  unsigned char *TRISD;
  unsigned char *TRISE;

  unsigned char *TXSTA;
  unsigned char *RCSTA;
  unsigned char *TXREG;
  unsigned char *RCREG;
  unsigned char *SPBRG;
  unsigned char *SPBRGH;

  unsigned char *TMR0;

  unsigned char *T1CON;
  unsigned char *TMR1L;
  unsigned char *TMR1H;

  unsigned char *CCP1CON;
  unsigned char *CCP2CON;
  unsigned char *CCP3CON;
  unsigned char *CCPR1L;
  unsigned char *CCPR1H;
  unsigned char *CCPR2L;
  unsigned char *CCPR2H;
  unsigned char *CCPR3L;
  unsigned char *CCPR3H;

  unsigned char *TMR2;
  unsigned char *T2CON;
  unsigned char *PR2;

  unsigned char *SSPCON;
  unsigned char *SSPCON2;
  unsigned char *SSPBUF;
  unsigned char *SSPSTAT;
  unsigned char *SSPADD;

  unsigned char *ADCON0;
  unsigned char *ADCON1;
  unsigned char *ADCON2;
  unsigned char *ADRESL;
  unsigned char *ADRESH;

  unsigned char *ANSEL;
  unsigned char *ANSELH;

  unsigned char *EECON1;
  unsigned char *EECON2;
  unsigned char *EEDATA;
  unsigned char *EEADR;
  unsigned char *EEDATH;
  unsigned char *EEADRH;

  unsigned char *BAUDCTL;
  /*
  unsigned char * PCON;
  unsigned char * OSCCON;
  unsigned char * OSCTUNE;
  unsigned char * CMCON;
  unsigned char * CVRCON;
  unsigned char * VRCON;
  unsigned char * WDTCON;
  unsigned char * LVDCON;
  unsigned char * PMDATA;
  unsigned char * PMADR;
  unsigned char * PMDATH;
  unsigned char * PMADRH;
  unsigned char * PMCON1;
   */
} P16map_t;

#ifdef __cplusplus
}
#endif
