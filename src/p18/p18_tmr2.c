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

extern const int fpw2[];

void
p18_tmr2_rst(void)
{
 pic->cp2 = 0;
 pic->cp2_ = 0;
 pic->t2pr = 0;
}

void
p18_tmr2(void)
{
 if (((*pic->P18map.T2CON) & 0x04) == 0x04) //TMR2EN
  {
   pic->cp2++;

   if (((*pic->P18map.T2CON)&0x02) == 0x02)
    {
     pic->t2pr = 16;
    }
   else if (((*pic->P18map.T2CON)&0x01) == 0x01)
    {
     pic->t2pr = 4;
    }
   else
    {
     pic->t2pr = 1;
    }

   if (pic->cp2 >= pic->t2pr)
    {
     (*pic->P18map.TMR2)++;
     if ((*pic->P18map.TMR2) == (*pic->P18map.PR2))
      {
       (*pic->P18map.TMR2) = 0;
       pic->cp2_++;

       if (pic->cp2_ >= ((((*pic->P18map.T2CON)&0x78) >> 3) + 1))
        {
         (*pic->P18map.PIR1) |= 0x02; //TMR2IF
         pic->cp2_ = 0;
        }

       //PWM

       if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P18map.CCP1CON)& 0x0C) == 0x0C)
        {
         (*pic->P18map.CCPR1H) = (*pic->P18map.CCPR1L);
         if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0] - 1)].port) = 0x01 << (pic->pins[(pic->ccp[0] - 1)].pord);
        }

       if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P18map.CCP2CON)& 0x0C) == 0x0C)
        {
         (*pic->P18map.CCPR2H) = (*pic->P18map.CCPR2L);
         if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1] - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[1] - 1)].pord);
        }

      }
     pic->cp2 = 0;
    }
   //PWM - only if TMR2 is on

   //only use 8 bits ! not 10 bits  
   if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P18map.CCP1CON)& 0x0C) == 0x0C)
    {
     if ((*pic->P18map.TMR2) >= (*pic->P18map.CCPR1H))
      {
       if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
        (*pic->pins[(pic->ccp[0] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[0] - 1)].pord));
      }
    }

   if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P18map.CCP2CON)& 0x0C) == 0x0C)
    {
     if ((*pic->P18map.TMR2) >= (*pic->P18map.CCPR2H))
      {
       if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
        (*pic->pins[(pic->ccp[1] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[1] - 1)].pord));
      }
    }
  }
}

void
p18_tmr2_2(void)
{
 //TODO TMR2 incomplete
 if ((*pic->P18map.T2CON) & 0x80) //TMR2EN
  {
   pic->cp2++;

   if (pic->cp2 >= fpw2[((*pic->P18map.T2CON)&0x70) >> 4])
    {
     (*pic->P18map.T2TMR)++;
     if ((*pic->P18map.T2TMR) == (*pic->P18map.T2PR))
      {
       (*pic->P18map.T2TMR) = 0;
       pic->cp2_++;

       if (pic->cp2_ >= ((((*pic->P18map.T2CON)&0x0F)) + 1))
        {
         (*pic->P18map.PIR4) |= 0x02; //TMR2IF
         pic->cp2_ = 0;
        }

       //PWM

       if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P18map.CCP1CON)& 0x0C) == 0x0C)
        {
         (*pic->P18map.CCPR1H) = (*pic->P18map.CCPR1L);
         if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0] - 1)].port) = 0x01 << (pic->pins[(pic->ccp[0] - 1)].pord);
        }

       if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P18map.CCP2CON)& 0x0C) == 0x0C)
        {
         (*pic->P18map.CCPR2H) = (*pic->P18map.CCPR2L);
         if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1] - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[1] - 1)].pord);
        }

      }
     pic->cp2 = 0;
    }
  
   //PWM - only if TMR2 is on
   //only use 8 bits ! not 10 bits  
   if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P18map.CCP1CON)& 0x0C) == 0x0C)
    {
     if ((*pic->P18map.TMR2) >= (*pic->P18map.CCPR1H))
      {
       if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
        (*pic->pins[(pic->ccp[0] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[0] - 1)].pord));
      }
    }

   if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P18map.CCP2CON)& 0x0C) == 0x0C)
    {
     if ((*pic->P18map.TMR2) >= (*pic->P18map.CCPR2H))
      {
       if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
        (*pic->pins[(pic->ccp[1] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[1] - 1)].pord));
      }
    }
  
  }
 
}
