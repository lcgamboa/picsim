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

#include<stdio.h>
#include"../../include/picsim.h"
#include"../../include/periferic16e.h"


int
interrupt16E(void)
{
 //interrupt
 //GIE
 if ((*pic->P16Emap.INTCON) & 0x80)
  {
   //T0IE  T0IF
   if (((*pic->P16Emap.INTCON)&0x20)&&((*pic->P16Emap.INTCON)&0x04)) return 1;
   //18855 if(((((*pic->P16Emap.PIE0]&0x20)&&((*pic->P16Emap.PIR0)&0x20)) return 1;  

   //INTE INTF
   if (((*pic->P16Emap.INTCON)&0x10)&&((*pic->P16Emap.INTCON)&0x02)) return 1;
   //RBIE
   if (((*pic->P16Emap.INTCON)&0x08)&&((*pic->P16Emap.INTCON)&0x01)) return 1;
   //PEIE	
   if ((*pic->P16Emap.INTCON) & 0x40)
    {
     //EEIE
     //if(((*pic->P16Emap.PIE1) & 0x80)&&((*pic->P16Emap.PIR1) & 0x80)) return 1;
     //CMIE CMIF
     //if(((*pic->P16Emap.PIE1) & 0x40)&&((*pic->P16Emap.PIR1) & 0x40)) return 1;
     //ADIE ADIF 
     if (((*pic->P16Emap.PIE1) & 0x40)&&((*pic->P16Emap.PIR1) & 0x40)) return 1;
     //RCIE RCIF
     if (((*pic->P16Emap.PIE1) & 0x20)&&((*pic->P16Emap.PIR1) & 0x20)) return 1;
     //TXIE TXIF
     if (((*pic->P16Emap.PIE1) & 0x10)&&((*pic->P16Emap.PIR1) & 0x10)) return 1;
     //SSPIE
     if (((*pic->P16Emap.PIE1) & 0x08)&&((*pic->P16Emap.PIR1) & 0x08)) return 1;
     //CCP1IE CCP1IF
     if (((*pic->P16Emap.PIE1) & 0x04)&&((*pic->P16Emap.PIR1) & 0x04)) return 1;
     //TMR2IE TMR2IF
     if (((*pic->P16Emap.PIE1) & 0x02)&&((*pic->P16Emap.PIR1) & 0x02)) return 1;
     //TMR1IE TMR1IF
     if (((*pic->P16Emap.PIE1) & 0x01)&&((*pic->P16Emap.PIR1) & 0x01)) return 1;

     //CCP2IE CCP2IF
     if (((*pic->P16Emap.PIE2) & 0x01)&&((*pic->P16Emap.PIR2) & 0x01)) return 1;
     //CCP3IE CCP3IF
     if (((*pic->P16Emap.PIE2) & 0x02)&&((*pic->P16Emap.PIR2) & 0x02)) return 1;
    }

  }

 return 0;
}

int
interrupt16E_2(void)
{
//interrupt
  //GIE
  if((*pic->P16Emap.INTCON) & 0x80)
  {
    //T0IE  T0IF
    if(((*pic->P16Emap.PIE0)&0x20)&&((*pic->P16Emap.PIR0)&0x20)) return 1;  
    //INTE INTF
    //if(((*pic->P16Emap.INTCON)&0x10)&&((*pic->P16Emap.INTCON)&0x02)) return 1;
    //RBIE
    //if(((*pic->P16Emap.INTCON)&0x08)&&((*pic->P16Emap.INTCON)&0x01)) return 1;
    //PEIE	
    if((*pic->P16Emap.INTCON) & 0x40)
    {
      //EEIE
      //if(((*pic->P16Emap.PIE1) & 0x80)&&((*pic->P16Emap.PIR1) & 0x80)) return 1;
      //CMIE CMIF
      //if(((*pic->P16Emap.PIE1) & 0x40)&&((*pic->P16Emap.PIR1) & 0x40)) return 1;
      //ADIE ADIF 
      //if(((*pic->P16Emap.PIE1) & 0x40)&&((*pic->P16Emap.PIR1) & 0x40)) return 1;
      //RCIE RCIF
      //if(((*pic->P16Emap.PIE1) & 0x20)&&((*pic->P16Emap.PIR1) & 0x20)) return 1;
      //TXIE TXIF
      //if(((*pic->P16Emap.PIE1) & 0x10)&&((*pic->P16Emap.PIR1) & 0x10)) return 1;
      //SSPIE
      //if(((*pic->P16Emap.PIE1) & 0x08)&&((*pic->P16Emap.PIR1) & 0x08)) return 1;
      //CCP1IE CCP1IF
      //if(((*pic->P16Emap.PIE1) & 0x04)&&((*pic->P16Emap.PIR1) & 0x04)) return 1;
      //TMR2IE TMR2IF
      //if(((*pic->P16Emap.PIE1) & 0x02)&&((*pic->P16Emap.PIR1) & 0x02)) return 1;
      //TMR1IE TMR1IF
      //if(((*pic->P16Emap.PIE1) & 0x01)&&((*pic->P16Emap.PIR1) & 0x01)) return 1;

      //CCP2IE CCP2IF
      //if(((*pic->P16Emap.PIE2) & 0x01)&&((*pic->P16Emap.PIR2) & 0x01)) return 1;
      //CCP3IE CCP3IF
      //if(((*pic->P16Emap.PIE2) & 0x02)&&((*pic->P16Emap.PIR2) & 0x02)) return 1;
    }
  
  }

 return 0;
}