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

extern const int fpw2_[];

void
p18_tmr3_rst(void)
{
 pic->cp3 = 0;
}

void
p18_tmr3(void)
{
 if ((((*pic->P18map.T3CON) & 0x03) == 0x01) || //TMRICS=FOSC/4 TMREN=1
     ((((*pic->P18map.T3CON) & 0x03) == 0x03)&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki - 1].value == 1)))) //TMRICS=t1cki  TMREN=1
  {
   pic->cp3++;

   if (pic->cp3 >= fpw2_[((*pic->P18map.T3CON)&0x30) >> 4])
    {
     (*pic->P18map.TMR3L)++;
     if ((*pic->P18map.TMR3L) == 0)
      {
       if (((*pic->P18map.TMR3H) + 1) == 0x100)(*pic->P18map.PIR2) |= 0x02; //TMR3IF
       (*pic->P18map.TMR3H)++;
      }
     pic->cp3 = 0;
    }

   //CCP - only when TMR3 is ON
   //CCP3 compare modes 
   if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(((*pic->P18map.CCP1CON) & 0x0C) == 0x08)&&((*pic->P18map.T3CON) & 0x40))
    {
     if (((*pic->P18map.TMR3H) == (*pic->P18map.CCPR1H))&&((*pic->P18map.TMR3L) == (*pic->P18map.CCPR1L)))//match !!
      {
       (*pic->P18map.PIR1) |= 0x04; //CCP1IF
       switch ((*pic->P18map.CCP1CON) & 0x03)
        {
        case 0://set output
         if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0] - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[0] - 1)].pord);
         break;
        case 1://clear output
         if (pic->pins[pic->ccp[0] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[0] - 1)].pord));
         break;
        case 2://software interrupt
         break;
        case 3://trigger special event
         (*pic->P18map.TMR3H) = 0;
         (*pic->P18map.TMR3L) = 0;
         break;
        }
      }
    }
   //CCP2 compare modes 
   if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(((*pic->P18map.CCP2CON) & 0x0C) == 0x08)&&((*pic->P18map.T3CON) & 0x48))
    {
     if (((*pic->P18map.TMR3H) == (*pic->P18map.CCPR2H))&&((*pic->P18map.TMR3L) == (*pic->P18map.CCPR2L)))//match !!
      {
       (*pic->P18map.PIR2) |= 0x01; //CCP2IF
       switch ((*pic->P18map.CCP2CON) & 0x03)
        {
        case 0://set output
         if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1] - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[1] - 1)].pord);
         break;
        case 1://clear output
         if (pic->pins[pic->ccp[1] - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1] - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[1] - 1)].pord));
         break;
        case 2://software interrupt
         break;
        case 3://trigger special event
         (*pic->P18map.TMR3H) = 0;
         (*pic->P18map.TMR3L) = 0;
         if (pic->processor == P18F452)
          {
           if ((*pic->P18map.ADCON0) & 0x01)(*pic->P18map.ADCON0) |= 0x04; //if ad on, enable one conversion
          }
         else
          {
           if ((*pic->P18map.ADCON0) & 0x01)(*pic->P18map.ADCON0) |= 0x02; //if ad on, enable one conversion  
          }
         break;
        }
      }
    }
  }

 pic->t1cki_ = pic->pins[pic->t1cki - 1].value;

}
