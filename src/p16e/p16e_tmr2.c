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

void
p16e_tmr2_rst(void)
{
 pic->cp2 = 0;
 pic->cp2_ = 0;
 pic->t2pr = 0;
}

void
p16e_tmr2(void)
{

 if (((*pic->P16Emap.T2CON) & 0x04) == 0x04) //TMR2EN
  {
   pic->cp2++;

   if (((*pic->P16Emap.T2CON)&0x02) == 0x02)
    {
     pic->t2pr = 16;
    }
   else if (((*pic->P16Emap.T2CON)&0x01) == 0x01)
    {
     pic->t2pr = 4;
    }
   else
    {
     pic->t2pr = 1;
    }

   if (pic->cp2 >= pic->t2pr)
    {
     (*pic->P16Emap.TMR2)++;
     if ((*pic->P16Emap.TMR2) == (*pic->P16Emap.PR2))
      {
       (*pic->P16Emap.TMR2) = 0;
       pic->cp2_++;

       if (pic->cp2_ >= ((((*pic->P16Emap.T2CON)&0x78) >> 3) + 1))
        {
         (*pic->P16Emap.PIR1) |= 0x02; //TMR2IF
         pic->cp2_ = 0;
        }

       //PWM

       if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P16Emap.CCP1CON)& 0x0C) == 0x0C)
        {
         (*pic->P16Emap.CCPR1H) = (*pic->P16Emap.CCPR1L);
         if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0] - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[0] - 1)].pord);
        }

       if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P16Emap.CCP2CON)& 0x0C) == 0x0C)
        {
         (*pic->P16Emap.CCPR2H) = (*pic->P16Emap.CCPR2L);
         if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1] - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[1] - 1)].pord);
        }
       /*         
                if((pic->CCPCOUNT >= 3)&&(pic->ccp[2] > 0)&&((*pic->P16Emap.CCP3CON)& 0x0C) == 0x0C)
                {
                  pic->ram[P16E_CCPR3H]=pic->ram[P16E_CCPR3L];
                  if(pic->pins[pic->ccp[2]-1].dir == PD_OUT)
                    pic->ram[pic->pins[(pic->ccp[2]-1)].port]|=0x01<<(pic->pins[(pic->ccp[2]-1)].pord);
                } 
        */
      }
     pic->cp2 = 0;
    }
   //PWM - only if TMR2 is on

   //only use 8 bits ! not 10 bits  
   if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P16Emap.CCP1CON)& 0x0C) == 0x0C)
    {
     if ((*pic->P16Emap.TMR2) >= (*pic->P16Emap.CCPR1H))
      {
       if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
        (*pic->pins[(pic->ccp[0] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[0] - 1)].pord));
      }
    }

   if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P16Emap.CCP2CON)& 0x0C) == 0x0C)
    {
     if ((*pic->P16Emap.TMR2) >= (*pic->P16Emap.CCPR2H))
      {
       if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
        (*pic->pins[(pic->ccp[1] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[1] - 1)].pord));
      }
    }
   /*   
      if((pic->CCPCOUNT >= 3)&&(pic->ccp[2] > 0)&&((*pic->P16Emap.CCP3CON)& 0x0C) == 0x0C)
      {
         if((*pic->P16Emap.TMR2) >=  (*pic->P16Emap.CCP3RH))
         {
           if(pic->pins[pic->ccp[2]-1].dir == PD_OUT)
             pic->ram[pic->pins[(pic->ccp[2]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[2]-1)].pord));
         }
      }	
    */

  }

}
