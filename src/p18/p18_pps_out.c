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
#include"../../include/periferic18.h"

//TODO implement PPS Lock

//for PIC18F47K40
#define ADGRDB          0x17 
#define ADGRDA          0x16
#define DSM             0x15 
#define CLKR            0x14
#define TMR0            0x13
#define MSSP2_SDO_SDA   0x12 
#define MSSP2_SCK_SCL   0x11
#define MSSP1_SDO_SDA   0x10 
#define MSSP1_SCK_SCL   0x0F  
#define CMP2            0x0E  
#define CMP1            0x0D  
#define EUSART2_DT      0x0C 
#define EUSART2_TX_CK   0x0B 
#define EUSART1_DT      0x0A
#define EUSART1_TX_CK   0x09 
#define PWM4            0x08
#define PWM3            0x07 
#define CCP2            0x06
#define CCP1            0x05
#define CWG1D           0x04  
#define CWG1C           0x03
#define CWG1B           0x02
#define CWG1A           0x01
#define LATxy           0x00  

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

 switch (val)
  {
   //case ADGRDB: break;
   //case ADGRDA: break;
   //case DSM: break;
   //case CLKR: break;
   //case TMR0: break;
   //case MSSP2_SDO_SDA: break;
   //case MSSP2_SCK_SCL: break;
  case MSSP1_SDO_SDA:
   pic->sdo = pinn;
   break;
  case MSSP1_SCK_SCL:
   pic->sck = pinn;
   break;
   //case CMP2: break;
   //case CMP1: break;
   //case EUSART2_DT: break;
  case EUSART2_TX_CK: break;
   pic->usart_tx[1] = pinn; 
   break;
   //case EUSART1_DT: break;
  case EUSART1_TX_CK:
   pic->usart_tx[0] = pinn;
   break;
   //case PWM4: break;
   //case PWM3: break;
  case CCP2:
   pic->ccp[1] = pinn;
   break;
  case CCP1:
   pic->ccp[0] = pinn;
   break;
   //case CWG1D: break;
   //case CWG1C: break;
   //case CWG1B: break;
   //case CWG1A: break;
  case LATxy:
   if (pic->sdo == pinn) pic->sdo = 0;
   if (pic->sck == pinn) pic->sck = 0;
   if (pic->usart_tx[0] == pinn) pic->usart_tx[0] = 0;
   if ((pic->USARTCOUNT > 1)&&(pic->usart_tx[1] == pinn)) pic->usart_tx[1] = 0;
   if (pic->ccp[1] == pinn) pic->ccp[1] = 0;
   if (pic->ccp[0] == pinn) pic->ccp[0] = 0;
   break;
  }
}

void
p18_pps_out_rst(void) { }

void
p18_pps_out(void)
{

 //PORTA
 if ((pic->P18map.RA0PPS)&&(pic->lram == sfr_addr (pic->P18map.RA0PPS)))
  {
   set_pps ((*pic->P18map.RA0PPS), pic->P18map.PORTA, 0);
   return;
  }

 if ((pic->P18map.RA1PPS)&&(pic->lram == sfr_addr (pic->P18map.RA1PPS)))
  {
   set_pps ((*pic->P18map.RA1PPS), pic->P18map.PORTA, 1);
   return;
  }
 if ((pic->P18map.RA2PPS)&&(pic->lram == sfr_addr (pic->P18map.RA2PPS)))
  {
   set_pps ((*pic->P18map.RA2PPS), pic->P18map.PORTA, 2);
   return;
  }
 if ((pic->P18map.RA3PPS)&&(pic->lram == sfr_addr (pic->P18map.RA3PPS)))
  {
   set_pps ((*pic->P18map.RA3PPS), pic->P18map.PORTA, 3);
   return;
  }
 if ((pic->P18map.RA4PPS)&&(pic->lram == sfr_addr (pic->P18map.RA4PPS)))
  {
   set_pps ((*pic->P18map.RA4PPS), pic->P18map.PORTA, 4);
   return;
  }
 if ((pic->P18map.RA5PPS)&&(pic->lram == sfr_addr (pic->P18map.RA5PPS)))
  {
   set_pps ((*pic->P18map.RA5PPS), pic->P18map.PORTA, 5);
   return;
  }
 if ((pic->P18map.RA6PPS)&&(pic->lram == sfr_addr (pic->P18map.RA6PPS)))
  {
   set_pps ((*pic->P18map.RA6PPS), pic->P18map.PORTA, 6);
   return;
  }

 if ((pic->P18map.RA7PPS)&&(pic->lram == sfr_addr (pic->P18map.RA7PPS)))
  {
   set_pps ((*pic->P18map.RA7PPS), pic->P18map.PORTA, 7);
   return;
  }

 //PORTB
 if ((pic->P18map.RB0PPS)&&(pic->lram == sfr_addr (pic->P18map.RB0PPS)))
  {
   set_pps ((*pic->P18map.RB0PPS), pic->P18map.PORTB, 0);
   return;
  }

 if ((pic->P18map.RB1PPS)&&(pic->lram == sfr_addr (pic->P18map.RB1PPS)))
  {
   set_pps ((*pic->P18map.RB1PPS), pic->P18map.PORTB, 1);
   return;
  }
 if ((pic->P18map.RB2PPS)&&(pic->lram == sfr_addr (pic->P18map.RB2PPS)))
  {
   set_pps ((*pic->P18map.RB2PPS), pic->P18map.PORTB, 2);
   return;
  }
 if ((pic->P18map.RB3PPS)&&(pic->lram == sfr_addr (pic->P18map.RB3PPS)))
  {
   set_pps ((*pic->P18map.RB3PPS), pic->P18map.PORTB, 3);
   return;
  }
 if ((pic->P18map.RB4PPS)&&(pic->lram == sfr_addr (pic->P18map.RB4PPS)))
  {
   set_pps ((*pic->P18map.RB4PPS), pic->P18map.PORTB, 4);
   return;
  }
 if ((pic->P18map.RB5PPS)&&(pic->lram == sfr_addr (pic->P18map.RB5PPS)))
  {
   set_pps ((*pic->P18map.RB5PPS), pic->P18map.PORTB, 5);
   return;
  }
 if ((pic->P18map.RB6PPS)&&(pic->lram == sfr_addr (pic->P18map.RB6PPS)))
  {
   set_pps ((*pic->P18map.RB6PPS), pic->P18map.PORTB, 6);
   return;
  }

 if ((pic->P18map.RB7PPS)&&(pic->lram == sfr_addr (pic->P18map.RB7PPS)))
  {
   set_pps ((*pic->P18map.RB7PPS), pic->P18map.PORTB, 7);
   return;
  }

 //PORTC
 if ((pic->P18map.RC0PPS)&&(pic->lram == sfr_addr (pic->P18map.RC0PPS)))
  {
   set_pps ((*pic->P18map.RC0PPS), pic->P18map.PORTC, 0);
   return;
  }

 if ((pic->P18map.RC1PPS)&&(pic->lram == sfr_addr (pic->P18map.RC1PPS)))
  {
   set_pps ((*pic->P18map.RC1PPS), pic->P18map.PORTC, 1);
   return;
  }
 if ((pic->P18map.RC2PPS)&&(pic->lram == sfr_addr (pic->P18map.RC2PPS)))
  {
   set_pps ((*pic->P18map.RC2PPS), pic->P18map.PORTC, 2);
   return;
  }
 if ((pic->P18map.RC3PPS)&&(pic->lram == sfr_addr (pic->P18map.RC3PPS)))
  {
   set_pps ((*pic->P18map.RC3PPS), pic->P18map.PORTC, 3);
   return;
  }
 if ((pic->P18map.RC4PPS)&&(pic->lram == sfr_addr (pic->P18map.RC4PPS)))
  {
   set_pps ((*pic->P18map.RC4PPS), pic->P18map.PORTC, 4);
   return;
  }
 if ((pic->P18map.RC5PPS)&&(pic->lram == sfr_addr (pic->P18map.RC5PPS)))
  {
   set_pps ((*pic->P18map.RC5PPS), pic->P18map.PORTC, 5);
   return;
  }
 if ((pic->P18map.RC6PPS)&&(pic->lram == sfr_addr (pic->P18map.RC6PPS)))
  {
   set_pps ((*pic->P18map.RC6PPS), pic->P18map.PORTC, 6);
   return;
  }

 if ((pic->P18map.RC7PPS)&&(pic->lram == sfr_addr (pic->P18map.RC7PPS)))
  {
   set_pps ((*pic->P18map.RC7PPS), pic->P18map.PORTC, 7);
   return;
  }


 //PORTD
 if ((pic->P18map.RD0PPS)&&(pic->lram == sfr_addr (pic->P18map.RD0PPS)))
  {
   set_pps ((*pic->P18map.RD0PPS), pic->P18map.PORTD, 0);
   return;
  }

 if ((pic->P18map.RD1PPS)&&(pic->lram == sfr_addr (pic->P18map.RD1PPS)))
  {
   set_pps ((*pic->P18map.RD1PPS), pic->P18map.PORTD, 1);
   return;
  }
 if ((pic->P18map.RD2PPS)&&(pic->lram == sfr_addr (pic->P18map.RD2PPS)))
  {
   set_pps ((*pic->P18map.RD2PPS), pic->P18map.PORTD, 2);
   return;
  }
 if ((pic->P18map.RD3PPS)&&(pic->lram == sfr_addr (pic->P18map.RD3PPS)))
  {
   set_pps ((*pic->P18map.RD3PPS), pic->P18map.PORTD, 3);
   return;
  }
 if ((pic->P18map.RD4PPS)&&(pic->lram == sfr_addr (pic->P18map.RD4PPS)))
  {
   set_pps ((*pic->P18map.RD4PPS), pic->P18map.PORTD, 4);
   return;
  }
 if ((pic->P18map.RD5PPS)&&(pic->lram == sfr_addr (pic->P18map.RD5PPS)))
  {
   set_pps ((*pic->P18map.RD5PPS), pic->P18map.PORTD, 5);
   return;
  }
 if ((pic->P18map.RD6PPS)&&(pic->lram == sfr_addr (pic->P18map.RD6PPS)))
  {
   set_pps ((*pic->P18map.RD6PPS), pic->P18map.PORTD, 6);
   return;
  }

 if ((pic->P18map.RD7PPS)&&(pic->lram == sfr_addr (pic->P18map.RD7PPS)))
  {
   set_pps ((*pic->P18map.RD7PPS), pic->P18map.PORTD, 7);
   return;
  }


 //PORTE
 if ((pic->P18map.RE0PPS)&&(pic->lram == sfr_addr (pic->P18map.RE0PPS)))
  {
   set_pps ((*pic->P18map.RE0PPS), pic->P18map.PORTE, 0);
   return;
  }

 if ((pic->P18map.RE1PPS)&&(pic->lram == sfr_addr (pic->P18map.RE1PPS)))
  {
   set_pps ((*pic->P18map.RE1PPS), pic->P18map.PORTE, 1);
   return;
  }
 if ((pic->P18map.RE2PPS)&&(pic->lram == sfr_addr (pic->P18map.RE2PPS)))
  {
   set_pps ((*pic->P18map.RE2PPS), pic->P18map.PORTE, 2);
   return;
  }

}



