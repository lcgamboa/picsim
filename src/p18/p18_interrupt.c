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
#include"../../include/periferic18.h"


int
interrupt18(void)
{
//interrupt

 if ((pic->P18map.RCON)&&((*pic->P18map.RCON) & 0x80)) //priority 
  {
   //GIEH
   if ((*pic->P18map.INTCON) & 0x80)
    {
     //T0IE  T0IF
     if (((*pic->P18map.INTCON)&0x20)&&((*pic->P18map.INTCON)&0x04)&&((*pic->P18map.INTCON2) & 0x04)) return 1;
     //INTE INTF
     if (((*pic->P18map.INTCON)&0x10)&&((*pic->P18map.INTCON)&0x02)) return 1;
     //RBIE
     if (((*pic->P18map.INTCON)&0x08)&&((*pic->P18map.INTCON)&0x01)&&((*pic->P18map.INTCON2) & 0x01)) return 1;
     //EEIE
     //if(((*pic->P18map.PIE1) & 0x80)&&((*pic->P18map.PIR1) & 0x80)&&((*pic->P18map.IPR1) & 0x80)) return 1;
     //CMIE CMIF
     //if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&((*pic->P18map.IPR1) & 0x40)) return 1;
     //ADIE ADIF 
     if (((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&((*pic->P18map.IPR1) & 0x40)) return 1;
     //RCIE RCIF
     if (((*pic->P18map.PIE1) & 0x20)&&((*pic->P18map.PIR1) & 0x20)&&((*pic->P18map.IPR1) & 0x20)) return 1;
     //TXIE TXIF
     if (((*pic->P18map.PIE1) & 0x10)&&((*pic->P18map.PIR1) & 0x10)&&((*pic->P18map.IPR1) & 0x10)) return 1;
     //SSPIE
     if (((*pic->P18map.PIE1) & 0x08)&&((*pic->P18map.PIR1) & 0x08)&&((*pic->P18map.IPR1) & 0x08)) return 1;
     //CCP1IE CCP1IF
     if (((*pic->P18map.PIE1) & 0x04)&&((*pic->P18map.PIR1) & 0x04)&&((*pic->P18map.IPR1) & 0x04)) return 1;
     //TMR2IE TMR2IF
     if (((*pic->P18map.PIE1) & 0x02)&&((*pic->P18map.PIR1) & 0x02)&&((*pic->P18map.IPR1) & 0x02)) return 1;
     //TMR1IE TMR1IF
     if (((*pic->P18map.PIE1) & 0x01)&&((*pic->P18map.PIR1) & 0x01)&&((*pic->P18map.IPR1) & 0x01)) return 1;
     //TMR3IE TMR3IF
     if (((*pic->P18map.PIE2) & 0x02)&&((*pic->P18map.PIR2) & 0x02)&&((*pic->P18map.IPR2) & 0x02)) return 1;
     //CCP2IE CCP2IF
     if (((*pic->P18map.PIE2) & 0x01)&&((*pic->P18map.PIR2) & 0x01)&&((*pic->P18map.IPR2) & 0x01)) return 1;
     //INT1E INT1F
     if (((*pic->P18map.INTCON3) & 0x08)&&((*pic->P18map.INTCON3) & 0x01)&&((*pic->P18map.INTCON3) & 0x40)) return 1;
     //INT2E INT2F
     if (((*pic->P18map.INTCON3) & 0x10)&&((*pic->P18map.INTCON3) & 0x02)&&((*pic->P18map.INTCON3) & 0x80)) return 1;
     //GIEL
     if ((*pic->P18map.INTCON) & 0x40)
      {
       //T0IE  T0IF
       if (((*pic->P18map.INTCON)&0x20)&&((*pic->P18map.INTCON)&0x04)&&(!((*pic->P18map.INTCON2) & 0x04))) return 2;
       //RBIE
       if (((*pic->P18map.INTCON)&0x08)&&((*pic->P18map.INTCON)&0x01)&&(!((*pic->P18map.INTCON2) & 0x01))) return 2;
       //EEIE
       //if(((*pic->P18map.PIE1) & 0x80)&&((*pic->P18map.PIR1) & 0x80)&&(!((*pic->P18map.IPR1) & 0x80))) return 2;
       //CMIE CMIF
       //if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&(!((*pic->P18map.IPR1) & 0x40))) return 2;
       //ADIE ADIF 
       if (((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&(!((*pic->P18map.IPR1) & 0x40))) return 2;
       //RCIE RCIF
       if (((*pic->P18map.PIE1) & 0x20)&&((*pic->P18map.PIR1) & 0x20)&&(!((*pic->P18map.IPR1) & 0x20))) return 2;
       //TXIE TXIF
       if (((*pic->P18map.PIE1) & 0x10)&&((*pic->P18map.PIR1) & 0x10)&&(!((*pic->P18map.IPR1) & 0x10))) return 2;
       //SSPIE
       if (((*pic->P18map.PIE1) & 0x08)&&((*pic->P18map.PIR1) & 0x08)&&(!((*pic->P18map.IPR1) & 0x08))) return 2;
       //CCP1IE CCP1IF
       if (((*pic->P18map.PIE1) & 0x04)&&((*pic->P18map.PIR1) & 0x04)&&(!((*pic->P18map.IPR1) & 0x04))) return 2;
       //TMR2IE TMR2IF
       if (((*pic->P18map.PIE1) & 0x02)&&((*pic->P18map.PIR1) & 0x02)&&(!((*pic->P18map.IPR1) & 0x02))) return 2;
       //TMR1IE TMR1IF
       if (((*pic->P18map.PIE1) & 0x01)&&((*pic->P18map.PIR1) & 0x01)&&(!((*pic->P18map.IPR1) & 0x01))) return 2;
       //CCP2IE CCP2IF      
       if (((*pic->P18map.PIE2) & 0x01)&&((*pic->P18map.PIR2) & 0x01)&&(!((*pic->P18map.IPR2) & 0x01))) return 2;
       //TMR3IE TMR3IF
       if (((*pic->P18map.PIE2) & 0x02)&&((*pic->P18map.PIR2) & 0x02)&&(!((*pic->P18map.IPR2) & 0x02))) return 2;
       //INT1E INT1F
       if (((*pic->P18map.INTCON3) & 0x08)&&((*pic->P18map.INTCON3) & 0x01)&&(!((*pic->P18map.INTCON3) & 0x40))) return 2;
       //INT2E INT2F
       if (((*pic->P18map.INTCON3) & 0x10)&&((*pic->P18map.INTCON3) & 0x02)&&(!((*pic->P18map.INTCON3) & 0x80))) return 2;
      }
    }
  }
 else //legacy
  {
   //GIE
   if ((*pic->P18map.INTCON) & 0x80)
    {
     //T0IE  T0IF
     if (((*pic->P18map.INTCON)&0x20)&&((*pic->P18map.INTCON)&0x04)) return 1;
     //INTE INTF
     if (((*pic->P18map.INTCON)&0x10)&&((*pic->P18map.INTCON)&0x02)) return 1;
     //RBIE
     if (((*pic->P18map.INTCON)&0x08)&&((*pic->P18map.INTCON)&0x01)) return 1;
     //INT1E INT1F
     if (((*pic->P18map.INTCON3) & 0x08)&&((*pic->P18map.INTCON3) & 0x01)) return 1;
     //INT2E INT2F
     if (((*pic->P18map.INTCON3) & 0x10)&&((*pic->P18map.INTCON3) & 0x02)) return 1;
     //PEIE	
     if (((*pic->P18map.INTCON) & 0x40) == 0x40)
      {
       //EEIE
       //if(((*pic->P18map.PIE1) & 0x80)&&((*pic->P18map.PIR1) & 0x80)) return 1;
       //CMIE CMIF
       //if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)) return 1;
       //ADIE ADIF 
       if (((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)) return 1;
       //RCIE RCIF
       if (((*pic->P18map.PIE1) & 0x20)&&((*pic->P18map.PIR1) & 0x20)) return 1;
       //TXIE TXIF
       if (((*pic->P18map.PIE1) & 0x10)&&((*pic->P18map.PIR1) & 0x10)) return 1;
       //SSPIE
       if (((*pic->P18map.PIE1) & 0x08)&&((*pic->P18map.PIR1) & 0x08)) return 1;
       //CCP1IE CCP1IF
       if (((*pic->P18map.PIE1) & 0x04)&&((*pic->P18map.PIR1) & 0x04)) return 1;
       //TMR2IE TMR2IF
       if (((*pic->P18map.PIE1) & 0x02)&&((*pic->P18map.PIR1) & 0x02)) return 1;
       //TMR1IE TMR1IF
       if (((*pic->P18map.PIE1) & 0x01)&&((*pic->P18map.PIR1) & 0x01)) return 1;
       //TMR3IE TMR3IF
       if (((*pic->P18map.PIE2) & 0x02)&&((*pic->P18map.PIR2) & 0x02)) return 1;
       //CCP2IE CCP2IF
       if (((*pic->P18map.PIE2) & 0x01)&&((*pic->P18map.PIR2) & 0x01)) return 1;
      }
    }
  }
 return 0;
}

int
interrupt18_2(void)
{
 //TODO
 return 0;
}