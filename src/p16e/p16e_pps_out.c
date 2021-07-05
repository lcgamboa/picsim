/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2020  Luis Claudio Gamboa Lopes

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

#include"../../include/picsim.h"
#include"../../include/periferic16e.h"

//TODO implement PPS Lock

//for PIC18F18855 
#define ADGRDG    0x25
#define ADGRDA    0x24
#define CWG3D     0x23
#define CWG3C     0x22
#define CWG3B     0x21
#define CWG3A     0x20
#define CWG2D     0x1F
#define CWG2C     0x1E
#define CWG2B     0x1D
#define CWG2A     0x1C
#define DSM       0x1B
#define CLKR      0x1A
#define NCO       0x19
#define TMR0      0x18
#define SDO2_SDA2 0x17
#define SCK2_SCL2 0x16
#define SD01_SDA1 0x15
#define SCK1_SCL1 0x14
#define C2OUT     0x13
#define C1OUT     0x12
#define DT        0x11
#define TX_CK     0x10
#define PWM7OUT   0x0F
#define PWM6OUT   0x0E
#define CCP5      0x0D
#define CCP4      0x0C
#define CCP3      0x0B
#define CCP2      0x0A
#define CCP1      0x09
#define CWG1D     0x08
#define CWG1C     0x07
#define CWG1B     0x06
#define CWG1A     0x05
#define CLC4OUT   0x04
#define CLC3OUT   0x03
#define CLC2OUT   0x02
#define CLC1OUT   0x01
#define LATxy     0x00  

//PIC18F18324
/*
1111 = Rxy source is DSM
11110 = Rxy source is CLKR
11101 = Rxy source is NCO1
11100 = Rxy source is TMR0
11011 = Reserved
11010 = Reserved
 */
#define _SDO_SDA1  0x19 
#define _SCK1_SCL1 0x18 
/*   
10111 = Rxy source is C2
10110 = Rxy source is C1
10101 = Rxy source is DT (1)
 */
#define _TX_CK   0x14  
/*
10011 = Rxy source is CWG2D (1)
10010 = Rxy source is CWG2C (1)
10001 = Rxy source is CWG2B (1)
10000 = Rxy source is CWG2A (1)
 */
#define _CCP4 0x0F  
#define _CCP3 0x0E 
#define _CCP2 0x0D  
#define _CCP1 0x0C 
/* 
01011 = Rxy source is CWG1D (1)
01010 = Rxy source is CWG1C (1)
01001 = Rxy source is CWG1B (1)
01000 = Rxy source is CWG1A (1)
00111 = Rxy source is CLC4OUT
00110 = Rxy source is CLC3OUT
00101 = Rxy source is CLC2OUT
00100 = Rxy source is CLC1OUT
00011 = Rxy source is PWM6
00010 = Rxy source is PWM5
00001 = Reserved
00000 = Reserved
 */
#define _LATxy     0x00  

static void
set_pps(unsigned char val, unsigned char * port, unsigned char pin)
{
 int pinn = -1;

 for (int i = 0; i < pic->PINCOUNT; i++)
  {
   if ((pic->pins[i].port == port)&&((pic->pins[i].pord == pin)))
    {
     pinn = i + 1;
    }
  }

 if (pinn == -1)return;

 if (pic->processor == P16F18855) //TODO make better selection 
  {
   switch (val)
    {
     //case ADGRDB: break;
     //case ADGRDA: break;
     //case DSM: break;
     //case CLKR: break;
     //case TMR0: break;
     //case MSSP2_SDO_SDA: break;
     //case MSSP2_SCK_SCL: break;
    case SD01_SDA1:
     pic->sdo = pinn;
     break;
    case SCK1_SCL1:
     pic->sck = pinn;
     break;
     //case CMP2: break;
     //case CMP1: break;
     //case EUSART2_DT: break;
     //case EUSART2_TX_CK: break;
     //case EUSART1_DT: break;
    case TX_CK:
     pic->usart_tx[0] = pinn;
     break;
     //case PWM4: break;
     //case PWM3: break;
    case CCP1:
     pic->ccp[0].pin = pinn;
     break;
    case CCP2:
     pic->ccp[1].pin = pinn;
     break;
    case CCP3:
     pic->ccp[2].pin = pinn;
     break;
    case CCP4:
     pic->ccp[3].pin = pinn;
     break;
    case CCP5:
     pic->ccp[4].pin = pinn;
     break;
     //case CWG1D: break;
     //case CWG1C: break;
     //case CWG1B: break;
     //case CWG1A: break;
    case LATxy:
     if (pic->sdo == pinn) pic->sdo = 0;
     if (pic->sck == pinn) pic->sck = 0;
     if (pic->usart_tx[0] == pinn) pic->usart_tx[0] = 0;
     if (pic->ccp[1].pin == pinn) pic->ccp[1].pin = 0;
     if (pic->ccp[0].pin == pinn) pic->ccp[0].pin = 0;
     if (pic->ccp[2].pin == pinn) pic->ccp[2].pin = 0;
     if (pic->ccp[3].pin == pinn) pic->ccp[3].pin = 0;
     if (pic->ccp[4].pin == pinn) pic->ccp[4].pin = 0;
     break;
    }
  }
 else //PIC16F18324
  {
   switch (val)
    {
     //case ADGRDB: break;
     //case ADGRDA: break;
     //case DSM: break;
     //case CLKR: break;
     //case TMR0: break;
     //case MSSP2_SDO_SDA: break;
     //case MSSP2_SCK_SCL: break;
    case _SDO_SDA1:
     pic->sdo = pinn;
     break;
    case _SCK1_SCL1:
     pic->sck = pinn;
     break;
     //case CMP2: break;
     //case CMP1: break;
     //case EUSART2_DT: break;
     //case EUSART2_TX_CK: break;
     //case EUSART1_DT: break;
    case _TX_CK:
     pic->usart_tx[0] = pinn;
     break;
     //case PWM4: break;
     //case PWM3: break;
    case _CCP1:
     pic->ccp[0].pin = pinn;
     break;
    case _CCP2:
     pic->ccp[1].pin = pinn;
     break;
    case _CCP3:
     pic->ccp[2].pin = pinn;
     break;
    case _CCP4:
     pic->ccp[3].pin = pinn;
     break;
     //case CWG1D: break;
     //case CWG1C: break;
     //case CWG1B: break;
     //case CWG1A: break;
    case _LATxy:
     if (pic->sdo == pinn) pic->sdo = 0;
     if (pic->sck == pinn) pic->sck = 0;
     if (pic->usart_tx[0] == pinn) pic->usart_tx[0] = 0;
     if (pic->ccp[3].pin == pinn) pic->ccp[3].pin = 0;
     if (pic->ccp[2].pin == pinn) pic->ccp[2].pin = 0;
     if (pic->ccp[1].pin == pinn) pic->ccp[1].pin = 0;
     if (pic->ccp[0].pin == pinn) pic->ccp[0].pin = 0;
     break;
    }
  }
}

void
p16e_pps_out_rst(void) { }

void
p16e_pps_out(void)
{

 //PORTA
 if ((pic->P16Emap.RA0PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA0PPS)))
  {
   set_pps ((*pic->P16Emap.RA0PPS), pic->P16Emap.PORTA, 0);
   return;
  }

 if ((pic->P16Emap.RA1PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA1PPS)))
  {
   set_pps ((*pic->P16Emap.RA1PPS), pic->P16Emap.PORTA, 1);
   return;
  }
 if ((pic->P16Emap.RA2PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA2PPS)))
  {
   set_pps ((*pic->P16Emap.RA2PPS), pic->P16Emap.PORTA, 2);
   return;
  }
 if ((pic->P16Emap.RA3PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA3PPS)))
  {
   set_pps ((*pic->P16Emap.RA3PPS), pic->P16Emap.PORTA, 3);
   return;
  }
 if ((pic->P16Emap.RA4PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA4PPS)))
  {
   set_pps ((*pic->P16Emap.RA4PPS), pic->P16Emap.PORTA, 4);
   return;
  }
 if ((pic->P16Emap.RA5PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA5PPS)))
  {
   set_pps ((*pic->P16Emap.RA5PPS), pic->P16Emap.PORTA, 5);
   return;
  }
 if ((pic->P16Emap.RA6PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA6PPS)))
  {
   set_pps ((*pic->P16Emap.RA6PPS), pic->P16Emap.PORTA, 6);
   return;
  }

 if ((pic->P16Emap.RA7PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RA7PPS)))
  {
   set_pps ((*pic->P16Emap.RA7PPS), pic->P16Emap.PORTA, 7);
   return;
  }

 //PORTB
 if ((pic->P16Emap.RB0PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB0PPS)))
  {
   set_pps ((*pic->P16Emap.RB0PPS), pic->P16Emap.PORTB, 0);
   return;
  }

 if ((pic->P16Emap.RB1PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB1PPS)))
  {
   set_pps ((*pic->P16Emap.RB1PPS), pic->P16Emap.PORTB, 1);
   return;
  }
 if ((pic->P16Emap.RB2PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB2PPS)))
  {
   set_pps ((*pic->P16Emap.RB2PPS), pic->P16Emap.PORTB, 2);
   return;
  }
 if ((pic->P16Emap.RB3PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB3PPS)))
  {
   set_pps ((*pic->P16Emap.RB3PPS), pic->P16Emap.PORTB, 3);
   return;
  }
 if ((pic->P16Emap.RB4PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB4PPS)))
  {
   set_pps ((*pic->P16Emap.RB4PPS), pic->P16Emap.PORTB, 4);
   return;
  }
 if ((pic->P16Emap.RB5PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB5PPS)))
  {
   set_pps ((*pic->P16Emap.RB5PPS), pic->P16Emap.PORTB, 5);
   return;
  }
 if ((pic->P16Emap.RB6PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB6PPS)))
  {
   set_pps ((*pic->P16Emap.RB6PPS), pic->P16Emap.PORTB, 6);
   return;
  }

 if ((pic->P16Emap.RB7PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RB7PPS)))
  {
   set_pps ((*pic->P16Emap.RB7PPS), pic->P16Emap.PORTB, 7);
   return;
  }

 //PORTC
 if ((pic->P16Emap.RC0PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC0PPS)))
  {
   set_pps ((*pic->P16Emap.RC0PPS), pic->P16Emap.PORTC, 0);
   return;
  }

 if ((pic->P16Emap.RC1PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC1PPS)))
  {
   set_pps ((*pic->P16Emap.RC1PPS), pic->P16Emap.PORTC, 1);
   return;
  }
 if ((pic->P16Emap.RC2PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC2PPS)))
  {
   set_pps ((*pic->P16Emap.RC2PPS), pic->P16Emap.PORTC, 2);
   return;
  }
 if ((pic->P16Emap.RC3PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC3PPS)))
  {
   set_pps ((*pic->P16Emap.RC3PPS), pic->P16Emap.PORTC, 3);
   return;
  }
 if ((pic->P16Emap.RC4PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC4PPS)))
  {
   set_pps ((*pic->P16Emap.RC4PPS), pic->P16Emap.PORTC, 4);
   return;
  }
 if ((pic->P16Emap.RC5PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC5PPS)))
  {
   set_pps ((*pic->P16Emap.RC5PPS), pic->P16Emap.PORTC, 5);
   return;
  }
 if ((pic->P16Emap.RC6PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC6PPS)))
  {
   set_pps ((*pic->P16Emap.RC6PPS), pic->P16Emap.PORTC, 6);
   return;
  }

 if ((pic->P16Emap.RC7PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RC7PPS)))
  {
   set_pps ((*pic->P16Emap.RC7PPS), pic->P16Emap.PORTC, 7);
   return;
  }


 //PORTD
 if ((pic->P16Emap.RD0PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD0PPS)))
  {
   set_pps ((*pic->P16Emap.RD0PPS), pic->P16Emap.PORTD, 0);
   return;
  }

 if ((pic->P16Emap.RD1PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD1PPS)))
  {
   set_pps ((*pic->P16Emap.RD1PPS), pic->P16Emap.PORTD, 1);
   return;
  }
 if ((pic->P16Emap.RD2PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD2PPS)))
  {
   set_pps ((*pic->P16Emap.RD2PPS), pic->P16Emap.PORTD, 2);
   return;
  }
 if ((pic->P16Emap.RD3PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD3PPS)))
  {
   set_pps ((*pic->P16Emap.RD3PPS), pic->P16Emap.PORTD, 3);
   return;
  }
 if ((pic->P16Emap.RD4PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD4PPS)))
  {
   set_pps ((*pic->P16Emap.RD4PPS), pic->P16Emap.PORTD, 4);
   return;
  }
 if ((pic->P16Emap.RD5PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD5PPS)))
  {
   set_pps ((*pic->P16Emap.RD5PPS), pic->P16Emap.PORTD, 5);
   return;
  }
 if ((pic->P16Emap.RD6PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD6PPS)))
  {
   set_pps ((*pic->P16Emap.RD6PPS), pic->P16Emap.PORTD, 6);
   return;
  }

 if ((pic->P16Emap.RD7PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RD7PPS)))
  {
   set_pps ((*pic->P16Emap.RD7PPS), pic->P16Emap.PORTD, 7);
   return;
  }


 //PORTE
 if ((pic->P16Emap.RE0PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RE0PPS)))
  {
   set_pps ((*pic->P16Emap.RE0PPS), pic->P16Emap.PORTE, 0);
   return;
  }

 if ((pic->P16Emap.RE1PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RE1PPS)))
  {
   set_pps ((*pic->P16Emap.RE1PPS), pic->P16Emap.PORTE, 1);
   return;
  }
 if ((pic->P16Emap.RE2PPS)&&(pic->lram == sfr_addr (pic->P16Emap.RE2PPS)))
  {
   set_pps ((*pic->P16Emap.RE2PPS), pic->P16Emap.PORTE, 2);
   return;
  }

}



